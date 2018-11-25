#include "tutorial2.h"

const int labelIndex = 0;
const int label2Index = 1;
const int gameFieldIndex = 2;
const int boardIndex = 3;
const int buttonIndex = 4;

void Tutorial2::showStep0()
{
  layoutItemRect[ labelIndex ] = QRect( QPoint( 0, 0 ), QSize( width(), height() * 0.5 ) );
  layoutItemRect[ label2Index ] = QRect( QPoint( 0, height() * 0.5 ), QSize( width(), height() * 0.4 ) );
  layoutItemRect[ buttonIndex ] = QRect( QPoint( 0, height() * 0.9 ), QSize( width(), height() * 0.1 ) );
  layoutItemRect[ gameFieldIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
  layoutItemRect[ boardIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
}

void Tutorial2::showStep1( void )
{
  layoutItemRect[ labelIndex ] = QRect( QPoint( 0, 0 ), QSize( width(), height() * 0.5 ) );
  layoutItemRect[ gameFieldIndex ] = QRect( QPoint( 0, height() * 0.5 ), QSize( width(), height() * 0.5 ) );
  layoutItemRect[ buttonIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
  layoutItemRect[ label2Index ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
  layoutItemRect[ boardIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
}

void Tutorial2::showStep2( void )
{
  layoutItemRect[ labelIndex ] = QRect( QPoint( 0, 0 ), QSize( width(), height() * 0.5 ) );
  layoutItemRect[ label2Index ] = QRect( QPoint( 0, height() * 0.5 ), QSize( width(), height() * 0.4 ) );
  layoutItemRect[ buttonIndex ] = QRect( QPoint( 0, height() * 0.9 ), QSize( width(), height() * 0.1 ) );
  layoutItemRect[ gameFieldIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
  layoutItemRect[ boardIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
}

void Tutorial2::showStep3( void )
{
  layoutItemRect[ labelIndex ] = QRect( QPoint( 0, 0 ), QSize( width(), height() * 0.9 ) );
  layoutItemRect[ buttonIndex ] = QRect( QPoint( 0, height() * 0.9 ), QSize( width(), height() * 0.1 ) );
  layoutItemRect[ boardIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
  layoutItemRect[ gameFieldIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
  layoutItemRect[ label2Index ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
}

Tutorial2::Tutorial2( QWidget *parent ) : QWidget( parent )
{
  step = -1;
  mainLayout = new QVBoxLayout( this );

  label = new Label( "", 25 );
  mainLayout->addWidget( label );
  layoutItemRect << QRect( 0, 0, 0, 0 );

  label2 = new Label( "", 25 );
  mainLayout->addWidget( label2 );
  layoutItemRect << QRect( 0, 0, 0, 0 );

  Challenge *challenge = new Challenge();
  challenge->setGameId( HIGHSCOREGAMEID );
  game = Data::getData()->getGame( challenge->getGameId() );
  game->setChallenge( challenge );
  game->setFusionPointState( true );
  game->reset();

  gameField = new GameField();
  gameField->setGame( game );
  connect( gameField, SIGNAL( move( QList< int > ) ), this, SLOT( move( QList< int > ) ) );
  mainLayout->addWidget( gameField );
  layoutItemRect << QRect( 0, 0, 0, 0 );

  board = new Board();
  board->setCaption( true );
  board->setGame( game );
  mainLayout->addWidget( board );
  layoutItemRect << QRect( 0, 0, 0, 0 );

  button = new Button();
  button->setHeightWidthRatio( 6 );
  button->setTextColor( WHITE );
  button->setColors( TRANSPARENTC, TRANSPARENTBLACK );
  connect( button, SIGNAL( clicked() ), this, SLOT( showNextStep() ) );
  mainLayout->addWidget( button );
  layoutItemRect << QRect( 0, 0, 0, 0 );

  timer = new QTimer();
  connect( timer, SIGNAL( timeout() ), this, SLOT( showNextStep() ) );

  showNextStep();
}

void Tutorial2::showNextStep( void )
{
  step++;
  switch( step )
  {
    case 0:
      label->setText( tr( "In between, a FusionPoint appears." ) );
      label2->setImage( Config::getConfig()->FUSIONPOINTSIMAGE );
      button->setText( tr( "Continue" ) );
      showStep0();
      break;
    case 1:
      label->setText( tr( "Collect a FusionPoint." ) );
      showStep2();
      gameField->animate();
      break;
    case 2:
      label->setText( tr( "You need FusionPoints to use items. Used correctly, items make the game easier." ) );
      label2->setImage( Config::getConfig()->ITEMSIMAGE );
      button->setText( tr( "Continue" ) );
      showStep1();
      break;
    case 3:
      label->setText( tr( "Under the menu entry \"Items\" you can select items that you should have during a game available." ) );
      showStep3();
      button->setText( tr( "Finish" ) );
      break;
    default:
      emit tutorialFinished();
      break;
  }
  update();
  timer->stop();
}

void Tutorial2::move( QList< int > selectedTileIndex )
{
  if( !game->doMove( NOITEM, selectedTileIndex ) )
    return;
  if( game->isGameFinished() )
    game->reset();
  gameField->update();
  board->update();
  switch( step )
  {
    case 1:
      if( game->getFusionPoints() > 0 )
      {
        label->setText( tr( "Great!" ) );
        if( !timer->isActive() )
          timer->start( 1000 );
      }
      break;
  }
}

void Tutorial2::paintEvent( QPaintEvent * )
{
  switch( step )
  {
    case 0:
      showStep0();
      break;
    case 1:
      showStep1();
      break;
    case 2:
      showStep2();
      break;
    case 3:
      showStep3();
      break;
  }
  for( int i = 0; i < layoutItemRect.length(); i++ )
    mainLayout->itemAt( i )->setGeometry( layoutItemRect[ i ] );
}
