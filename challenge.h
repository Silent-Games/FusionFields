#ifndef CHALLENGE_H
#define CHALLENGE_H

#include "config.h"
#include <QtWidgets>

class Challenge : public QWidget
{
  Q_OBJECT
  private:
    int id;
    int gameId;
    QString challengeText;
    bool isCompleted;
    int scoreTarget;
    int moveTarget;
    int objectTarget;
    int tileValueTarget;
    int difficulty;
    int rewardXP;

  public:
    Challenge( void );
    explicit Challenge( int id, int gameId, QString challengeText, bool isCompleted, int scoreTarget, int moveTarget, int objectTarget, int tileValueTarget, int difficulty, int rewardXP, QWidget *parent = 0 );
    int getNr( void );
    int getId( void );
    void setId( int id );
    int getGameId( void );
    void setGameId( int gameId );
    QString getChallengeText( void );
    void setCompleted( bool state );
    bool isChallengeCompleted( void );
    int getScoreTarget( void );
    int getMoveTarget( void );
    int getObjectTarget( void );
    int getTileValueTarget( void );
    int getDifficulty( void );
    int getRewardXP( void );

  protected:
    virtual void paintEvent( QPaintEvent * );
};

#endif // CHALLENGE_H
