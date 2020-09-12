#include "imageloot.h"

Loot *loot=Loot::SingletonProvider();

ImageLoot::ImageLoot(QQuickItem *parent) : QQuickItem(parent)
{
}

ImageLoot::~ImageLoot()
{

}

QString ImageLoot::getURL()
{
    return url;
}
void ImageLoot::setURL(const QString &value)
{
    url=value;
    if(loot->contains(url)){
        emit dataReady("data:"+loot->getFileType(url)+";base64,"+loot->getImage(url).toBase64());
    } else {
        SendRequest * req = new SendRequest();
        connect(req,&SendRequest::setRespons,this,&ImageLoot::getData);
        req->sendRequest({}, url);
    }
}

void ImageLoot::getData(QByteArray data)
{
    if(data.contains(QByteArray::fromStdString("html"))){
        emit imageError();
    } else if(data.size()>0){
        loot->appendNew(url,data);
        emit dataReady("data:"+loot->getFileType(url)+";base64,"+data.toBase64());
    } else {
        emit dataEmpty();
    }
}

void ImageLoot::retryOnce(const QString url)
{
    if(!retried){
        ImageLoot::setURL(url);
    }
    retried=true;
}
