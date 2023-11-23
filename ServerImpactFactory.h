#ifndef SERVERIMPACTFACTORY_H
#define SERVERIMPACTFACTORY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>
#include <QNetworkRequest>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSharedPointer>

#include "serverImpact.h"

class ServerImpactFactory : public QObject
{
    Q_OBJECT

    QNetworkAccessManager *m_netManager;
    QNetworkReply *m_netReply;
    QByteArray *m_dataBuffer;
    ServerImpact* m_serverImpact;

public:
    explicit ServerImpactFactory(QObject *parent = nullptr);

    void postServerImpact(const QJsonObject* postData);

public slots:
    void readData();
    void finishReading();

signals:
    void endRead(ServerImpact* serverImpact);

};

#endif // SERVERIMPACTFACTORY_H
