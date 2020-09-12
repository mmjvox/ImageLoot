#ifndef LOOT_H
#define LOOT_H

#include <QObject>
#include <QMap>
#include <QMimeDatabase>

class Loot : public QObject
{
    Q_OBJECT
public:
    explicit Loot(QObject *parent = nullptr);
    static Loot *instance;
    static Loot *inst();
    static Loot *SingletonProvider () {
      if(!LootInstance){
          LootInstance = new Loot();
      }
      return LootInstance;
    }

    QMimeDatabase mimdb;

    void setMaxSize(int max);
    void appendNew(QString url,QByteArray data);
    QByteArray getImage(QString url);
    bool contains(QString url);
    QString getFileType(QString url);

private:
    static Loot* LootInstance;
    int maxSize=400;
    QMap<QString,QByteArray> imageLoot;
    QString removeWWW(QString url);

signals:

};

#endif // LOOT_H
