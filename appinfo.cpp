#include "appinfo.h"

AppInfo::AppInfo( QWidget *parent ) : QWidget( parent )
{
  infoText = "FusionFields\r\n"
             "2017-2018\r\n"
             "Version: " + APPVERSION + "\r\n"
             "Developed by Leon Rose\r\n"
             "Developed with Qt (Qt 5.7.0)\r\n"
             "\r\n"
             "Source code available on\r\n"
             "silent-games.de/fusionfields_source_code";
}

void AppInfo::paintEvent( QPaintEvent * )
{
  QPainter painter( this );
  painter.setRenderHint( QPainter::Antialiasing );
  QFont font;

  QRectF appIconRect( QPointF( 0, 0 ), QSizeF( width(), height() / 2 ) );
  QRectF infoTextRect( QPointF( 0, appIconRect.y() + appIconRect.height() ), QSizeF( width(), height() - appIconRect.height() ));

  //AppIcon
  int appIconSize = appIconRect.width() <= appIconRect.height() ? appIconRect.width() * 0.8 : appIconRect.height() * 0.8;
  QImage appIcon = Config::getConfig()->APPICONIMAGE.scaled( appIconSize, appIconSize );
  painter.drawImage( QPointF( appIconRect.x() + appIconRect.width() / 2 - appIcon.width() / 2, appIconRect.y() + appIconRect.height() / 2 - appIcon.height() / 2 ), appIcon );

  //InfoText
  painter.setPen( WHITE );
  painter.setBrush( Qt::NoBrush );
  font.setPixelSize( infoTextRect.height() / 3 * 0.8 <= infoTextRect.width() / 22 ? infoTextRect.height() / 3 * 0.8 : infoTextRect.width() / 22 );
  painter.setFont( font );
  painter.drawText( infoTextRect, Qt::AlignCenter, infoText );
}
