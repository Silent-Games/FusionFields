#ifndef DATABASE_H
#define DATABASE_H

#include "itemgame.h"
#include "game.h"
#include "challenge.h"
#include "item.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtCore>
#include <QObject>

class Database : public QObject
{
  Q_OBJECT
  private:
    QSqlDatabase db;
    int getInt( QString column, QString table );
    int getBool( QString column, QString table );

  public:
    explicit Database( QObject *parent = 0 );
    //game
    void setGame( Game *game );
    QList< Game* > getGames( void );
    void setField( int gameId, QList< int > field );
    QList< int > getField( int gameId ) const;
    //infos
    void setHighScore( int score );
    int getHighScore( void );
    void setHighestTileValue( int highestTileValue );
    int getHighestTileValue( void );
    void setItem1( int item );
    int getItem1( void );
    void setItem2( int item );
    int getItem2( void );
    void setLevel( int level );
    int getLevel( void );
    void setXP( int xp );
    int getXP( void );
    void setIsSoundMuted( bool state );
    bool getIsSoundMuted( void );
    void setTutorialLevel( int level );
    int getTutorialLevel( void );
    void setLastTutorialFinished( bool state );
    bool getLastTutorialFinished( void );
    void setResetAllGames( bool state );
    //items
    QList< Item * > getItems( void );
    void setIsItemUnlocked( int itemId, bool state );
    QList< ItemGame * > getItemGames( void );
    void setItemGameMove( int itemId, int gameId, int move );
    //challenges
    QList< Challenge * > getChallenges( void );
    void setIsChallengeCompleted( int challengeId, bool state );
};

#endif // DATABASE_H
