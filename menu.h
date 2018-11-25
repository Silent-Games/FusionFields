#ifndef MENU_H
#define MENU_H

#include "data.h"
#include "controller.h"
#include "config.h"
#include "ui_menu.h"
#include <QtWidgets>

class Controller;

class Menu : public QWidget, private Ui::Menu
{
  Q_OBJECT
  private:
    Controller *controller;

  public:
    explicit Menu( Controller *controller, QWidget *parent = 0 );

  public slots:
    void homeWidgetClicked( int section );
    void switchIsSoundMuted( void );

  protected:
    virtual void paintEvent( QPaintEvent * );

  signals:
    void muteButtonClicked( void );
};

#endif // MENU_H
