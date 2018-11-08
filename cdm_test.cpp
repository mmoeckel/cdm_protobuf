#include "ConjunctionDataMessage.h"

#include <iostream>

int main(int argc, char *argv[])
{
    ConjunctionDataMessage cdm;
    cdm.setHeader("1.0", "2010-03-12T22:31:12.000", "SERC", "T00000", "", "This is a test");
    cdm.setRelativeMetadata(cdm.formatDate(2018,9,7,4,8,3.3333333333), 0.002);
    cdm.setObject1Metadata("48113", "2019-001A", "EOSCAT", "ALWES-1", "NONE", CDM::CALCULATED, CDM::NOT_MANEUVERABLE, CDM::GCRF);
    cdm.setObject2Metadata("50129", "2020-014A", "EOSCAT", "PACMAN", "NONE", CDM::DEFAULT, CDM::NOT_MANEUVERABLE, CDM::GCRF);
    cdm.setObject1StateVector(9800.0,1277.3,868.22,0.01,0.67,7.34,"Not a proper orbit but considered valid");
    cdm.setObject2StateVector(9800.0,1277.3,868.22,0.01,0.67,7.34,"Not a proper orbit but considered valid");
    cdm.setRelativePosition(3.5, 6.7, 1.1);
    //std::cout << cdm.toKVN();

    ConjunctionDataMessage cdm2(cdm.toProtobufString());
    std::cout << cdm2.toKVN();
    //std::cout << cdm.toJSON() << std::endl;
    return 0;
}
