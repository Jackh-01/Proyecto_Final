
#ifndef COMIDA_H
#define COMIDA_H


#include "sprite.h"

class Comida: public sprite
{
public:
    Comida();
    void Movimiento();

private:
    QTimer* MoverComida;
};

#endif // COMIDA_H
