#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include "sprite.h"

class Enemigos: public sprite
{
public:
    Enemigos(int numero);
    void GenerarSemilla(int posicionX, int posicionY, int velocidad, int aceleracion);
    void ModificarSemilla (int nuevaSemilla);
    void GenerarMovimiento(int** map, int posicionX, int posicionY, int velocidad,int ace);
    void PerseguirPersonaje(int posicionX_Personaje, int posicionY_Personaje);

signals:
    void EnemigoMurio(int NumeroEnemigo);

private:
    int TipoEnemigo, posicionenemigo, semilla, var;
    int bloqueX,bloqueY,FuturaPosicionX, FuturaPosicionY,FuturoBloqueY_1,FuturoBloqueX_1, aceleracion, tiempo;

};

#endif // ENEMIGOS_H


