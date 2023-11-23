#include "ImpactType.h"

ImpactType::ImpactType()
{

}

void ImpactType::read(const QJsonObject &json) {
    embedded.read(json["embedded"].toObject());
    use.read(json["use"].toObject());
    unit = json["unit"].toString();
    description = json["description"].toString();
}
