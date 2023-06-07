#ifndef LETREROS_H
#define LETREROS_H


#include "sprite.h"

class Letreros: public sprite
{
public:
    Letreros(int numero);
    void Movimiento();

private:
    QTimer* MoverLetrero;
    int var;
};

#endif // LETREROS_H
