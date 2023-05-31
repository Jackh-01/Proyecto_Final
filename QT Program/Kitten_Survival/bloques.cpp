
#include "bloques.h"

Bloques::Bloques(int TipoBloque)
{
    if (TipoBloque==0)
    {
        set_imagen(2285,2346,0,2397,1,1,":/Sprite/26346.jpg");
        select_sprite(0,0);
    }
    else if (TipoBloque==1)
    {
        set_imagen(1200,1200,0,0,1,1,":/Sprite/425.jpg");
        select_sprite(0,0);
    }
}

