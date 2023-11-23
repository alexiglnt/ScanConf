#include "component.h"

Component::Component()
{

}

void Component::read(const QJsonObject &json) {
    impacts.read(json["impacts"].toObject());
    // Ajoutez la logique pour lire d'autres champs ici
}
