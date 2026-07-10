#ifndef USUARIOAUTENTICAVEL_H
#define USUARIOAUTENTICAVEL_H

#include <string>

// Classe base concreta: armazena dados não sensíveis
class Usuario {
protected:
    int         id;
    std::string username;

public:
    Usuario(int id, const std::string& username);
    virtual ~Usuario() = default;

    int         getId()       const;
    std::string getUsername() const;
};

// Classe abstrata: herda de Usuario e impõe contrato de autenticação
// Não pode ser instanciada diretamente por conter método virtual puro
class UsuarioAutenticavel : public Usuario {
public:
    UsuarioAutenticavel(int id, const std::string& username);
    virtual ~UsuarioAutenticavel() = default;

    // Método virtual puro — cada perfil implementa sua própria lógica de login
    virtual bool autenticar(std::string senha) = 0;
};

#endif