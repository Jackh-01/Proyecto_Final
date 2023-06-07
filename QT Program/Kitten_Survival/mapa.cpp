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
    for (int i = 0; i <= 3 ; i++)
    {
        Posicion_X_Ememigo[i]=0;
        Posicion_Y_Ememigo[i]=0;
    }
    GenerarLaberinto_1();
    MovimientoEnemigos = new QTimer(this);
    Posicion_Personajes = new QTimer(this);
    connect(MovimientoEnemigos, &QTimer::timeout, this, &Mapa::MoverEnemigos);
    connect(Posicion_Personajes, &QTimer::timeout, this, &Mapa::Monitorear_Posiciones);
    srand(time(NULL));
    GenerarMapa();
    GenerarEnemigosySalida();    
    P_Ppal = new Personaje();
    addItem(P_Ppal);
    P_Ppal->setPos(48,16);
    P_Ppal->select_sprite(0,0);
    vidas = 0;
    Descubierto = false;
    Premio = new Comida();
    addItem(Premio);
    Premio->setPos(48*29,48*3);
    Premio->select_sprite(0,0);
    Ayudas[0] = new Comodin(48);
    addItem(Ayudas[0]);
    Ayudas[0]->setPos(48*5+15,48*9-15);
    Ayudas[0]->select_sprite(0,0);
    Ayudas[1] = new Comodin(24);
    addItem(Ayudas[1]);
    Ayudas[1]->setPos(48*22+17,48*13+24);
    Ayudas[1]->select_sprite(0,0);
    comer = false;    
    iniciar = false;    
    Letrero3 = new Letreros (3);
    addItem(Letrero3);
    Letrero3->setPos(0,0);
    Letrero3->select_sprite(0,0);
    iniciar = false;
    Letrero1 = new Letreros (1);
    addItem(Letrero1);
    Letrero1->setPos(48*13,48*5+24);
    Letrero1->select_sprite(0,0);

}

Mapa::~Mapa()
{
    for (int i = 0; i < bloques_y_mapa; i++)
    {
        delete[] Matriz[i];
    }
    delete[] Matriz;
}

void Mapa::GenerarLaberinto_1()
{
    Matriz = new int*[bloques_y_mapa];
    for (int i = 0;i<bloques_y_mapa;i++)
    {
        Matriz[i] = new int[bloques_x_mapa];
    }
    int laberintoDatos[17][31]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0},{0,1,0,0,0,1,0,0,0,0,0,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0},{0,1,0,1,1,1,0,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,0},{0,1,0,1,0,0,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0},{0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,1,0,1,0},{0,1,0,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0},{0,1,0,1,1,1,0,1,1,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0},{0,1,0,1,0,0,0,0,0,1,0,1,1,1,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,1,0},{0,1,0,1,0,1,1,1,0,1,0,1,0,0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,0},{0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,0,0,0,1,0,1,0,0,0,0,0,0},{0,1,0,0,0,1,1,1,0,1,1,1,0,0,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,0},{0,1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,1,0},{0,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,0},{0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,0,1,0,1,0},{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
//    int laberintoDatos[17][31]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,0,1,0,0,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,0,0,1,1,1,0,1,0},{0,1,0,1,0,1,1,1,1,1,0,0,1,1,0,1,0,1,0,1,1,0,1,0,0,1,0,1,1,1,0},{0,1,1,1,1,0,0,1,0,1,0,1,1,0,0,1,0,1,1,1,0,0,1,0,0,1,0,1,0,1,0},{0,1,0,0,1,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0},{0,1,1,0,0,1,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1,0,1,0,0,1,0,1,1,1,0},{0,0,1,1,1,1,1,0,1,1,1,0,0,1,0,0,1,0,0,0,1,0,1,0,0,1,0,0,0,1,0},{0,0,0,1,0,0,1,1,1,0,0,0,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,0},{0,1,1,1,0,0,1,0,0,0,1,1,1,1,0,1,0,0,1,0,0,0,1,0,0,1,1,0,0,1,0},{0,1,0,0,0,1,1,1,0,0,1,0,0,0,0,1,0,1,1,0,1,1,1,1,1,0,1,0,1,1,0},{0,1,1,1,0,1,1,1,0,0,1,1,0,1,1,1,0,1,0,0,1,0,0,0,1,0,1,0,0,1,0},{0,0,0,1,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,1,0,1,1,1,0,1,1,0,1,0},{0,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,0,0,1,0,1,0,1,0,0,0,0,1,0,1,0},{0,1,0,0,1,1,1,1,0,1,1,1,1,0,0,1,0,1,1,0,1,0,1,0,1,1,1,1,0,1,0},{0,1,1,0,0,0,0,1,0,0,1,0,1,0,1,1,0,1,0,0,1,0,1,1,1,0,0,0,0,1,0},{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    for (int i = 0; i < bloques_y_mapa; ++i)
    {
        for (int j = 0; j < bloques_x_mapa; ++j)
        {
            Matriz[i][j] = laberintoDatos [i][j];
        }
    }
}

void Mapa::GenerarMapa()
{    
    for (int i = 0;i<bloques_y_mapa;i++)
    {
        for (int j = 0;j<bloques_x_mapa;j++)
        {

            if (Matriz[i][j] == 0)
            {
                bl_mapa[i][j] = new Bloques(0);
                Matriz[i][j] = 0;
            }
            else if (Matriz[i][j] == 1)
            {
                bl_mapa[i][j] = new Bloques(1);
                Matriz[i][j] = 1;
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

    if(event->key()==Qt::Key_Return)
    {
        removeItem(Letrero1);
        MovimientoEnemigos->start(100);
        Posicion_Personajes->start(100);
        iniciar = true;
    }
    if(event->key()==Qt::Key_P)
    {
        if (iniciar == true)
        {
            iniciar = false;
        }
        else if (iniciar == false)
        {
            iniciar = true;
        }

    }
    if (iniciar == true)
    {
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
        else if(event->key()==Qt::Key_Return)
        {
            removeItem(Letrero1);
            removeItem(Letrero3);
            MovimientoEnemigos->start(100);
            Posicion_Personajes->start(100);
            Vidas_gato = new Vidas ();
            addItem(Vidas_gato);
            Vidas_gato->setPos(48*15,48*17);
            Vidas_gato->select_sprite(0,0);
        }
    }

}

void Mapa::GenerarEnemigosySalida()
{
    for (int i =0; i<4;i++)
    {
        CoordenadaX = (bloques_x_mapa/2) + rand() % (bloques_x_mapa + 1 - (bloques_x_mapa/2));
        CoordenadaY = 1 + rand() % (bloques_y_mapa - 1);
        while (Matriz[CoordenadaY][CoordenadaX]!=1 || (CoordenadaX == Posicion_X_Ememigo[0] && CoordenadaY == Posicion_Y_Ememigo[0] ) || (CoordenadaX == Posicion_X_Ememigo[1] && CoordenadaY == Posicion_Y_Ememigo[1] )|| (CoordenadaX == Posicion_X_Ememigo[2] && CoordenadaY == Posicion_Y_Ememigo[2] )|| (CoordenadaX == Posicion_X_Ememigo[3] && CoordenadaY == Posicion_Y_Ememigo[3] )|| (CoordenadaX == Posicion_X_Ememigo[4] && CoordenadaY == Posicion_Y_Ememigo[4] )|| (CoordenadaX == Posicion_X_Ememigo[5] && CoordenadaY == Posicion_Y_Ememigo[5] ))
        {
            CoordenadaX = (bloques_x_mapa/2) + rand() % (bloques_x_mapa + 1 - (bloques_x_mapa/2));
            CoordenadaY = 1 + rand() % (bloques_y_mapa - 1);
        }
        Posicion_X_Ememigo[i]=CoordenadaX;
        Posicion_Y_Ememigo[i]=CoordenadaY;
        Enemy[i]= new Enemigos(0);
        addItem(Enemy[i]);
        Enemy[i]->setPos(CoordenadaX*bloques_ancho,(CoordenadaY*bloques_alto)-45);
        Enemy[i]->select_sprite(0,0);
    }
    for (int i = 1; i<3;i++)
    {
        CoordenadaX = (bloques_x_mapa/2) + rand() % (bloques_x_mapa + 1 - (bloques_x_mapa/2));
        CoordenadaY = 1 + rand() % (bloques_y_mapa - 1);
        while (Matriz[CoordenadaY][CoordenadaX]!=1 || (CoordenadaX == Posicion_X_Ememigo[0] && CoordenadaY == Posicion_Y_Ememigo[0] ) || (CoordenadaX == Posicion_X_Ememigo[1] && CoordenadaY == Posicion_Y_Ememigo[1] )|| (CoordenadaX == Posicion_X_Ememigo[2] && CoordenadaY == Posicion_Y_Ememigo[2] )|| (CoordenadaX == Posicion_X_Ememigo[3] && CoordenadaY == Posicion_Y_Ememigo[3] )|| (CoordenadaX == Posicion_X_Ememigo[4] && CoordenadaY == Posicion_Y_Ememigo[4] )|| (CoordenadaX == Posicion_X_Ememigo[5] && CoordenadaY == Posicion_Y_Ememigo[5] ))
        {
            CoordenadaX = (bloques_x_mapa/2) + rand() % (bloques_x_mapa + 1 - (bloques_x_mapa/2));
            CoordenadaY = 1 + rand() % (bloques_y_mapa - 1);
        }
        Posicion_X_Ememigo[3+i]=CoordenadaX;
        Posicion_Y_Ememigo[3+i]=CoordenadaY;
        Enemy[3+i]= new Enemigos(i);
        addItem(Enemy[3+i]);
        Enemy[3+i]->setPos(CoordenadaX*bloques_ancho,(CoordenadaY*bloques_alto)-45);
        Enemy[3+i]->select_sprite(0,0);
    }
}

void Mapa::MoverEnemigos()
{

    if (iniciar == true)
    {
        if (Descubierto == false)
        {
            Enemy[0]->GenerarMovimiento(Matriz,Enemy[0]->x()+16,Enemy[0]->y()+48,16,0);
            Enemy[1]->GenerarMovimiento(Matriz,Enemy[1]->x()+16,Enemy[1]->y()+48,16,0);
            Enemy[2]->GenerarMovimiento(Matriz,Enemy[2]->x()+16,Enemy[2]->y()+48,16,0);
            Enemy[3]->GenerarMovimiento(Matriz,Enemy[3]->x()+16,Enemy[3]->y()+48,16,0);
            Enemy[4]->GenerarMovimiento(Matriz,Enemy[4]->x()+16,Enemy[4]->y()+48,16,0);
            Enemy[5]->GenerarMovimiento(Matriz,Enemy[5]->x()+16,Enemy[5]->y()+48,16,0);
        }
        else
        {
            Enemy[0]->GenerarMovimiento(Matriz,Enemy[0]->x()+16,Enemy[0]->y()+48,16,0.5);
            Enemy[1]->GenerarMovimiento(Matriz,Enemy[1]->x()+16,Enemy[1]->y()+48,16,0.5);
            Enemy[2]->GenerarMovimiento(Matriz,Enemy[2]->x()+16,Enemy[2]->y()+48,16,0.5);
            Enemy[3]->GenerarMovimiento(Matriz,Enemy[3]->x()+16,Enemy[3]->y()+48,16,0.5);
            Enemy[4]->GenerarMovimiento(Matriz,Enemy[4]->x()+16,Enemy[4]->y()+48,16,0.5);
            Enemy[5]->GenerarMovimiento(Matriz,Enemy[5]->x()+16,Enemy[5]->y()+48,16,0.5);
        }
    }

}

bool Mapa::VerificarMuros(int posicion1_x, int posicion1_y, int posicion2_x, int posicion2_y, Enemigos* Enemy)
{
    if (posicion1_x == posicion2_x)
    {
        if ((posicion1_y-posicion2_y)<=3 && (posicion1_y-posicion2_y)>= (-3) )
        {
            int suma;
            if (posicion2_y > posicion1_y)
            {
                for (int i = 1; i<4;i++)
                {
                    suma = posicion1_y+i;
                    if (suma == bloques_y_mapa)
                    {
                        break;
                    }
                    if (Matriz[suma][posicion1_x] == 0)
                    {
                        return false;
                    }
                }
                Enemy->ModificarSemilla(0);
                return true;
            }
            else
            {
                for (int i = 1; i<4;i++)
                {
                    suma = posicion1_y-i;
                    if (suma == 0)
                    {
                        break;
                    }
                    if (Matriz[suma][posicion1_x] == 0)
                    {
                        return false;
                    }
                }
                Enemy->ModificarSemilla(2);
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else if (posicion1_y == posicion2_y)
    {
        if ((posicion1_x-posicion2_x)<=3 && (posicion1_x-posicion2_x)>= (-3) )
        {
            int suma;
            if (posicion2_x > posicion1_x)
            {
                for (int i = 1; i<4;i++)
                {
                    suma = posicion1_x+i;
                    if (suma == bloques_x_mapa)
                    {
                        break;
                    }
                    if (Matriz[posicion1_y][suma] == 0)
                    {
                        return false;
                    }
                }
                Enemy->ModificarSemilla(3);
                return true;
            }
            else
            {
                for (int i = 1; i<4;i++)
                {
                    suma = posicion1_x-i;
                    if (suma == 0)
                    {
                        break;
                    }
                    if (Matriz[posicion1_y][suma] == 0)
                    {
                        return false;
                    }
                }
                Enemy->ModificarSemilla(1);
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

}

void Mapa::Monitorear_Posiciones()
{
    int Gato_x, Gato_y, Perro1_x, Perro1_y, Perro2_x, Perro2_y,Perro3_x, Perro3_y,Perro0_x, Perro0_y, humano1_x, humano1_y,humano2_x, humano2_y;
    int Comodin1_x, Comodin1_y, Comodin2_x, Comodin2_y, Premio_x, Premio_y;
    Gato_x = (P_Ppal->x()+16)/ bloques_ancho;
    Gato_y = (P_Ppal->y()+47)/ bloques_alto;
    Perro0_x = (Enemy[0]->x())/ bloques_ancho;
    Perro0_y = (Enemy[0]->y()+45)/ bloques_alto;
    Perro1_x = (Enemy[1]->x())/ bloques_ancho;
    Perro1_y = (Enemy[1]->y()+45)/ bloques_alto;
    Perro2_x = (Enemy[2]->x())/ bloques_ancho;
    Perro2_y = (Enemy[2]->y()+45)/ bloques_alto;
    Perro3_x = (Enemy[3]->x())/ bloques_ancho;
    Perro3_y = (Enemy[3]->y()+45)/ bloques_alto;
    humano1_x = (Enemy[4]->x())/ bloques_ancho;
    humano1_y = (Enemy[4]->y()+45)/ bloques_alto;
    humano2_x = (Enemy[5]->x())/ bloques_ancho;
    humano2_y = (Enemy[5]->y()+45)/ bloques_alto;
    Comodin1_x = (Ayudas[0]->x())/ bloques_ancho;
    Comodin1_y = (Ayudas[0]->y())/ bloques_alto;
    Comodin2_x = (Ayudas[1]->x())/ bloques_ancho;
    Comodin2_y = (Ayudas[1]->y())/ bloques_alto;
    Premio_x = (Premio->x())/ bloques_ancho;
    Premio_y = (Premio->y())/ bloques_alto;
    if ((Gato_x == Perro0_x && Gato_y == Perro0_y) || (Gato_x == Perro1_x && Gato_y == Perro1_y) || (Gato_x == Perro2_x && Gato_y == Perro2_y) || (Gato_x == Perro3_x && Gato_y == Perro3_y)|| (Gato_x == humano1_x && Gato_y == humano1_y)|| (Gato_x == humano2_x && Gato_y == humano2_y))
    {
        Descubierto = false;
        comer = false;
        for (int i = 0; i < 6 ; i++)
        {
            removeItem(Enemy[i]);
            delete Enemy[i];
        }
        GenerarEnemigosySalida();
        removeItem(P_Ppal);
        addItem(Premio);
        addItem(Ayudas[0]);
        addItem(Ayudas[1]);
        vidas++;
        if (vidas <3)
        {
            P_Ppal->setPos(48,16);
            P_Ppal->select_sprite(0,0);
            addItem(P_Ppal);
        }
        else if (vidas == 3)
        {
            removeItem(Vidas_gato);
        }
        Vidas_gato->select_sprite(0,vidas);
    }
    if (VerificarMuros(Gato_x,Gato_y,Perro0_x,Perro0_y,Enemy[0]))
    {
        Descubierto = true;
    }
    if (VerificarMuros(Gato_x,Gato_y,Perro1_x,Perro1_y,Enemy[1]))
    {
        Descubierto = true;
    }
    if (VerificarMuros(Gato_x,Gato_y,Perro2_x,Perro2_y,Enemy[2]))
    {
        Descubierto = true;
    }
    if (VerificarMuros(Gato_x,Gato_y,Perro3_x,Perro3_y,Enemy[3]))
    {
        Descubierto = true;
    }
    if (VerificarMuros(Gato_x,Gato_y,humano1_x,humano1_y,Enemy[4]))
    {
        Descubierto = true;
    }
    if (VerificarMuros(Gato_x,Gato_y,humano2_x,humano2_y,Enemy[5]))
    {
        Descubierto = true;
    }
    if (Gato_x == Comodin1_x && Gato_y == Comodin1_y)
    {
        Descubierto = false;
        removeItem(Ayudas[0]);
    }
    if (Gato_x == Comodin2_x && Gato_y == Comodin2_y)
    {
        Descubierto = false;
        removeItem(Ayudas[1]);
    }
    if (Gato_x == Premio_x && Gato_y == Premio_y)
    {
        removeItem(Premio);
        comer = true;
    }
    if (Gato_x == 0 && Gato_y == 1 && comer == true)
    {
        for (int i = 0; i < 6 ; i++)
        {
            removeItem(Enemy[i]);
        }
        removeItem(P_Ppal);
        addItem(Letrero3);
        Letrero2 = new Letreros (2);
        addItem(Letrero2);
        Letrero2->setPos(48*13,48*5+24);
        Letrero2->select_sprite(0,0);
        iniciar = false;
    }
}
