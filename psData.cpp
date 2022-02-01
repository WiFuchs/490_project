#include <sstream>
#include "psData.h"

/* print police data - fill in*/
std::ostream& operator<<(std::ostream &out, const psData &PD) {
    out << "Police Shotting Info: " << PD.state;
    out << "\nPerson name: " << PD.name;
    out << "\nRace: " << PD.ethnicity ;
    out << "\nArmed: " << PD.armed;
    out << "\nMental Illness: " << PD.signsMentalIllness; //True or False
    out << "\nBody Camera On: " << PD.bodyCam; //True or False
    return out;
}
