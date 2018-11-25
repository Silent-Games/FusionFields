#ifndef SAVEDATATHREAD_H
#define SAVEDATATHREAD_H

#include "data.h"
#include <QtCore>

class SaveDataThread : public QThread
{
  private:
    int whatSaving;
    int gameId;
    int challengeId;

  public:
    SaveDataThread( void );
    void run( void );
    void setGameId( int gameId );
    void setChallengeId( int challengeId );
    void setWhatSaving( int whatSaving );
    void clear( void );

    const static int Game = 0x01;
    const static int Info = 0x02;
    const static int Item = 0x04;
    const static int Challenge = 0x08;
    const static int All = Game | Info | Item | Challenge;
};

#endif // SAVEDATATHREAD_H
