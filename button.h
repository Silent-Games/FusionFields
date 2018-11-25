#ifndef BUTTON_H
#define BUTTON_H

#include "config.h"
#include <QtWidgets>

class Button : public QWidget
{
  Q_OBJECT
  private:
    double btnWidth;
    double btnHeight;
    double heightWidthRatio;

    QString text;
    QImage image;
    QColor borderColor;
    QColor color;
    QColor textColor;

    bool isClicked;
    bool isEnabled;
    bool isActive;

  public:
    explicit Button( QWidget *parent = 0 );
    Button( QString text, QColor borderColor = BLACK, QColor color = WHITE );

    void setHeightWidthRatio( double ratio );

    QString getText( void ) const;
    void setText( QString text );

    QImage getImage( void  );
    void setImage( QImage image );

    QColor getBorderColor( void ) const;
    void setBorderColor( QColor color );
    QColor getColor( void ) const;
    void setTextColor( QColor color );
    void setColor( QColor color );
    void setColors( QColor borderColor, QColor color );

    void setEnabled( bool state );
    void setActive( bool state );

  protected:
    virtual void paintEvent( QPaintEvent * );
    virtual void mousePressEvent( QMouseEvent *event );
    virtual void mouseReleaseEvent( QMouseEvent *event );

  signals:
    void clicked( void );
};

#endif // BUTTON_H
