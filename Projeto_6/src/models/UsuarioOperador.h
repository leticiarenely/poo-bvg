#ifndef USUARIOOPERADOR_H
#define USUARIOOPERADOR_H

#include "../base/UsuarioAutenticavel.h"
#include "../interfaces/Relatorio.h"
#include "UsuarioAdmin.h"  // TipoUsuario
#include <string>
#include <vector>

class UsuarioOperador : public UsuarioAutenticavel, public Relatorio {
private:
    std::string senhaHash;

    // Classe Interna (Nested Class) — encapsulamento total
    // Dados de navegação do operador nunca vazam para fora da classe externa
    class HistoricoAcessos {
    private:
        struct Registro {
            std::string recursoAcessado;
            std::string dataHora;
            int         statusCodigo;
        };

        std::vector<Registro> registros;

    public:
        void adicionarRegistro(const std::string& recurso,
                               const std::string& dataHora,
                               int status);

        void exibir() const;
    };

    HistoricoAcessos historico; //Membro privado da classe externa

public:
    UsuarioOperador(int id, const std::string& username, const std::string& senha);

    bool autenticar(std::string senha) override;
    void gerarRelatorio() const override;

    //Permite registrar acessos de fora sem expor a classe interna
    void registrarAcesso(const std::string& recurso,
                         const std::string& dataHora,
                         int status);

    TipoUsuario getTipo() const{return TipoUsuario::OPERADOR;}
};

#endif