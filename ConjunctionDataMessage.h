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

    ///brief Set message header fields, most of which are obligatory.
    ///
    /// \param version Format version in the form of ‘x.y’, where ‘y’ is incremented for corrections
    /// and minor changes, and ‘x’ is incremented for major changes.
    /// \param creationDate Message creation date/time in Coordinated Universal Time (UTC).
    /// Use the formatDate() function to create a string in the specified format.
    /// \param originator Creating agency or owner/operator. Value should be the ‘Abbreviation’ value
    /// from the SANA ‘Organizations’ registry (https://sanaregistry.org/r/organizations)
    /// for an organization that has the Role of ‘Conjunction Data Message Originator’.
    /// (See 5.2.9 for formatting rules.)
    /// \param messageFor Spacecraft name(s) for which the CDM is provided. Optional.
    /// \param comment A comment for the header. Optional.
    void setHeader(
            std::string version,
            std::string creationDate,
            std::string originator,
            std::string messageID,
            std::string messageFor = "",
            std::string comment = ""
            );

    /// brief Set obligatory relative metadata fields.
    ///
    /// \param tca The date and time in UTC of the closest approach. Use the formatDate() function
    /// to create a string in the specified format.
    /// \param missDistance The norm of the relative position vector, in metres. It indicates how
    /// close the two objects are at TCA.
    /// \param comment An optional comment for the relative metadata block.
    void setRelativeMetadata(
            std::string tca,
            double missDistance,
            std::string comment = ""
            );

    /// brief Set obligatory metadata fields for the first object.
    ///
    /// \param designator The satellite catalog designator for the object. (See 5.2.9 for formatting rules.)
    /// \param intDesignator The full international designator for the object. Values shall have the format
    /// YYYY-NNNP{PP}, where:
    /// YYYY = year of launch;
    /// NNN = three-digit serial number of launch (with leading zeros);
    /// P{PP} = At least one capital letter for the identification of the part brought into
    /// space by the launch. In cases where the object has no international designator, the
    /// value UNKNOWN should be used.
    /// (See 5.2.9 for further formatting rules.)
    /// \param catalogName The satellite catalog used for the object. Value should be taken from the SANA
    /// ‘Conjunction Data Message CATALOG_NAME’ registry (https://sanaregistry.org/r/cdm_catalog).
    /// (See 5.2.9 for formatting rules.)
    /// \param name Spacecraft name for the object.
    /// \param ephemerisName Unique name of the external ephemeris file used for the object or NONE. This is
    /// used to indicate whether an external (i.e., Owner/Operator [O/O] provided) ephemeris file was
    /// used to calculate the CA. If ‘NONE’ is specified, then the output of the most current
    /// Orbit Determination (OD) of the CDM originator was used in the CA.
    /// \param covMethod Method used to calculate the covariance during the OD that produced the state vector,
    /// or whether an arbitrary, non-calculated default value was used. Caution should be used when using the
    /// default value for calculating collision probability.
    /// \param maneuverable The maneuver capacity of the object. YES, NO, or N/A (not applicable or not available).
    /// \param frame Name of the reference frame in which the state vector data are given. Value must be
    /// the same for both Object1 and Object2.
    /// \param comment An optional comment for the first object's metadata block.
    void setObject1Metadata(
            std::string designator,
            std::string intDesignator,
            std::string catalogName,
            std::string name,
            std::string ephemerisName,
            CDM::CovarianceMethod covMethod,
            CDM::YesOrNo maneuverable,
            CDM::ReferenceFrame frame,
            std::string comment = ""
            );

    /// brief Set obligatory metadata fields for second object.
    ///
    /// \param designator The satellite catalog designator for the object. (See 5.2.9 for formatting rules.)
    /// \param intDesignator The full international designator for the object. Values shall have the format
    /// YYYY-NNNP{PP}, where:
    /// YYYY = year of launch;
    /// NNN = three-digit serial number of launch (with leading zeros);
    /// P{PP} = At least one capital letter for the identification of the part brought into
    /// space by the launch. In cases where the object has no international designator, the
    /// value UNKNOWN should be used.
    /// (See 5.2.9 for further formatting rules.)
    /// \param catalogName The satellite catalog used for the object. Value should be taken from the SANA
    /// ‘Conjunction Data Message CATALOG_NAME’ registry (https://sanaregistry.org/r/cdm_catalog).
    /// (See 5.2.9 for formatting rules.)
    /// \param name Spacecraft name for the object.
    /// \param ephemerisName Unique name of the external ephemeris file used for the object or NONE. This is
    /// used to indicate whether an external (i.e., Owner/Operator [O/O] provided) ephemeris file was
    /// used to calculate the CA. If ‘NONE’ is specified, then the output of the most current
    /// Orbit Determination (OD) of the CDM originator was used in the CA.
    /// \param covMethod Method used to calculate the covariance during the OD that produced the state vector,
    /// or whether an arbitrary, non-calculated default value was used. Caution should be used when using the
    /// default value for calculating collision probability.
    /// \param maneuverable The maneuver capacity of the object. YES, NO, or N/A (not applicable or not available).
    /// \param frame Name of the reference frame in which the state vector data are given. Value must be
    /// the same for both Object1 and Object2.
    /// \param comment An optional comment for the second object's metadata block.
    void setObject2Metadata(
            std::string designator,
            std::string intDesignator,
            std::string catalogName,
            std::string name,
            std::string ephemerisName,
            CDM::CovarianceMethod covMethod,
            CDM::YesOrNo maneuverable,
            CDM::ReferenceFrame frame,
            std::string comment = ""
            );

    /// brief Set obligatory state vector information for first object.
    ///
    /// \param positionX Object Position Vector X component, in km.
    /// \param positionY Object Position Vector Y component, in km.
    /// \param positionZ Object Position Vector Z component, in km.
    /// \param velocityX Object Velocity Vector X component, in km.
    /// \param velocityY Object Velocity Vector Y component, in km.
    /// \param velocityZ Object Velocity Vector Z component, in km.
    /// \param comment An optional comment for the first object's state vector.
    void setObject1StateVector(
            double positionX,
            double positionY,
            double positionZ,
            double velocityX,
            double velocityY,
            double velocityZ,
            std::string comment = ""
            );

    /// brief Set obligatory state vector information for second object.
    ///
    /// \param positionX Object Position Vector X component, in km.
    /// \param positionY Object Position Vector Y component, in km.
    /// \param positionZ Object Position Vector Z component, in km.
    /// \param velocityX Object Velocity Vector X component, in km.
    /// \param velocityY Object Velocity Vector Y component, in km.
    /// \param velocityZ Object Velocity Vector Z component, in km.
    /// \param comment An optional comment for the second object's state vector.
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

    void setRelativeSpeed(double v);
    void setRelativePosition(double r, double t, double n);
    void setRelativeVelocity(double r, double t, double n);

    ///brief Output in keyword=value notation
    std::string toKVN();

    ///brief Output in JSON
    std::string toJSON();

    ///brief Output as protocol buffer serialized string.
    std::string toProtobufString();

    CDM::ConjunctionDataMessage toProtobufMessage();

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

    std::string headerToKVN(CDM::Header header);
    std::string relativeMetadataToKVN(CDM::RelativeMetadata relativeMetadata);
    std::string objectMetadataToKVN(CDM::ObjectMetadata objectMeta);
    std::string objectDataToKVN(CDM::ObjectData objectData);

    std::string formatValue(std::string key, std::string value, std::string unit, bool obligatory);
    std::string formatValue(std::string key, double value, std::string unit, bool obligatory);
    std::string formatValue(std::string key, int value, std::string unit, bool obligatory);
    std::string formatComment(const std::string commentString);
    std::string formatObject(const CDM::ObjectNumber object);
    std::string formatCovarianceMethod(const CDM::CovarianceMethod covmeth);
    std::string formatReferenceFrame(const CDM::ReferenceFrame frame);
    std::string formatYesNo(const CDM::YesOrNo value);
    std::string formatObjectType(const CDM::ObjectType type);

};

#endif // CONJUNCTIONDATAMESSAGE_H
