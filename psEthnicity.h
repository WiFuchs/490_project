//
// Created by Sarah Hallam on 2/1/22.
//
#ifndef INC_490_PROJECT_PSETHNICITY_H
#define INC_490_PROJECT_PSETHNICITY_H

class psEthnicity {
public:
    // White, non-Hispanic B: Black, non-Hispanic A: Asian N: Native American H: Hispanic O: Other None: unknown
    psEthnicity(int wnh, int black, int asian , int nativeA, int hispanic, int other, int tc) :
                whiteNH(wnh), black(black), asian(asian), nativeAmerican(nativeA), hispanic(hispanic), other(other), totalCount(tc) {}

    int getWhiteNH() const { return whiteNH; }
    int getBlack() const { return black; }
    int getAsian() const { return asian; }
    int getNativeAmerican() const { return nativeAmerican; }
    int getHispanic() const { return hispanic; }
    int getOther() const { return other; }
    int getTotalCount() const { return totalCount; }

    friend std::ostream& operator<<(std::ostream &out, const psEthnicity &E);

protected:
    const int whiteNH;
    const int black;
    const int asian;
    const int nativeAmerican;
    const int hispanic;
    const int other;
    const int totalCount;



};


#endif//INC_490_PROJECT_PSETHNICITY_H
