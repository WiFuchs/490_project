#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "psData.h"
#include "Ethnicity.h"
#include "RegionData.h"
#include "demogData.h"
#include "visitor.h"


using namespace std;

class psCombo : public RegionData, public std::enable_shared_from_this<psCombo> {
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

    void accept(class Visitor &v) override {
        v.visit(std::shared_from_this());
    }

    psCombo& operator+=(const psData &elem) {
        if (elem.getSignsMentalIllness() == "TRUE"){numMentalI += 1;}
        if (elem.getArmed() == "unarmed" or elem.getArmed() == "" or elem.getArmed() == "undetermined"){unArmedCount += 1;}
        if (elem.getArmed().find("toy") != string::npos){armedToy += 1;}
        if (elem.getBodyCam() == "TRUE"){numBodyCam += 1;}

        int Asian = 0;
        int Latinx = 0;
        int Black = 0;
        int WhiteNH = 0;
        int FirstNation = 0;
        int Unspecified = 0;

        if (elem.getEthnicity() == "A"){Asian += 1;}
        if (elem.getEthnicity() == "H"){Latinx += 1;}
        if (elem.getEthnicity() == "B"){Black += 1;}
        if (elem.getEthnicity() == "W"){WhiteNH += 1;}
        if (elem.getEthnicity() == "N"){FirstNation += 1;}
        if (elem.getEthnicity() == "O" or elem.getEthnicity() == ""){ Unspecified += 1;}
        raceEthnicity += Ethnicity(WhiteNH, Black, FirstNation, Asian, Latinx, Unspecified, 1);

        return *this;
    }

protected:
    const string state;
    //add others
    int numMentalI;
    int unArmedCount;
    int armedToy;
    int numBodyCam;
    int numberOfCases;
    const string region;
    Ethnicity raceEthnicity;
};

#endif