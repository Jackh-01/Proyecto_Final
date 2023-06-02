#include "enemigos.h"
#include "bloques.h"
#include <cstdlib>
#include <ctime>

Enemigos::Enemigos(int numero)
{
    IniciarMuerte = new QTimer(this);
    srand(time(NULL));
    connect(IniciarMuerte, &QTimer::timeout, this, &Enemigos::iniciaMuerte);
    set_imagen(32,32,0,0,4,4,":/Sprite/PC Computer - Stardew Valley - Dog Brown.png",48,48);
    NumeroEnemigo = numero;
    posicionenemigo = 0;
    semilla = rand() % 4;
    var = 0;

}

Enemigos::~Enemigos()
{
    delete IniciarMuerte;
}

void Enemigos::Iniciar()
{
    IniciarMuerte->start(1000);
}

void Enemigos::Finalizar()
{
    IniciarMuerte->stop();
}

void Enemigos::GenerarSemilla(int posicionX, int posicionY)
{
    bloqueX = posicionX / bloques_ancho;
    bloqueY = posicionY / bloques_alto;
    if (semilla == 0)
    {
        FuturoBloqueX_1 = bloqueX;
        FuturoBloqueY_1 = bloqueY-1;
        FuturoBloqueX_2 = bloqueX;
        FuturoBloqueY_2 = bloqueY-2;
        FuturaPosicionX = posicionX / bloques_ancho;
        FuturaPosicionY = (posicionY-16) / bloques_alto;
    }
    else if (semilla == 1)
    {
        FuturoBloqueX_1 = bloqueX+1;
        FuturoBloqueY_1 = bloqueY;
        FuturoBloqueX_2 = bloqueX+2;
        FuturoBloqueY_2 = bloqueY;
        FuturaPosicionX = (posicionX+16) / bloques_ancho;
        FuturaPosicionY = posicionY / bloques_alto;
    }
    else if (semilla == 2)
    {
        FuturoBloqueX_1 = bloqueX;
        FuturoBloqueY_1 = bloqueY+1;
        FuturoBloqueX_2 = bloqueX;
        FuturoBloqueY_2 = bloqueY+2;
        FuturaPosicionX = posicionX / bloques_ancho;
        FuturaPosicionY = (posicionY+16) / bloques_alto;
    }
    else if (semilla == 3)
    {
        FuturoBloqueX_1 = bloqueX-1;
        FuturoBloqueY_1 = bloqueY;
        FuturoBloqueX_2 = bloqueX-2;
        FuturoBloqueY_2 = bloqueY;
        FuturaPosicionX = (posicionX-16) / bloques_ancho;
        FuturaPosicionY = posicionY / bloques_alto;
    }
}

void Enemigos::GenerarMovimiento(int** map,int posicionX, int posicionY)
{
    // generar una dirección de movimiento aleatoria (0 = arriba, 1 = derecha, 2 = abajo, 3 = izquierda)
    GenerarSemilla( posicionX, posicionY);
    //    while (map[FuturoBloqueY_2][FuturoBloqueX_2]==1)
    //    {
    //        GenerarSemilla( posicionX, posicionY);
    //    }
    if (map[FuturoBloqueY_1][FuturoBloqueX_1]==1 || map[FuturaPosicionY][FuturaPosicionX]==1)
    {
        // Velocidad = 16
        if(semilla == 0)
        {
            setPos(x(),y()-16);
            select_sprite(var,2);
            var++;
            if(var>3) var = 0;
        }
        else if(semilla == 1)
        {
            setPos(x()+16,y());
            select_sprite(var,1);
            var++;
            if(var>3) var = 0;
        }
        else if(semilla == 2)
        {
            setPos(x(),y()+16);
            select_sprite(var,0);
            var++;
            if(var>3) var = 0;
        }
        else if(semilla == 3)
        {
            setPos(x()-16,y());
            select_sprite(var,3);
            var++;
            if(var>3) var = 0;
        }
    }
    else
    {
        semilla = rand() % 4;
    }
}

void Enemigos::iniciaMuerte()
{
    posicionenemigo +=1;
    if (posicionenemigo>5)
    {
        Finalizar();
    }
    else
    {
        select_sprite(5+posicionenemigo,0);
    }
}
