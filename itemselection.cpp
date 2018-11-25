#include "itemselection.h"

void ItemSelection::showButton( void )
{
  int btnIndex = btnItem.length() - animation->getTimerCount() - 1;
  btnItem[ btnIndex ]->setColors( TRANSPARENTC, TRANSPARENTBLACK );
  QImage itemImg;
  if( item[ btnIndex ]->isItemUnlocked() )
    itemImg = Config::getConfig()->getItemImage( item[ btnIndex ]->getId() );
  else
    itemImg = Config::getConfig()->LOCKEDIMAGE;
  btnItem[ btnIndex ]->setImage( itemImg );
  connect( btnItem[ btnIndex ], SIGNAL( clicked() ), this, SLOT( setSelectedItem() ) );
}

ItemSelection::ItemSelection( int selectedItemId, Controller *controller, QWidget *parent ) : QWidget( parent )
{
  QVBoxLayout *vLayout = new QVBoxLayout( this );
  //ItemDescription
  itemDescription = new ItemDescription;
  vLayout->addWidget( itemDescription );

  //Items
  this->selectedItemId = selectedItemId;
  QGridLayout *itemLayout = new QGridLayout();
  item << Data::getData()->item;
  for( int i = item.length() - 1; i >= 0; i-- )
    if( item[ i ]->getId() == LOCKED || item[ i ]->getId() == UNLOCKED || item[ i ]->getId() == NOITEM )
    {
      item.removeAt( i );
      continue;
    }
  Item *selectedItem = new Item();
  selectedItem->setId( -1 );
  for( int r = 0, i = 0; r < 3; r++ )
    for( int c = 0; c < 3 && i < item.length(); c++, i++ )
    {
      if( item[ i ]->getId() == selectedItemId )
        selectedItem = item[ i ];
      btnItem << new Button;
      btnItem[ i ]->setHeightWidthRatio( 1 );
      btnItem[ i ]->setColors( TRANSPARENTC, TRANSPARENTC );
      itemLayout->addWidget( btnItem[ i ], r, c );
    }
  vLayout->addLayout( itemLayout );

  if( selectedItem->getId() == -1 )
    setSelectedItem( item[ 0 ] );
  else setSelectedItem( selectedItem );

  animation = new Animation;
  animation->setTimerCount( btnItem.length() );
  animation->setTimerMsec( ANIMATIONLENGTH / btnItem.length() );
  connect( animation, SIGNAL( working() ), this, SLOT( showButton() ) );
}

int ItemSelection::getSelectedItemId( void )
{
  return selectedItemId;
}

void ItemSelection::setSelectedItem( void )
{
  for( int i = 0; i < btnItem.length(); i++ )
    if( sender() == btnItem[ i ] )
      setSelectedItem( item[ i ] );
}

void ItemSelection::setSelectedItem( Item *item )
{
  for( int i = 0; i < this->item.length(); i++ )
  {
    btnItem[ i ]->setActive( false );
    if( item->getId() == this->item[ i ]->getId() )
    {
      if( this->item[ i ]->isItemUnlocked() )
        selectedItemId = this->item[ i ]->getId();
      btnItem[ i ]->setActive( true );
      itemDescription->setItem( this->item[ i ] );
    }
  }
}

void ItemSelection::animate( void )
{
  animation->start();
  itemDescription->animate();
}

void ItemSelection::paintEvent( QPaintEvent * )
{
  itemDescription->setFixedHeight( height() * 0.35 );
}
