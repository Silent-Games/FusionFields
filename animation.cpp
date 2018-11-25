#include "animation.h"

void Animation::decreaseTimerCount( void )
{
  timerCount--;
  if( timerCount <= 0 )
  {
    timer->stop();
    timerCount = 0;
    emit finished();
  }
  else
    timer->start( timerMsec );
}

Animation::Animation( int timerCount, int timerMsec, QObject *parent ) : QObject( parent )
{
  setTimerCount( timerCount );
  setTimerMsec( timerMsec );
  timer = new QTimer();
  connect( timer, SIGNAL( timeout() ), this, SLOT( decreaseTimerCount() ) );
  connect( timer, SIGNAL( timeout() ), this, SIGNAL( working() ) );
}

void Animation::start( void )
{
  timer->stop();
  timerCount = timerCountDefault;
  timer->start( timerMsec );
}

void Animation::setTimerCount( int timerCount )
{
  this->timerCountDefault = timerCount;
  this->timerCount = timerCount;
}

int Animation::getTimerCount( void )
{
  return timerCount;
}

void Animation::setTimerMsec( int msec )
{
  timerMsec = msec;
}
