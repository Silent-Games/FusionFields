#ifndef ITEMGAME_H
#define ITEMGAME_H

#include "item.h"
#include <QObject>

class ItemGame : public QObject
{
  Q_OBJECT
  private:
    Item *item;
    int gameId;
    int move;

  public:
    explicit ItemGame( Item *item, int gameId, int move, QObject *parent = 0 );
    int getItemId( void );
    int getGameId( void );
    int getItemCost( void );
    void setMove( int move );
    int getMove( void );
};

#endif // ITEMGAME_H
