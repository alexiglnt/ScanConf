#ifndef IMPACTDETAIL_H
#define IMPACTDETAIL_H

#include <QStringList>
#include <QJsonObject>
#include <QJsonArray>

class ImpactDetail
{
public:
    ImpactDetail();

    double value;
    double min;
    double max;
    QStringList warnings;

    void read(const QJsonObject &json);
};

#endif // IMPACTDETAIL_H
