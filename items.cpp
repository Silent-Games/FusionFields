#include "items.h"

Items::Items( QList< int > item, Controller *controller, QWidget *parent ) : QWidget( parent )
{
  this->controller = controller;

  this->item = item;
  QVBoxLayout *vLayout = new QVBoxLayout( this );
  //Items
  for( int i = 0; i < this->item.length(); i++ )
  {
    btnItem << new Button;
    btnItem[ i ]->setColors( TRANSPARENTC, TRANSPARENTC );
    btnItem[ i ]->setHeightWidthRatio( 1 );
    QSizePolicy itemSP( QSizePolicy::Preferred, QSizePolicy::Preferred );
    itemSP.setVerticalStretch( 4 );
    btnItem[ i ]->setSizePolicy( itemSP );
    vLayout->addWidget( btnItem[ i ] );
  }

  animation = new Animation;
  animation->setTimerCount( btnItem.length() );
  animation->setTimerMsec( ANIMATIONLENGTH / btnItem.length() );
  connect( animation, SIGNAL( working() ), this, SLOT( showButton() ) );
  animation->start();

}

void Items::showItemSelection( void )
{
  int itemSlotNr = 1;
  for( int i = 0; i < btnItem.length(); i++ )
    if( sender() == btnItem[ i ] )
    {
      itemSlotNr = i + 1;
      break;
    }
  controller->showItemSelection( itemSlotNr );
}

void Items::showButton( void )
{
  btnItem[ btnItem.length() - animation->getTimerCount() - 1 ]->setColors( TRANSPARENTC, TRANSPARENTBLACK );
  btnItem[ btnItem.length() - animation->getTimerCount() - 1 ]->setImage( Config::getConfig()->getItemImage( this->item[ btnItem.length() - animation->getTimerCount() - 1 ] ) );
  connect( btnItem[ btnItem.length() - animation->getTimerCount() - 1 ], SIGNAL( clicked() ), this, SLOT( showItemSelection() ) );
}
