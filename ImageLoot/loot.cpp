#include "loot.h"

Loot *Loot::LootInstance = nullptr;

Loot::Loot(QObject *parent) : QObject(parent)
{

}


void Loot::setMaxSize(int max)
{
    this->maxSize=max;
}
void Loot::appendNew(QString url,QByteArray data)
{
    if(imageLoot.count()==maxSize){
        imageLoot.remove(imageLoot.firstKey());
    }
    this->imageLoot.insert(removeWWW(url),data);
}
QByteArray Loot::getImage(QString url)
{
    return this->imageLoot.value(removeWWW(url));
}
bool Loot::contains(QString url)
{
    return this->imageLoot.contains(removeWWW(url));
}

QString Loot::removeWWW(QString url)
{
    QString str=url;
    if(str.startsWith("https://"))
        str=str.remove("https://");
    if(str.startsWith("http://"))
        str=str.remove("http://");
    if(str.startsWith("www."))
        str=str.remove("www.");
    return str;
}


QString Loot::getFileType(QString url)
{
    return mimdb.mimeTypeForData(getImage(url)).name();
}
