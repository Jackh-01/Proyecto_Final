#ifndef MAPA_H
#define MAPA_H

#include <QVector>
#include <QGraphicsScene>
#include "bloques.h"
#include "Personaje.h"
#include "enemigos.h"

#define bloques_x_mapa 31
#define bloques_y_mapa 17


class Mapa : public QGraphicsScene
{
    Q_OBJECT
public:
    Mapa();
    ~Mapa();
    void GenerarMapa ();
    void Mover_Personaje(QKeyEvent *event);
    void GenerarEnemigosySalida();
    void MoverEnemigos();

private:
    int** Matriz;
    int Posicion_X_Ememigo[4];
    int Posicion_Y_Ememigo[4];
    int filas, columnas, CoordenadaX, CoordenadaY;
    Bloques *bl_mapa[bloques_y_mapa][bloques_x_mapa];
    Personaje *P_Ppal;
    bool boom;
    Enemigos *Enemy[4];
    QTimer* MovimientoEnemigos;
    //    Enemigos *EnemigoPrueba;

};

#endif // MAPA_H
