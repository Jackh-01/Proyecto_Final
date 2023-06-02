#include "sprite.h"
#include <QString>

sprite::sprite()
{
    pixmap = new QPixmap;
    current_pixmap = new QPixmap;
}

sprite::~sprite()
{
    delete pixmap;
    delete current_pixmap;
}

void sprite::set_imagen(int ancho, int alto, int x_origin, int y_origin, int x_sprites, int y_sprites, QString ubicacion,int ancho_x, int ancho_y)
{

    pixmap->load(ubicacion);
    *pixmap = pixmap->copy(x_origin,y_origin,x_sprites*ancho,y_sprites*alto);
    *pixmap = pixmap->scaled(x_sprites*ancho_x, y_sprites*ancho_x);
    this->ancho = ancho_x;
    this->alto  = ancho_y;
}

void sprite::select_sprite(int x, int y)
{
    *current_pixmap = pixmap->copy(x*ancho,y*alto,ancho,alto);
    setPixmap(*current_pixmap);
}

