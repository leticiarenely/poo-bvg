#include "UsuarioAutenticavel.h"

// Usuario 
Usuario::Usuario(int id, const std::string& username)
    : id(id), username(username) {}

int         Usuario::getId()       const{return id;}
std::string Usuario::getUsername() const{return username;}

// UsuarioAutenticavel 
UsuarioAutenticavel::UsuarioAutenticavel(int id, const std::string& username)
    : Usuario(id, username) {}