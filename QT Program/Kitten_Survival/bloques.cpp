#include "bloques.h"

Bloques::Bloques(int TipoBloque)
{
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

