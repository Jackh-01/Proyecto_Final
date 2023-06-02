#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QString>

class sprite : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    sprite();
    ~sprite();
    void set_imagen(int ancho, int alto, int x_origin, int y_origin, int x_sprites, int y_sprites, QString ubicacion,int ancho_x, int ancho_y);
    void select_sprite(int x, int y);


private:

    int ancho, alto;
    QPixmap *pixmap, *current_pixmap;
};

#endif // SPRITE_H
