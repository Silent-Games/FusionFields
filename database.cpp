#include "database.h"

int Database::getInt( QString column, QString table )
{
  QSqlQuery query( "SELECT " + column + " FROM " + table );
  query.first();
  return query.value( 0 ).toInt();
}

int Database::getBool( QString column, QString table )
{
  QSqlQuery query( "SELECT " + column + " FROM " + table );
  query.first();
  return query.value( 0 ).toBool();
}

Database::Database( QObject *parent ) : QObject( parent )
{
  db = QSqlDatabase::addDatabase( "QSQLITE" );
  db.setDatabaseName( "./databaseFF" );
  if( !db.open() )
    qDebug() << "Fehler beim Öffnen der Datenbank!";
}

void Database::setGame( Game *game )
{
  QString resetGameString = game->getResetGame() ? "1" : "0";
  QSqlQuery query( "UPDATE game SET score = " + QString::number( game->getScore() ) +
                    ", fusionPoints = " + QString::number( game->getFusionPoints() ) +
                    ", fusionPointTileIndex = " + QString::number( game->getFusionPointTileIndex() ) +
                    ", move = " + QString::number( game->getMove() ) +
                    ", nextTile = " + QString::number( game->getNextTile() ) +
                    ", object = " + QString::number( game->getObject() ) +
                    ", objectTileIndex = " + QString::number( game->getObjectTileIndex() ) +
                    ", resetGame = " + resetGameString + " WHERE gameId = " + QString::number( game->getId() ) );
  setField( game->getId(), game->getField() );
}

QList< Game* > Database::getGames( void )
{
  QSqlQuery query( "SELECT gameId, score, fusionPoints, fusionPointTileIndex, move, nextTile, object, objectTileIndex, resetGame FROM game" );
  QList< Game* > g;
  while( query.next() )
  {
    g << new Game( query.value( 0 ).toInt(),
                   getField( query.value( 0 ).toInt() ),
                   query.value( 1 ).toInt(),
                   query.value( 2 ).toInt(),
                   query.value( 3 ).toInt(),
                   query.value( 4 ).toInt(),
                   query.value( 5 ).toInt(),
                   query.value( 6 ).toInt(),
                   query.value( 7 ).toInt(),
                   query.value( 8 ).toBool() );
  }
  return g;
}

void Database::setField( int gameId, QList< int > field )
{
  QString fieldString( "" );
  for( int i = 0; i < field.length(); i++ )
    fieldString.append( QString::number( field[ i ] ).append( "," ) );
  fieldString.remove( fieldString.length() - 1, 1 );
  QSqlQuery query( "UPDATE game SET field = '" + fieldString + "' WHERE gameId = " + QString::number( gameId ) );
}

QList< int > Database::getField( int gameId ) const
{
  QSqlQuery query( "SELECT field FROM game WHERE gameId = " + QString::number( gameId ) );
  query.first();
  QStringList fieldList = query.value( 0 ).toString().split( "," );;
  QList< int > field;
  for( int i = 0; i < fieldList.length(); i++ )
    field << fieldList.at( i ).toInt();
  return field;
}

void Database::setHighScore( int score )
{
  QSqlQuery query( "UPDATE info SET highScore = " + QString::number( score ) );
}

int Database::getHighScore( void )
{
  return getInt( "highScore", "info" );
}

void Database::setHighestTileValue( int highestTileValue )
{
  QSqlQuery query( "UPDATE info SET highestTileValue = " + QString::number( highestTileValue ) );
}

int Database::getHighestTileValue( void )
{
  return getInt( "highestTileValue", "info" );
}

void Database::setItem1( int item )
{
  QSqlQuery query( "UPDATE info SET itemSlot1 = " + QString::number( item ) );
}

int Database::getItem1( void )
{
  return getInt( "itemSlot1", "info" );
}

void Database::setItem2( int item )
{
  QSqlQuery query( "UPDATE info SET itemSlot2 = " + QString::number( item ) );
}

int Database::getItem2( void )
{
  return getInt( "itemSlot2", "info" );
}

void Database::setLevel( int level )
{
  QSqlQuery query( "UPDATE info SET level = " + QString::number( level ) );
}

int Database::getLevel( void )
{
  return getInt( "level", "info" );
}

void Database::setXP( int xp )
{
  QSqlQuery query( "UPDATE info SET xp = " + QString::number( xp ) );
}

int Database::getXP( void )
{
  QSqlQuery query( "SELECT xp FROM info" );
  query.first();
  return query.value( 0 ).toInt();
}

void Database::setIsSoundMuted( bool state )
{
  QString isMutedString = state ? "1" : "0";
  QSqlQuery query( "UPDATE info SET isSoundMuted = " + isMutedString );
}

bool Database::getIsSoundMuted( void )
{
    return getInt( "isSoundMuted", "info" );
}

void Database::setTutorialLevel( int level )
{
  QSqlQuery query( "UPDATE info SET tutorialLevel = " + QString::number( level ) );
}

int Database::getTutorialLevel( void )
{
  return getInt( "tutorialLevel", "info" );
}

void Database::setLastTutorialFinished( bool state )
{
  QString stateString = state ? "1" : "0";
  QSqlQuery query( "UPDATE info SET lastTutorialFinished = " + stateString );
}

bool Database::getLastTutorialFinished( void )
{
  return getBool( "lastTutorialFinished", "info" );
}

void Database::setResetAllGames( bool state )
{
  QString stateString = state ? "1" : "0";
  QSqlQuery query( "UPDATE game SET resetGame = " + stateString );
}


QList< Item * > Database::getItems( void )
{
  QList< Item * > item;
  QSqlQuery query( "SELECT itemId, name, description, cost, isUnlocked FROM item ORDER BY itemId ASC" );
  while( query.next() )
  {
    Item *i = new Item;
    i->setId( query.value( 0 ).toInt() );
    i->setName( query.value( 1 ).toString() );
    i->setDescription( query.value( 2 ).toString() );
    i->setCost( query.value( 3 ).toInt() );
    i->setIsItemUnlocked( query.value( 4 ).toBool() );
    item << i;
  }
  return item;
}

void Database::setIsItemUnlocked( int itemId, bool state )
{
  QString stateString = ( state ? "1" : "0" );
  QSqlQuery query( "UPDATE item SET isUnlocked = " + stateString + " WHERE itemId = " + QString::number( itemId ) );
}

QList< ItemGame * > Database::getItemGames( void )
{
  QList< ItemGame * > itemGame;
  QSqlQuery itemGameQuery( "SELECT itemId, gameId, move FROM item_game" );
  while( itemGameQuery.next() )
  {
    QSqlQuery itemQuery( "SELECT name, description, cost, isUnlocked FROM item WHERE itemId = " + itemGameQuery.value( 0 ).toString() );
    itemQuery.first();
    Item *i = new Item;
    i->setId( itemGameQuery.value( 0 ).toInt() );
    i->setName( itemQuery.value( 0 ).toString() );
    i->setDescription( itemQuery.value( 1 ).toString() );
    i->setCost( itemQuery.value( 2 ).toInt() );
    i->setIsItemUnlocked( itemQuery.value( 3 ).toBool() );
    ItemGame *iG = new ItemGame( i, itemGameQuery.value( 1 ).toInt(), itemGameQuery.value( 2 ).toInt() );
    itemGame << iG;
  }
  return itemGame;
}

void Database::setItemGameMove( int itemId, int gameId, int move )
{
  QSqlQuery query( "UPDATE item_game SET move = " + QString::number( move ) + " WHERE itemId = " + QString::number( itemId ) + " AND gameId = " + QString::number( gameId ) );
}

QList< Challenge * > Database::getChallenges( void )
{
  QList< Challenge * > challenge;
  QSqlQuery query( "SELECT challengeId, gameId, challengeText, isCompleted, scoreTarget, moveTarget, objectTarget, tileValueTarget, difficulty, rewardXP FROM challenge ORDER BY challengeId ASC" );
  while( query.next() )
  {
    challenge << new Challenge( query.value( 0 ).toInt(),
                                query.value( 1 ).toInt(),
                                query.value( 2 ).toString(),
                                query.value( 3 ).toBool(),
                                query.value( 4 ).toInt(),
                                query.value( 5 ).toInt(),
                                query.value( 6 ).toInt(),
                                query.value( 7 ).toInt(),
                                query.value( 8 ).toInt(),
                                query.value( 9 ).toInt() );
  }
  return challenge;
}

void Database::setIsChallengeCompleted( int challengeId, bool state )
{
  QString stateString = ( state ? "1" : "0" );
  QSqlQuery query( "UPDATE challenge SET isCompleted = " + stateString + " WHERE challengeId = " + QString::number( challengeId ) );
}
