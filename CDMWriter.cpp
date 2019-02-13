#include "CDMWriter.h"

#include <iomanip>
#include <sstream>

CDMWriter::CDMWriter()
{

}

bool CDMWriter::isComplete(CDM_C::ConjunctionDataMessage cdm)
{
    return (cdm.header.CCSDS_CDM_VERS.length() > 0
            && cdm.header.CREATION_DATE.length() > 0
            && cdm.header.ORIGINATOR.length() > 0
            && cdm.header.MESSAGE_ID.length() > 0

            && cdm.relativeMetadata.TCA.length() > 0
            && cdm.relativeMetadata.MISS_DISTANCE > 0.0

            && cdm.object1Metadata.OBJECT == CDM_C::OBJECT1
            && cdm.object1Metadata.OBJECT_DESIGNATOR.length() > 0
            && cdm.object1Metadata.CATALOG_NAME.length() > 0
            && cdm.object1Metadata.OBJECT_NAME.length() > 0
            && cdm.object1Metadata.INTERNATIONAL_DESIGNATOR.length() > 0
            && (cdm.object1Metadata.COVARIANCE_METHOD == CDM_C::CALCULATED || cdm.object1Metadata.COVARIANCE_METHOD == CDM_C::DEFAULT)
            && (cdm.object1Metadata.MANEUVERABLE == CDM_C::YES || cdm.object1Metadata.MANEUVERABLE == CDM_C::NO || cdm.object1Metadata.MANEUVERABLE == CDM_C::N_A)
            && (cdm.object1Metadata.REF_FRAME == CDM_C::GCRF || cdm.object1Metadata.REF_FRAME == CDM_C::EME2000 || cdm.object1Metadata.REF_FRAME == CDM_C::ITRF)

            && cdm.object2Metadata.OBJECT == CDM_C::OBJECT2
            && cdm.object2Metadata.OBJECT_DESIGNATOR.length() > 0
            && cdm.object2Metadata.CATALOG_NAME.length() > 0
            && cdm.object2Metadata.OBJECT_NAME.length() > 0
            && cdm.object2Metadata.INTERNATIONAL_DESIGNATOR.length() > 0
            && (cdm.object2Metadata.COVARIANCE_METHOD == CDM_C::CALCULATED || cdm.object2Metadata.COVARIANCE_METHOD == CDM_C::DEFAULT)
            && (cdm.object2Metadata.MANEUVERABLE == CDM_C::YES || cdm.object2Metadata.MANEUVERABLE == CDM_C::NO || cdm.object2Metadata.MANEUVERABLE == CDM_C::N_A)
            && (cdm.object2Metadata.REF_FRAME == CDM_C::GCRF || cdm.object2Metadata.REF_FRAME == CDM_C::EME2000 || cdm.object2Metadata.REF_FRAME == CDM_C::ITRF)

            // State vector is considered valid if at least one value is non-zero.
            // This doesn't catch invalid orbits but it catches forgetting to set it.
            && (cdm.object1Data.stateVector.X != 0.0 || cdm.object1Data.stateVector.Y != 0.0 || cdm.object1Data.stateVector.Z != 0.0 || cdm.object1Data.stateVector.X_DOT != 0.0 || cdm.object1Data.stateVector.Y_DOT != 0.0 || cdm.object1Data.stateVector.Z_DOT != 0.0)
            && (cdm.object2Data.stateVector.X != 0.0 || cdm.object2Data.stateVector.Y != 0.0 || cdm.object2Data.stateVector.Z != 0.0 || cdm.object2Data.stateVector.X_DOT != 0.0 || cdm.object2Data.stateVector.Y_DOT != 0.0 || cdm.object2Data.stateVector.Z_DOT != 0.0)

            );
}

// Output functions

std::string CDMWriter::toKVN(CDM_C::ConjunctionDataMessage cdm)
{
    // Just in case someone forgot this
    cdm.object1Metadata.OBJECT = CDM_C::OBJECT1;
    cdm.object2Metadata.OBJECT = CDM_C::OBJECT2;

    std::stringstream kvn;

    // Write header
    kvn << headerToKVN(cdm);
    kvn << relativeMetadataToKVN(cdm.relativeMetadata);
    kvn << objectMetadataToKVN(cdm.object1Metadata);
    kvn << objectDataToKVN(cdm.object1Data);
    kvn << objectMetadataToKVN(cdm.object2Metadata);
    kvn << objectDataToKVN(cdm.object2Data);
    // Return completed KVN CDM
    return kvn.str();
}

// Private auxiliary functions

std::string CDMWriter::headerToKVN(CDM_C::ConjunctionDataMessage cdm)
{
    CDM_C::Header header = cdm.header;
    // Add a warning to the header comment if CDM is incomplete
    std::stringstream headerComment;
    if (!isComplete(cdm))
    {
        headerComment << "Warning: Incomplete CDM! Not all obligatory fields are set!" << std::endl;
    }
    headerComment << header.COMMENT;

    std::stringstream kvn;
    kvn << formatValue("CCSDS_CDM_VERS", header.CCSDS_CDM_VERS, "", true);
    kvn << formatComment(headerComment.str());
    kvn << formatValue("CREATION_DATE", header.CREATION_DATE, "", true);
    kvn << formatValue("ORIGINATOR", header.ORIGINATOR, "", true);
    kvn << formatValue("MESSAGE_FOR", header.MESSAGE_FOR, "", false);
    kvn << formatValue("MESSAGE_ID", header.MESSAGE_ID, "", true);
    return kvn.str();
}

std::string CDMWriter::relativeMetadataToKVN(CDM_C::RelativeMetadata relativeMetadata)
{
    std::stringstream kvn;
    kvn << formatComment(relativeMetadata.COMMENT);
    kvn << formatValue("TCA", relativeMetadata.TCA, "", true);
    kvn << formatValue("MISS_DISTANCE", relativeMetadata.MISS_DISTANCE, "m", true);
    kvn << formatValue("RELATIVE_SPEED", relativeMetadata.RELATIVE_SPEED, "m/s", false);
    kvn << formatValue("RELATIVE_POSITION_R", relativeMetadata.RELATIVE_POSITION_R, "m", false);
    kvn << formatValue("RELATIVE_POSITION_T", relativeMetadata.RELATIVE_POSITION_T, "m", false);
    kvn << formatValue("RELATIVE_POSITION_N", relativeMetadata.RELATIVE_POSITION_N, "m", false);
    kvn << formatValue("RELATIVE_VELOCITY_R", relativeMetadata.RELATIVE_VELOCITY_R, "m/s", false);
    kvn << formatValue("RELATIVE_VELOCITY_T", relativeMetadata.RELATIVE_VELOCITY_T, "m/s", false);
    kvn << formatValue("RELATIVE_VELOCITY_N", relativeMetadata.RELATIVE_VELOCITY_N, "m/s", false);
    kvn << formatValue("START_SCREEN_PERIOD", relativeMetadata.START_SCREEN_PERIOD, "", false);
    kvn << formatValue("STOP_SCREEN_PERIOD", relativeMetadata.STOP_SCREEN_PERIOD, "", false);
    kvn << formatValue("SCREEN_VOLUME_FRAME", relativeMetadata.SCREEN_VOLUME_FRAME, "", false);
    kvn << formatValue("SCREEN_VOLUME_SHAPE", relativeMetadata.SCREEN_VOLUME_SHAPE, "", false);
    kvn << formatValue("SCREEN_VOLUME_X", relativeMetadata.SCREEN_VOLUME_X, "m", false);
    kvn << formatValue("SCREEN_VOLUME_Y", relativeMetadata.SCREEN_VOLUME_Y, "m", false);
    kvn << formatValue("SCREEN_VOLUME_Z", relativeMetadata.SCREEN_VOLUME_Z, "m", false);
    kvn << formatValue("SCREEN_ENTRY_TIME", relativeMetadata.SCREEN_ENTRY_TIME, "", false);
    kvn << formatValue("SCREEN_EXIT_TIME", relativeMetadata.SCREEN_EXIT_TIME, "", false);
    kvn << formatValue("COLLISION_PROBABILITY", relativeMetadata.COLLISION_PROBABILITY, "", false);
    kvn << formatValue("COLLISION_PROBABILITY_METHOD", relativeMetadata.COLLISION_PROBABILITY_METHOD, "", false);
    return kvn.str();
}

std::string CDMWriter::objectMetadataToKVN(CDM_C::ObjectMetadata objectMeta)
{
    std::stringstream kvn;
    kvn << formatComment(objectMeta.COMMENT);
    kvn << formatValue("OBJECT",                   formatObject(objectMeta.OBJECT), "", true);
    kvn << formatValue("OBJECT_DESIGNATOR",        objectMeta.OBJECT_DESIGNATOR, "", true);
    kvn << formatValue("CATALOG_NAME",             objectMeta.CATALOG_NAME, "", true);
    kvn << formatValue("OBJECT_NAME",              objectMeta.OBJECT_NAME, "", true);
    kvn << formatValue("INTERNATIONAL_DESIGNATOR", objectMeta.INTERNATIONAL_DESIGNATOR, "", true);
    kvn << formatValue("OBJECT_TYPE",              formatObjectType(objectMeta.OBJECT_TYPE), "", false);
    kvn << formatValue("OPERATOR_CONTACT_POSITION",objectMeta.OPERATOR_CONTACT_POSITION, "", false);
    kvn << formatValue("OPERATOR_ORGANIZATION",    objectMeta.OPERATOR_ORGANIZATION, "", false);
    kvn << formatValue("OPERATOR_PHONE",           objectMeta.OPERATOR_PHONE, "", false);
    kvn << formatValue("OPERATOR_EMAIL",           objectMeta.OPERATOR_EMAIL, "", false);
    kvn << formatValue("EPHEMERIS_NAME",           objectMeta.EPHEMERIS_NAME, "", true);
    kvn << formatValue("COVARIANCE_METHOD",        formatCovarianceMethod(objectMeta.COVARIANCE_METHOD), "", true);
    kvn << formatValue("MANEUVERABLE",             formatYesNo(objectMeta.MANEUVERABLE, true), "", true);
    kvn << formatValue("ORBIT_CENTER",             objectMeta.ORBIT_CENTER, "", false);
    kvn << formatValue("REF_FRAME",                formatReferenceFrame(objectMeta.REF_FRAME), "", true);
    kvn << formatValue("GRAVITY_MODEL",            objectMeta.GRAVITY_MODEL, "", false);
    kvn << formatValue("ATMOSPHERIC_MODEL",        objectMeta.ATMOSPHERIC_MODEL, "", false);
    kvn << formatValue("N_BODY_PERTURBATIONS",     objectMeta.N_BODY_PERTURBATIONS, "", false);
    kvn << formatValue("SOLAR_RAD_PRESSURE",       formatYesNo(objectMeta.SOLAR_RAD_PRESSURE, false), "", false);
    kvn << formatValue("EARTH_TIDES",              formatYesNo(objectMeta.EARTH_TIDES, false),"", false);
    kvn << formatValue("INTRACK_THRUST",           formatYesNo(objectMeta.INTRACK_THRUST, false), "", false);
    return kvn.str();
}

std::string CDMWriter::objectDataToKVN(CDM_C::ObjectData objectData)
{
    std::stringstream kvn;

    kvn << formatComment(objectData.COMMENT);

    CDM_C::OdParameters od = objectData.odParameters;
    kvn << formatComment(od.COMMENT);
    kvn << formatValue("TIME_LASTOB_START", od.TIME_LASTOB_START, "", false);
    kvn << formatValue("TIME_LASTOB_END", od.TIME_LASTOB_END, "", false);
    kvn << formatValue("RECOMMENDED_OD_SPAN", od.RECOMMENDED_OD_SPAN, "d", false);
    kvn << formatValue("ACTUAL_OD_SPAN", od.ACTUAL_OD_SPAN, "d", false);
    kvn << formatValue("OBS_AVAILABLE", (int)od.OBS_AVAILABLE, "", false);
    kvn << formatValue("OBS_USED", (int)od.OBS_USED, "", false);
    kvn << formatValue("TRACKS_AVAILABLE", (int)od.TRACKS_AVAILABLE, "", false);
    kvn << formatValue("TRACKS_USED", (int)od.TRACKS_USED, "", false);
    kvn << formatValue("RESIDUALS_ACCEPTED", od.RESIDUALS_ACCEPTED, "%", false);
    kvn << formatValue("WEIGHTED_RMS", od.WEIGHTED_RMS, "", false);

    CDM_C::AdditionalParameters ap = objectData.additionalParameters;
    kvn << formatComment(ap.COMMENT);
    kvn << formatValue("AREA_PC", ap.AREA_PC, "m**2", false);
    kvn << formatValue("AREA_DRG", ap.AREA_DRG, "m**2", false);
    kvn << formatValue("AREA_SRP", ap.AREA_SRP, "m**2", false);
    kvn << formatValue("MASS", ap.MASS, "kg", false);
    kvn << formatValue("CD_AREA_OVER_MASS", ap.CD_AREA_OVER_MASS, "m**2/kg", false);
    kvn << formatValue("CR_AREA_OVER_MASS", ap.CR_AREA_OVER_MASS, "m**2/kg", false);
    kvn << formatValue("THRUST_ACCELERATION", ap.THRUST_ACCELERATION, "m/s**2", false);
    kvn << formatValue("SEDR", ap.SEDR, "W/kg", false);

    CDM_C::StateVector objectStateVector = objectData.stateVector;
    kvn << formatComment(objectStateVector.COMMENT);
    kvn << formatValue("X", objectStateVector.X, "km", true);
    kvn << formatValue("Y", objectStateVector.Y, "km", true);
    kvn << formatValue("Z", objectStateVector.Z, "km", true);
    kvn << formatValue("X_DOT", objectStateVector.X_DOT, "km/s", true);
    kvn << formatValue("Y_DOT", objectStateVector.Y_DOT, "km/s", true);
    kvn << formatValue("Z_DOT", objectStateVector.Z_DOT, "km/s", true);

    CDM_C::CovarianceMatrix objectCovMatrix = objectData.covarianceMatrix;
    kvn << formatComment(objectCovMatrix.COMMENT);
    kvn << formatValue("CR_R",       objectCovMatrix.CR_R,       "m**2"     , true);
    kvn << formatValue("CT_R",       objectCovMatrix.CT_R,       "m**2"     , true);
    kvn << formatValue("CT_T",       objectCovMatrix.CT_T,       "m**2"     , true);
    kvn << formatValue("CN_R",       objectCovMatrix.CN_R,       "m**2"     , true);
    kvn << formatValue("CN_T",       objectCovMatrix.CN_T,       "m**2"     , true);
    kvn << formatValue("CN_N",       objectCovMatrix.CN_N,       "m**2"     , true);
    kvn << formatValue("CRDOT_R",    objectCovMatrix.CRDOT_R,    "m**2/s"   , true);
    kvn << formatValue("CRDOT_T",    objectCovMatrix.CRDOT_T,    "m**2/s"   , true);
    kvn << formatValue("CRDOT_N",    objectCovMatrix.CRDOT_N,    "m**2/s"   , true);
    kvn << formatValue("CRDOT_RDOT", objectCovMatrix.CRDOT_RDOT, "m**2/s**2", true);
    kvn << formatValue("CTDOT_R",    objectCovMatrix.CTDOT_R,    "m**2/s"   , true);
    kvn << formatValue("CTDOT_T",    objectCovMatrix.CTDOT_T,    "m**2/s"   , true);
    kvn << formatValue("CTDOT_N",    objectCovMatrix.CTDOT_N,    "m**2/s"   , true);
    kvn << formatValue("CTDOT_RDOT", objectCovMatrix.CTDOT_RDOT, "m**2/s**2", true);
    kvn << formatValue("CTDOT_TDOT", objectCovMatrix.CTDOT_TDOT, "m**2/s**2", true);
    kvn << formatValue("CNDOT_R",    objectCovMatrix.CNDOT_R,    "m**2/s"   , true);
    kvn << formatValue("CNDOT_T",    objectCovMatrix.CNDOT_T,    "m**2/s"   , true);
    kvn << formatValue("CNDOT_N",    objectCovMatrix.CNDOT_N,    "m**2/s"   , true);
    kvn << formatValue("CNDOT_RDOT", objectCovMatrix.CNDOT_RDOT, "m**2/s**2", true);
    kvn << formatValue("CNDOT_TDOT", objectCovMatrix.CNDOT_TDOT, "m**2/s**2", true);
    kvn << formatValue("CNDOT_NDOT", objectCovMatrix.CNDOT_NDOT, "m**2/s**2", true);
    kvn << formatValue("CDRG_R", objectCovMatrix.CDRG_R, "m**3/kg", false);
    kvn << formatValue("CDRG_T", objectCovMatrix.CDRG_T, "m**3/kg", false);
    kvn << formatValue("CDRG_N", objectCovMatrix.CDRG_N, "m**3/kg", false);
    kvn << formatValue("CDRG_RDOT", objectCovMatrix.CDRG_RDOT, "m**3/(kg*s)", false);
    kvn << formatValue("CDRG_TDOT", objectCovMatrix.CDRG_TDOT, "m**3/(kg*s)", false);
    kvn << formatValue("CDRG_NDOT", objectCovMatrix.CDRG_NDOT, "m**3/(kg*s)", false);
    kvn << formatValue("CDRG_DRG", objectCovMatrix.CDRG_DRG, "m**4/kg**2", false);
    kvn << formatValue("CSRP_R", objectCovMatrix.CSRP_R, "m**3/kg", false);
    kvn << formatValue("CSRP_T", objectCovMatrix.CSRP_T, "m**3/kg", false);
    kvn << formatValue("CSRP_N", objectCovMatrix.CSRP_N, "m**3/kg", false);
    kvn << formatValue("CSRP_RDOT", objectCovMatrix.CSRP_RDOT, "m**3/(kg*s)", false);
    kvn << formatValue("CSRP_TDOT", objectCovMatrix.CSRP_TDOT, "m**3/(kg*s)", false);
    kvn << formatValue("CSRP_NDOT", objectCovMatrix.CSRP_NDOT, "m**3/(kg*s)", false);
    kvn << formatValue("CSRP_DRG", objectCovMatrix.CSRP_DRG, "m**4/kg**2", false);
    kvn << formatValue("CSRP_SRP", objectCovMatrix.CSRP_SRP, "m**4/kg**2", false);
    kvn << formatValue("CTHR_R", objectCovMatrix.CTHR_R, "m**3/kg", false);
    kvn << formatValue("CTHR_T", objectCovMatrix.CTHR_T, "m**3/kg", false);
    kvn << formatValue("CTHR_N", objectCovMatrix.CTHR_N, "m**3/kg", false);
    kvn << formatValue("CTHR_RDOT", objectCovMatrix.CTHR_RDOT, "m**3/(kg*s)", false);
    kvn << formatValue("CTHR_TDOT", objectCovMatrix.CTHR_TDOT, "m**3/(kg*s)", false);
    kvn << formatValue("CTHR_NDOT", objectCovMatrix.CTHR_NDOT, "m**3/(kg*s)", false);
    kvn << formatValue("CTHR_DRG", objectCovMatrix.CTHR_DRG, "m**4/kg**2", false);
    kvn << formatValue("CTHR_SRP", objectCovMatrix.CTHR_SRP, "m**4/kg**2", false);
    kvn << formatValue("CTHR_THR", objectCovMatrix.CTHR_THR, "m**4/kg**2", false);
    return kvn.str();
}

std::string CDMWriter::formatValue(std::string key, std::string value, std::string unit, bool obligatory)
{
    std::stringstream line;
    if (obligatory || value.length() > 0)
    {
        line << std::setw(36) << std::left << key << "=" << std::setw(36) << std::left << value;
        if (unit != "") line << "[" << unit << "]";
        line << std::endl;
    }
    return line.str();
}

std::string CDMWriter::formatValue(std::string key, double value, std::string unit, bool obligatory)
{
    std::stringstream line;
    if (obligatory || value != 0.0)
    {
        line << std::setw(36) << std::left << key << "=" << std::setw(36) << std::left << value;
        if (unit != "") line << "[" << unit << "]";
        line << std::endl;
    }
    return line.str();
}

std::string CDMWriter::formatValue(std::string key, int value, std::string unit, bool obligatory)
{
    std::stringstream line;
    if (obligatory || value != 0)
    {
        line << std::setw(36) << std::left << key << "=" << std::setw(36) << std::left << value;
        if (unit != "") line << "[" << unit << "]";
        line << std::endl;
    }
    return line.str();
}

std::string CDMWriter::formatDate(const int year, const int month, const int day, const int hour, const int minute, const double second)
{
    std::stringstream dateString;
    if (year > 1900 && year < 10000 && month > 0 && month < 13 && day > 0 && day < 32
        && hour >= 0 && hour < 24 && minute >= 0 && minute < 60 && second > 0.0 && second < 60.0)
    {
        dateString << year << "-" << std::setfill('0') << std::setw(2) << month << "-" << std::setw(2) << day << "T"
                   << std::setw(2) << hour << ":" << std::setw(2) << minute << ":";
        if (second < 10.0) dateString << "0";
        dateString << std::setprecision(15) << second;
    }
    return dateString.str();
}

std::string CDMWriter::formatComment(const std::string commentString)
{
    if (commentString != "")
    {
        std::stringstream formattedComment;
        formattedComment << "COMMENT " << commentString << std::endl;
        return formattedComment.str();
    }
    else return "";
}

std::string CDMWriter::formatObject(const CDM_C::ObjectNumber object)
{
    if (object == CDM_C::OBJECT1) return "OBJECT1";
    else return "OBJECT2";
}

std::string CDMWriter::formatCovarianceMethod(const CDM_C::CovarianceMethod covmeth)
{
    if (covmeth == CDM_C::CALCULATED) return "CALCULATED";
    else return "DEFAULT";
}

std::string CDMWriter::formatReferenceFrame(const CDM_C::ReferenceFrame frame)
{
    if (frame == CDM_C::GCRF) return "GCRF";
    else if (frame == CDM_C::EME2000) return "EME2000";
    else return "ITRF";
}

std::string CDMWriter::formatYesNo(const CDM_C::YesOrNo value, bool allowNA)
{
    if (value == CDM_C::NO) return "NO";
    else if (value == CDM_C::YES) return "YES";
    else return (allowNA ? "N/A" : "");
}

std::string CDMWriter::formatObjectType(const CDM_C::ObjectType type)
{
    if (type == CDM_C::PAYLOAD) return "PAYLOAD";
    else if (type == CDM_C::ROCKET_BODY) return "ROCKET BODY";
    else if (type == CDM_C::DEBRIS) return "DEBRIS";
    else if (type == CDM_C::UNKNOWN) return "UNKNOWN";
    else return "OTHER";
}
