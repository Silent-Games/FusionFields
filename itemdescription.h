#ifndef ITEMDESCRIPTION_H
#define ITEMDESCRIPTION_H

#include "animation.h"
#include "config.h"
#include "item.h"
#include <QtWidgets>

class ItemDescription : public QWidget
{
  Q_OBJECT
  private:
    Item *item;
    Animation *animation;

  public:
    explicit ItemDescription( QWidget *parent = 0 );
    void setItem( Item *item );
    void animate( void );

  protected:
    virtual void paintEvent( QPaintEvent * );
};

#endif // ITEMDESCRIPTION_H
