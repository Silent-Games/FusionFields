#ifndef FUSIONFIELDS_H
#define FUSIONFIELDS_H

#include "data.h"
#include "challenge.h"
#include "config.h"
#include "item.h"
#include "database.h"
#include "game.h"
#include "controller.h"
#include "ui_fusionfields.h"
#include <QtWidgets>
#include <QtGui>
#include <QMediaPlayer>

class Controller;

class FusionFields : public QWidget, private Ui::FusionFields
{
  Q_OBJECT
  private:
    Controller *controller;
    Game *game;
    int activeItem;
    Challenge *challenge;
    QMediaPlayer *moveSound;

    void saveData( void );

  public:
    explicit FusionFields( Challenge *challenge, Controller *controller, QWidget *parent = 0 );
    ~FusionFields( void );

  private slots:
    void move( QList< int > selectedTileIndex );
    void restart( void );
    void setActiveItem( int item );
    void checkLevelRewards( void );
    void startChallenge( void );
    void finishGame( void );
    void setFusionFieldsWidgetsHidden( int widgetHiddenState );
    void gameEndButtonSlot( void );
};

#endif // FUSIONFIELDS_H
