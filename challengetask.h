#ifndef CHALLENGETASK_H
#define CHALLENGETASK_H

#include "animation.h"
#include "config.h"
#include <QtWidgets>

class ChallengeTask : public QWidget
{
  Q_OBJECT
  private:
    QString challengeText;
    Animation *animation;

  public:
    explicit ChallengeTask( QWidget *parent = 0 );
    void setChallengeText( QString text );
    void animate( void );

  protected:
    virtual void paintEvent( QPaintEvent * );
};

#endif // CHALLENGETASK_H
