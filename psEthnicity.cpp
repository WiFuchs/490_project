
#include <iostream>
#include <iomanip>
#include "psEthnicity.h"

std::ostream& operator<<(std::ostream &out, const psEthnicity &E) {
    out << "Racial Demographics Info:";
    out << std::setprecision(2) << std::fixed;
    double t = E.getTotalCount();
    out << "\n% American Indian and Alaska Native percent: " << (double(E.getNativeAmerican()) / t) * 100 << " count: " << E.getNativeAmerican();
    out << "\n% Asian American percent: " << (double(E.getAsian()) / t) * 100 << " count: " << E.getAsian();
    out << "\n% Black/African American percent:" << (double(E.getBlack()) / t) * 100 << " count: " << E.getBlack();
    out << "\n% Hispanic or Latinx percent:" << (double(E.getHispanic()) / t) * 100 << " count: " << E.getHispanic();
    out << "\n% Native Hawaiian and Other Pacific Islander count: " << 0;
    out << "\n% Two or More Races count: " << 0;
    out << "\n% White (inclusive) percent: " << (double(E.getWhiteNH()) / t) * 100 << " count: " << E.getWhiteNH(); //E.getHispanic() + E.getWhiteNH();
    out << "\n% White (nonHispanic) percent: " << (double(E.getWhiteNH()) / t) * 100 << " count: " << E.getWhiteNH();
    out << "\n% Other percent: " << (double(E.getOther()) / t) * 100 << " count: " << E.getOther(); //OFF
    out << "\ntotal Racial Demographic Count: " << E.getTotalCount();
    return out;
}