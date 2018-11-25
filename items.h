#ifndef ITEMS_H
#define ITEMS_H

#include "header.h"
#include "button.h"
#include "controller.h"
#include <QtWidgets>
#include "config.h"

class Controller;

class Items : public QWidget
{
  Q_OBJECT
  private:
    Controller *controller;
    QList< int > item;
    QList< Button * > btnItem;
    Animation *animation;

  public:
    explicit Items( QList< int > item, Controller *controller, QWidget *parent = 0 );

  public slots:
    void showItemSelection( void );
    void showButton( void );
};

#endif // ITEMS_H
