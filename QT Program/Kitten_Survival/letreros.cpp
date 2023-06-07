#include "letreros.h"

Letreros::Letreros(int numero)
{

    if (numero == 1)
    {
        set_imagen(960,533,0,0,2,2,":/Sprite/Finish_1.png",48*4,48*4);
    }
    else if (numero == 2)
    {
        set_imagen(960,533,0,0,2,2,":/Sprite/start_1.png",48*4,48*4);
    }
    else
    {
        set_imagen(960,533,0,0,2,2,":/Sprite/start_2.png",1920,48*17);
    }
    MoverLetrero = new QTimer(this);
    connect(MoverLetrero, &QTimer::timeout, this, &Letreros::Movimiento);
    MoverLetrero->start(150);
    var = 0;
}

void Letreros::Movimiento()
{
    if (var == 0)
    {
        select_sprite(0,0);
        var=1;
    }
    else if (var == 1)
    {
        select_sprite(1,0);
        var=2;
    }
    else if (var == 2)
    {
        select_sprite(0,1);
        var=3;
    }
    else if (var == 3)
    {
        select_sprite(1,1);
        var=0;
    }


}

