#include "Impacts.h"

Impact::Impact()
{

}

void Impact::read(const QJsonObject &json) {
    gwp.read(json["gwp"].toObject());
    adp.read(json["adp"].toObject());
    pe.read(json["pe"].toObject());
}
