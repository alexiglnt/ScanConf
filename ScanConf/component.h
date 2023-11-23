#ifndef COMPONENT_H
#define COMPONENT_H

#include <QJsonObject>
#include <QVariant>

#include "Impacts.h"

class Component
{
public:
    Component();

    Impact impacts;
    QVariantMap additionalData; // Pour stocker d'autres données comme "duration", "units", etc.

    void read(const QJsonObject &json);
};

#endif // COMPONENT_H
