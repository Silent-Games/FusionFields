#ifndef GAMEENDWIDGET_H
#define GAMEENDWIDGET_H

#include "animation.h"
#include "config.h"
#include <QtWidgets>

class GameEndWidget : public QWidget
{
  Q_OBJECT
  private:
    QString gameState;
    QList< QString > infoText;
    QList< int > infoNumber;
    Animation *animation;

  public:
    explicit GameEndWidget( QWidget *parent = 0 );
    void setValues( QString gameState, int score, int move, int object = -1 );
    void setOtherValues( QList< QString > other );
    void animate( void );

  protected:
    virtual void paintEvent( QPaintEvent * );
};

#endif // GAMEENDWIDGET_H
