
#ifndef STATTOOL_H
#define STATTOOL_H

#include "demogCombo.h"
#include "psCombo.h"

#include "Visitor.h"
#include "stats.h"

/* wrapper for some useful functions to report necessary data */
class statTool {

public:

  /* call visitor pattern to create state data */
  static void createStateData(std::vector<shared_ptr<regionData> >& theData, Visitor& theStates);

  /* call visitor pattern to create county data */
  static  void createCountyData(std::vector<shared_ptr<regionData> >& theData, Visitor& theCounties);
  
  /* call visitor pattern to create aggregate data using a specific criteria */
  static  void createKeyData(std::vector<shared_ptr<regionData> >& theData, Visitor& theAggregator);

  /* helper functions to fill in arrays based on funciton pointers  - on mix*/
  static void gatherCountStats(visitorCombine* theAggregate, vector<double> &XPer, vector<double> &YPer, 
                int (demogCombo::*f1)() const, int (psCombo::*f2)() const);

  /* helper functions to fill in arrays based on funciton pointers  - on police hsooting only*/
  static void gatherCountStats(visitorCombine* theAggregate, vector<double> &XPer, vector<double> &YPer, 
                int (psCombo::*f1)() const, int (psCombo::*f2)() const);

  /* helper functions to fill in arrays based on funciton pointers  - on demog percentages*/
  static void gatherPerStats(visitorCombine*  theAggregate, vector<double> &XPer, vector<double> &YPer, 
                        double (demogCombo::*f1)() const, double (demogCombo::*f2)() const);

  /* percents and counts on demog */
  static int gatherBothStats(visitorCombine*  theAggregate, vector<double> &XPer, vector<double> &YPer,
                                    vector<double> &XCount, vector<double> &Ycount,
                                    double (demogCombo::*f1)() const, double (demogCombo::*f2)() const,
                                    int (demogCombo::*f3)() const, int (demogCombo::*f4)() const);
  
  /* compute statistics for demographic data for a given region expects, 
  the region and function pointers for the methods to fill in - mix ps and demog */
  static void computeStatsMixRegionData(visitorCombine*  theRegions, 
        int (demogCombo::*f1)() const, int (psCombo::*f2)() const);

  /* compute statistics for demographic data for a given region expects, 
  the region and function pointers for the methods to fill in - two demog fields */
  static void computeStatsDemogRegionData(visitorCombine*  theRegions, 
                                double  (demogCombo::*f1)()const, double(demogCombo::*f2)() const,
                                int (demogCombo::*f3)() const, int (demogCombo::*f4)() const);

  /* compute statistics for demographic data for a given region expects, 
  the region and function pointers for the methods to fill in - two police shooting fields */
  static void computeStatsPSData(visitorCombine*  theRegions, 
                                int (psCombo::*f1)()const, int (psCombo::*f2)() const);

};
#endif




