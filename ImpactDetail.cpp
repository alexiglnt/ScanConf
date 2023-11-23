#include "impactDetail.h"

ImpactDetail::ImpactDetail()
{

}

void ImpactDetail::read(const QJsonObject &json) {
    value = json["value"].toDouble();
    min = json["min"].toDouble();
    max = json["max"].toDouble();
    QJsonArray warningsArray = json["warnings"].toArray();
    for (int warningIndex = 0; warningIndex < warningsArray.size(); ++warningIndex) {
        warnings.append(warningsArray[warningIndex].toString());
    }
}
