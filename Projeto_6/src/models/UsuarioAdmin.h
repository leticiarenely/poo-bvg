#ifndef USUARIOADMIN_H
#define USUARIOADMIN_H

#include "../base/UsuarioAutenticavel.h"
#include "../interfaces/Relatorio.h"
#include <string>
#include <vector>

// Enum class de escopo: define os perfis do sistema IAM
// Declarado aqui e reutilizado pelas demais classes
enum class TipoUsuario {
    ADMIN,
    AUDITOR,
    OPERADOR
};

class UsuarioAdmin : public UsuarioAutenticavel, public Relatorio {
private:
    std::string           senhaHash;        // Senha (simulada como hash)
    std::vector<std::string> logsModificacao; // Histórico de ações do Admin

public:
    UsuarioAdmin(int id, const std::string& username, const std::string& senha);

    bool autenticar(std::string senha) override;
    void gerarRelatorio() const override;

    void registrarModificacao(const std::string& log);

    TipoUsuario getTipo() const { return TipoUsuario::ADMIN; }
};

#endif