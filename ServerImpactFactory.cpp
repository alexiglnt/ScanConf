#include "serverImpactFactory.h"

ServerImpactFactory::ServerImpactFactory(QObject *parent)
    : QObject{parent}
    ,m_netManager(new QNetworkAccessManager)
    ,m_dataBuffer(new QByteArray)
    ,m_serverImpact(new ServerImpact)
{

}

void ServerImpactFactory::postServerImpact(const QJsonObject* requestBody)
{
    QNetworkRequest req{QUrl(QString("https://api.boavizta.org/v1/server/?archetype=compute_medium&verbose=true&criteria=gwp&criteria=adp&criteria=pe"))};
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    QJsonDocument jsonDocument(*requestBody);
    QByteArray postData = jsonDocument.toJson();

    m_netReply = m_netManager->post(req, postData);

    connect(m_netReply, &QNetworkReply::readyRead, this, &ServerImpactFactory::readData);
    connect(m_netReply, &QNetworkReply::finished, this, &ServerImpactFactory::finishReading);

}

void ServerImpactFactory::readData()
{
    m_dataBuffer->append(m_netReply->readAll());
}

void ServerImpactFactory::finishReading()
{
    m_serverImpact = new ServerImpact;

    if(m_netReply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error : " << m_netReply->errorString();
    }
    else
    {
        QJsonObject serverImpactJsonInfo = QJsonDocument::fromJson(*m_dataBuffer).object();

        Impact globalImpacts;
        globalImpacts.read(serverImpactJsonInfo["impacts"].toObject());

        QJsonObject verboseObj = serverImpactJsonInfo["verbose"].toObject();
        QMap<QString, Component> verbose;
        for (const QString &key : verboseObj.keys()) {
            Component component;
            component.read(verboseObj[key].toObject());
            verbose.insert(key, component);
        }

        m_serverImpact->globalImpacts = globalImpacts;
        m_serverImpact->verbose = verbose;

        m_dataBuffer->clear();
    }

    emit endRead(m_serverImpact);
}
