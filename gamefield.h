#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "config.h"
#include "game.h"
#include "animation.h"
#include <QtWidgets>

class GameField : public QWidget
{
  Q_OBJECT
  private:
    Game *game;
    double fieldSize;
    double tileSize;
    QList< int > selectedTileIndex;
    Animation *animation;

    int getSelectedTileIndex( QPoint pos );

  public:
    explicit GameField( QWidget *parent = 0 );
    void setGame( Game *game );
    void animate( void );

  protected:
    virtual void paintEvent( QPaintEvent * );
    virtual void mousePressEvent( QMouseEvent *event );
    virtual void mouseReleaseEvent( QMouseEvent *event );

  signals:
    void move( QList< int > selectedTileIndex);
};

#endif // GAMEFIELD_H
