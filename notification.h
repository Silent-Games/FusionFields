#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "config.h"
#include <QtWidgets>

class Notification : public QWidget
{
  Q_OBJECT
  private:
    QString gameModeText;
    QString notificationText;

  public:
    explicit Notification( QWidget *parent = 0 );
    void setGameModeText( QString text );

  public slots:
    void setNotificationText( QString text );
    void setNotificationNullText();

  protected:
    virtual void paintEvent( QPaintEvent * );
};

#endif // NOTIFICATION_H
