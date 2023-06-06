
#include "comida.h"

Comida::Comida()
{
    set_imagen(32,32,0,31,3,1,":/Sprite/FishSheet1.png",48,48);
    MoverComida = new QTimer(this);
    connect(MoverComida, &QTimer::timeout, this, &Comida::Movimiento);
    MoverComida->start(100);
}

void Comida::Movimiento()
{
    static int var =0;
    select_sprite(var,0);
    var++;
    if(var>2) var = 0;
}

