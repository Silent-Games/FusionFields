#include "controller.h"
#include <QApplication>

int main( int argc, char *argv[] )
{
  QApplication a(argc, argv);

  QFile file( ":/Database/Database/databaseFF" );
  if( file.exists() )
  {
    file.copy( "./databaseFF" );
    QFile::setPermissions( "./databaseFF", QFile::WriteOwner | QFile::ReadOwner );
  }else qDebug() << "Nicht verfügbar: ";

  Controller c;
  c.show();

  return a.exec();
}
