#ifndef POLICE_H
#define POLICE_H

#include <string>
#include <iostream>
#include <utility>
#include "RegionData.h"

using namespace std;

/*
  class to represent police shooting data
  from Washington Post
*/
class psData : public RegionData {
public:
    //add appropriate function paramaters to constructor once you add data
    psData(string inState, string city, string name, string eth, string mentalIll,
           string armed, string bodyCam) : RegionData(), state(inState), city(city), name(name), ethnicity(eth),
                                           signsMentalIllness(mentalIll), armed(armed), bodyCam(bodyCam)  {}

    string getState() const { return state; }
    //add getters

    string getCity() const { return city; }
    string getName() const { return name; }
    string getEthnicity() const { return ethnicity; }

    string getSignsMentalIllness() const { return signsMentalIllness; }
    string getArmed() const { return armed; }
    string getBodyCam() const { return bodyCam; }

    friend std::ostream& operator<<(std::ostream &out, const psData &PD);

private:
    const string state;
    //add others
    const string city;
    const string name;
    const string ethnicity;
    const string signsMentalIllness;
    const string armed;
    const string bodyCam;

};

#endif
