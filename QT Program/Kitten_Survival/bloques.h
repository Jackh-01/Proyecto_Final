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
};

#endif // BLOQUES_H
