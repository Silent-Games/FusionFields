#ifndef CONFIG_H
#define CONFIG_H

#include <QImage>
#include <QDebug>
#include "math.h"
#include <QColor>

const QString APPVERSION = QString( "1.02" );

const int ROUNDEDRADIUS = 10;
const double LINESPACEDEC = 0.05;
const int HIGHSCOREGAMEID = 40;
const int ANIMATIONLENGTH = 250;

//Color
const QColor WHITE = QColor( 255, 255, 255 );
const QColor BLACK = QColor( 0, 0, 0 );
const QColor GREEN = QColor( 0, 180, 4 );
const QColor DARKGREEN = QColor( 1, 110, 12 );
const QColor SUCCESSGREEN = QColor( 28, 223, 28 );
const QColor BLUE = QColor( 1, 41, 244 );
const QColor DARKBLUE = QColor( 3, 32, 178 );
const QColor YELLOW = QColor( 228, 228, 20 );
const QColor ORANGE = QColor( 255, 120, 10 );
const QColor DARKORANGE = QColor( 226, 84, 3 );
const QColor RED = QColor( 255, 25, 25 );
const QColor DARKRED = QColor( 189, 3, 3 );
const QColor FAILURERED = QColor( 255, 35, 30 );
const QColor PURPLE = QColor( 180, 10, 255 );
const QColor GRAY = QColor( 150, 150, 150 );
const QColor DARKGRAY = QColor( 40, 40, 40 );

const QColor HIGHSCORECOLOR = DARKGREEN;
const QColor CHALLENGECOLOR = DARKRED;
const QColor ITEMCOLOR = DARKORANGE;
const QColor ACHIEVEMENTCOLOR = DARKBLUE;

const QColor TRANSPARENT = QColor( 0, 0, 0, 0 );
const QColor TRANSPARENTC = TRANSPARENT;
const QColor TRANSPARENTBLACK = QColor( 0, 0, 0, 130 );
const QColor BOARDCOLOR = TRANSPARENT;//TRANSPARENTBLACK;//QColor( 46, 46, 46 );
const QColor UNLOCKEDCOLOR = RED.darker( 250 );

QColor getValueColor( int value );
const QColor VALUECOLOR1 = BLUE;
const QColor VALUECOLOR2 = GREEN;
const QColor VALUECOLOR3 = YELLOW;
const QColor VALUECOLOR4 = ORANGE;
const QColor VALUECOLOR5 = RED;
const QColor VALUECOLOR6 = PURPLE;
const QColor VALUECOLOR7 = BLUE.darker( 200 );
const QColor VALUECOLOR8 = GREEN.darker( 200 );
const QColor VALUECOLOR9 = YELLOW.darker( 200 );
const QColor VALUECOLOR10 = ORANGE.darker( 200 );
const QColor VALUECOLOR11 = RED.darker( 200 );
const QColor VALUECOLOR12 = PURPLE.darker( 200 );

//Items
const int LOCKED = 0;
const int UNLOCKED = 1;
const int NOITEM = 2;
const int RANDOMITEM = 3;
const int SWAPITEM = 4;
const int INCREASEITEM = 5;
const int DECREASEITEM = 6;
const int NEWNEXTTILEITEM = 7;

//Strings
QList< QString > splitStringInParts( QString string, int partLength );
QString getStringWithLineEnd(QString string, int partLength );

//Level
int getMaxXPLevel( int level );
int getLevelXP( int xp );

//Config Class
class Config
{
  private:
    static Config *config;
    Config( void );

  public:
    static Config *getConfig( void );
    //Files
    const QString APPICONIMAGEFILE = QString( ":/Images/Images/appicon.png" );
    const QString MOVESOUNDFILE = QString( "qrc:/Sounds/Media/pop.mp3" );
    const QString PLAYIMAGEFILE = QString( ":/Images/Images/play.png" );
    const QString UNLOCKEDIMAGEFILE = QString( ":/Items/Images/unlocked.png" );
    const QString LOCKEDIMAGEFILE = QString( ":/Items/Images/locked.png" );
    const QString SWAPITEMIMAGEFILE = QString( ":/Items/Images/swapitem.png" );
    const QString INCREASEITEMIMAGEFILE = QString( ":/Items/Images/increaseitem.png" );
    const QString DECREASEITEMIMAGEFILE = QString( ":/Items/Images/decreaseitem.png" );
    const QString RANDOMITEMIMAGEFILE = QString( ":/Items/Images/randomitem.png" );
    const QString NEWNEXTITEMIMAGEFILE = QString( ":/Items/Images/nexttileitem.png" );
    const QString FUSIONPOINTSIMAGEFILE = QString( ":/Images/Images/fusionpoints.png" );
    const QString OBJECTIMAGEFILE = QString( ":/Images/Images/object.png" );
    const QString ARROWIMAGEFILE = QString( ":/Images/Images/arrow.png" );
    const QString RESTARTIMAGEFILE = QString( ":/Images/Images/restart.png" );
    const QString SOUNDONIMAGEFILE = QString( ":/Images/Images/soundon.png" );
    const QString SOUNDOFFIMAGEFILE = QString( ":/Images/Images/soundoff.png" );
    const QString HIGHSCOREIMAGEFILE = QString( ":/Images/Images/highscore.png" );
    const QString CHALLENGEIMAGEFILE = QString( ":/Images/Images/challenges.png" );
    const QString ITEMSIMAGEFILE = QString( ":/Images/Images/item.png" );
    const QString INFOIMAGEFILE = QString( ":/Images/Images/info.png" );
    const QString MENUIMAGEFILE = QString( ":/Images/Images/menu.png" );
    const QString CANCELIMAGEFILE = QString( ":/Images/Images/cancel.png" );
    const QString CHECKIMAGEFILE = QString( ":/Images/Images/check.png" );
    //Images
    const QImage APPICONIMAGE = QImage( APPICONIMAGEFILE );
    const QImage PLAYIMAGE = QImage( PLAYIMAGEFILE );
    const QImage UNLOCKEDIMAGE = QImage( UNLOCKEDIMAGEFILE );
    const QImage LOCKEDIMAGE = QImage( LOCKEDIMAGEFILE );
    const QImage SWAPITEMIMAGE = QImage( SWAPITEMIMAGEFILE );
    const QImage INCREASEITEMIMAGE = QImage( INCREASEITEMIMAGEFILE );
    const QImage DECREASEITEMIMAGE = QImage( DECREASEITEMIMAGEFILE );
    const QImage RANDOMITEMIMAGE = QImage( RANDOMITEMIMAGEFILE );
    const QImage NEWNEXTTILEITEMIMAGE = QImage( NEWNEXTITEMIMAGEFILE );
    const QImage FUSIONPOINTSIMAGE = QImage( FUSIONPOINTSIMAGEFILE );
    const QImage OBJECTIMAGE = QImage( OBJECTIMAGEFILE );
    const QImage ARROWIMAGE = QImage( ARROWIMAGEFILE );
    const QImage RESTARTIMAGE = QImage( RESTARTIMAGEFILE );
    const QImage SOUNDONIMAGE = QImage( SOUNDONIMAGEFILE );
    const QImage SOUNDOFFIMAGE = QImage( SOUNDOFFIMAGEFILE );
    const QImage HIGHSCOREIMAGE = QImage( HIGHSCOREIMAGEFILE );
    const QImage CHALLENGEIMAGE = QImage( CHALLENGEIMAGEFILE );
    const QImage ITEMSIMAGE = QImage( ITEMSIMAGEFILE );
    const QImage INFOIMAGE = QImage( INFOIMAGEFILE );
    const QImage MENUIMAGE = QImage( MENUIMAGEFILE );
    const QImage CANCELIMAGE = QImage( CANCELIMAGEFILE );
    const QImage CHECKIMAGE = QImage( CHECKIMAGEFILE );
    QImage getItemImage( int item ) const;
};

#endif // CONFIG_H
