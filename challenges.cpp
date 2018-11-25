#include "challenges.h"

const int ROWCOUNT = 5;
const int COLUMNCOUNT = 4;

void Challenges::showButton( void )
{
  int btnIndex = btnChallenge.length() - animation->getTimerCount() - 1;
  btnChallenge[ btnIndex ]->setTextColor( WHITE );
  if( challenge[ btnIndex + controller->startChallengeNr - 1 ]->isChallengeCompleted() || challenge[ btnIndex + controller->startChallengeNr - 1 ]->getNr() == 1 ||
      ( ( btnIndex + controller->startChallengeNr - 1 ) > 0 && challenge[ btnIndex + controller->startChallengeNr - 1 - 1 ]->isChallengeCompleted() ) ||
      ( ( btnIndex + controller->startChallengeNr - 1 ) > 1 && challenge[ btnIndex + controller->startChallengeNr - 1 - 2 ]->isChallengeCompleted() ) )
  {
    btnChallenge[ btnIndex ]->setEnabled( true );
    btnChallenge[ btnIndex ]->setColors( challenge[ btnIndex + controller->startChallengeNr - 1 ]->isChallengeCompleted() ? SUCCESSGREEN : WHITE, TRANSPARENTBLACK );
    connect( btnChallenge[ btnIndex ], SIGNAL( clicked() ), this, SLOT( setSelectedChallenge() ) );
  }
  else
  {
    btnChallenge[ btnIndex ]->setColors( FAILURERED, TRANSPARENTBLACK );
    btnChallenge[ btnIndex ]->setEnabled( false );
  }
}

Challenges::Challenges( Controller *controller, QWidget *parent ) : QWidget( parent )
{
  this->controller = controller;
  QVBoxLayout *vLayout = new QVBoxLayout( this );
  //Challenges
  challengeLayout = new QGridLayout();
  challenge = Data::getData()->challenge;
  for( int r = 0, i = 0; r < ROWCOUNT; r++ )
  {
    for( int c = 0; c < COLUMNCOUNT; c++, i++ )
    {
      if( i + controller->startChallengeNr - 1 >= challenge.length() ) break;
      btnChallenge << new Button( QString::number( challenge[ i + controller->startChallengeNr - 1 ]->getNr() ) );
      btnChallenge[ i ]->setHeightWidthRatio( 1 );
      btnChallenge[ i ]->setTextColor( TRANSPARENTC );
      btnChallenge[ i ]->setColors( TRANSPARENTC, TRANSPARENTC );
      challengeLayout->addWidget( btnChallenge[ i ], r, c );
    }
  }

  animation = new Animation;
  animation->setTimerCount( btnChallenge.length() );
  animation->setTimerMsec( ANIMATIONLENGTH / btnChallenge.length() );
  connect( animation, SIGNAL( working() ), this, SLOT( showButton() ) );
  animation->start();

  vLayout->addLayout( challengeLayout );
}

Challenges::~Challenges()
{
  //delete controller;
}

void Challenges::setSelectedChallenge( void )
{
  Challenge *c;
  for( int i = 0; i < btnChallenge.length(); i++ )
    if( sender() == btnChallenge[ i ] )
    {
      c = challenge[ i + controller->startChallengeNr - 1 ];
      break;
    }
  controller->showFusionFields( c );
}
