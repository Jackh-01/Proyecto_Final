
#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "sprite.h"

class Personaje: public sprite
{
    Q_OBJECT
public:
    Personaje();
    void tecla_pressed(QKeyEvent *event, int VelocidadX, int VelocidadY);
};

#endif // PERSONAJE_H
