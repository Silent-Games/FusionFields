#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "tutorial2.h"
#include "tutorial1.h"
#include "appinfo.h"
#include "savedatathread.h"
#include "data.h"
#include "itemselection.h"
#include "items.h"
#include "menu.h"
#include "challenges.h"
#include "fusionfields.h"
#include "ui_controller.h"
#include <QtWidgets>
#include <QtGui>
#include <QMediaPlayer>

class Menu;
class Challenges;
class FusionFields;
class Items;
class ItemSelection;

class Controller : public QWidget, private Ui::Controller
{
  Q_OBJECT
  private:
    Menu *menu;
    Challenges *challenges;
    FusionFields *fusionFields;
    Items *items;
    ItemSelection *itemSelection;
    int itemSlotNr;
    AppInfo *appInfo;
    Tutorial1 *tutorial1;
    Tutorial2 *tutorial;
    QColor backgroundColor;

  public:
    explicit Controller( QWidget *parent = 0 );
    int startChallengeNr;
    ~Controller( void );

  public slots:
    void showMenu( void );
    void showChallenges( int startChallengeNr = 1 );
    void showFusionFields( Challenge *challenge = new Challenge() );
    void showItems( void );
    void showItemSelection( int itemSlotNr );
    void setItemSlot( int itemId );
    void showAppInfo( void );
    void showTutorial( int level = 1 );
    void setTutorialFinished( void );
    void setMenuButton( void );
    void showLeftClickedWidget( void );
    void showMiddleClickedWidget( void );
    void showRightClickedWidget( void );
    void saveData( int whatSaving = SaveDataThread::All, int gameId = -1, int challengeId = -1 );

  protected:
    virtual void paintEvent( QPaintEvent * );
};

#endif // CONTROLLER_H
