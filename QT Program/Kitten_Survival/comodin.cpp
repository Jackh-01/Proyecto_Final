
#include "comodin.h"
#include <cmath>

Comodin::Comodin(int numero)
{
    set_imagen(64,64,0,0,9,6,":/Sprite/861565115.png",64,64);
    MoverComodin = new QTimer(this);
    connect(MoverComodin, &QTimer::timeout, this, &Comodin::MovimientoCircular);
    MoverComodin->start(200);
    Velocidad_Angular = 1;
    tiempo = 0;
    radio = numero;
}

void Comodin::MovimientoCircular()
{
    static int var = 0;
    setPos(x()+(radio*cos(Velocidad_Angular*tiempo)),y()+(radio*sin(Velocidad_Angular*tiempo)));
    tiempo++;
    select_sprite(var,0);
    var++;
    if(var>3) var = 0;

}

