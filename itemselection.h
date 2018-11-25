#ifndef ITEMSELECTION_H
#define ITEMSELECTION_H

#include "animation.h"
#include "itemdescription.h"
#include "config.h"
#include "item.h"
#include "button.h"
#include "controller.h"
#include <QtWidgets>

class Controller;

class ItemSelection : public QWidget
{
  Q_OBJECT
  private:
    QList< Button * > btnItem;
    QList< Item * > item;
    int selectedItemId;
    ItemDescription *itemDescription;
    Animation *animation;

  private slots:
    void showButton( void );

  public:
    explicit ItemSelection( int selectedItemId, Controller *controller, QWidget *parent = 0 );
    int getSelectedItemId( void );
    void setSelectedItem(Item *item );
    void animate( void );

  protected:
    virtual void paintEvent( QPaintEvent * );

  public slots:
    void setSelectedItem( void );

  signals:
    void itemSelected( int item );
};

#endif // ITEMSELECTION_H
