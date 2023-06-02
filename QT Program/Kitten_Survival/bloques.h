#ifndef BLOQUES_H
#define BLOQUES_H

#include "sprite.h"
#include <QString>

#define bloques_ancho 48
#define bloques_alto 48

class Bloques: public sprite
{
public:
    Bloques(int TipoBloque);
    ~Bloques();
    void Iniciar(int tipoBloque);
    void Finalizar();

private slots:
    void iniciarExplosion();

private:
    QTimer* ExplotarBloque;
    int posicion, tipoB;
};

#endif // BLOQUES_H
