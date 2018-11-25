#ifndef BOARD_H
#define BOARD_H

#include "config.h"
#include "game.h"
#include "challenge.h"
#include "animation.h"
#include <QtWidgets>

class Board : public QWidget
{
  Q_OBJECT
  private:
    Game *game;
    Challenge *challenge;
    Animation *animation;
    bool isCaption;

  public:
    explicit Board( QWidget *parent = 0 );
    void setGame( Game *game );
    void setChallenge( Challenge *challenge );
    void animate( void );
    void setCaption( bool isCaption );

  protected:
    virtual void paintEvent( QPaintEvent * );
};

#endif // BOARD_H
