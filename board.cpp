#include "board.h"

const int TIMERCOUNTDEFAULT = 6;
const int TIMERMSEC = ANIMATIONLENGTH / TIMERCOUNTDEFAULT;

Board::Board( QWidget *parent ) : QWidget( parent ),
  isCaption( false )
{
  challenge = new Challenge();

  animation = new Animation( TIMERCOUNTDEFAULT, TIMERMSEC );
  connect( animation, SIGNAL( working() ), this, SLOT( update() ) );
}

void Board::setGame( Game *game )
{
  this->game = game;
}

void Board::setChallenge( Challenge *challenge )
{
  this->challenge = challenge;
}

void Board::animate( void )
{
  animation->start();
}

void Board::setCaption( bool isCaption )
{
  this->isCaption = isCaption;
}

void Board::paintEvent( QPaintEvent * )
{
  QPainter painter( this );
  painter.translate( -width() / TIMERCOUNTDEFAULT * animation->getTimerCount(), 0 );
  painter.setRenderHint( QPainter::Antialiasing );
  QFont font;

  double boardWidth = width() - 1;
  double boardHeight = height();
  QRectF scoreRect;
  QRectF moveRect;
  QRectF objectRect;
  QRectF nextTileRect = QRectF( QPointF( boardWidth * 0.6, 0 ), QSizeF( boardWidth * 0.4, game->isFusionPoint() ? boardHeight * 0.6 : boardHeight ) );
  QRectF fusionPointsRect = QRectF( QPointF( boardWidth * 0.6, boardHeight * 0.6 ), QSizeF( boardWidth * 0.4, boardHeight - nextTileRect.height() ) );
  double currentValueDec = 0.65;
  if( challenge->getObjectTarget() == 0 )
  {
    scoreRect = QRectF( QPointF( 0, 0 ), QSizeF( boardWidth * 0.6, boardHeight * 0.6 ) );
    moveRect = QRectF( QPointF( 0, boardHeight * 0.6 ), QSizeF( boardWidth * 0.6, boardHeight * 0.4 ) );
  }
  else
  {
    scoreRect = QRectF( QPointF( 0, 0 ), QSizeF( boardWidth * 0.6, boardHeight * 0.4 ) );
    moveRect = QRectF( QPointF( 0, boardHeight * 0.4 ), QSizeF( boardWidth * 0.6, boardHeight * 0.3 ) );
    objectRect = QRectF( QPointF( 0, boardHeight * 0.7 ), QSizeF( boardWidth * 0.6, boardHeight * 0.3 ) );
  }

  //Background
  painter.setPen( Qt::NoPen );
  painter.setBrush( TRANSPARENTBLACK );
  painter.drawRoundedRect( rect(), ROUNDEDRADIUS, ROUNDEDRADIUS );

  //Score
  painter.setPen( WHITE );
    //ScoreCaption
  if( isCaption )
  {
      font.setPixelSize( scoreRect.height() / 5 );
      painter.setFont( font );
      painter.drawText( QRectF( QPointF( scoreRect.x(), scoreRect.y() ), QSizeF( scoreRect.width(), scoreRect.height() * 0.2 ) ), Qt::AlignCenter, tr( "Score" ) );
  }
  font.setPixelSize( scoreRect.height() / 2 );
  painter.setFont( font );
  if( challenge->getScoreTarget() > 0 )
  {
    painter.drawText( QRectF( QPointF( scoreRect.x(), scoreRect.y() ), QSizeF( scoreRect.width() * currentValueDec, scoreRect.height() ) ), Qt::AlignVCenter | Qt::AlignRight, QString::number( game->getScore() ) );
    painter.setPen( GRAY );
    font.setPixelSize( scoreRect.height() / 4 );
    painter.setFont( font );
    painter.drawText( QRectF( QPointF( scoreRect.x() + scoreRect.width() * currentValueDec, scoreRect.y() ), QSizeF( scoreRect.width() * ( 1 - currentValueDec ) , scoreRect.height() ) ), Qt::AlignVCenter | Qt::AlignLeft, QString::number( challenge->getScoreTarget() ) );
  }
  else
  {
    painter.drawText( scoreRect, Qt::AlignCenter, QString::number( game->getScore() ) );
  }

  if( game->isFusionPoint() )
  {
    //FusionPoints
    painter.setPen( WHITE );
    font.setPixelSize( fusionPointsRect.height() / 2 );
    painter.setFont( font );
    painter.drawText( QRectF( QPointF( fusionPointsRect.x(), fusionPointsRect.y() ), QSizeF( fusionPointsRect.width() / 2, fusionPointsRect.height() ) ), ( Qt::AlignVCenter | Qt::AlignRight ), QString::number( game->getFusionPoints() ) );
      //FusionPointsImage
    int fusionPointsImgSize = fusionPointsRect.height() / 2;
    QImage fusionPointsImg = Config::getConfig()->FUSIONPOINTSIMAGE.scaled( fusionPointsImgSize, fusionPointsImgSize );
    painter.drawImage( QPointF( fusionPointsRect.x() + fusionPointsRect.width() / 2, fusionPointsRect.y() + ( fusionPointsRect.height() / 2 ) - ( fusionPointsImgSize / 2 ) ), fusionPointsImg );
  }

  //Next Tile
  double tileSize = nextTileRect.width() > nextTileRect.height() ? nextTileRect.height() / 2 : nextTileRect.width() / 2;
  double tileX = ( nextTileRect.x() + nextTileRect.width() / 2 ) - tileSize / 2;
  double tileY = ( nextTileRect.y() + nextTileRect.height() / 2 ) - tileSize / 2;
    //Schatten
  painter.setPen( Qt::NoPen );
  painter.setBrush( BLACK );
  painter.drawRoundedRect( QRectF( QPointF( tileX, tileY ), QSizeF( tileSize, tileSize ) ), 10, 10 );
    //Felder
  painter.setPen( Qt::NoPen );
  painter.setBrush( getValueColor( game->getNextTile() ) );
  painter.drawRoundedRect( QRectF( QPointF( tileX, tileY ), QSizeF( tileSize, tileSize ) ), 10, 10 );
    //Text
  font.setPixelSize( tileSize / 2 );
  painter.setFont( font );
  painter.setPen( WHITE );
  painter.drawText( QRectF( QPointF( tileX, tileY ), QSizeF( tileSize, tileSize ) ), Qt::AlignCenter, QString::number( game->getNextTile() ) );
    //NextTileCaption
  if( isCaption )
  {
      painter.setPen( WHITE );
      font.setPixelSize( nextTileRect.height() / 8 );
      painter.setFont( font );
      painter.drawText( QRectF( QPointF( nextTileRect.x(), nextTileRect.y() ), QSizeF( nextTileRect.width(), nextTileRect.height() * 0.2 ) ), Qt::AlignCenter, tr( "Next Field" ) );
  }

  //Move
  painter.setPen( WHITE );
    //MoveCaption
  if( isCaption )
  {
      font.setPixelSize( moveRect.height() / 5 );
      painter.setFont( font );
      painter.drawText( QRectF( QPointF( moveRect.x(), moveRect.y() ), QSizeF( moveRect.width(), moveRect.height() * 0.2 ) ), Qt::AlignCenter, tr( "Move" ) );
  }
  font.setPixelSize( moveRect.height() / 2 );
  painter.setFont( font );
  if( challenge->getMoveTarget() > 0 )
  {
    painter.drawText( QRectF( QPointF( moveRect.x(), moveRect.y() ), QSizeF( moveRect.width() * currentValueDec, moveRect.height() ) ), Qt::AlignVCenter | Qt::AlignRight, QString::number( game->getMove() ) );
    painter.setPen( GRAY );
    font.setPixelSize( moveRect.height() / 4 );
    painter.setFont( font );
    painter.drawText( QRectF( QPointF( moveRect.x() + moveRect.width() * currentValueDec, moveRect.y() ), QSizeF( moveRect.width() * ( 1 - currentValueDec ), moveRect.height() ) ), Qt::AlignVCenter | Qt::AlignLeft, QString::number( challenge->getMoveTarget() ) );
  }
  else
  {
    painter.drawText( moveRect, Qt::AlignCenter, QString::number( game->getMove() ) );
  }

  //Object
  if( challenge->getObjectTarget() > 0 )
  {
      //ObjectImage
    int objectImgSize = objectRect.height() / 2;
    QImage objectImg = Config::getConfig()->OBJECTIMAGE.scaled( objectImgSize, objectImgSize );
    painter.drawImage( QPointF( objectRect.x() + ( objectRect.width() * 0.15 ) - ( objectImgSize / 2 ), objectRect.y() + ( objectRect.height() / 2 ) - ( objectImgSize / 2 ) ), objectImg );
      //ObjectText
    painter.setPen( WHITE );
    font.setPixelSize( objectRect.height() / 2 );
    painter.setFont( font );
      painter.drawText( QRectF( QPointF( objectRect.x() + objectRect.width() * 0.3, objectRect.y() ), QSizeF( objectRect.width() * 0.7 * currentValueDec, objectRect.height() ) ), Qt::AlignVCenter | Qt::AlignRight, QString::number( game->getObject() ) );
      painter.setPen( GRAY );
      font.setPixelSize( objectRect.height() / 4 );
      painter.setFont( font );
      painter.drawText( QRectF( QPointF( objectRect.x() + objectRect.width() * 0.3 + objectRect.width() * 0.7 * currentValueDec, objectRect.y() ), QSizeF( objectRect.width() * 0.7 * ( 1 - currentValueDec ), objectRect.height() ) ), Qt::AlignVCenter | Qt::AlignLeft, QString::number( challenge->getObjectTarget() ) );
  }

  //Lines
  painter.setPen( WHITE );
    // Score - Move
  double lineSpace = scoreRect.width() * LINESPACEDEC;
  painter.drawLine( QPointF( scoreRect.x() + lineSpace, scoreRect.y() + scoreRect.height() ), QPointF( scoreRect.x() + scoreRect.width() - lineSpace, scoreRect.y() + scoreRect.height() ) );
    // Move - Object
  if( challenge->getObjectTarget() > 0 )
  {
    lineSpace = moveRect.width() * LINESPACEDEC;
    painter.drawLine( QPointF( moveRect.x() + lineSpace, moveRect.y() + moveRect.height() ), QPointF( moveRect.x() + moveRect.width() - lineSpace, moveRect.y() + moveRect.height() ) );
  }
    // Score/Move/Object - NextTile/FusionPoints
  lineSpace = boardHeight * LINESPACEDEC;
  painter.drawLine( QPointF( scoreRect.x() + scoreRect.width(), scoreRect.y() + lineSpace ), QPointF( scoreRect.x() + scoreRect.width(), boardHeight - lineSpace ) );
    // NextTile - FusionPoints
  if( game->isFusionPoint() )
  {
    lineSpace = nextTileRect.width() * LINESPACEDEC;
    painter.drawLine( QPointF( nextTileRect.x() + lineSpace, nextTileRect.y() + nextTileRect.height() ), QPointF( nextTileRect.x() + nextTileRect.width() - lineSpace, nextTileRect.y() + nextTileRect.height() ) );
  }
}
