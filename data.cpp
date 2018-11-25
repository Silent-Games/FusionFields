#include "data.h"

Data *Data::data = nullptr;

Data::Data( void )
{
  //game
  game = db.getGames();
  //info
  highscore = db.getHighScore();
  highestTileValue = db.getHighestTileValue();
  itemSlot << db.getItem1() << db.getItem2();
  level = db.getLevel();
  xp = db.getXP();
  isSoundMuted = db.getIsSoundMuted();
  tutorialLevel = db.getTutorialLevel();
  lastTutorialFinished = db.getLastTutorialFinished();
  //item
  item = db.getItems();
  itemGame = db.getItemGames();
  //challenge
  challenge = db.getChallenges();
}

Data *Data::getData( void )
{
  if( data == nullptr )
    data = new Data();
  return data;
}

void Data::saveGame( void )
{
  for( int i = 0; i < game.length(); i++ )
    db.setGame( game[ i ] );
  for( int i = 0; i < itemGame.length(); i++ )
    db.setItemGameMove( itemGame[ i ]->getItemId(), itemGame[ i ]->getGameId(), itemGame[ i ]->getMove() );
  qDebug() << "Games saved";
}

void Data::saveGame( int gameId )
{
  for( int i = 0; i < game.length(); i++ )
    if( game[ i ]->getId() == gameId )
    {
      db.setGame( game[ i ] );
      break;
    }
  for( int iG = 0; iG < itemGame.length(); iG++ )
    if( itemGame[ iG ]->getGameId() == gameId )
      db.setItemGameMove( itemGame[ iG ]->getItemId(), itemGame[ iG ]->getGameId(), itemGame[ iG ]->getMove() );
  qDebug() << "Game saved (" << gameId << ")";
}

void Data::saveInfo( void )
{
  db.setHighScore( highscore );
  db.setHighestTileValue( highestTileValue );
  db.setItem1( itemSlot[ 0 ] );
  db.setItem2( itemSlot[ 1 ] );
  db.setLevel( level );
  db.setXP( xp );
  db.setIsSoundMuted( isSoundMuted );
  db.setTutorialLevel( tutorialLevel );
  db.setLastTutorialFinished( lastTutorialFinished );
  qDebug() << "Info saved";
}

void Data::saveItem( void )
{
  for( int i = 0; i < item.length(); i++ )
    db.setIsItemUnlocked( item[ i ]->getId(), item[ i ]->isItemUnlocked() );
  qDebug() << "Item saved";
}

void Data::saveChallenge( void )
{
  for( int i = 0; i < challenge.length(); i++ )
    db.setIsChallengeCompleted( challenge[ i ]->getId(), challenge[ i ]->isChallengeCompleted() );
  qDebug() << "Challenges saved";
}

void Data::saveChallenge( int challengeId )
{
  for( int i = 0; i < challenge.length(); i++ )
    if( challenge[ i ]->getId() == challengeId )
    {
      db.setIsChallengeCompleted( challenge[ i ]->getId(), challenge[ i ]->isChallengeCompleted() );
      break;
    }
  qDebug() << "Challenge saved (" << challengeId << ")";
}

void Data::save( void )
{
  saveGame();
  saveInfo();
  saveItem();
  saveChallenge();
}

void Data::updateGames( Game *game )
{
  for( int i = 0; i < this->game.length(); i++ )
    if( this->game[ i ]->getId() == game->getId() )
    {
      this->game[ i ] = game;
      break;
    }
}

Game *Data::getGame( int id )
{
  for( int i = 0; i < game.length(); i++ )
  {
    if( game[ i ]->getId() == id )
      return game[ i ];
  }
}

void Data::addXP( int xp )
{
  this->xp += xp;
}

void Data::setResetAllGame( bool state )
{
  for( int i = 0; i < game.length(); i++ )
    game[ i ]->setResetGame( true );
  db.setResetAllGames( state );
}

Item *Data::getItem( int id )
{
  for( int i = 0; i < item.length(); i++ )
    if( item[ i ]->getId() == id )
      return item[ i ];
}

QList< ItemGame* > Data::getItemGames( int gameId )
{
  QList< ItemGame* > itemGame;
  for( int i = 0; i < this->itemGame.length(); i++ )
    if( this->itemGame[ i ]->getGameId() == gameId )
      itemGame << this->itemGame[ i ];
  return itemGame;
}

void Data::updateItemGames( QList< ItemGame* > itemGames )
{
  for( int i = 0; i < itemGames.length(); i++ )
    for( int x = 0; x < itemGame.length(); x++ )
      if( itemGames[ i ]->getItemId() == itemGame[ x ]->getItemId() && itemGames[ i ]->getGameId() == itemGame[ x ]->getGameId() )
      {
        itemGame[ x ] = itemGames[ i ];
        break;
      }
}

Challenge *Data::getChallenge( int id )
{
  for( int i = 0; i < challenge.length(); i++ )
    if( challenge[ i ]->getId() == id )
      return challenge[ i ];
}

Challenge *Data::getChallengeWithNr( int nr )
{
  for( int i = 0; i < challenge.length(); i++ )
    if( challenge[ i ]->getNr() == nr )
      return challenge[ i ];
}

int Data::getNumberOfCompletedChallenges( void )
{
  int numberOfCompletedChallenges = 0;
  for( int i = 0; i < challenge.length(); i++ )
    if( challenge[ i ]->isChallengeCompleted() )
      numberOfCompletedChallenges++;
  return numberOfCompletedChallenges;
}
