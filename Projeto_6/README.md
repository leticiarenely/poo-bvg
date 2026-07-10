# Projeto 6 — SecureBank Pro: Módulo IAM (Autenticação e Auditoria)

Implementação do core de **Gestão de Identidades e Acessos** utilizando Classes Abstratas, Interface, `enum class` e Classe Interna (Nested Class) em C++.

---

## Estrutura do Projeto

```
Projeto_6/
├── docs/
│   └── Arquitetura_IAM_UML.png
├── src/
│   ├── interfaces/
│   │   └── Relatorio.h
│   ├── base/
│   │   └── UsuarioAutenticavel.h / .cpp
│   ├── models/
│   │   ├── UsuarioAdmin.h / .cpp
│   │   ├── UsuarioAuditor.h / .cpp
│   │   └── UsuarioOperador.h / .cpp
│   └── main.cpp
└── README.md
```

---

## Como Compilar

```bash
cd src/
g++ -std=c++17 -Wall -Wextra -o ../securebank \
    base/UsuarioAutenticavel.cpp \
    models/UsuarioAdmin.cpp \
    models/UsuarioAuditor.cpp \
    models/UsuarioOperador.cpp \
    main.cpp
```

### Executar

```bash
cd Projeto_6/
./securebank
```

---

## Conceitos Implementados

### 1. Hierarquia Abstrata (`Usuario` → `UsuarioAutenticavel`)
- `Usuario` é concreta: armazena `id` e `username` (dados não sensíveis).
- `UsuarioAutenticavel` herda de `Usuario` e declara `virtual bool autenticar(std::string) = 0`, tornando-se abstrata. Nenhuma instância direta é possível.

### 2. Interface (`Relatorio`)
- Classe puramente abstrata: sem atributos, sem implementações. Apenas o contrato `virtual void gerarRelatorio() const = 0`.
- As três classes concretas assinam a interface via herança múltipla: `class UsuarioAdmin : public UsuarioAutenticavel, public Relatorio`.

### 3. `enum class TipoUsuario`
- Definida em `UsuarioAdmin.h` e reutilizada pelas demais classes.
- Valores `ADMIN`, `AUDITOR`, `OPERADOR` permitem triagem rápida por perfil sem risco de colisão de nomes (escopo fechado do `enum class`).

### 4. Classe Interna `HistoricoAcessos` (dentro de `UsuarioOperador`)
- Declarada como `private` dentro de `UsuarioOperador`: invisível para o código externo.
- Armazena `struct Registro { recursoAcessado, dataHora, statusCodigo }`.
- Implementada em `UsuarioOperador.cpp` com resolução de escopo dupla:
  ```cpp
  void UsuarioOperador::HistoricoAcessos::adicionarRegistro(...) { ... }
  void UsuarioOperador::HistoricoAcessos::exibir() const { ... }
  ```
- Os dados só são expostos via `gerarRelatorio()`, garantindo encapsulamento total.

### 5. Polimorfismo via `std::vector<Relatorio*>`
- O `main.cpp` armazena ponteiros da interface `Relatorio*` e emite relatórios em cascata sem conhecer os tipos concretos.
- Objetos alocados na stack: sem `new`/`delete` necessário neste contexto.