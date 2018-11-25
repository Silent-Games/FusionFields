#include "challenge.h"

Challenge::Challenge( void ) : id( -1 ), gameId( -1 ), challengeText( "" ), isCompleted( false ), scoreTarget( 0 ), moveTarget( 0 ), objectTarget( 0 ), difficulty( 0 )
{
}

Challenge::Challenge( int id, int gameId, QString challengeText, bool isCompleted, int scoreTarget, int moveTarget, int objectTarget, int tileValueTarget, int difficulty, int rewardXP, QWidget *parent ) : QWidget( parent )
{
  this->id = id;
  this->gameId = gameId;
  this->challengeText = challengeText;
  this->isCompleted = isCompleted;
  this->scoreTarget = scoreTarget;
  this->moveTarget = moveTarget;
  this->objectTarget = objectTarget;
  this->tileValueTarget = tileValueTarget;
  this->difficulty = difficulty;
  this->rewardXP = rewardXP;
}

int Challenge::getNr( void )
{
  return id + 1;
}

int Challenge::getId( void )
{
  return id;
}

void Challenge::setId( int id )
{
  this->id = id;
}

int Challenge::getGameId( void )
{
  return gameId;
}

void Challenge::setGameId( int gameId )
{
  this->gameId = gameId;
}

QString Challenge::getChallengeText( void )
{
  return challengeText;
}

void Challenge::setCompleted( bool state )
{
  isCompleted = state;
}

bool Challenge::isChallengeCompleted( void )
{
  return isCompleted;
}

int Challenge::getScoreTarget( void )
{
  return scoreTarget;
}

int Challenge::getMoveTarget( void )
{
  return moveTarget;
}

int Challenge::getObjectTarget( void )
{
  return objectTarget;
}

int Challenge::getTileValueTarget()
{
  return tileValueTarget;
}

int Challenge::getDifficulty( void )
{
  return difficulty;
}

int Challenge::getRewardXP( void )
{
  return rewardXP;
}

void Challenge::paintEvent( QPaintEvent * )
{

}
