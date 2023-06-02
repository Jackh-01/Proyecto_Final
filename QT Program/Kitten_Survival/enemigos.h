#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include "sprite.h"

class Enemigos: public sprite
{
public:
    Enemigos(int numero);
    ~Enemigos();
    void Iniciar();
    void Finalizar();
    void GenerarSemilla( int posicionX, int posicionY);
    void GenerarMovimiento(int** map, int posicionX, int posicionY);


private slots:
    void iniciaMuerte();

signals:
    void EnemigoMurio(int NumeroEnemigo);

private:
    int NumeroEnemigo, posicionenemigo, semilla, var;
    QTimer* IniciarMuerte;
    int bloqueX,bloqueY,FuturaPosicionX, FuturaPosicionY, FuturoBloqueX_1, FuturoBloqueY_1,FuturoBloqueX_2, FuturoBloqueY_2;
};

#endif // ENEMIGOS_H


