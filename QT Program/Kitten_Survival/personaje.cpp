#include "Personaje.h"

Personaje::Personaje()
{
//    set_imagen(32,32,0,0,4,4,":/Sprite/PC Computer - Stardew Valley - Cat.png",48,48);
    set_imagen(48,48,0,0,3,4,":/Sprite/151346-61e6dc8b6dc37f21997f60b4b52fc324.jpg",48,48);


}

void Personaje::tecla_pressed(QKeyEvent *event, int VelocidadX, int VelocidadY)
{
    static int var =0;
//    if(event->key()==Qt::Key_D)
//    {
//        setPos(x()+VelocidadX,y());
//        select_sprite(var,1);
//        var++;
//        if(var>3) var = 0;
//    }
//    else if(event->key()==Qt::Key_A)
//    {
//        setPos(x()-VelocidadX,y());
//        select_sprite(var,3);
//        var++;
//        if(var>3) var = 0;
//    }
//    else if(event->key()==Qt::Key_S)
//    {
//        setPos(x(),y()+VelocidadY);
//        select_sprite(var,0);
//        var++;
//        if(var>3) var = 0;
//    }
//    else if(event->key()==Qt::Key_W)
//    {
//        setPos(x(),y()-VelocidadY);
//        select_sprite(var,2);
//        var++;
//        if(var>3) var = 0;
//    }
    if(event->key()==Qt::Key_D)
    {
        setPos(x()+VelocidadX,y());
        select_sprite(var,2);
        var++;
        if(var>2) var = 0;
    }
    else if(event->key()==Qt::Key_A)
    {
        setPos(x()-VelocidadX,y());
        select_sprite(var,1);
        var++;
        if(var>2) var = 0;
    }
    else if(event->key()==Qt::Key_S)
    {
        setPos(x(),y()+VelocidadY);
        select_sprite(var,0);
        var++;
        if(var>2) var = 0;
    }
    else if(event->key()==Qt::Key_W)
    {
        setPos(x(),y()-VelocidadY);
        select_sprite(var,3);
        var++;
        if(var>2) var = 0;
    }
}
