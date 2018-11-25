#ifndef LABEL_H
#define LABEL_H

#include "config.h"
#include <QtWidgets>

class Label : public QWidget
{
  Q_OBJECT
  private:
    QString text;
    QColor color;
    QImage image;
    int fontSize;

  public:
    explicit Label( QString text = QString(), int fontSize = 20, QColor color = WHITE, QWidget *parent = 0 );
    void setText( QString text );
    void setColor( QColor color );
    void setImage( QImage image );
    void setFontSize( int size );

  protected:
    virtual void paintEvent( QPaintEvent * );
};

#endif // LABEL_H
