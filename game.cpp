#include "game.h"

QList< int > Game::generateField( int fieldWidth, int fieldHeight )
{
  QList< int > field;
  for( int i = 0; i < fieldWidth * fieldHeight; i++ )
  {
    int randValue = qrand() % 2 + 1;
    field << randValue;
  }
  return field;
}

bool Game::isFieldIndexCorrect( int fieldIndex )
{
  if( fieldIndex < field.length() && fieldIndex >= 0 )
    return true;
  return false;
}

int Game::getRandomNextTile( void )
{
  int maxValue = 2;
  if( score >= 1500 )
    maxValue = 4;
  else if( score >= 500 )
    maxValue = 3;
  return qrand() % maxValue + 1;
}

int Game::getRandomTileIndex( void )
{
  int tileIndex;
  do
  {
    tileIndex = qrand() % field.length();
  }while( tileIndex == fusionPointTileIndex || tileIndex == objectTileIndex );
  return tileIndex;
}

int Game::getRandomFusionPointTileIndex()
{
  int tileIndex = -1;
  if( fusionPointState && qrand() % 10 < 1 ) tileIndex = getRandomTileIndex();
  return tileIndex;
}

int Game::setObjectTileIndex( void )
{
  if( qrand() % 5 == 0 )
    objectTileIndex = getRandomTileIndex();
  else
    objectTileIndex = -1;
}

Game::Game( QObject *parent ) : QObject( parent ),
  fieldWidth( 5 ), fieldHeight( 5 ), score( 0 ), move( 0 ), nextTile( getRandomNextTile() ),
  objectState( false ), object( 0 ), objectTileIndex( -1 ), challenge( new Challenge() ), resetGame( false )
{
  qsrand( time( 0 ) );
}

Game::Game( int id, QList< int > field, int score, int fusionPoints, int fusionPointTileIndex, int move, int nextTile, int object, int objectTileIndex, bool resetGame )
{
  this->id = id;
  setFieldSize( 5, 5 );
  setField( field );
  this->score = score;
  this->fusionPoints = fusionPoints;
  this->fusionPointTileIndex = fusionPointTileIndex;
  this->move = move;
  this->nextTile = nextTile;
  this->object = object;
  this->objectTileIndex = objectTileIndex;
  setResetGame( resetGame );
}

int Game::getId( void )
{
  return id;
}

QList< int > Game::getField( void )
{
  return field;
}

void Game::setFieldSize( int fieldWidth, int fieldHeight )
{
  if( fieldWidth > 0 )
    this->fieldWidth = fieldWidth;
  if( fieldHeight > 0 )
    this->fieldHeight = fieldHeight;
}

int Game::getFieldWidth( void )
{
  return fieldWidth;
}

int Game::getFieldHeight( void )
{
  return fieldHeight;
}

void Game::setField( QList< int > newField )
{
  if( newField.length() == fieldWidth * fieldHeight )
    field = newField;
}

int Game::getAboveNeighbor( int fieldIndex )
{
  if( fieldIndex - fieldWidth < 0 )
    return -1;
  return fieldIndex - fieldWidth;
}

int Game::getRightNeighbor( int fieldIndex )
{
  if( ( fieldIndex + 1 ) % fieldWidth == 0 )
    return -1;
  return fieldIndex + 1;
}

int Game::getBelowNeighbor( int fieldIndex )
{
  if( fieldIndex + fieldWidth > field.length() - 1 )
    return -1;
  return fieldIndex + fieldWidth;
}

int Game::getLeftNeighbor( int fieldIndex )
{
  if( fieldIndex % fieldWidth == 0 )
    return -1;
  return fieldIndex - 1;
}

QList< int > Game::getNeighbors( int fieldIndex )
{
  if( !( fieldIndex > field.length() - 1 || fieldIndex < 0 ) )
  {
    QList< int > neighbors;
    neighbors << getAboveNeighbor( fieldIndex )
              << getRightNeighbor( fieldIndex )
              << getBelowNeighbor( fieldIndex )
              << getLeftNeighbor( fieldIndex );
    neighbors.removeAll( -1 );
    return neighbors;
  }
}

QList< int > Game::getNeighborsWithSameValue( int fieldIndex )
{
  QList< int > neighbors;
  if( isFieldIndexCorrect( fieldIndex ) )
  {
    neighbors = getNeighbors( fieldIndex );
    int value = field[ fieldIndex ];
    for( int i = neighbors.length() - 1; i >= 0; i-- )
      if( field[ neighbors[ i ] ] != value )
        neighbors.removeAll( neighbors[ i ] );
  }
  return neighbors;
}

bool Game::isGameFinished( void )
{
  bool existNeighbors = false;
  for( int i = 0; i < field.length(); i++ )
    if( !getNeighborsWithSameValue( i ).isEmpty() )
      existNeighbors = true;

  if( score < 0 || !existNeighbors || isChallengeLose() || isChallengeWon() )
    return true;

  return false;
}

bool Game::mergeTiles( int fromTileIndex, int toTileIndex )
{
  if( !isFieldIndexCorrect( fromTileIndex ) || !isFieldIndexCorrect( toTileIndex ) )
    return false;
  QList< int > neighbors = getNeighborsWithSameValue( fromTileIndex );
  if( !neighbors.contains( toTileIndex ) )
    return false;
  field[ fromTileIndex ] = nextTile;
  field[ toTileIndex ] += 1;
  //FusionPoints
  if( toTileIndex == fusionPointTileIndex )
    fusionPoints++;
  //Object
  if( objectState )
  {
    if( toTileIndex == objectTileIndex )
    {
      object++;
      objectTileIndex = -1;
    }
    if( objectTileIndex == -1 )
      setObjectTileIndex();
  }

  score += field[ toTileIndex ];
  nextTile = getRandomNextTile();

  return true;
}

int Game::getScore( void ) const
{
  return score;
}

void Game::setFusionPointState( bool state )
{
  fusionPointState = state;
}

bool Game::isFusionPoint( void )
{
  return fusionPointState;
}

int Game::getFusionPoints( void )
{
  return fusionPoints;
}

int Game::getFusionPointTileIndex( void )
{
  return fusionPointTileIndex;
}

int Game::getMove( void ) const
{
  return move;
}

int Game::getNextTile( void ) const
{
  return nextTile;
}

int Game::getObject( void )
{
  return object;
}

int Game::getObjectTileIndex( void )
{
  return objectTileIndex;
}

void Game::setResetGame( bool state )
{
  this->resetGame = state;
}

bool Game::getResetGame( void )
{
  return resetGame;
}

int Game::getItemCost( int itemId )
{
  for( int i = 0; i < itemGame.length(); i++ )
    if( itemGame[ i ]->getItemId() == itemId )
      return itemGame[ i ]->getItemCost();
}

void Game::setChallenge( Challenge *challenge )
{
  this->challenge = challenge;
  objectState = challenge->getObjectTarget() > 0 ? true : false;
  if( objectState && objectTileIndex == -1 )
      setObjectTileIndex();
}

Challenge *Game::getChallenge( void )
{
  return challenge;
}

bool Game::isChallengeWon( void )
{
  if( challenge->getId() < 0 )
    return false;
  if( challenge->getMoveTarget() > 0 && move > challenge->getMoveTarget() )
    return false;
  if( challenge->getScoreTarget() > 0 && score < challenge->getScoreTarget() )
    return false;
  if( challenge->getObjectTarget() > 0 && object < challenge->getObjectTarget() )
    return false;
  if( challenge->getTileValueTarget() > 0 && getHighestTileValue() < challenge->getTileValueTarget() )
    return false;
  return true;
}

bool Game::isChallengeLose( void )
{
  if( challenge->getId() < 0 )
    return false;
  if( isChallengeWon() )
    return false;
  if( challenge->getMoveTarget() > 0 && move >= challenge->getMoveTarget() )
    return true;
  return false;
}

bool Game::swapTiles( int fromTileIndex, int toTileIndex )
{
  if( !isFieldIndexCorrect( fromTileIndex ) || !isFieldIndexCorrect( toTileIndex ) )
    return false;
  QList< int > neighbors = getNeighbors( fromTileIndex );
  if( !neighbors.contains( toTileIndex ) )
    return false;

  int toTileValue = field[ toTileIndex ];
  field[ toTileIndex ] = field[ fromTileIndex ];
  field[ fromTileIndex ] = toTileValue;

  fusionPoints -= getItemCost( SWAPITEM );
  setItemGameMove( SWAPITEM, getItemGameMove( SWAPITEM ) + 1 );

  return true;
}

void Game::reset( void )
{
  field = generateField( fieldWidth, fieldHeight );
  score = 0;
  fusionPoints = 0;
  fusionPointTileIndex = getRandomFusionPointTileIndex();
  move = 0;
  nextTile = getRandomNextTile();
  object = 0;
  if( objectState )
    setObjectTileIndex();
  for( int i = 0; i < itemGame.length(); i++ )
    itemGame[ i ]->setMove( 0 );
}

bool Game::increaseTile( int tileIndex )
{
  if( !isFieldIndexCorrect( tileIndex ) )
    return false;

  field[ tileIndex ] += 1;

  fusionPoints -= getItemCost( INCREASEITEM );
  setItemGameMove( INCREASEITEM, getItemGameMove( INCREASEITEM ) + 1 );

  return true;
}

bool Game::decreaseTile( int tileIndex )
{
  if( !isFieldIndexCorrect( tileIndex ) )
    return false;
  if( field[ tileIndex ] <= 0 )
    return false;

  field[ tileIndex ] -= 1;

  fusionPoints -= getItemCost( DECREASEITEM );
  setItemGameMove( DECREASEITEM, getItemGameMove( DECREASEITEM ) + 1 );

  return true;
}

bool Game::setTileValueToRandom( int tileIndex )
{
  if( !isFieldIndexCorrect( tileIndex ) )
    return false;

  field[ tileIndex ] = qrand() % field[ tileIndex ] + 1;

  fusionPoints -= getItemCost( RANDOMITEM );
  setItemGameMove( RANDOMITEM, getItemGameMove( RANDOMITEM ) + 1 );

  return true;
}

bool Game::setNewNextTile(int tileIndex)
{
  if( !isFieldIndexCorrect( tileIndex ) )
    return false;

  nextTile = field[ tileIndex ];

  fusionPoints -= getItemCost( NEWNEXTTILEITEM );
  setItemGameMove( NEWNEXTTILEITEM, getItemGameMove( NEWNEXTTILEITEM ) + 1 );

  return true;
}

void Game::setItemGameMove( int itemId, int move )
{
  for( int i = 0; i < itemGame.length(); i++ )
    if( itemGame[ i ]->getItemId() == itemId )
      itemGame[ i ]->setMove( move );
}

int Game::getItemGameMove( int itemId )
{
  for( int i = 0; i < itemGame.length(); i++ )
    if( itemGame[ i ]->getItemId() == itemId )
      return itemGame[ i ]->getMove();
}

bool Game::doMove( int item, QList< int > tileIndex )
{
  if( tileIndex.length() != 2 ) return false;
  bool ok = false;
  switch( item )
  {
    case SWAPITEM: ok = swapTiles( tileIndex[ 0 ], tileIndex[ 1 ] ); break;
    case INCREASEITEM: ok = increaseTile( tileIndex[ 0 ] ); break;
    case DECREASEITEM: ok = decreaseTile( tileIndex[ 0 ] ); break;
    case RANDOMITEM: ok = setTileValueToRandom( tileIndex[ 0 ] ); break;
    case NEWNEXTTILEITEM: ok = setNewNextTile( tileIndex[ 0 ] ); break;
    case LOCKED:
    case UNLOCKED:
    case NOITEM:
    default: ok = mergeTiles( tileIndex[ 0 ], tileIndex[ 1 ] ); break;
  }
  if( !ok ) return ok;
  move++;
  fusionPointTileIndex = getRandomFusionPointTileIndex();
  return ok;
}

int Game::getHighestTileValue( void )
{
  int highestValue = 0;
  for( int i = 0; i < field.length(); i++ )
  {
    if( field[ i ] > highestValue )
      highestValue = field[ i ];
  }
  return highestValue;
}

void Game::setItemGames( QList< ItemGame * > itemGame )
{
  this->itemGame = itemGame;
}

QList< ItemGame * > Game::getItemGames( void )
{
  return itemGame;
}
