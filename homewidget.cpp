#include "homewidget.h"

const int HIGHSCOREINDEX = 0;
const int CHALLENGEINDEX = 1;
const int ITEMINDEX = 2;
const int ACHIEVEMENTINDEX = 3;

const int TIMERCOUNTDEFAULT = 6;
const int TIMERMSEC = ANIMATIONLENGTH / TIMERCOUNTDEFAULT;

QPointF HomeWidget::getTranslatePoint( void )
{
  return QPointF( rect().width() / TIMERCOUNTDEFAULT * animation->getTimerCount(), 0 );
}

HomeWidget::HomeWidget( QWidget *parent ) : QWidget( parent )
{
  sectionHeader << tr( "Highscore" ) << tr( "Challenges" ) << tr( "Items" );
  sectionImage << Config::getConfig()->HIGHSCOREIMAGE << Config::getConfig()->CHALLENGEIMAGE << Config::getConfig()->ITEMSIMAGE;
  sectionColor << HIGHSCORECOLOR << CHALLENGECOLOR << ITEMCOLOR;
  sectionUnfold << false << false << false << false;

  animation = new Animation;
  animation->setTimerCount( TIMERCOUNTDEFAULT );
  animation->setTimerMsec( TIMERMSEC );
  connect( animation, SIGNAL( working() ), this, SLOT( update() ) );
}

void HomeWidget::setValues( int highscore, int highestTileValue, int currentChallenges, int maxChallenges, QList< int > selectedItemIds )
{
  this->highscore = highscore;
  this->highestTileValue = highestTileValue;
  this->currentChallenges = currentChallenges;
  this->maxChallenges = maxChallenges;
  this->selectedItemImages.clear();
  for( int i = 0; i < selectedItemIds.length(); i++ )
    this->selectedItemImages << Config::getConfig()->getItemImage( selectedItemIds[ i ] );
}

void HomeWidget::animate( void )
{
  animation->start();
}

void HomeWidget::paintEvent( QPaintEvent * )
{
  QPainter painter( this );
  painter.setRenderHint( QPainter::Antialiasing );
  painter.translate( getTranslatePoint() );
  QFont font;

  double spaceWidth = rect().width() * 0.05;
  double spaceHeight = rect().height() * 0.01;
  QSizeF sectionSize( rect().width() - 2 * spaceWidth, rect().height() / 3 -  2 * spaceHeight );

  QRectF highscoreRect( QPointF( rect().x() + spaceWidth, rect().y() + spaceHeight ), sectionSize );
  QRectF challengesRect( QPointF( rect().x() + spaceWidth, highscoreRect.y() + highscoreRect.height() + 2 * spaceHeight  ), sectionSize );
  QRectF itemsRect( QPointF( rect().x() + spaceWidth, challengesRect.y() + challengesRect.height() + 2 * spaceHeight ), sectionSize );

  sectionRect.clear();
  sectionRect << highscoreRect << challengesRect << itemsRect;

  QList< QRectF > imageRect, headerRect, infoRect;
  unfoldRect.clear();
  for( int i = 0; i < sectionRect.length(); i++ )
  {
    imageRect << QRectF( QPointF( sectionRect[ i ].x(), sectionRect[ i ].y() ), QSizeF( sectionRect[ i ].width() * 0.3, sectionRect[ i ].height() ) );
    headerRect << QRectF( QPointF( imageRect[ i ].x() + imageRect[ i ].width(), imageRect[ i ].y() ), QSizeF( sectionRect[ i ].width() * 0.6, sectionUnfold[ i ] ? sectionRect[ i ].height() * 0.4 : sectionRect[ i ].height() ) );
    unfoldRect << QRectF( QPointF( headerRect[ i ].x() + headerRect[ i ].width(), headerRect[ i ].y() ), QSizeF( sectionRect[ i ].width() * 0.1, headerRect[ i ].height() ) );
    infoRect << QRectF( QPointF(), QSizeF() );
  }
  int headerTextSize = headerRect[ 0 ].width() / 8;
  for( int i = 0; i < sectionRect.length(); i++ )
  {
    //Background
    painter.setPen( Qt::NoPen );
    painter.setBrush( sectionColor[ i ] );
    painter.drawRoundedRect( sectionRect[ i ], ROUNDEDRADIUS, ROUNDEDRADIUS );
    //Image
    int imgSize = imageRect[ i ].width() <= imageRect[ i ].height() ? imageRect[ i ].width() * 0.75 : imageRect[ i ].height() * 0.75;
    QImage sectionImg = sectionImage[ i ].scaled( imgSize, imgSize );
    painter.drawImage( QPointF( imageRect[ i ].x() + imageRect[ i ].width() / 2 - imgSize / 2, imageRect[ i ].y() + imageRect[ i ].height() / 2 - imgSize / 2 ), sectionImg );
    //Header
    painter.setPen( WHITE );
    font.setPixelSize( headerTextSize );
    font.setBold( true );
    painter.setFont( font );
    painter.drawText( headerRect[ i ], Qt::AlignCenter, sectionHeader[ i ] );
    //Unfold
    int unfoldSize = unfoldRect[ i ].width() <= unfoldRect[ i ].height() ? unfoldRect[ i ].width() / 2 : unfoldRect[ i ].height() / 2;
    QImage unfoldImg = sectionUnfold[ i ] ? Config::getConfig()->ARROWIMAGE.scaled( unfoldSize, unfoldSize ) : Config::getConfig()->ARROWIMAGE.scaled( unfoldSize, unfoldSize ).mirrored();
    painter.drawImage( QPointF( unfoldRect[ i ].x() + unfoldRect[ i ].width() / 2 - unfoldSize / 2, unfoldRect[ i ].y() + unfoldRect[ i ].height() / 2 - unfoldSize / 2 ), unfoldImg );
    //HeaderLine
    if( sectionUnfold[ i ] )
    {
      painter.setPen( WHITE );
      painter.drawLine( QPointF( headerRect[ i ].x(), headerRect[ i ].y() + headerRect[ i ].height() ), QPointF( headerRect[ i ].x() + headerRect[ i ].width() + unfoldRect[ i ].width(), headerRect[ i ].y() + headerRect[ i ].height() ) );
    }
  }

  font.setBold( false );
  //HighscoreMode
  if( sectionUnfold[ HIGHSCOREINDEX ] )
  {
    painter.setPen( WHITE );
    font.setPixelSize( sectionRect[ HIGHSCOREINDEX ].height() * 0.12 );
    painter.setFont( font );
    painter.drawText( QRectF( QPointF( sectionRect[ HIGHSCOREINDEX ].x() + sectionRect[ HIGHSCOREINDEX ].width() * 0.3, sectionRect[ HIGHSCOREINDEX ].y() + sectionRect[ HIGHSCOREINDEX ].height() * 0.4 ), QSizeF( sectionRect[ HIGHSCOREINDEX ].width() * 0.7, sectionRect[ HIGHSCOREINDEX ].height() * 0.6 ) ), Qt::AlignCenter, tr( "Highscore: " ) + QString::number( highscore ) + "\r\n" + tr( "Highest Field Value: " ) + QString::number( highestTileValue ) );
  }

  //Challenges
  if( sectionUnfold[ CHALLENGEINDEX ] )
  {
    painter.setPen( WHITE );
    font.setPixelSize( sectionRect[ CHALLENGEINDEX ].height() * 0.12 );
    painter.setFont( font );
    painter.drawText( QRectF( QPointF( sectionRect[ CHALLENGEINDEX ].x() + sectionRect[ CHALLENGEINDEX ].width() * 0.3, sectionRect[ CHALLENGEINDEX ].y() + sectionRect[ CHALLENGEINDEX ].height() * 0.4 ), QSizeF( sectionRect[ CHALLENGEINDEX ].width() * 0.7, sectionRect[ CHALLENGEINDEX ].height() * 0.6 ) ), Qt::AlignCenter, tr( "You completed " ) + "\r\n" + QString::number( currentChallenges ) + tr( " of " ) + QString::number( maxChallenges ) + tr( " Challenges!" ) );
  }

  //Items
  if( sectionUnfold[ ITEMINDEX ] )
  {
    //Text
    painter.setPen( WHITE );
    font.setPixelSize( sectionRect[ ITEMINDEX ].height() * 0.12 );
    painter.setFont( font );
    painter.drawText( QRectF( QPointF( sectionRect[ ITEMINDEX ].x() + sectionRect[ ITEMINDEX ].width() * 0.3, sectionRect[ ITEMINDEX ].y() + sectionRect[ ITEMINDEX ].height() * 0.4 ), QSizeF( sectionRect[ ITEMINDEX ].width() * 0.7 / ( selectedItemImages.length() + 1 ), sectionRect[ ITEMINDEX ].height() * 0.6 ) ), Qt::AlignCenter, tr( "Selected" ) + "\r\n" + tr( "Items:" ) );
    //ItemImage
    int imgSize = sectionRect[ ITEMINDEX ].width() * 0.7 / ( selectedItemImages.length() + 1 ) < sectionRect[ ITEMINDEX ].height() * 0.6 ? sectionRect[ ITEMINDEX ].width() * 0.7 / ( selectedItemImages.length() + 1 ) / 2 : sectionRect[ ITEMINDEX ].height() * 0.6 / 2;
    for( int i = 0; i < selectedItemImages.length(); i++ )
    {
      selectedItemImages[ i ] = selectedItemImages[ i ].scaled( imgSize, imgSize );
      painter.drawImage( QPointF(  sectionRect[ ITEMINDEX ].x() + ( sectionRect[ ITEMINDEX ].width() * 0.3 ) + ( sectionRect[ ITEMINDEX ].width() * 0.7 / ( selectedItemImages.length() + 1 ) ) * ( i + 1.5 ) - selectedItemImages[ i ].width() / 2, sectionRect[ ITEMINDEX ].y() + sectionRect[ ITEMINDEX ].height() * 0.4 + sectionRect[ ITEMINDEX ].height() * 0.6 / 2 - selectedItemImages[ i ].width() / 2 ), selectedItemImages[ i ] );
    }
  }
}

void HomeWidget::mouseReleaseEvent( QMouseEvent *event )
{
  for( int i = 0; i < sectionRect.length(); i++ )
    if( sectionRect[ i ].contains( event->pos() ) )
    {
      if( unfoldRect[ i ].contains( event->pos() )  )
      {
        sectionUnfold[ i ] = !sectionUnfold[ i ];
        update();
        break;
      }
      emit clicked( i + 1 );
      break;
    }
}
