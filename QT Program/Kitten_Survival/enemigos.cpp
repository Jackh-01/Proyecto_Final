#include "enemigos.h"
#include "bloques.h"
#include <cstdlib>
#include <ctime>

Enemigos::Enemigos(int numero)
{
    srand(time(NULL));
    set_imagen(32,32,0,0,4,4,":/Sprite/PC Computer - Stardew Valley - Dog Brown.png",48,48);
    NumeroEnemigo = numero;
    posicionenemigo = 0;
    semilla = rand() % 4;
    var = 0;
    aceleracion = 0;
    tiempo = 0;
}



void Enemigos::GenerarSemilla(int posicionX, int posicionY,int velocidad, int aceleracion)
{
    bloqueX = posicionX / bloques_ancho;
    bloqueY = posicionY / bloques_alto;
    if (semilla == 0)
    {
        FuturoBloqueX_1 = bloqueX;
        FuturoBloqueY_1 = bloqueY-1;
        FuturaPosicionX = posicionX / bloques_ancho;
        FuturaPosicionY = (posicionY-(velocidad+(aceleracion*tiempo))) / bloques_alto;
    }
    else if (semilla == 1)
    {
        FuturoBloqueX_1 = bloqueX+1;
        FuturoBloqueY_1 = bloqueY;
        FuturaPosicionX = (posicionX+(velocidad+(aceleracion*tiempo))) / bloques_ancho;
        FuturaPosicionY = posicionY / bloques_alto;
    }
    else if (semilla == 2)
    {
        FuturoBloqueX_1 = bloqueX;
        FuturoBloqueY_1 = bloqueY+1;
        FuturaPosicionX = posicionX / bloques_ancho;
        FuturaPosicionY = (posicionY+(velocidad+(aceleracion*tiempo))) / bloques_alto;
    }
    else if (semilla == 3)
    {
        FuturoBloqueX_1 = bloqueX-1;
        FuturoBloqueY_1 = bloqueY;
        FuturaPosicionX = (posicionX-(velocidad+(aceleracion*tiempo))) / bloques_ancho;
        FuturaPosicionY = posicionY / bloques_alto;
    }
}

void Enemigos::GenerarMovimiento(int** map, int posicionX, int posicionY, int velocidad, int ace)
{
    GenerarSemilla( posicionX, posicionY, velocidad, ace);
    if (map[FuturoBloqueY_1][FuturoBloqueX_1]==1 || map[FuturaPosicionY][FuturaPosicionX]==1)
    {
        // Velocidad = 16
        if(semilla == 0)
        {
            setPos(x(),y()-(velocidad+(ace*tiempo)));
            select_sprite(var,2);
            var++;
            tiempo++;
            if(var>3) var = 0;
        }
        else if(semilla == 1)
        {
            setPos(x()+(velocidad+(ace*tiempo)),y());
            select_sprite(var,1);
            var++;
            tiempo++;
            if(var>3) var = 0;
        }
        else if(semilla == 2)
        {
            setPos(x(),y()+(velocidad+(ace*tiempo)));
            select_sprite(var,0);
            var++;
            tiempo++;
            if(var>3) var = 0;
        }
        else if(semilla == 3)
        {
            setPos(x()-(velocidad+(ace*tiempo)),y());
            select_sprite(var,3);
            var++;
            tiempo++;
            if(var>3) var = 0;
        }
    }
    else
    {
        semilla = rand() % 4;
        tiempo = 0;
    }
}

void Enemigos::PerseguirPersonaje(int posicionX_Personaje, int posicionY_Personaje)
{
    int Pos_x, Pos_y, Bl_x_enemigo,Bl_y_enemigo, Bl_x_aliado, Bl_y_aliado ;
    Pos_x = x();
    Pos_y = y() + 45;
    Bl_x_enemigo = Pos_x / bloques_ancho;
    Bl_y_enemigo = Pos_y / bloques_alto;
    Bl_x_aliado = posicionX_Personaje / bloques_ancho;
    Bl_y_aliado = posicionY_Personaje / bloques_alto;
    while (!(Bl_x_enemigo == Bl_x_aliado && Bl_y_enemigo == Bl_y_aliado))
    {
        if (Bl_x_enemigo == Bl_x_aliado)
        {
            if (Bl_y_enemigo>Bl_y_aliado)
            {
                setPos(x(),y()-16);
                select_sprite(var,2);
                var++;
                if(var>3) var = 0;
            }
            else if (Bl_y_enemigo<Bl_y_aliado)
            {
                setPos(x(),y()+16);
                select_sprite(var,0);
                var++;
                if(var>3) var = 0;
            }
        }
        else if (Bl_y_enemigo == Bl_y_aliado)
        {
            if (Bl_x_enemigo>Bl_x_aliado)
            {
                setPos(x()-16,y());
                select_sprite(var,3);
                var++;
                if(var>3) var = 0;
            }
            else if (Bl_x_enemigo<Bl_x_aliado)
            {
                setPos(x()+16,y());
                select_sprite(var,1);
                var++;
                if(var>3) var = 0;
            }
        }
    }
}




