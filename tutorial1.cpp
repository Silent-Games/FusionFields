#include "tutorial1.h"

const int labelIndex = 0;
const int gameFieldIndex = 1;
const int boardIndex = 2;
const int buttonIndex = 3;

void Tutorial1::showStep0()
{
  layoutItemRect[ labelIndex ] = QRect( QPoint( 0, 0 ), QSize( width(), height() * 0.5 ) );
  layoutItemRect[ gameFieldIndex ] = QRect( QPoint( 0, height() * 0.5 ), QSize( width(), height() * 0.5 ) );
  layoutItemRect[ boardIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
  layoutItemRect[ buttonIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
}

void Tutorial1::showStep1()
{
  layoutItemRect[ boardIndex ] = QRect( QPoint( 0, 0 ), QSize( width(), height() * 0.4 ) );
  layoutItemRect[ labelIndex ] = QRect( QPoint( 0, height() * 0.4 ), QSize( width(), height() * 0.5 ) );
  layoutItemRect[ buttonIndex ] = QRect( QPoint( 0, height() * 0.9 ), QSize( width(), height() * 0.1 ) );
  layoutItemRect[ gameFieldIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
}

void Tutorial1::showStep2()
{
  layoutItemRect[ boardIndex ] = QRect( QPoint( 0, 0 ), QSize( width(), height() * 0.4 ) );
  layoutItemRect[ gameFieldIndex ] = QRect( QPoint( 0, height() * 0.4 ), QSize( width(), height() * 0.6 ) );
  layoutItemRect[ buttonIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
  layoutItemRect[ labelIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
}

void Tutorial1::showStep3()
{
  layoutItemRect[ labelIndex ] = QRect( QPoint( 0, 0 ), QSize( width(), height() * 0.9 ) );
  layoutItemRect[ buttonIndex ] = QRect( QPoint( 0, height() * 0.9 ), QSize( width(), height() * 0.1 ) );
  layoutItemRect[ boardIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
  layoutItemRect[ gameFieldIndex ] = QRect( QPoint( 0, 0 ), QSize( 0, 0 ) );
}

Tutorial1::Tutorial1( QWidget *parent ) : QWidget( parent )
{
  step = -1;
  mainLayout = new QVBoxLayout( this );

  label = new Label( "", 25 );
  mainLayout->addWidget( label );
  layoutItemRect << QRect( 0, 0, 0, 0 );

  Challenge *challenge = new Challenge();
  challenge->setGameId( HIGHSCOREGAMEID );
  game = Data::getData()->getGame( challenge->getGameId() );
  game->setChallenge( challenge );
  game->setFusionPointState( false );
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

Tutorial1::~Tutorial1()
{
}

void Tutorial1::showNextStep( void )
{
  step++;
  switch( step )
  {
    case 0:
      label->setText( tr( "Fusion two equally adjacent fields." ) );
      showStep0();
      gameField->animate();
      break;
    case 1:
      label->setText( tr( "The overview shows all information about the current game." ) );
      button->setText( tr( "Continue" ) );
      showStep1();
      board->animate();
      break;
    case 2:
      showStep2();
      gameField->animate();
      break;
    case 3:
      label->setText( tr( "Tutorial completed!\r\n\r\nThe game is automatically saved in between or when you call up the menu!" ) );
      button->setText( tr( "Finish" ) );
      showStep3();
      break;
    default:
      emit tutorialFinished();
      break;
  }
  update();
  timer->stop();
}

void Tutorial1::move( QList< int > selectedTileIndex )
{
  if( !game->doMove( NOITEM, selectedTileIndex ) )
    return;
  gameField->update();
  board->update();
  switch( step )
  {
    case 0:
      label->setText( tr( "Perfect!" ) );
      if( !timer->isActive() )
        timer->start( 1000 );
      break;
    case 2:
      if( !timer->isActive() )
        timer->start( 1000 );
      break;
  }
}

void Tutorial1::paintEvent( QPaintEvent * )
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
