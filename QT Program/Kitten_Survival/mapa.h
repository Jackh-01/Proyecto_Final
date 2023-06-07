#ifndef MAPA_H
#define MAPA_H

#include <QVector>
#include <QGraphicsScene>
#include "bloques.h"
#include "Personaje.h"
#include "comida.h"
#include "comodin.h"
#include "enemigos.h"
#include "letreros.h"
#include "vidas.h"

#define bloques_x_mapa 31
#define bloques_y_mapa 17


class Mapa : public QGraphicsScene
{
    Q_OBJECT
public:
    Mapa();
    ~Mapa();
    void GenerarLaberinto_1();
    void GenerarMapa ();
    void Mover_Personaje(QKeyEvent *event);
    void GenerarEnemigosySalida();
    void MoverEnemigos();
    bool VerificarMuros(int posicion1_x, int posicion1_y, int posicion2_x, int posicion2_y,Enemigos* Enemy);
    void Monitorear_Posiciones();


private:
    int** Matriz;
    int Posicion_X_Ememigo[6];
    int Posicion_Y_Ememigo[6];
    int CoordenadaX, CoordenadaY, vidas;
    Bloques *bl_mapa[bloques_y_mapa][bloques_x_mapa];
    Personaje *P_Ppal;
    bool Descubierto, comer, iniciar;
    Enemigos *Enemy[6];
    QTimer* MovimientoEnemigos;
    QTimer* Posicion_Personajes;
    Comida* Premio;
    Comodin* Ayudas[2];
    Letreros* Letrero1;
    Letreros* Letrero2;
    Letreros* Letrero3;
    Vidas* Vidas_gato;

};

#endif // MAPA_H
