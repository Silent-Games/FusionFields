#ifndef HEADER_H
#define HEADER_H

#include "config.h"
#include "animation.h"
#include <QtWidgets>

class Header : public QWidget
{
  Q_OBJECT
  private:
    QString header;
    QString caption;
    QColor backgroundColor;
    Animation *animation;

  public:
    explicit Header( QWidget *parent = 0 );
    void setHeader( QString text );
    void setCaption( QString text );
    void setBackgroundColor( QColor color );
    void animate( void );

  protected:
    virtual void paintEvent( QPaintEvent *event );
};

#endif // HEADER_H
