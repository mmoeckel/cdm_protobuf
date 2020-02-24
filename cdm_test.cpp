#include "CDMWriter.h"
#include "cdm.cpp.h"
#include "cdm_protobuf_adapter.h"

#include <iostream>

int main(int argc, char *argv[])
{
    CDMWriter writer;

    CDM_C::ConjunctionDataMessage cdm;

    cdm.header.CCSDS_CDM_VERS = "1.0";
    cdm.header.COMMENT = "This is a test";
    cdm.header.CREATION_DATE = "2010-03-12T22:31:12.000";
    cdm.header.ORIGINATOR = "SERC";
    cdm.header.MESSAGE_ID = "T00000";
    cdm.relativeMetadata.TCA = writer.formatDate(2018,9,7,4,8,3.3333333333);
    cdm.relativeMetadata.MISS_DISTANCE = 0.002;
    cdm.relativeMetadata.RELATIVE_POSITION_R = 3.5;
    cdm.relativeMetadata.RELATIVE_POSITION_T = 6.7;
    cdm.relativeMetadata.RELATIVE_POSITION_N = 1.1;
    cdm.object1Metadata.OBJECT_DESIGNATOR = "48113";
    cdm.object1Metadata.INTERNATIONAL_DESIGNATOR = "2019-001A";
    cdm.object1Metadata.CATALOG_NAME = "EOSCAT";
    cdm.object1Metadata.OBJECT_NAME = "TEST-1";
    cdm.object1Metadata.EPHEMERIS_NAME = "NONE";
    cdm.object1Metadata.COVARIANCE_METHOD = CDM_C::CALCULATED;
    cdm.object1Metadata.MANEUVERABLE = CDM_C::NO;
    cdm.object1Metadata.REF_FRAME = CDM_C::GCRF;
    cdm.object2Metadata.OBJECT_DESIGNATOR = "50129";
    cdm.object2Metadata.INTERNATIONAL_DESIGNATOR = "2020-014A";
    cdm.object2Metadata.CATALOG_NAME = "EOSCAT";
    cdm.object2Metadata.OBJECT_NAME = "TEST-2";
    cdm.object2Metadata.EPHEMERIS_NAME = "NONE";
    cdm.object2Metadata.COVARIANCE_METHOD = CDM_C::DEFAULT;
    cdm.object2Metadata.MANEUVERABLE = CDM_C::NO;
    cdm.object2Metadata.REF_FRAME = CDM_C::GCRF;
    cdm.object1Data.stateVector.COMMENT = "Not a proper orbit but considered valid";
    cdm.object1Data.stateVector.X = 9800.0;
    cdm.object1Data.stateVector.Y = 1277.3;
    cdm.object1Data.stateVector.Z = 868.22;
    cdm.object1Data.stateVector.X_DOT = 0.01;
    cdm.object1Data.stateVector.Y_DOT = 0.67;
    cdm.object1Data.stateVector.Z_DOT = 7.34;
    cdm.object2Data.stateVector.X = 9800.0;
    cdm.object2Data.stateVector.Y = 1277.3;
    cdm.object2Data.stateVector.Z = 868.22;
    cdm.object2Data.stateVector.X_DOT = 0.01;
    cdm.object2Data.stateVector.Y_DOT = 0.67;
    cdm.object2Data.stateVector.Z_DOT = 7.34;
    std::cout << writer.toKVN(cdm);    

    CDM::ConjunctionDataMessage protoCDM = CDM_PA::ConjunctionDataMessage(cdm);
    CDM_C::ConjunctionDataMessage cdm2 = CDM_PA::ConjunctionDataMessage(protoCDM);
    //std::cout << protoCDM.SerializeAsString() << std::endl;
    std::cout << writer.toKVN(cdm2);

    std::cout << writer.toJSON(cdm);

    return 0;
}
