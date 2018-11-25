#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include "animation.h"
#include "config.h"
#include <QtWidgets>

class HomeWidget : public QWidget
{
  Q_OBJECT
  private:
    QList< QRectF > sectionRect;
    QList< QString > sectionHeader;
    QList< QImage > sectionImage;
    QList< QColor > sectionColor;
    QList< bool > sectionUnfold;
    QList< QRectF > unfoldRect;

    int highscore;
    int highestTileValue;
    int currentChallenges;
    int maxChallenges;
    QList< QImage > selectedItemImages;
    Animation *animation;

    QPointF getTranslatePoint( void );

  public:
    explicit HomeWidget( QWidget *parent = 0 );
    void setValues( int highscore, int highestTileValue, int currentChallenges, int maxChallenges, QList< int > selectedItemIds );
    void animate( void );

  protected:
    virtual void paintEvent( QPaintEvent * );
    virtual void mouseReleaseEvent( QMouseEvent *event );

  signals:
    void clicked( int section );
};

#endif // HOMEWIDGET_H
