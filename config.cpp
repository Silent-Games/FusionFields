#include "config.h"

QColor getValueColor( int value )
{
  QList< QColor > valueColor;
  valueColor << VALUECOLOR1 << VALUECOLOR2 << VALUECOLOR3 << VALUECOLOR4 << VALUECOLOR5 << VALUECOLOR6
             << VALUECOLOR7 << VALUECOLOR8 << VALUECOLOR9 << VALUECOLOR10 << VALUECOLOR11 << VALUECOLOR12;
  if( value <= 0 || value > valueColor.length() )
    return valueColor.last();
  return valueColor[ value - 1 ];
}

QList< QString > splitStringInParts( QString string, int partLength )
{
  QStringList word = string.split( " " );
  QList< QString > stringPart;
  stringPart << word[ 0 ];
  for( int w = 1, s = 0; w < word.length(); w++ )
  {
    if( stringPart[ s ].length() + word[ w ].length() <= partLength )
      stringPart[ s ] += " " + word[ w ];
    else
    {
      stringPart << word[ w ];
      s++;
    }
  }

  return stringPart;
}

QString getStringWithLineEnd( QString string, int partLength )
{
  QList< QString > stringParts = splitStringInParts( string, partLength );
  QString stringWithLineEnd( "" );
  for( int i = 0; i < stringParts.length(); i++ )
  {
    stringWithLineEnd += stringParts[ i ];
    if( i < stringParts.length() - 1 )
       stringWithLineEnd += "\r\n";
  }
  return stringWithLineEnd;
}

int getMaxXPLevel( int level )
{
  return 1000 * pow( 2, level );
}

int getLevelXP( int xp )
{
  int level = 0;
  if( xp > 0 ) level = ( log10( xp / 1000.0 ) / log10( 2 ) ) + 1;
  return level < 0 ? 0 : level;
}

QImage getScaledImage( QString imagePath, int imageWidth, int imageHeight )
{
  QImage image;
  image.load( imagePath );
  image = image.scaled( imageWidth, imageHeight );
  return image;
}

Config *Config::config = nullptr;

Config::Config( void )
{

}

Config *Config::getConfig( void )
{
  if( config == nullptr )
    config = new Config();
  return config;
}

QImage Config::getItemImage( int item ) const
{
  QImage itemImage;
  switch( item )
  {
    case UNLOCKED: itemImage = UNLOCKEDIMAGE; break;
    case SWAPITEM: itemImage = SWAPITEMIMAGE; break;
    case INCREASEITEM: itemImage = INCREASEITEMIMAGE; break;
    case DECREASEITEM: itemImage = DECREASEITEMIMAGE; break;
    case RANDOMITEM: itemImage = RANDOMITEMIMAGE; break;
    case NEWNEXTTILEITEM: itemImage = NEWNEXTTILEITEMIMAGE; break;
    case LOCKED:
    default: itemImage = LOCKEDIMAGE ; break;
  }
  return itemImage;
}
