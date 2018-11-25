#include "itemboard.h"

const int TIMERCOUNTDEFAULT = 6;
const int TIMERMSEC = ANIMATIONLENGTH / TIMERCOUNTDEFAULT;

ItemBoard::ItemBoard( QWidget *parent ) : QWidget( parent ), selectedItem( NOITEM )
{
  animation = new Animation( TIMERCOUNTDEFAULT, TIMERMSEC );
  connect( animation, SIGNAL( working() ), this, SLOT( update() ) );
}

void ItemBoard::setItems( QList< int > item )
{
  this->item = item;
  update();
}

QList< int > ItemBoard::getItems( void )
{
  return item;
}

void ItemBoard::setGame( Game *game )
{
  this->game = game;
  update();
}

void ItemBoard::setSelectedItem( int item )
{
  selectedItem = item;
}

void ItemBoard::animate()
{
  animation->start();
}

void ItemBoard::paintEvent( QPaintEvent * )
{
  QPainter painter( this );
  painter.translate( -width() / TIMERCOUNTDEFAULT * animation->getTimerCount(), 0 );
  painter.setRenderHint( QPainter::Antialiasing );
  QFont font;

  double boardWidth = width() - 1;
  double boardHeight = height();
  itemRect.clear();
  for( int i = 0; i < item.length(); i++ )
    itemRect << QRectF( QPointF( ( boardWidth / item.length() ) * i, 0 ), QSizeF( boardWidth / item.length(), boardHeight ) );

  //Allgemeiner Hintergrund
  painter.setPen( Qt::NoPen );
  painter.setBrush( TRANSPARENTBLACK );
  painter.drawRoundedRect( rect(), ROUNDEDRADIUS, ROUNDEDRADIUS );

  //Item
  for( int i = 0; i < itemRect.length(); i++ )
  {
    //SelectedItem
    if( selectedItem == item[ i ] )
    {
      painter.setPen( Qt::NoPen );
      painter.setBrush( BLACK );
      painter.drawRoundedRect( itemRect[ i ], ROUNDEDRADIUS, ROUNDEDRADIUS );
    }

    //Image
    int imgSize = itemRect[ i ].height() / 2;
    QImage img = Config::getConfig()->getItemImage( item[ i ] ).scaled( imgSize, imgSize );
    if( item[ i ] == LOCKED || item[ i ] == UNLOCKED || item[ i ] == NOITEM )
      painter.drawImage( QPointF( itemRect[ i ].x() + ( itemRect[ i ].width() / 2 ) - ( imgSize / 2 ), ( itemRect[ i ].y() + itemRect[ i ].height() / 2 ) - ( imgSize / 2 ) ), img );
    else
    {
      painter.drawImage( QPointF( itemRect[ i ].x() + ( itemRect[ i ].width() / 4 ) - ( imgSize / 2 ), ( itemRect[ i ].y() + itemRect[ i ].height() / 2 ) - ( imgSize / 2 ) ), img );

      //Costs
      painter.setPen( game->getItemCost( item[ i ] ) <= game->getFusionPoints() ? WHITE : GRAY );
      font.setPixelSize( itemRect[ i ].height() / 2 );
      painter.setFont( font );
      painter.setBrush( Qt::NoBrush );
      painter.drawText( QRectF( QPointF( itemRect[ i ].x() + itemRect[ i ].width() / 2, itemRect[ i ].y() ), QSizeF( itemRect[ i ].width() / 4, itemRect[ i ].height() ) ), ( Qt::AlignVCenter | Qt::AlignRight ), QString::number( game->getItemCost( item[ i ] ) ) );

      //FusionPoints
      int fusionPointsImgSize = itemRect[ i ].height() / 2;
      QImage fusionPointsImg = Config::getConfig()->FUSIONPOINTSIMAGE.scaled( fusionPointsImgSize, fusionPointsImgSize );
      painter.drawImage( QPointF( itemRect[ i ].x() + itemRect[ i ].width() * 0.75, ( itemRect[ i ].y() + itemRect[ i ].height() / 2 ) - ( fusionPointsImgSize / 2 ) ), fusionPointsImg );
    }

    if( i >= itemRect.length() - 1 ) return;
    //Line
    painter.setPen( WHITE );
    painter.setBrush( Qt::NoBrush );
    double lineSpace = itemRect[ i ].height() * LINESPACEDEC;
    painter.drawLine( QPointF( itemRect[ i ].x() + itemRect[ i ].width(), itemRect[ i ].y() + lineSpace ), QPointF( itemRect[ i ].x() + itemRect[ i ].width(), itemRect[ i ].y() + itemRect[ i ].height() - lineSpace ) );
  }
}

void ItemBoard::mouseReleaseEvent( QMouseEvent *event )
{
  QPointF pos = event->pos();
  //Items
  for( int i = 0; i < itemRect.length(); i++ )
  {
    if( pos.x() >= itemRect[ i ].x() && pos.x() <= itemRect[ i ].x() + itemRect[ i ].width()
        && pos.y() >= itemRect[ i ].y() && pos.y() <= itemRect[ i ].y() + itemRect[ i ].height()
        && item[ i ] != LOCKED && item[ i ] != UNLOCKED && game->getFusionPoints() >= game->getItemCost( item[ i ] ) )
    {
      selectedItem = selectedItem == item[ i ] ? NOITEM : item[ i ];
      update();
      emit itemClicked( selectedItem );
    }
  }
}
