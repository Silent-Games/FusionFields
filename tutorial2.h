#ifndef TUTORIAL2_H
#define TUTORIAL2_H

#include "data.h"
#include "config.h"
#include "board.h"
#include "gamefield.h"
#include "game.h"
#include "label.h"
#include "button.h"
#include <QtWidgets>

class Tutorial2 : public QWidget
{
  Q_OBJECT
  private:
    QList< QRect > layoutItemRect;
    QVBoxLayout *mainLayout;
    int step;
    Label * label;
    Label * label2;
    Game *game;
    GameField *gameField;
    Board *board;
    Button *button;
    QTimer *timer;

    void showStep0( void );
    void showStep1( void );
    void showStep2( void );
    void showStep3( void );

  public:
    explicit Tutorial2( QWidget *parent = 0 );

  private slots:
    void showNextStep( void );
    void move( QList< int > selectedTileIndex );

  protected:
    virtual void paintEvent( QPaintEvent * );

  signals:
    void tutorialFinished( void );
};

#endif // TUTORIAL2_H
