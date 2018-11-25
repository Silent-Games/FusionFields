#include "gamefield.h"

int GameField::getSelectedTileIndex( QPoint pos )
{
  int posX = pos.x() / tileSize + 1;
  int posY = pos.y() / tileSize + 1;
  if( posX < 1 || posX > game->getFieldWidth()
      || posY < 1 || posY > game->getFieldHeight() )
    return -1;
  return ( posY - 1 ) * game->getFieldWidth() + ( posX - 1 );
}

void GameField::setGame( Game *game )
{
  this->game = game;

  animation = new Animation( game->getField().length(), ANIMATIONLENGTH / game->getField().length() );
  connect( animation, SIGNAL( working() ), this, SLOT( update() ) );
}

void GameField::animate( void )
{
  animation->start();
}

GameField::GameField( QWidget *parent ) : QWidget( parent )
{
}

void GameField::paintEvent( QPaintEvent * )
{
  QPainter painter( this );
  painter.setRenderHint( QPainter::Antialiasing );
  painter.translate( width() / 2, height() / 2 );

  //Feld
  fieldSize = width() >= height() ? height() : width();
  double fieldBorder = fieldSize * 0.02;
  fieldSize -= fieldBorder;

  //painter.setPen( GREEN );
  painter.setBrush( QColor( 0,0,0, 100 ) );
  //painter.drawRoundedRect( QRectF( QPointF( -fieldSize / 2, -fieldSize / 2), QSizeF( fieldSize, fieldSize ) ), 10, 10);

  //Felder/Tiles
  double tileSize = fieldSize / ( game->getFieldWidth() > game->getFieldHeight() ? game->getFieldWidth() : game->getFieldHeight() );
  this->tileSize = tileSize;
  double tileMargin = tileSize * 0.05;
  tileSize -= tileMargin;

  for( int r = 0, i = 0; r < game->getFieldHeight(); r++ )
    for( int c = 0; c < game->getFieldWidth(); c++, i++ )
    {
      if( !( i <= game->getField().length() - animation->getTimerCount() ) )
        break;
      painter.setPen( Qt::NoPen );
      QColor tileColor = getValueColor( game->getField()[ i ] );
    //Hintergrund
      double tileX = ( -fieldSize / 2 ) + ( tileSize * c ) + ( tileMargin * c ) + ( tileMargin / 2 );
      double tileY = ( -fieldSize / 2 ) + ( tileSize * r ) + ( tileMargin * r ) + ( tileMargin / 2 );
      if( selectedTileIndex.contains( i ) )
      {//SelectedTiles
        tileColor.setAlpha( 120  );
        painter.setBrush( tileColor );
        tileColor.setAlpha( 255 );
      }
      else
        painter.setBrush( QColor( 0,0,0, 100 ) );
      painter.drawRoundedRect( QRectF( QPointF( tileX, tileY ), QSizeF( tileSize, tileSize ) ), 10, 10 );
    //Inhalt
      double tilePadding = tileSize * 0.14;
      tileX += tilePadding / 2;
      tileY += tilePadding / 2;
      //Schatten
      painter.setBrush( BLACK );
      painter.drawRoundedRect( QRectF( QPointF( tileX, tileY ), QSizeF( tileSize - tilePadding, tileSize - ( tilePadding * 0.65 ) ) ), 10, 10 );
      //Felder
      painter.setBrush( tileColor );
      painter.drawRoundedRect( QRectF( QPointF( tileX, tileY ), QSizeF( tileSize - tilePadding, tileSize - tilePadding ) ), 10, 10 );

      if( i == game->getFusionPointTileIndex() )
      {
    //FusionPoint
        QImage fusionPointsImg = Config::getConfig()->FUSIONPOINTSIMAGE.scaled( tileSize - tilePadding, tileSize - tilePadding );
        painter.drawImage( QPointF( tileX, tileY ), fusionPointsImg );
      }
      else if( i == game->getObjectTileIndex() )
      {
    //Object
        QImage objectImg = Config::getConfig()->OBJECTIMAGE.scaled( tileSize - tilePadding, tileSize - tilePadding );
        painter.drawImage( QPointF( tileX, tileY ), objectImg );
      }
      else
      {
    //Text
      QFont font;
      font.setPixelSize( tileSize / 2 );
      painter.setFont( font );
      painter.setPen( WHITE );
      painter.drawText( QRectF( QPointF( tileX, tileY ), QSizeF( tileSize - tilePadding, tileSize - tilePadding ) ), Qt::AlignCenter, QString::number( game->getField()[ i ] ) );
      }
    }
}

void GameField::mousePressEvent( QMouseEvent *event )
{
  if( game->isGameFinished() )
    return;

  QPoint pos( event->x() - ( ( width() - fieldSize ) / 2 ), event->y() - ( ( height() - fieldSize ) / 2 ) ) ;
  int selectedTileIndex = getSelectedTileIndex( pos );
  this->selectedTileIndex << selectedTileIndex;
  if( this->selectedTileIndex.length() == 2 )
  {
    emit move( this->selectedTileIndex );
    this->selectedTileIndex.clear();
  }
  update();
}

void GameField::mouseReleaseEvent( QMouseEvent *event )
{
  if( this->selectedTileIndex.isEmpty() )
    return;
  QPoint pos( event->x() - ( ( width() - fieldSize ) / 2 ), event->y() - ( ( height() - fieldSize ) / 2 ) ) ;
  int selectedTileIndex = getSelectedTileIndex( pos );
  if( !this->selectedTileIndex.contains( selectedTileIndex ) )
    this->selectedTileIndex << selectedTileIndex;
  if( this->selectedTileIndex.length() == 2 )
  {
    emit move( this->selectedTileIndex );
    this->selectedTileIndex.clear();
  }
  update();
}
