#ifndef SERVERIMPACT_H
#define SERVERIMPACT_H

#include "impacts.h"
#include "component.h"

struct ServerImpact {

    Impact globalImpacts;
    QMap<QString, Component> verbose;

};

#endif // SERVERIMPACT_H
