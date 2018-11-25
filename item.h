#ifndef ITEM_H
#define ITEM_H

#include <QObject>

class Item : public QObject
{
    Q_OBJECT
  private:
    int id;
    QString name;
    QString description;
    int cost;
    bool isUnlocked;

  public:
    Item( QObject *parent = 0 );
    void setId( int id );
    int getId( void );
    void setName( QString name );
    QString getName( void );
    void setDescription( QString description );
    QString getDescription( void );
    void setCost( int cost );
    int getCost( void );
    void setIsItemUnlocked( bool state );
    bool isItemUnlocked( void );
};

#endif // ITEM_H
