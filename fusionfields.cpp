#include "fusionfields.h"

const int CHALLENGETASK = 0;
const int GAME = 1;
const int GAMEFINISHED = 2;

void FusionFields::saveData( void )
{
  Data::getData()->updateGames( game );
  Data::getData()->updateItemGames( game->getItemGames() );
  controller->saveData( SaveDataThread::Game | SaveDataThread::Info, game->getId() );
}

FusionFields::FusionFields( Challenge *challenge, Controller *controller, QWidget *parent ) : QWidget( parent )
{
  setupUi( this );
  this->controller = controller;
  this->challenge = challenge;

  //MenuButton
  QImage menuImg;
  menuImg.load( ":/Images/Images/menu.png" );
  btnMenu->setImage( menuImg );
  btnMenu->setHeightWidthRatio( 2 );
  btnMenu->setTextColor( WHITE );
  btnMenu->setColors( TRANSPARENTC, TRANSPARENTBLACK );

  //RestartButton
  QImage restartImg;
  restartImg.load( ":/Images/Images/restart.png" );
  btnRestart->setImage( restartImg );
  btnRestart->setHeightWidthRatio( 2 );
  btnRestart->setTextColor( WHITE );
  btnRestart->setColors( TRANSPARENTC, TRANSPARENTBLACK );

  //Notification
  QString gameModeText = challenge->getId() >= 0 ? tr( "Challenge " ) + QString::number( challenge->getNr() ) : tr( "Highscore" );
  notification->setGameModeText( gameModeText );

  //Game
  game = Data::getData()->getGame( challenge->getGameId() );
  if( game->getResetGame() )
  {
    game->reset();
    game->setResetGame( false );
  }
  game->setChallenge( challenge );
  game->setFusionPointState( false );
  game->setItemGames( Data::getData()->getItemGames( challenge->getGameId() ) );

  //ItemBoard
  itemBoard->setHidden( true );
  for( int i = 0; i < Data::getData()->itemSlot.length(); i++ )
    if( Data::getData()->itemSlot[ i ] != LOCKED )
    {
      itemBoard->setHidden( false );
      game->setFusionPointState( true );
      itemBoard->setGame( game );
      itemBoard->setItems( Data::getData()->itemSlot );
      break;
    }

  //GameField
  gameField->setGame( game );

  //Board
  board->setGame( game );
  QSizePolicy sp( QSizePolicy::Preferred, QSizePolicy::Preferred );
  sp.setVerticalStretch( 3 );
  board->setSizePolicy( sp );
  board->setChallenge( challenge );

  //EndButton
  btnNav->setTextColor( WHITE );
  btnNav->setColors( TRANSPARENTC, TRANSPARENTBLACK );

  //Current GameState
  if( game->isGameFinished() )
  {
    restart();
    setFusionFieldsWidgetsHidden( GAME );
  }
  else if( challenge->getId() >= 0 )
  {
    btnNav->setImage( Config::getConfig()->PLAYIMAGE );
    setFusionFieldsWidgetsHidden( CHALLENGETASK );
  }
  else
  {
    setFusionFieldsWidgetsHidden( GAME );
  }

  //Sound
  moveSound = new QMediaPlayer;
  moveSound->setMedia( QUrl( Config::getConfig()->MOVESOUNDFILE ) );

  connect( btnMenu, SIGNAL( clicked() ), controller, SLOT( showMenu() ) );
  connect( btnRestart, SIGNAL( clicked() ), this, SLOT( restart() ) );
  connect( gameField, SIGNAL( move( QList< int > ) ), this, SLOT( move( QList< int > ) ) );
  connect( itemBoard, SIGNAL( itemClicked( int ) ), this, SLOT( setActiveItem( int ) ) );
  connect( btnNav, SIGNAL( clicked() ), this, SLOT( gameEndButtonSlot() ) );
}

FusionFields::~FusionFields( void )
{
  saveData();
}

void FusionFields::gameEndButtonSlot( void )
{
  if( game->isChallengeWon() )
    controller->showFusionFields( Data::getData()->getChallengeWithNr( challenge->getNr() + 1 ) );
  else if( game->getChallenge()->getId() >= 0 && !game->isGameFinished() )
    setFusionFieldsWidgetsHidden( GAME );
  else restart();
}

void FusionFields::move( QList< int > selectedTileIndex )
{
  //Spielzug
  if( !game->doMove( activeItem, selectedTileIndex ) ) return;
  activeItem = NOITEM;
  itemBoard->setSelectedItem( NOITEM );

  //Sound
  if( !Data::getData()->isSoundMuted )
    moveSound->play();

  //Update
  gameField->update();
  board->update();
  itemBoard->update();
  if( game->getScore() > Data::getData()->highscore )
    Data::getData()->highscore = game->getScore();
  if( game->getHighestTileValue() > Data::getData()->highestTileValue )
    Data::getData()->highestTileValue = game->getHighestTileValue();

  //GameFinished
  if( game->isGameFinished() )
    finishGame();

  //AutoSave
  if( game->getMove() % 5 == 0 )
    saveData();
}

void FusionFields::restart( void )
{
  game->reset();
  gameField->update();
  board->update();
  itemBoard->update();
  itemBoard->setSelectedItem( NOITEM );
  setFusionFieldsWidgetsHidden( GAME );
  saveData();
}

void FusionFields::setActiveItem( int item )
{
  activeItem = item;
}

void FusionFields::checkLevelRewards( void )
{
  if( Data::getData()->level >= 1 )
  {
    if( Data::getData()->tutorialLevel == 1 )
    {
      Data::getData()->tutorialLevel = 2;
      Data::getData()->lastTutorialFinished = false;
    }
    if( Data::getData()->itemSlot[ 0 ] == LOCKED )
      Data::getData()->itemSlot[ 0 ] = UNLOCKED;

    if( !Data::getData()->getItem( RANDOMITEM )->isItemUnlocked() )
      Data::getData()->getItem( RANDOMITEM )->setIsItemUnlocked( true );

    controller->saveData( SaveDataThread::Info );
  }
  if( Data::getData()->level >= 2 )
  {
    if( Data::getData()->itemSlot[ 1 ] == LOCKED )
      Data::getData()->itemSlot[ 1 ] = UNLOCKED;

    if( !Data::getData()->getItem( SWAPITEM )->isItemUnlocked() )
      Data::getData()->getItem( SWAPITEM )->setIsItemUnlocked( true );

    controller->saveData( SaveDataThread::Item );
  }
  if( Data::getData()->level >= 3 )
  {
    if( !Data::getData()->getItem( INCREASEITEM )->isItemUnlocked() )
      Data::getData()->getItem( INCREASEITEM )->setIsItemUnlocked( true );

    controller->saveData( SaveDataThread::Item );
  }
  if( Data::getData()->level >= 4 )
  {
    if( !Data::getData()->getItem( DECREASEITEM )->isItemUnlocked() )
      Data::getData()->getItem( DECREASEITEM )->setIsItemUnlocked( true );

    controller->saveData( SaveDataThread::Item );
  }
  if( Data::getData()->level >= 5 )
  {
    if( !Data::getData()->getItem( NEWNEXTTILEITEM )->isItemUnlocked() )
      Data::getData()->getItem( NEWNEXTTILEITEM )->setIsItemUnlocked( true );

    controller->saveData( SaveDataThread::Item );
  }
}

void FusionFields::startChallenge( void )
{
  setFusionFieldsWidgetsHidden( GAME );
}

void FusionFields::finishGame( void )
{
  //BtnNav
  QString gameEndText = "Game Over";
  btnNav->setImage( Config::getConfig()->RESTARTIMAGE );
  if( game->isChallengeWon() )
  {
    QImage img( Config::getConfig()->ARROWIMAGE );
    QTransform transform;
    transform.rotate( 90 );
    img = img.transformed( transform );
    btnNav->setImage( img );
    gameEndText = tr( "Challenge Won" );
  }
  else if( challenge->getId() > 0 && !game->isChallengeWon() )
  {
    gameEndText = tr( "Challenge Lose" );
  }
  gameEndWidget->setValues( gameEndText, game->getScore(), game->getMove(), challenge->getObjectTarget() > 0 ? game->getObject() : -1 );

  QList< QString > other;
  //HighScore
  if( game->getScore() == Data::getData()->highscore )
    other << tr( "New Highscore" );

  //XP
  int scoreXP = game->getScore() / 10;
  int moveXP = scoreXP * ( ( double ) 1 - ( ( double ) game->getMove() / ( double ) game->getScore() ) );
  int fusionPointXP = game->getFusionPoints() * 2;
  int xp = scoreXP + moveXP + fusionPointXP;
  Data::getData()->addXP( xp );
  other << "+ " + QString::number( xp ) + " XP";

  //Challenge
  if( !game->getChallenge()->isChallengeCompleted() && game->isChallengeWon() )
  {
    int challengeXP = game->getChallenge()->getRewardXP();
    other << "+ " + QString::number( challengeXP ) + " XP";
    Data::getData()->getChallenge( game->getChallenge()->getId() )->setCompleted( true );
    controller->saveData( SaveDataThread::Challenge, -1, game->getChallenge()->getId() );
    Data::getData()->addXP( challengeXP );
    controller->saveData( SaveDataThread::Info );
  }

  if( Data::getData()->xp >= getMaxXPLevel( Data::getData()->level ) )
  {
    Data::getData()->xp -= getMaxXPLevel( Data::getData()->level );
    Data::getData()->level++;
    if( Data::getData()->level > 4 )
      other << tr( "Level Up" );
    else
      other << tr( "New Item" );
  }
  gameEndWidget->setOtherValues( other );

  checkLevelRewards();

  saveData();

  setFusionFieldsWidgetsHidden( GAMEFINISHED );
}

void FusionFields::setFusionFieldsWidgetsHidden( int widgetHiddenState )
{
  switch( widgetHiddenState )
  {
    case CHALLENGETASK:
      challengeTask->setHidden( false );
      challengeTask->setChallengeText( challenge->getChallengeText() );
      board->setHidden( true );
      itemBoard->setHidden( true );
      gameField->setHidden( true );
      gameEndWidget->setHidden( true );
      btnNav->setHidden( false );
      break;
    case GAME:
      challengeTask->setHidden( true );
      board->setHidden( false );
      itemBoard->setHidden( true );
      for( int i = 0; i < itemBoard->getItems().length(); i++ )
        if( itemBoard->getItems()[ i ] != LOCKED )
          itemBoard->setHidden( false );
      gameField->setHidden( false );
      gameEndWidget->setHidden( true );
      btnNav->setHidden( true );
      break;
    case GAMEFINISHED:
      challengeTask->setHidden( true );
      board->setHidden( true );
      itemBoard->setHidden( true );
      gameField->setHidden( true );
      gameEndWidget->setHidden( false );
      btnNav->setHidden( false );
      break;
  }
  challengeTask->animate();
  board->animate();
  itemBoard->animate();
  gameField->animate();
  gameEndWidget->animate();
}
