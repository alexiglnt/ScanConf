#ifndef IMPACTTYPE_H
#define IMPACTTYPE_H

#include <QString>
#include <QJsonObject>

#include "ImpactDetail.h"

class ImpactType
{
public:
    ImpactType();

    ImpactDetail embedded;
    ImpactDetail use;
    QString unit;
    QString description;

    void read(const QJsonObject &json);
};

#endif // IMPACTTYPE_H
