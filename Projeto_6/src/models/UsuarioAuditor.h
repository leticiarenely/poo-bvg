#ifndef USUARIOAUDITOR_H
#define USUARIOAUDITOR_H

#include "../base/UsuarioAutenticavel.h"
#include "../interfaces/Relatorio.h"
#include "UsuarioAdmin.h"  // TipoUsuario definido aqui
#include <string>

class UsuarioAuditor : public UsuarioAutenticavel, public Relatorio {
private:
    std::string senhaHash;
    std::string chavePublica;    // Chave criptográfica pública
    std::string escopoVarredura;

public:
    UsuarioAuditor(int id, const std::string& username, const std::string& senha,
                   const std::string& chavePublica, const std::string& escopo);

    bool autenticar(std::string senha) override;
    void gerarRelatorio() const override;

    TipoUsuario getTipo() const { return TipoUsuario::AUDITOR; }
};

#endif