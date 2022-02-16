#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "psData.h"
#include "Ethnicity.h"
#include "RegionData.h"

using namespace std;

class psCombo : public RegionData {
public:
    psCombo(string inS, int mentalI, int unArmedC, int armedToy, int bodyC, int cases, string region, Ethnicity eth) : RegionData(),
                                                                                                        state(inS), numMentalI(mentalI), unArmedCount(unArmedC), armedToy(armedToy), numBodyCam(bodyC),
                                                                                                        numberOfCases(cases), region(region), raceEthnicity(eth) {} //add
    //complete these
    int getNumMentalI() const { return numMentalI; } //total count “TRUE”
    int getUnArmedCount() const { return unArmedCount; } //total count blank, ‘unarmed’
    int getArmedToy() const { return armedToy; }  //total count ’toy weapon’
    int getNumBodyCam() const { return numBodyCam; } //total count “TRUE”
    int getNumberOfCases() const { return numberOfCases; } //total number for a region
    string getRegion() const { return region; } //return state for p2

    //add any others needed
    Ethnicity getRaceEthnicity() const { return raceEthnicity; }

    double getMentalIP() const { return (double(numMentalI) / double(numberOfCases)) * 100;}
    double getUnArmedP() const { return (double(unArmedCount) / double(numberOfCases)) * 100;}
    double getArmedToyP() const { return (double(armedToy) / double(numberOfCases)) * 100;}
    double getNumBodyCamP() const { return (double(numBodyCam) / double(numberOfCases)) * 100;}

    int getRealUnarmed() const { return unArmedCount + armedToy; } //number incidents unarmed or toy weapon
    double getRealUnarmedP() const { return (double(unArmedCount + armedToy) / double(numberOfCases)) * 100; }

    friend std::ostream& operator<<(std::ostream &out, const psCombo& PD);

protected:
    const string state;
    //add others
    const int numMentalI;
    const int unArmedCount;
    const int armedToy;
    const int numBodyCam;
    const int numberOfCases;
    const string region;
    const Ethnicity raceEthnicity;
};

#endif