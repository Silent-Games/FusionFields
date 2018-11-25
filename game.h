#ifndef GAME_H
#define GAME_H

#include "itemgame.h"
#include "config.h"
#include "challenge.h"
#include <time.h>
#include <QObject>
#include <QDebug>

class Game : public QObject
{
  Q_OBJECT
  private:
    int id;
    int fieldWidth;
    int fieldHeight;
    QList< int > field;
    int score;
    bool fusionPointState;
    int fusionPoints;
    int fusionPointTileIndex;
    int move;
    int nextTile;
    bool objectState;
    int object;
    int objectTileIndex;
    bool resetGame;
    QList< ItemGame * > itemGame;
    Challenge *challenge;

    int getAboveNeighbor( int fieldIndex );
    int getRightNeighbor( int fieldIndex );
    int getBelowNeighbor( int fieldIndex );
    int getLeftNeighbor( int fieldIndex );
    QList< int > getNeighbors( int fieldIndex );
    QList< int > getNeighborsWithSameValue( int fieldIndex );
    bool isFieldIndexCorrect( int fieldIndex );
    int getRandomNextTile( void );
    int getRandomTileIndex( void );
    int getRandomFusionPointTileIndex( void );
    int setObjectTileIndex( void );
    bool mergeTiles( int fromTileIndex, int toTileIndex );
    bool swapTiles( int fromTileIndex, int toTileIndex );
    bool increaseTile( int tileIndex );
    bool decreaseTile( int tileIndex );
    bool setTileValueToRandom( int tileIndex );
    bool setNewNextTile( int tileIndex );
    void setItemGameMove( int itemId, int move );
    int getItemGameMove( int itemId );

  public:
    explicit Game( QObject *parent = 0 );
    Game( int id, QList< int > field, int score, int fusionPoints, int fusionPointTileIndex, int move, int nextTile, int object, int objectTileIndex, bool resetGame );
    int getId( void );
    void setFieldSize( int fieldWidth, int fieldHeight );
    int getFieldWidth( void );
    int getFieldHeight( void );
    void setField( QList< int > newField );
    QList< int > getField( void );
    static QList< int > generateField( int fieldWidth, int fieldHeight );
    bool isGameFinished( void );
    int getScore( void ) const;
    void setFusionPointState( bool state );
    bool isFusionPoint( void );
    int getFusionPoints( void );
    int getFusionPointTileIndex( void );
    int getMove( void ) const;
    int getNextTile( void ) const;
    int getObject( void );
    int getObjectTileIndex( void );
    void setResetGame( bool state );
    bool getResetGame( void );
    void setItemGames( QList< ItemGame * > item );
    QList< ItemGame * > getItemGames( void );
    int getItemCost( int itemId );
    void setChallenge( Challenge *challenge );
    Challenge *getChallenge( void );
    bool isChallengeWon( void );
    bool isChallengeLose( void );
    void reset( void );
    bool doMove( int item, QList< int > tileIndex );
    int getHighestTileValue( void );
};

#endif // GAME_H
