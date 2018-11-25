#include "notification.h"

Notification::Notification( QWidget *parent ) : QWidget( parent )
{
}

void Notification::setGameModeText( QString text )
{
  this->gameModeText = text;
  update();
}

void Notification::setNotificationText( QString text )
{
  notificationText = text;
  update();
  QTimer *timer = new QTimer();
  connect( timer, SIGNAL( timeout() ), this, SLOT( setNotificationNullText() ) );
  timer->start( 5000 );
}

void Notification::setNotificationNullText( void )
{
  notificationText.clear();
  update();
}

void Notification::paintEvent( QPaintEvent * )
{
  QPainter painter( this );
  painter.setRenderHint( QPainter::Antialiasing );

  //GameModeText
  QRectF headerRect = QRectF( QPointF( 0, 0 ), QSizeF( width(), height() * 0.4 ) );
  QRectF gameModeRect = QRectF( QPointF( 0, headerRect.height() ), QSizeF( width(), height() - headerRect.height() ) );
  painter.setPen( WHITE );
  QFont font;
  font.setPixelSize(  headerRect.height() * 0.7 );
  painter.setFont( font );
  painter.drawText( headerRect, Qt::AlignHCenter | Qt::AlignBottom, tr( "Game:" ) );
  font.setPixelSize(  gameModeRect.height() * 0.7 );
  painter.setFont( font );
  painter.drawText( gameModeRect, Qt::AlignCenter, gameModeText );

  //Notification
  if( !notificationText.isEmpty() )
  {
    font.setPixelSize( height() / 2 < width() / notificationText.length() ? height() / 2 : width() / notificationText.length() );
    painter.setFont( font );
    painter.setPen( UNLOCKEDCOLOR );
    painter.setBrush( UNLOCKEDCOLOR );
    painter.drawRect( rect() );
    painter.setPen( WHITE );
    painter.drawText( rect(), Qt::AlignCenter, notificationText );
  }
}
