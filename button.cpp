#include "button.h"

Button::Button( QWidget *parent ) : QWidget( parent ),
  heightWidthRatio( 0 ), borderColor( BLACK ), color( WHITE ), isClicked( false ), isEnabled( true ), isActive( false )
{
}

Button::Button( QString text, QColor borderColor, QColor color ) :
  heightWidthRatio( 0 ), borderColor( BLACK ), color( WHITE ), isClicked( false ), isEnabled( true ), isActive( false )
{
  setText( text );
  setBorderColor( borderColor );
  setColor( color );
}

void Button::setHeightWidthRatio( double ratio )
{
  if( ratio <= 0 )
    heightWidthRatio = 0;
  heightWidthRatio = ratio;
}

QString Button::getText( void ) const
{
  return text;
}

void Button::setText( QString text )
{
  this->text = text;
  image = QImage();
  update();
}

QImage Button::getImage( void )
{
  return image;
}

void Button::setImage( QImage image )
{
  this->image = image;
  text.clear();
  update();
}

QColor Button::getBorderColor( void ) const
{
  return borderColor;
}

void Button::setBorderColor( QColor color )
{
  this->borderColor = color;
  update();
}

QColor Button::getColor( void ) const
{
  return color;
}

void Button::setTextColor( QColor color )
{
  textColor = color;
  update();
}

void Button::setColor( QColor color )
{
  this->color = color;
  update();
}

void Button::setColors( QColor borderColor, QColor color )
{
  setBorderColor( borderColor );
  setColor( color );
  update();
}

void Button::setEnabled( bool state )
{
  isEnabled = state;
  update();
}

void Button::setActive( bool state )
{
  isActive = state;
  update();
}

void Button::paintEvent( QPaintEvent * )
{
  QPainter painter( this );
  painter.translate( this->width() / 2, height() / 2 );
  painter.setRenderHint( QPainter::Antialiasing );


  if( heightWidthRatio <= 0 )
  {
    btnHeight = this->height();
    btnWidth = this->width();
  }
  else
  {
    btnHeight = this->width() / heightWidthRatio < this->height() ? this->width() / heightWidthRatio : this->height();
    btnWidth = btnHeight * heightWidthRatio - 10;//10 = Padding
  }
  double border = btnWidth * 0.025;
  btnHeight -= border;
  btnWidth -= border;
  if( isClicked )
  {
    btnWidth *= 0.97;
    btnHeight *= 0.97;
  }

  //Button
  QPoint buttonPoint( -btnWidth / 2, -btnHeight / 2 );
  QSize buttonSize( btnWidth, btnHeight );
  QPen pen( borderColor, border );
  painter.setPen( pen );
  if( !isActive )
    painter.setBrush( color );
  else
    painter.setBrush( color == color.darker( 255 ) ? BLACK : color.darker( 255 ) );
  painter.drawRoundedRect( QRect( buttonPoint, buttonSize ), ROUNDEDRADIUS, ROUNDEDRADIUS );

  //Text
  QPoint textPoint( -( btnWidth / 2 - border ), -( btnHeight / 2 - border ) );
  QSize textSize( btnWidth - ( border * 2 ), btnHeight - ( border * 2 ) );
  QFont font;
  int textPixelSize = btnHeight / 2 < btnWidth / text.length() ? btnHeight / 2 : btnWidth / text.length();
  font.setPixelSize( textPixelSize );
  painter.setFont( font );
  painter.setPen( textColor.isValid() ? textColor : borderColor );
  painter.drawText( QRectF( textPoint, textSize ), Qt::AlignCenter, text );

  //Image
  if( image.isNull() )
    return;
  int imgSize = btnWidth / 2 < btnHeight / 2 ? btnWidth / 2 : btnHeight / 2;
  QPoint imagePoint( -imgSize / 2, -imgSize / 2 );
  QImage btnImg = image.scaled( imgSize, imgSize );
  painter.drawImage( imagePoint, btnImg );
}

void Button::mousePressEvent( QMouseEvent *event )
{
  if( event->y() >= ( height() / 2 ) - ( btnHeight / 2 )
      && event->y() <= ( height() / 2 ) + ( btnHeight / 2 )
      && event->x() >= ( width() / 2 ) - ( btnWidth / 2 )
      && event->x() <= ( width() / 2 ) + ( btnWidth / 2 )
      && isEnabled )
  {
    isClicked = true;
    update();
  }
}

void Button::mouseReleaseEvent( QMouseEvent *event )
{
  if( event->y() >= ( height() / 2 ) - ( btnHeight / 2 )
      && event->y() <= ( height() / 2 ) + ( btnHeight / 2 )
      && event->x() >= ( width() / 2 ) - ( btnWidth / 2 )
      && event->x() <= ( width() / 2 ) + ( btnWidth / 2 )
      && isEnabled )
  {
    isClicked = false;
    update();
    emit clicked();
  }
  else
  {
    isClicked = false;
    update();
  }
}

