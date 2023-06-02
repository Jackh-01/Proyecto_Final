#include "bloques.h"

Bloques::Bloques(int TipoBloque)
{
    ExplotarBloque = new QTimer(this);
    posicion = 0;
    connect(ExplotarBloque, &QTimer::timeout, this, &Bloques::iniciarExplosion);
    set_imagen(16,16,48,48,9,2,":/Sprite/NES - Bomberman - General Sprites.png",48,48);
    if (TipoBloque==0)
    {
        select_sprite(0,0);
    }
    else if (TipoBloque==1)
    {
        select_sprite(0,1);
    }
    else
    {
        select_sprite(1,0);
    }
}

Bloques::~Bloques()
{
    delete ExplotarBloque;
}

void Bloques::Iniciar(int tipoBloque)
{
    ExplotarBloque->start(100);
    tipoB = tipoBloque;
}

void Bloques::Finalizar()
{
    ExplotarBloque->stop();
}

void Bloques::iniciarExplosion()
{
    posicion +=1;
    if (posicion>6)
    {
        if (tipoB==2)
        {
            select_sprite(0,1);
            Finalizar();
        }
        else if (tipoB==3)
        {
            select_sprite(8,0);
            Finalizar();
        }

    }
    else
    {
        select_sprite(1+posicion,0);
    }
}
