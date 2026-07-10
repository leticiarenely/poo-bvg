#include "UsuarioAdmin.h"
#include <iostream>

UsuarioAdmin::UsuarioAdmin(int id, const std::string& username, const std::string& senha)
    : UsuarioAutenticavel(id, username), senhaHash(senha) {}

bool UsuarioAdmin::autenticar(std::string senha) {
    // Simulação: compara diretamente (em produção usaria bcrypt/argon2)
    return senha == senhaHash;
}

void UsuarioAdmin::registrarModificacao(const std::string& log) {
    logsModificacao.push_back(log);
}

void UsuarioAdmin::gerarRelatorio() const {
    std::cout << "=== RELATÓRIO - ADMIN [TI] ===\n";
    std::cout << "  ID       : " << id       << "\n";
    std::cout << "  Username : " << username << "\n";
    std::cout << "  Perfil   : ADMIN\n";
    std::cout << "  Logs de Modificações do Sistema:\n";
    if (logsModificacao.empty()) {
        std::cout << "    (nenhuma modificação registrada)\n";
    } else {
        for (size_t i = 0; i < logsModificacao.size(); ++i) {
            std::cout << "    [" << (i + 1) << "] " << logsModificacao[i] << "\n";
        }
    }
    std::cout << "──────────────────────────────────────────\n";
}