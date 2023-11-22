#ifndef SERVERIMPACT_H
#define SERVERIMPACT_H

#include <QString>

struct ImpactData {
    double value;
};

struct ImpactType {
    ImpactData* embedded;
    ImpactData* use;
    QString unit;
};

struct Impact {
    ImpactType* gwp;
    ImpactType* adp;
    ImpactType* pe;
};

struct Verbose {
    Impact* ASSEMBLY_1;
    Impact* CPU_1;
    Impact* RAM_1;
    Impact* SSD_1;
    Impact* POWER_SUPPLY_1;
    Impact* CASE_1;
    Impact* MOTHERBOARD_1;
};

struct ServerImpact {
    Impact* impacts;
    Verbose* verbose;
};

#endif // SERVERIMPACT_H
