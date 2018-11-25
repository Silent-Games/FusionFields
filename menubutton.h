#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "animation.h"
#include "config.h"
#include <QtWidgets>

class MenuButton : public QWidget
{
  Q_OBJECT
  private:
    QRectF leftButtonRect;
    QString leftButtonText;
    QImage leftButtonImage;
    QRectF middleButtonRect;
    QString middleButtonText;
    QImage middleButtonImage;
    QRectF rightButtonRect;
    QString rightButtonText;
    QImage rightButtonImage;
    Animation *animation;

  public:
    explicit MenuButton( QWidget *parent = 0 );
    void setLeftButtonText( QString btnText );
    void setLeftButtonImage( QImage img );
    void setLeftButtonImage( QString imgPath );
    void setMiddleButtonText( QString btnText );
    void setMiddleButtonImage( QImage img );
    void setMiddleButtonImage( QString imgPath );
    void setRightButtonText( QString btnText );
    void setRightButtonImage( QImage img );
    void setRightButtonImage( QString imgPath );
    void animate( void );

  protected:
    virtual void paintEvent( QPaintEvent * );
    virtual void mousePressEvent( QMouseEvent *event );
    virtual void mouseReleaseEvent( QMouseEvent *event );

  signals:
    void leftClicked( void );
    void middleClicked( void );
    void rightClicked( void );
};

#endif // MENUBUTTON_H
