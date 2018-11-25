#include "itemdescription.h"

const int TIMERCOUNTDEFAULT = 6;
const int TIMERMSEC = ANIMATIONLENGTH / TIMERCOUNTDEFAULT;

ItemDescription::ItemDescription( QWidget *parent ) : QWidget( parent )
{
  Item *item = new Item;
  this->item = item;

  animation = new Animation;
  animation->setTimerCount( TIMERCOUNTDEFAULT );
  animation->setTimerMsec( TIMERMSEC );
  connect( animation, SIGNAL( working() ), this, SLOT( update() ) );
}

void ItemDescription::setItem( Item *item )
{
  this->item = item;
  update();
}

void ItemDescription::animate( void )
{
  animation->start();
}

void ItemDescription::paintEvent( QPaintEvent * )
{
  QPainter painter( this );
  painter.setRenderHints( QPainter::Antialiasing );
  painter.translate( QPointF( -rect().width() / TIMERCOUNTDEFAULT * animation->getTimerCount(), 0 ) );
  QFont font;

  QRectF nameRect( QPointF( 0, 0 ), QSizeF( width() * 0.7, height() * 0.3 ) );
  QRectF costsRect( QPointF( nameRect.x() + nameRect.width(), 0 ), QSizeF( width() * 0.3, height() * 0.3 ) );
  QRectF descriptionRect( QPointF( 0, nameRect.y() + nameRect.height() ), QSizeF( width(), height() * 0.7 ) );

  //Background
  painter.setPen( Qt::NoPen );
  painter.setBrush( TRANSPARENTBLACK );
  painter.drawRoundedRect( rect(), ROUNDEDRADIUS, ROUNDEDRADIUS );

  //Name
  painter.setPen( WHITE );
  font.setPixelSize( nameRect.height() / 2 );
  painter.setFont( font );
  painter.drawText( nameRect, Qt::AlignCenter, item->isItemUnlocked() ? item->getName() : "???" );

  //Costs
  painter.setPen( WHITE );
  font.setPixelSize( costsRect.height() / 2 );
  painter.setFont( font );
  painter.drawText( QRectF( QPointF( costsRect.x(), costsRect.y() ), QSizeF( costsRect.width() / 2, costsRect.height() ) ), Qt::AlignVCenter | Qt::AlignRight, item->isItemUnlocked() ? QString::number( item->getCost() ) : "??" );
    //FusionPoints
  int fusionPointsImgSize = costsRect.height() / 2;
  QImage fusionPointsImg = Config::getConfig()->FUSIONPOINTSIMAGE.scaled( fusionPointsImgSize, fusionPointsImgSize );
  painter.drawImage( QPointF( costsRect.x() + costsRect.width() / 2, costsRect.y() + ( costsRect.height() / 2 ) - ( fusionPointsImgSize / 2 ) ), fusionPointsImg );

  //Description / 25 Zeichen pro Zeile | 6 Zeilen
  painter.setPen( WHITE );
  font.setPixelSize( descriptionRect.height() / 7 );
  painter.setFont( font );
  QString descriptionText = item->isItemUnlocked() ? getStringWithLineEnd( item->getDescription(), 25 ) : "???";
  painter.drawText( descriptionRect, Qt::AlignCenter, descriptionText );

  //Lines
  painter.setPen( WHITE );
    //Name - Costs
  double lineSpace = nameRect.height() * LINESPACEDEC;
  painter.drawLine( QPointF( nameRect.x() + nameRect.width(), nameRect.y() + lineSpace ), QPointF( nameRect.x() + nameRect.width(), nameRect.y() + nameRect.height() - lineSpace ) );
    //Name - Description
  lineSpace = nameRect.width() * LINESPACEDEC;
  painter.drawLine( QPointF( nameRect.x() + lineSpace, nameRect.y() + nameRect.height() ), QPointF( nameRect.x() + nameRect.width() - lineSpace, nameRect.y() + nameRect.height() ) );
    //Costs - Description
  lineSpace = costsRect.width() * LINESPACEDEC;
  painter.drawLine( QPointF( costsRect.x() + lineSpace, costsRect.y() + costsRect.height() ), QPointF( costsRect.x() + costsRect.width() - lineSpace, costsRect.y() + costsRect.height() ) );
}
