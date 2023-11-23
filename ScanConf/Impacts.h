#ifndef IMPACTS_H
#define IMPACTS_H

#include "ImpactType.h"

class Impact
{
public:
    Impact();

    ImpactType gwp;
    ImpactType adp;
    ImpactType pe;

    void read(const QJsonObject &json);
};

#endif // IMPACTS_H
