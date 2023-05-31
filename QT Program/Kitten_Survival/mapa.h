
#ifndef MAPA_H
#define MAPA_H

#include "bloques.h"
#include <QVector>
#include <QGraphicsScene>

#define bloques_x_mapa 30
#define bloques_y_mapa 18

class Mapa: public QGraphicsScene
{
    Q_OBJECT
public:
    Mapa();
    ~Mapa();
    void GenerarMapa ();
    void CargarMapa();
    void Mover_Personaje(QKeyEvent *event);
    void GenerarEnemigos();

private:
    int** Matriz;
    int filas, columnas, CoordenadaX, CoordenadaY;
    int laberintoDatos[18][30];
    Bloques *bl_mapa[bloques_y_mapa][bloques_x_mapa];
};

#endif // MAPA_H
