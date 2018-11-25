#include "challengetask.h"

const int TIMERCOUNTDEFAULT = 6;
const int TIMERMSEC = ANIMATIONLENGTH / TIMERCOUNTDEFAULT;

ChallengeTask::ChallengeTask( QWidget *parent ) : QWidget( parent ),
  challengeText( "" )
{
  animation = new Animation( TIMERCOUNTDEFAULT, TIMERMSEC );
  connect( animation, SIGNAL( working() ), this, SLOT( update() ) );
}

void ChallengeTask::setChallengeText( QString text )
{
  challengeText = text;
  update();
}

void ChallengeTask::animate( void )
{
  animation->start();
}

void ChallengeTask::paintEvent( QPaintEvent * )
{
  QPainter painter( this );
  painter.translate( -width() / TIMERCOUNTDEFAULT * animation->getTimerCount(), 0 );
  painter.setRenderHint( QPainter::Antialiasing );
  QFont font;

  QRectF infoRect( QPointF( rect().x(), rect().y() ), QSizeF( rect().width(), rect().height() ) );

  //Background
  painter.setPen( Qt::NoPen );
  painter.setBrush( TRANSPARENTBLACK );
  painter.drawRoundedRect( rect(), ROUNDEDRADIUS, ROUNDEDRADIUS );

  //Info
  painter.setPen( WHITE );
  font.setPointSize( 25 );
  painter.setFont( font );
  painter.drawText( infoRect, Qt::AlignCenter, getStringWithLineEnd( challengeText, 20 ) );
}
