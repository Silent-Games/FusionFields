#ifndef ITEMBOARD_H
#define ITEMBOARD_H

#include "animation.h"
#include "game.h"
#include "config.h"
#include <QtWidgets>

class ItemBoard : public QWidget
{
  Q_OBJECT
  private:
    QList< int > item;
    Game *game;
    QList< QRectF > itemRect;
    int selectedItem;
    Animation *animation;

  public:
    explicit ItemBoard( QWidget *parent = 0 );
    void setItems( QList< int > item );
    QList< int > getItems( void );
    void setGame( Game *game );
    void setSelectedItem( int item );
    void animate( void );

  protected:
    virtual void paintEvent( QPaintEvent * );
    virtual void mouseReleaseEvent( QMouseEvent *event );

  signals:
    void itemClicked( int item );
};

#endif // ITEMBOARD_H
