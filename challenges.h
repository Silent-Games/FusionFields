#ifndef CHALLENGES_H
#define CHALLENGES_H

#include "button.h"
#include "challenge.h"
#include "controller.h"
#include <QtWidgets>

class Controller;

class Challenges : public QWidget
{
  Q_OBJECT
  private:
    Controller *controller;
    QList< Challenge * > challenge;
    QList< Button* > btnChallenge;
    QGridLayout *challengeLayout;
    Animation *animation;

  private slots:
    void showButton( void );

  public:
    explicit Challenges( Controller *controller, QWidget *parent = 0 );
    ~Challenges( void );

  public slots:
    void setSelectedChallenge( void );
};

#endif // CHALLENGES_H
