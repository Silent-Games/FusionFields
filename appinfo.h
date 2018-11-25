#ifndef APPINFO_H
#define APPINFO_H

#include "config.h"
#include <QtWidgets>

class AppInfo : public QWidget
{
  Q_OBJECT
  private:
    QString infoText;

  public:
    explicit AppInfo( QWidget *parent = 0 );

  protected:
    virtual void paintEvent( QPaintEvent * );
};

#endif // APPINFO_H
