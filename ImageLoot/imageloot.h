#ifndef IMAGELOOT_H
#define IMAGELOOT_H

#include <QQuickItem>
#include <QObject>
#include "loot.h"
#include "ServerConn/sendrequest.h"

class ImageLoot : public QQuickItem
{
    Q_OBJECT
        Q_PROPERTY(QString url READ getURL WRITE setURL)

private:
    QString url;

public:
    explicit ImageLoot(QQuickItem *parent = 0);
    ~ImageLoot();

    bool retried=false;
    Q_INVOKABLE QString getURL() ;
    Q_INVOKABLE void setURL(const QString &value);

signals:
    void dataReady(QString data);
    void dataEmpty();
    void imageError();

public slots:
    void getData(QByteArray data);
    void retryOnce(const QString url);
};

#endif // IMAGELOOT_H
