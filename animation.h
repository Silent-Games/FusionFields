#ifndef ANIMATION_H
#define ANIMATION_H

#include <QTimer>
#include <QObject>

class Animation : public QObject
{
  Q_OBJECT
  private:
    QTimer *timer;
    int timerCountDefault;
    int timerCount;
    int timerMsec;

  private slots:
    void decreaseTimerCount( void );

  public:
    explicit Animation( int timerCount = 6, int timerMsec = 25, QObject *parent = 0 );
    void setTimerCount( int timerCount );
    int getTimerCount( void );
    void setTimerMsec( int msec );

  public slots:
    void start( void );

  signals:
    void working( void );
    void finished( void );
};

#endif // ANIMATION_H
