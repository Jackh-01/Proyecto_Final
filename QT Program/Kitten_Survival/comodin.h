
#ifndef COMODIN_H
#define COMODIN_H

#include "sprite.h"

class Comodin: public sprite
{
public:
    Comodin(int numero);
    void MovimientoCircular ();

private:
    QTimer* MoverComodin;
    int Velocidad_Angular,tiempo,radio;
};

#endif // COMODIN_H
