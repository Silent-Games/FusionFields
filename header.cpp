#include "header.h"

const int TIMERCOUNTDEFAULT = 6;
const int TIMERMSEC = ANIMATIONLENGTH / TIMERCOUNTDEFAULT;

Header::Header( QWidget *parent ) : QWidget( parent )
{
  animation = new Animation;
  animation->setTimerCount( TIMERCOUNTDEFAULT );
  animation->setTimerMsec( TIMERMSEC );
  connect( animation, SIGNAL( working() ), this, SLOT( update() ) );
}

void Header::setHeader( QString text )
{
  this->header = text;
  update();
}

void Header::setCaption( QString text )
{
  this->caption = text;
  update();
}

void Header::setBackgroundColor( QColor color )
{
  this->backgroundColor = color;
  update();
}

void Header::animate( void )
{
  animation->start();
}

void Header::paintEvent( QPaintEvent *event )
{
  QPainter painter( this );
  painter.setRenderHint( QPainter::Antialiasing );
  painter.translate( QPointF( 0, -rect().height() / TIMERCOUNTDEFAULT * animation->getTimerCount() ) );
  QFont font;

  QRectF headerRect = QRectF( 0, 0, 0, 0 );
  QRectF captionRect = QRectF( 0, 0, 0, 0 );

  if( !header.isEmpty()  ) headerRect = rect();
  if( !caption.isEmpty() )
  {
    if( !header.isEmpty() )
      headerRect = QRectF( QPointF( 0, 0 ), QSizeF( rect().width(), rect().height() * 0.6 ) );
    captionRect = QRectF( QPointF( headerRect.x(), headerRect.y() + headerRect.height() ), QSizeF( headerRect.width(), rect().height() - headerRect.height() ) );
  }

  //Background
  painter.setBrush( backgroundColor.isValid() ? backgroundColor : DARKGRAY );
  painter.drawRect( rect() );

  //Header
  if( !header.isEmpty() )
  {
    painter.setPen( WHITE );
    font.setPixelSize( headerRect.height() * 0.8 );
    font.setBold( true );
    painter.setFont( font );
    painter.drawText( headerRect, Qt::AlignCenter, header );
  }

  //Caption
  if( !caption.isEmpty() )
  {
    painter.setPen( WHITE );
    font.setPixelSize( captionRect.height() * 0.8 );
    font.setBold( false );
    painter.setFont( font );
    painter.drawText( captionRect, Qt::AlignHCenter | Qt::AlignTop, caption );
  }

  //Line
  painter.setPen( WHITE );
  painter.drawLine( QPointF( rect().x(), rect().y() + rect().height() ), QPointF( rect().x() + rect().width(), rect().y() + rect().height() ) );
}
