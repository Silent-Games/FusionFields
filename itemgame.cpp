#include "itemgame.h"

ItemGame::ItemGame( Item *item, int gameId, int move, QObject *parent ) : QObject( parent ),
  move( 0 ), gameId( -1 )
{
  this->item = item;
  this->gameId = gameId;
  this->move = move;
}

int ItemGame::getItemId( void )
{
  return item->getId();
}

int ItemGame::getGameId( void )
{
  return gameId;
}

int ItemGame::getItemCost( void )
{
  return this->item->getCost() * pow( 2, move );
}

void ItemGame::setMove( int move )
{
  this->move = move;
}

int ItemGame::getMove( void )
{
  return move;
}
