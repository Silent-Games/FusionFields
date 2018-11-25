#include "menu.h"

Menu::Menu( Controller *controller, QWidget *parent ) : QWidget( parent )
{
  setupUi( this );
  this->controller = controller;

  QImage soundImg( Data::getData()->isSoundMuted ? Config::getConfig()->SOUNDOFFIMAGEFILE : Config::getConfig()->SOUNDONIMAGEFILE );
  btnMute->setImage( soundImg );
  btnMute->setColors( TRANSPARENTC, TRANSPARENTBLACK );

  btnInfo->setImage( Config::getConfig()->INFOIMAGE );
  btnInfo->setColors( TRANSPARENTC, TRANSPARENTBLACK );

  xpProgressBar->setValues( Data::getData()->level, Data::getData()->xp );
  homeWidget->setValues( Data::getData()->highscore,
                         Data::getData()->highestTileValue,
                         Data::getData()->getNumberOfCompletedChallenges(),
                         Data::getData()->challenge.length(),
                         Data::getData()->itemSlot );
  homeWidget->animate();

  connect( homeWidget, SIGNAL( clicked( int ) ), this, SLOT( homeWidgetClicked( int ) ) );
  connect( btnMute, SIGNAL( clicked() ), this, SLOT( switchIsSoundMuted() ) );
  connect( btnMute, SIGNAL( clicked() ), this, SIGNAL( muteButtonClicked() ) );
  connect( btnInfo, SIGNAL( clicked() ), controller, SLOT( showAppInfo() ) );
}

void Menu::homeWidgetClicked( int section )
{
  switch( section )
  {
    case 1: controller->showFusionFields(); break;
    case 2: controller->showChallenges(); break;
    case 3: controller->showItems(); break;
  }
}

void Menu::switchIsSoundMuted( void )
{
  Data::getData()->isSoundMuted = !Data::getData()->isSoundMuted;
  controller->saveData( SaveDataThread::Info );
  QImage soundImg( Data::getData()->isSoundMuted ? Config::getConfig()->SOUNDOFFIMAGEFILE : Config::getConfig()->SOUNDONIMAGEFILE );
  btnMute->setImage( soundImg );
}

void Menu::paintEvent( QPaintEvent * )
{
  xpProgressBar->setFixedHeight( height() * 0.1 );
  btnMute->setFixedHeight( height() * 0.08 );
}
