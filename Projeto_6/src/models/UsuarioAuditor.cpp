#include "UsuarioAuditor.h"
#include <iostream>

UsuarioAuditor::UsuarioAuditor(int id, const std::string& username, const std::string& senha,
                               const std::string& chavePublica, const std::string& escopo)
    : UsuarioAutenticavel(id, username),
      senhaHash(senha),
      chavePublica(chavePublica),
      escopoVarredura(escopo) {}

bool UsuarioAuditor::autenticar(std::string senha) {
    return senha == senhaHash;
}

void UsuarioAuditor::gerarRelatorio() const {
    std::cout << " === RELATÓRIO - AUDITOR [Anti-Fraude] ===\n";
    std::cout << "  ID              : " << id             << "\n";
    std::cout << "  Username        : " << username       << "\n";
    std::cout << "  Perfil          : AUDITOR\n";
    std::cout << "  Chave Pública   : " << chavePublica   << "\n";
    std::cout << "  Escopo Varredura: " << escopoVarredura << "\n";
    std::cout << "──────────────────────────────────────────\n";
}