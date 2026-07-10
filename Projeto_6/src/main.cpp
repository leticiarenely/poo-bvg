#include <iostream>
#include <vector>
#include <string>
#include "interfaces/Relatorio.h"
#include "models/UsuarioAdmin.h"
#include "models/UsuarioAuditor.h"
#include "models/UsuarioOperador.h"

// Utilitário: exibe resultado de tentativa de login
void tentarLogin(UsuarioAutenticavel& usuario, const std::string& senha) {
    bool ok = usuario.autenticar(senha);
    std::cout << "  Login [" << usuario.getUsername() << "] "
              << "senha=\"" << senha << "\" → "
              << (ok ? "✓ AUTENTICADO" : "✗ NEGADO") << "\n";
}

int main() {
    std::cout << "  === SecureBank Pro — Módulo IAM   ===\n";

    //Instâncias concretas
    UsuarioAdmin    admin(1, "carlos.ti",    "Admin@2025");
    UsuarioAuditor  auditor(2, "ana.fraude",  "Audit#9988",
                            "PUB-RSA-4096-0xF3A7C2", "Transações > R$50.000");
    UsuarioOperador operador(3, "joao.caixa", "Op3r@dor!");

    //Registrar algumas ações para popular os relatórios
    admin.registrarModificacao("Atualização de política de senhas (baseline v2)");
    admin.registrarModificacao("Habilitação de MFA para perfil OPERADOR");

    operador.registrarAcesso("sistema/transferencia",  "2025-06-10 09:14:02", 200);
    operador.registrarAcesso("sistema/extrato",        "2025-06-10 09:31:45", 200);
    operador.registrarAcesso("sistema/admin-panel",    "2025-06-10 09:45:00", 403);

    //Simulação de login (senhas corretas e incorretas) 
    std::cout << "\n--- Simulação de Autenticação ---\n";
    tentarLogin(admin,    "Admin@2025");   // correto
    tentarLogin(admin,    "senha123");     // errado
    tentarLogin(auditor,  "Audit#9988");   // correto
    tentarLogin(operador, "errada");       // errado
    tentarLogin(operador, "Op3r@dor!");    // correto

    //Vetor de interface Relatorio (polimorfismo dinâmico) 
    //O vetor não sabe nada sobre Admin, Auditor ou Operador 
    //só conhece o contrato gerarRelatorio()
    std::vector<Relatorio*> relatorios;
    relatorios.push_back(&admin);
    relatorios.push_back(&auditor);
    relatorios.push_back(&operador);

    std::cout << "\n-- Emissão em Cascata de Relatórios --";
    for (Relatorio* r : relatorios) {
        r->gerarRelatorio();
    }

    // Nenhum delete necessário: objetos na stack, sem alocação dinâmica
    std::cout << "\n===== Sessão IAM encerrada com sucesso =====\n";
    return 0;
}