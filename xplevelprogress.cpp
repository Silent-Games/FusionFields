#include "xplevelprogress.h"

const int TIMERCOUNTDEFAULT = 6;
const int TIMERMSEC = ANIMATIONLENGTH / TIMERCOUNTDEFAULT;

XPLevelProgress::XPLevelProgress( QWidget *parent ) : QWidget( parent ), xp( 0 )
{
  animationProgress = new Animation;
  animationProgress->setTimerCount( TIMERCOUNTDEFAULT );
  animationProgress->setTimerMsec( TIMERMSEC );
  connect( animationProgress, SIGNAL( working() ), this, SLOT( update() ) );

  animationStart = new Animation;
  animationStart->setTimerCount( TIMERCOUNTDEFAULT );
  animationStart->setTimerMsec( TIMERMSEC );
  connect( animationStart, SIGNAL( working() ), this, SLOT( update() ) );
  connect( animationStart, SIGNAL( finished() ), animationProgress, SLOT( start() ) );
  animationStart->start();
}

void XPLevelProgress::setValues( int level, int xp )
{
  this->level = level;
  this->xp = xp;
  update();
}

void XPLevelProgress::paintEvent( QPaintEvent * )
{
  QPainter painter( this );
  painter.setRenderHint( QPainter::Antialiasing );
  painter.translate( width() / TIMERCOUNTDEFAULT * animationStart->getTimerCount() + width() / 2, height() / 2);
  QFont font;

  QRectF progressBarRect( QPointF( -width() / 2, -height() * 0.5 / 2 ), QSizeF( width(), height() * 0.5 ) );
  QRectF levelRect( QPointF( -( height() / 2 ), -height() / 2 ), QSizeF( height(), height() ) );
  QRectF currentXPRect( QPointF( progressBarRect.x() + width() * 0.05, progressBarRect.y() ), QSizeF( progressBarRect.width() / 2, progressBarRect.height() ) );
  QRectF maxXPRect( QPointF( progressBarRect.x() + progressBarRect.width() / 2, progressBarRect.y() ), QSizeF( progressBarRect.width() / 2 - width() * 0.05, progressBarRect.height() ) );

  double progressPercent = 0.0;
  if( xp != 0 )
    progressPercent =  1.0 / ( ( double ) getMaxXPLevel( level ) / xp );
  if( animationProgress->getTimerCount() > 0 )
    progressPercent = progressPercent / animationProgress->getTimerCount();

  //ProgressBar
  painter.setBrush( TRANSPARENTBLACK );
  painter.drawRect( progressBarRect );
  painter.setBrush( GREEN );
  painter.drawRect( QRectF( QPointF( progressBarRect.x(), progressBarRect.y() ), QSizeF( progressBarRect.width() * progressPercent, progressBarRect.height() ) ) );

  //level
  painter.setBrush( BLACK );
  painter.drawRect( levelRect );
  painter.setPen( WHITE );
  font.setPixelSize( levelRect.height() / 2 );
  font.setBold( true );
  painter.setFont( font );
  painter.drawText( levelRect, Qt::AlignCenter, QString::number( level ) );

  //CurrentXP
  painter.setPen( WHITE );
  font.setPixelSize( currentXPRect.height() / 2 );
  font.setBold( true );
  painter.setFont( font );
  painter.drawText( currentXPRect, Qt::AlignVCenter | Qt::AlignLeft, QString::number( xp ) + " XP" );

  //MaxXP
  painter.setPen( WHITE );
  font.setPixelSize( maxXPRect.height() / 2 );
  font.setBold( true );
  painter.setFont( font );
  painter.drawText( maxXPRect, Qt::AlignVCenter | Qt::AlignRight, QString::number( getMaxXPLevel( level ) ) + " XP" );
}
