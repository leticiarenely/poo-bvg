#include "UsuarioOperador.h"
#include <iostream>
#include <iomanip>

// Implementação da Classe Interna — escopo duplo obrigatório
// UsuarioOperador::HistoricoAcessos::método()

void UsuarioOperador::HistoricoAcessos::adicionarRegistro(
        const std::string& recurso,
        const std::string& dataHora,
        int status) {
    registros.push_back({recurso, dataHora, status});
}

void UsuarioOperador::HistoricoAcessos::exibir() const {
    if (registros.empty()) {
        std::cout << "    (nenhum acesso registrado)\n";
        return;
    }
    std::cout << "  " << std::left
              << std::setw(28) << "Recurso"
              << std::setw(22) << "Data/Hora"
              << "Status\n";
    std::cout << "  " << std::string(56, '-') << "\n";
    for (const auto& r : registros) {
        std::cout << "  " << std::left
                  << std::setw(28) << r.recursoAcessado
                  << std::setw(22) << r.dataHora
                  << r.statusCodigo << "\n";
    }
}

// Implementação da Classe Externa
UsuarioOperador::UsuarioOperador(int id, const std::string& username, const std::string& senha)
    : UsuarioAutenticavel(id, username), senhaHash(senha) {}

bool UsuarioOperador::autenticar(std::string senha) {
    return senha == senhaHash;
}

void UsuarioOperador::registrarAcesso(const std::string& recurso,
                                      const std::string& dataHora,
                                      int status) {
    historico.adicionarRegistro(recurso, dataHora, status);
}

void UsuarioOperador::gerarRelatorio() const {
    std::cout << " === RELATÓRIO - OPERADOR [Caixa/Retaguarda] ===\n";
    std::cout << "  ID       : " << id       << "\n";
    std::cout << "  Username : " << username << "\n";
    std::cout << "  Perfil   : OPERADOR\n";
    std::cout << "  Histórico de Acessos (HistoricoAcessos):\n";
    historico.exibir();
    std::cout << "──────────────────────────────────────────\n";
}