#include "savedatathread.h"

SaveDataThread::SaveDataThread( void )
{
  whatSaving = All;
  clear();
}

void SaveDataThread::run( void )
{
  int wS = whatSaving;
  if( wS % 2 == 1 )
  {
    if( gameId >= 0) Data::getData()->saveGame( gameId );
    else Data::getData()->saveGame();
  }

  wS = whatSaving;
  if( ( wS >> 1 ) % 2 == 1 )
  {
    Data::getData()->saveInfo();
  }

  wS = whatSaving;
  if( ( wS >> 2 ) % 2 == 1 )
  {
    Data::getData()->saveItem();
  }

  wS = whatSaving;
  if( ( wS >> 3 ) % 2 == 1 )
  {
    if( challengeId >= 0 ) Data::getData()->saveChallenge( challengeId );
    else Data::getData()->saveChallenge();
  }
}

void SaveDataThread::setGameId( int gameId )
{
  if( gameId >= 0 ) this->gameId = gameId;
}

void SaveDataThread::setChallengeId( int challengeId )
{
  if( challengeId >= 0 ) this->challengeId = challengeId;
}

void SaveDataThread::setWhatSaving( int whatSaving )
{
  this->whatSaving = whatSaving;
}

void SaveDataThread::clear()
{
  gameId = -1;
  challengeId = -1;
}
