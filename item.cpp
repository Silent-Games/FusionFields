#include "item.h"

Item::Item( QObject *parent ) : QObject( parent ),
  id( -1 ), name( "" ), description( "" ), cost( 0 ), isUnlocked( false )
{
}

void Item::setId( int id )
{
  this->id = id;
}

int Item::getId( void )
{
  return id;
}

void Item::setName( QString name )
{
  this->name = name;
}

QString Item::getName( void )
{
  return name;
}

void Item::setDescription( QString description )
{
  this->description = description;
}

QString Item::getDescription( void )
{
  return description;
}

void Item::setCost( int cost )
{
  this->cost = cost;
}

int Item::getCost( void )
{
  return cost;
}

void Item::setIsItemUnlocked( bool state )
{
  isUnlocked = state;
}

bool Item::isItemUnlocked( void )
{
  return isUnlocked;
}
