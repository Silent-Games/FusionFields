#include "label.h"

Label::Label( QString text, int fontSize, QColor color, QWidget *parent ) : QWidget( parent )
{
  setText( text );
  setFontSize( fontSize );
  setColor( color );
  setImage( QImage() );
}

void Label::setText(QString text)
{
  this->text = text;
  update();
}

void Label::setColor( QColor color )
{
  this->color = color;
  update();
}

void Label::setImage( QImage image )
{
  this->image = image;
  update();
}

void Label::setFontSize( int size )
{
  this->fontSize = size;
  update();
}

void Label::paintEvent( QPaintEvent * )
{
  QPainter painter( this );
  painter.setRenderHint( QPainter::Antialiasing );
  QFont font;

  if( image.isNull() )
  {
    painter.setPen( color );
    font.setPointSize( this->fontSize );
    painter.setFont( font );
    painter.drawText( rect(), Qt::AlignCenter, getStringWithLineEnd( text, 20 ) );
  }
  else
  {
    int imgSize = width() <= height() ? width() : height();
    QImage img = image.scaled( imgSize, imgSize );
    painter.drawImage( QPointF( width() / 2 - img.width() / 2, height() / 2 - img.height() / 2 ), img );
  }
}
