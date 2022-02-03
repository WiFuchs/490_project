#include <iomanip>
#include "psCombo.h"
#include <cmath>

/* print state data - as aggregate of all incidents in this state */
std::ostream& operator<<(std::ostream &out, const psCombo& PD) {
    out << "census data:" << endl;
    out << "Region Info: " << PD.state;
    out << "\nNumber of incidents: " << PD.getNumberOfCases();
    out << std::setprecision(2) << std::fixed;
    out << "\nIncidents involving unarmed or armed with toy weapons: " << PD.getRealUnarmed() << ", " << PD.getRealUnarmedP() <<"%"; //Real = unarmed + toy
    out << "\nIncidents involving mental illness: " << PD.getNumMentalI() << ", " << PD.getMentalIP() <<"%";
    out << "\nIncidents with body camera on: " << PD.getNumBodyCam() << ", " << PD.getNumBodyCamP() <<"%";
    out << "\nRacial demographics of state incidents: " << PD.getRaceEthnicity();
    return out;
}