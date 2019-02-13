#ifndef CDM_WRITER_H
#define CDM_WRITER_H

#include "cdm.cpp.h"

#include <string>
#include <vector>

class CDMWriter
{
public:
    CDMWriter();

    ///brief Check whether all obligatory fields are set
    bool isComplete(CDM_C::ConjunctionDataMessage cdm);

    ///brief Output in keyword=value notation
    std::string toKVN(CDM_C::ConjunctionDataMessage cdm);

    /*
    ///brief Output in JSON
    std::string toJSON();

    ///brief Output as protocol buffer serialized string.
    std::string toProtobufString();

    CDMPB::ConjunctionDataMessage toProtobufMessage(CDM::ConjunctionDataMessage message);
    */

    std::string formatDate(
            const int year,
            const int month,
            const int day,
            const int hour,
            const int minute,
            const double second
            );

private:   
    std::string headerToKVN(CDM_C::ConjunctionDataMessage cdm);
    std::string relativeMetadataToKVN(CDM_C::RelativeMetadata relativeMetadata);
    std::string objectMetadataToKVN(CDM_C::ObjectMetadata objectMeta);
    std::string objectDataToKVN(CDM_C::ObjectData objectData);

    std::string formatValue(std::string key, std::string value, std::string unit, bool obligatory);
    std::string formatValue(std::string key, double value, std::string unit, bool obligatory);
    std::string formatValue(std::string key, int value, std::string unit, bool obligatory);
    std::string formatComment(const std::string commentString);
    std::string formatObject(const CDM_C::ObjectNumber object);
    std::string formatCovarianceMethod(const CDM_C::CovarianceMethod covmeth);
    std::string formatReferenceFrame(const CDM_C::ReferenceFrame frame);
    std::string formatYesNo(const CDM_C::YesOrNo value, bool allowNA);
    std::string formatObjectType(const CDM_C::ObjectType type);
};

#endif // CONJUNCTIONDATAMESSAGE_H
