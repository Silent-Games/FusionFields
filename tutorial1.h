#ifndef TUTORIAL1_H
#define TUTORIAL1_H

#include "label.h"
#include "button.h"
#include "board.h"
#include "data.h"
#include "config.h"
#include "gamefield.h"
#include <QtWidgets>

class Tutorial1 : public QWidget
{
  Q_OBJECT
  private:
    QList< QRect > layoutItemRect;
    QVBoxLayout *mainLayout;
    int step;
    Label *label;
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
    explicit Tutorial1( QWidget *parent = 0 );
    ~Tutorial1( void );

  private slots:
    void showNextStep( void );
    void move( QList< int > selectedTileIndex );

  protected:
    virtual void paintEvent( QPaintEvent * );

  signals:
    void tutorialFinished( void );
};

#endif // TUTORIAL1_H
