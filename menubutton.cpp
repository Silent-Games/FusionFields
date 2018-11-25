#include "menubutton.h"

const int TIMERCOUNTDEFAULT = 6;
const int TIMERMSEC = ANIMATIONLENGTH / TIMERCOUNTDEFAULT;

MenuButton::MenuButton( QWidget *parent ) : QWidget( parent )
{
  animation = new Animation;
  animation->setTimerCount( TIMERCOUNTDEFAULT );
  animation->setTimerMsec( TIMERMSEC );
  connect( animation, SIGNAL( working() ), this, SLOT( update() ) );
}

void MenuButton::setLeftButtonText( QString btnText )
{
  leftButtonText = btnText;
  update();
}

void MenuButton::setLeftButtonImage( QImage img )
{
  leftButtonImage = img;
  update();
}

void MenuButton::setLeftButtonImage( QString imgPath )
{
  QImage img;
  img.load( imgPath );
  setLeftButtonImage( img );
}

void MenuButton::setMiddleButtonText( QString btnText )
{
  middleButtonText = btnText;
  update();
}

void MenuButton::setMiddleButtonImage( QImage img )
{
  middleButtonImage = img;
  update();
}

void MenuButton::setMiddleButtonImage( QString imgPath )
{
  QImage img;
  img.load( imgPath );
  setMiddleButtonImage( img );
}

void MenuButton::setRightButtonText( QString btnText )
{
  rightButtonText = btnText;
  update();
}

void MenuButton::setRightButtonImage( QImage img )
{
  rightButtonImage = img;
  update();
}

void MenuButton::setRightButtonImage( QString imgPath )
{
  QImage img;
  img.load( imgPath );
  setRightButtonImage( img );
}

void MenuButton::animate( void )
{
  animation->start();
}

void MenuButton::paintEvent(QPaintEvent *)
{
  QPainter painter( this );
  painter.setRenderHints( QPainter::Antialiasing );
  painter.translate( QPointF( 0, rect().height() / TIMERCOUNTDEFAULT * animation->getTimerCount() ) );
  QFont font;

  QList< QRectF > buttonRect;
  QList< QString > buttonText;
  QList< QImage > buttonImage;
  leftButtonRect = QRectF( QPointF( 0, 0 ), QSizeF( rect().width() / 3,  rect().height() ) );
  middleButtonRect = QRectF( QPointF( rect().width() / 3, 0 ), QSizeF( rect().width() / 3, rect().height() ) );
  rightButtonRect = QRectF( QPointF( rect().width() / 3 * 2, 0 ), QSizeF( rect().width() / 3,  rect().height() ) );
  buttonRect << leftButtonRect << middleButtonRect << rightButtonRect;
  buttonText << leftButtonText << middleButtonText << rightButtonText;
  buttonImage << leftButtonImage << middleButtonImage << rightButtonImage;

  //Allgemeiner Hintergrund
  painter.setBrush( BLACK );
  painter.drawRect( rect() );

  for( int i = 0; i < buttonRect.length(); i++ )
  {
    if( !buttonText[ i ].isEmpty() )
    {
      painter.setPen( WHITE );
      int textPixelSize;
      if( buttonImage[ i ].isNull() )
      {
        textPixelSize = buttonRect[ i ].height() / 2 < buttonRect[ i ].width() / buttonText[ i ].length() ? buttonRect[ i ].height() / 2 : buttonRect[ i ].width() / buttonText[ i ].length();
        font.setPixelSize( textPixelSize );
        painter.setFont( font );
        painter.drawText( buttonRect[ i ], Qt::AlignCenter, buttonText[ i ] );
      }
      else
      {
        textPixelSize = buttonRect[ i ].height() / 4 < buttonRect[ i ].width() / buttonText[ i ].length() ? buttonRect[ i ].height() / 4: buttonRect[ i ].width() / buttonText[ i ].length();
        font.setPixelSize( textPixelSize );
        painter.setFont( font );
        painter.drawText( QRectF( QPointF( buttonRect[ i ].x(), buttonRect[ i ].y() + buttonRect[ i ].height() * 0.6 ), QSizeF( buttonRect[ i ].width(), buttonRect[ i ].height() * 0.4) ), Qt::AlignCenter, buttonText[ i ] );
      }
    }
    if( !buttonImage[ i ].isNull() )
    {
      if( !buttonText[ i ].isEmpty() )
      {
        buttonImage[ i ] = buttonImage[ i ].scaled( buttonRect[ i ].height() / 2, buttonRect[ i ].height() / 2 );
        painter.drawImage( QPointF( buttonRect[ i ].x() + buttonRect[ i ].width() / 2 - buttonImage[ i ].width() / 2, buttonRect[ i ].y() + ( buttonRect[ i ].height() * 0.6 ) / 2 - buttonImage[ i ].height() / 2  ), buttonImage[ i ] );
      }
      else
      {
        buttonImage[ i ] = buttonImage[ i ].scaled( buttonRect[ i ].height() / 2, buttonRect[ i ].height() / 2 );
        painter.drawImage( QPointF( buttonRect[ i ].x() + buttonRect[ i ].width() / 2 - buttonImage[ i ].width() / 2, buttonRect[ i ].y() + buttonRect[ i ].height() / 2 - buttonImage[ i ].height() / 2  ), buttonImage[ i ] );
      }
    }
    //Line
    if( i <  buttonRect.length() - 1 )
    {
      painter.setPen( WHITE );
      double lineSpace = buttonRect[ i ].height() * LINESPACEDEC;
      painter.drawLine( QPointF( buttonRect[ i ].x() + buttonRect[ i ].width(), buttonRect[ i ].y() + lineSpace ), QPointF( buttonRect[ i ].x() + buttonRect[ i ].width(), buttonRect[ i ].y() + buttonRect[ i ].height() - lineSpace ) );
    }
  }

  //Lines
  painter.setPen( WHITE );
    //  - leftButton/rightButton
  painter.drawLine( QPointF( 0, 0 ), QPointF( rect().width(), 0 ) );
}

void MenuButton::mousePressEvent( QMouseEvent *event )
{
}

void MenuButton::mouseReleaseEvent( QMouseEvent *event )
{
  QPointF pos = event->pos();
  if( leftButtonRect.contains( pos ) )
    emit leftClicked();
  else if( middleButtonRect.contains( pos ) )
    emit middleClicked();
  else if( rightButtonRect.contains( pos ) )
    emit rightClicked();
}
