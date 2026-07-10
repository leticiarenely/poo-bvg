#ifndef RELATORIO_H
#define RELATORIO_H

// Qualquer classe que assinar esta interface DEVE implementar gerarRelatorio()
class Relatorio {
public:
    virtual void gerarRelatorio() const = 0;
    virtual ~Relatorio() = default;
};
 
#endif