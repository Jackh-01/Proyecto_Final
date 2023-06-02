#include <cstdlib>
#include <ctime>
#include <QVector>
#include <QTimer>
#include "mapa.h"
#include "qgraphicsitem.h"
#include "Personaje.h"
#include "enemigos.h"

Mapa::Mapa()
{
    int filas = 15, columnas = 15;
    for (int i = 0; i <= 3 ; i++)
    {
        Posicion_X_Ememigo[i]=0;
        Posicion_Y_Ememigo[i]=0;
    }
    MovimientoEnemigos = new QTimer(this);
    connect(MovimientoEnemigos, &QTimer::timeout, this, &Mapa::MoverEnemigos);
    srand(time(NULL));
    GenerarMapa();
    GenerarEnemigosySalida();
    MovimientoEnemigos->start(100);
    P_Ppal = new Personaje();
    addItem(P_Ppal);
    P_Ppal->setPos(48,0);
    P_Ppal->select_sprite(3,0);
    boom = false;
}

Mapa::~Mapa()
{
    for (int i = 0; i < filas; i++)
    {
        delete[] Matriz[i];
    }
    delete[] Matriz;
}

void Mapa::GenerarMapa()
{
    Matriz = new int*[bloques_y_mapa];
    for (int i = 0;i<bloques_y_mapa;i++)
    {
        Matriz[i] = new int[bloques_x_mapa];
    }
    int y;
    for (int i = 0;i<bloques_y_mapa;i++)
    {
        for (int j = 0;j<bloques_x_mapa;j++)
        {

            if (i==0 || j== 0 || i==bloques_y_mapa-1 || j== bloques_x_mapa-1 || (i%2==0 && j%2 ==0))
            {
                bl_mapa[i][j] = new Bloques(0);
                Matriz[i][j] = 0;
            }
            else if ( (i==1 && (j==1 || j==2)) || ((i==2 && j==1)) || (i==bloques_y_mapa-2 && (j==bloques_x_mapa-2 || j==bloques_x_mapa-3)) || (i==bloques_y_mapa-3 && j==bloques_x_mapa-2))
            {
                bl_mapa[i][j] = new Bloques(1);
                Matriz[i][j] = 1;
            }
            else
            {
                y = rand() % 2 + 1;
                if (y == 1)
                {
                    bl_mapa[i][j] = new Bloques(1);
                    Matriz[i][j] = 1;
                }
                else
                {
                    bl_mapa[i][j] = new Bloques(2);
                    Matriz[i][j] = 2;
                }

            }
            addItem(bl_mapa[i][j]);
            bl_mapa[i][j]->setPos(j*bloques_ancho,i*bloques_alto);
        }
    }
}

void Mapa::Mover_Personaje(QKeyEvent *event)
{
    QPointF posicion = P_Ppal->pos();
    int FuturaPosicionX, FuturaPosicionY, PosicionX, PosicionY;
    PosicionX = posicion.x()+16;
    PosicionY = posicion.y()+47;
    int bloqueX = PosicionX / bloques_ancho;
    int bloqueY = PosicionY / bloques_alto;


    if(event->key()==Qt::Key_D)
    {
        FuturaPosicionX = (PosicionX+16) / bloques_ancho;
        if (FuturaPosicionX==bloqueX)
        {
            P_Ppal->tecla_pressed(event,16,0);
        }
        else
        {
            if (Matriz[bloqueY][bloqueX+1] == 0 || Matriz[bloqueY][bloqueX+1] == 2 || Matriz[bloqueY][bloqueX+1] == 3)
            {
                P_Ppal->tecla_pressed(event,0,0);
            }
            else
            {

                P_Ppal->tecla_pressed(event,16,0);
            }
        }

    }
    else if(event->key()==Qt::Key_A)
    {
        FuturaPosicionX = (PosicionX-16)/ bloques_ancho;
        if (FuturaPosicionX==bloqueX)
        {
            P_Ppal->tecla_pressed(event,16,0);
        }
        else
        {
            if (Matriz[bloqueY][bloqueX-1] == 0 || Matriz[bloqueY][bloqueX-1] == 2 || Matriz[bloqueY][bloqueX-1] == 3)
            {
                P_Ppal->tecla_pressed(event,0,0);
            }
            else
            {
                P_Ppal->tecla_pressed(event,16,0);
            }
        }
    }
    else if(event->key()==Qt::Key_S)
    {
        FuturaPosicionY = (PosicionY+16) / bloques_alto;
        if (FuturaPosicionY==bloqueY)
        {
            P_Ppal->tecla_pressed(event,0,16);
        }
        else
        {
            if (Matriz[bloqueY+1][bloqueX] == 0 || Matriz[bloqueY+1][bloqueX] == 2 || Matriz[bloqueY+1][bloqueX] == 3)
            {
                P_Ppal->tecla_pressed(event,0,0);
            }
            else
            {
                P_Ppal->tecla_pressed(event,0,16);
            }
        }
    }
    else if(event->key()==Qt::Key_W)
    {
        FuturaPosicionY = (PosicionY-16) / bloques_alto;
        if (FuturaPosicionY==bloqueY)
        {
            P_Ppal->tecla_pressed(event,0,16);
        }
        else
        {
            if (Matriz[bloqueY-1][bloqueX] == 0 || Matriz[bloqueY-1][bloqueX] == 2 || Matriz[bloqueY-1][bloqueX] == 3)
            {
                P_Ppal->tecla_pressed(event,0,0);
            }
            else
            {
                P_Ppal->tecla_pressed(event,0,16);
            }
        }
    }
}

void Mapa::GenerarEnemigosySalida()
{
    for (int i =0; i<4;i++)
    {
        CoordenadaX = (bloques_x_mapa/2) + rand() % (bloques_x_mapa + 1 - (bloques_x_mapa/2));
        CoordenadaY = 1 + rand() % (bloques_y_mapa - 1);
        while (Matriz[CoordenadaY][CoordenadaX]!=1 || (CoordenadaX == Posicion_X_Ememigo[0] && CoordenadaY == Posicion_Y_Ememigo[0] ) || (CoordenadaX == Posicion_X_Ememigo[1] && CoordenadaY == Posicion_Y_Ememigo[1] )|| (CoordenadaX == Posicion_X_Ememigo[2] && CoordenadaY == Posicion_Y_Ememigo[2] )|| (CoordenadaX == Posicion_X_Ememigo[3] && CoordenadaY == Posicion_Y_Ememigo[3] ))
        {
            CoordenadaX = (bloques_x_mapa/2) + rand() % (bloques_x_mapa + 1 - (bloques_x_mapa/2));
            CoordenadaY = 1 + rand() % (bloques_y_mapa - 1);
        }
        Posicion_X_Ememigo[i]=CoordenadaX;
        Posicion_Y_Ememigo[i]=CoordenadaY;
        Enemy[i]= new Enemigos(i);
        addItem(Enemy[i]);
        Enemy[i]->setPos(CoordenadaX*bloques_ancho,(CoordenadaY*bloques_alto)-45);
        Enemy[i]->select_sprite(0,0);

    }
    CoordenadaX = (bloques_x_mapa-10) + rand() % (bloques_x_mapa - (bloques_x_mapa-10));
    CoordenadaY = (bloques_y_mapa-10) + rand() % (bloques_y_mapa - (bloques_y_mapa-10));
    while (Matriz[CoordenadaY][CoordenadaX]!=2)
    {
        CoordenadaX = (bloques_x_mapa-10) + rand() % (bloques_x_mapa - (bloques_x_mapa-10));
        CoordenadaY = (bloques_y_mapa-10) + rand() % (bloques_y_mapa - (bloques_y_mapa-10));
    }
    Matriz[CoordenadaY][CoordenadaX]=3;
}

void Mapa::MoverEnemigos()
{
    Enemy[0]->GenerarMovimiento(Matriz,Enemy[0]->x()+16,Enemy[0]->y()+48);
    Enemy[1]->GenerarMovimiento(Matriz,Enemy[1]->x()+16,Enemy[1]->y()+48);
    Enemy[2]->GenerarMovimiento(Matriz,Enemy[2]->x()+16,Enemy[2]->y()+48);
    Enemy[3]->GenerarMovimiento(Matriz,Enemy[3]->x()+16,Enemy[3]->y()+48);
}


//int laberintoDatos[18][30] = {
//    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
//    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
//    {0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
//    {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
//    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
//    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
//    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
//    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
//    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
//    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
//    {0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
//    {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
//    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
//    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
//    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0},
//    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
//    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
