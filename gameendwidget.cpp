#include "gameendwidget.h"

const int TIMERCOUNTDEFAULT = 6;
const int TIMERMSEC = ANIMATIONLENGTH / TIMERCOUNTDEFAULT;

GameEndWidget::GameEndWidget( QWidget *parent ) : QWidget( parent )
{
  animation = new Animation( TIMERCOUNTDEFAULT, TIMERMSEC );
  connect( animation, SIGNAL( working() ), this, SLOT( update() ) );
}

void GameEndWidget::setValues( QString gameState, int score, int move, int object )
{
  this->gameState = gameState;
  infoText.clear();
  infoText << "Score" << "Moves";
  infoNumber.clear();
  infoNumber << score << move;
  if( object >= 0 )
  {
    infoText << "Object";
    infoNumber << object;
  }
  update();
}

void GameEndWidget::setOtherValues( QList< QString > other )
{
  for( int i = 0; i < other.length(); i++ )
    infoText << other[ i ];
  update();
}

void GameEndWidget::animate( void )
{
  animation->start();
}

void GameEndWidget::paintEvent( QPaintEvent * )
{
  QPainter painter( this );
  painter.translate( -width() / TIMERCOUNTDEFAULT * animation->getTimerCount(), 0 );
  painter.setRenderHint( QPainter::Antialiasing );
  QFont font;

  double lineSpace = rect().width() * LINESPACEDEC;
  QRectF gameStateRect( QPointF( rect().x() + lineSpace, rect().y() ), QSizeF( rect().width() - 2 * lineSpace, rect().height() * 0.2 ) );
  QRectF infoRect( QPointF( gameStateRect.x() + lineSpace, gameStateRect.y() + gameStateRect.height() ), QSizeF( gameStateRect.width() - 2 * lineSpace, rect().height() - gameStateRect.height() ) );

  //Background
  painter.setPen( Qt::NoPen );
  painter.setBrush( TRANSPARENTBLACK );
  painter.drawRoundedRect( rect(), ROUNDEDRADIUS, ROUNDEDRADIUS );

  //GameState
  painter.setPen( WHITE );
  font.setPointSize( 30 );
  painter.setFont( font );
  painter.drawText( gameStateRect, Qt::AlignCenter, getStringWithLineEnd( gameState, 15 ) );

  //Info
  QString textString( "" );
  QString numberString( "" );
  QString otherString( "" );
  for( int i = 0; i < infoText.length(); i++ )
  {
    if( i < infoNumber.length() )
    {
      textString += infoText[ i ] + "\r\n";
      numberString += QString::number( infoNumber[ i ] ) + "\r\n";
    }
    else
      otherString += infoText[ i ] + "\r\n";
  }
  painter.setPen( WHITE );
  font.setPointSize( 25 );
  painter.setFont( font );
  QRectF textRect;
  if( infoText.length() != infoNumber.length() )
  {
    textRect = QRectF( QPointF( infoRect.x(), infoRect.y() + infoRect.height() * 0.1 ), QSizeF( infoRect.width() / 2, infoRect.height() * 0.4 ) );
    painter.drawText( QRectF( QPointF( textRect.x(), textRect.y() + textRect.height() ), QSizeF( infoRect.width(), textRect.height() ) ), Qt::AlignCenter, otherString );
  }
  else
    textRect = QRectF( QPointF( infoRect.x(), infoRect.y() ), QSizeF( infoRect.width() / 2, infoRect.height() ) );
  painter.drawText( textRect, Qt::AlignVCenter | Qt::AlignLeft, textString );
  painter.drawText( QRectF( QPointF( textRect.x() + textRect.width(), textRect.y() ), QSizeF( infoRect.width() - textRect.width(), textRect.height() ) ), Qt::AlignVCenter | Qt::AlignRight, numberString );

  //Line
    //GameState - Info
  painter.setPen( WHITE );
  painter.drawLine( QPointF( gameStateRect.x(), gameStateRect.y() + gameStateRect.height() ), QPointF( gameStateRect.x() + gameStateRect.width(), gameStateRect.y() + gameStateRect.height() ) );
}
