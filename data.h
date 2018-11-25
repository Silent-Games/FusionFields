#ifndef DATA_H
#define DATA_H

#include "game.h"
#include "itemgame.h"
#include "config.h"
#include "challenge.h"
#include "database.h"

class Data
{
  private:
    Data( void );
    static Data *data;
    Database db;

  public:
    static Data *getData( void );
    void saveGame( void );
    void saveGame( int gameId );
    void saveInfo( void );
    void saveItem( void );
    void saveChallenge( void );
    void saveChallenge( int challengeId );
    void save( void );
    //game
    QList< Game* > game;
    void updateGames( Game *game );
    Game *getGame( int id );
    //info
    int highscore;
    int highestTileValue;
    QList< int > itemSlot;
    int level;
    int xp;
    void addXP( int xp );
    bool isSoundMuted;
    int tutorialLevel;
    bool lastTutorialFinished;
    void setResetAllGame( bool state );
    //item
    QList< Item* > item;
    Item *getItem( int id );
    QList< ItemGame* > itemGame;
    QList< ItemGame* > getItemGames( int gameId );
    void updateItemGames( QList< ItemGame* > itemGames );
    //challenge
    QList< Challenge* > challenge;
    Challenge *getChallenge( int id );
    Challenge *getChallengeWithNr( int nr );
    int getNumberOfCompletedChallenges( void );
};

#endif // DATA_H
