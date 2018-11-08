#ifndef CONJUNCTIONDATAMESSAGE_H
#define CONJUNCTIONDATAMESSAGE_H

#include "cdm.pb.h"
#include <string>
#include <vector>

class ConjunctionDataMessage
{
public:
    ConjunctionDataMessage();

    ConjunctionDataMessage(std::string received);

    ///brief Set message header fields
    void setHeader(
            std::string version,
            std::string creationDate,
            std::string originator,
            std::string messageID,
            std::string messageFor = "",
            std::string comment = ""
            );

    /// brief Set obligatory relative metadata fields
    void setRelativeMetadata(
            std::string tca,
            double missDistance,
            std::string comment = ""
            );

    /// brief Set obligatory metadata fields for first object
    void setObject1Metadata(
            std::string designator,
            std::string intDesignator,
            std::string catalogName,
            std::string name,
            std::string ephemerisName,
            CDM::CovarianceMethod covMethod,
            CDM::ManeuverabilityState maneuverable,
            CDM::ReferenceFrame frame,
            std::string comment = ""
            );

    /// brief Set obligatory metadata fields for second object
    void setObject2Metadata(
            std::string designator,
            std::string intDesignator,
            std::string catalogName,
            std::string name,
            std::string ephemerisName,
            CDM::CovarianceMethod covMethod,
            CDM::ManeuverabilityState maneuverable,
            CDM::ReferenceFrame frame,
            std::string comment = ""
            );

    /// brief Set obligatory state vector information for first object
    void setObject1StateVector(
            double positionX,
            double positionY,
            double positionZ,
            double velocityX,
            double velocityY,
            double velocityZ,
            std::string comment = ""
            );

    /// brief Set obligatory state vector information for second object
    void setObject2StateVector(
            double positionX,
            double positionY,
            double positionZ,
            double velocityX,
            double velocityY,
            double velocityZ,
            std::string comment = ""
            );

    /// brief Set covariance matrix information for first object
    void setObject1CovarianceMatrix(std::vector<double> covarianceMatrix, std::string comment = "");

    /// brief Set covariance matrix information for second object
    void setObject2CovarianceMatrix(std::vector<double> covarianceMatrix, std::string comment = "");

    ///brief Check whether all obligatory fields are set
    bool isComplete(); 

    ///brief Output in keyword=value notation
    std::string toKVN();

    ///brief Output in JSON
    std::string toJSON();

    std::string formatDate(
            const int year,
            const int month,
            const int day,
            const int hour,
            const int minute,
            const double second
            );

private:
    CDM::Header header;
    CDM::RelativeMetadata relativeMetadata;
    CDM::ObjectMetadata object1Meta;
    CDM::ObjectMetadata object2Meta;
    CDM::OdParameters object1ODParams;
    CDM::OdParameters object2ODParams;
    CDM::AdditionalParameters object1AdditionalParams;
    CDM::AdditionalParameters object2AdditionalParams;
    CDM::StateVector object1StateVector;
    CDM::StateVector object2StateVector;
    CDM::CovarianceMatrix object1CovMatrix;
    CDM::CovarianceMatrix object2CovMatrix;


    CDM::ConjunctionDataMessage buildMessage();

    std::string headerToKVN(CDM::Header header);
    std::string relativeMetadataToKVN(CDM::RelativeMetadata relativeMetadata);
    std::string objectMetadataToKVN(CDM::ObjectMetadata objectMeta);
    std::string objectDataToKVN(CDM::ObjectData objectData);

    std::string formatComment(const std::string commentString);
    std::string formatManeuverable(const CDM::ManeuverabilityState state);
    std::string formatObject(const CDM::ObjectNumber object);
    std::string formatCovarianceMethod(const CDM::CovarianceMethod covmeth);
    std::string formatReferenceFrame(const CDM::ReferenceFrame frame);
};

#endif // CONJUNCTIONDATAMESSAGE_H
