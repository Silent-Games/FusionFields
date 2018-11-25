#ifndef XPLEVELPROGRESS_H
#define XPLEVELPROGRESS_H

#include "animation.h"
#include "config.h"
#include <QtWidgets>

class XPLevelProgress : public QWidget
{
  Q_OBJECT
  private:
    int level;
    int xp;
    Animation *animationStart;
    Animation *animationProgress;

  public:
    explicit XPLevelProgress( QWidget *parent = 0 );
    void setValues( int level, int xp );

  protected:
    virtual void paintEvent( QPaintEvent * );
};

#endif // XPLEVELPROGRESS_H
