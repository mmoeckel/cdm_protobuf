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
    outputMode mode = OUT_KVN;

    // Write header
    kvn << headerToText(cdm, mode);
    kvn << relativeMetadataToText(cdm.relativeMetadata, mode);
    kvn << objectMetadataToText(cdm.object1Metadata, mode);
    kvn << objectDataToText(cdm.object1Data, mode);
    kvn << objectMetadataToText(cdm.object2Metadata, mode);
    kvn << objectDataToText(cdm.object2Data, mode);
    // Return completed KVN CDM
    return kvn.str();
}

std::string CDMWriter::toJSON(CDM_C::ConjunctionDataMessage cdm)
{
    // Just in case someone forgot this
    cdm.object1Metadata.OBJECT = CDM_C::OBJECT1;
    cdm.object2Metadata.OBJECT = CDM_C::OBJECT2;

    std::stringstream out;
    outputMode mode = OUT_JSON;

    // Write header
    out << "{" << std::endl;
    out << headerToText(cdm, mode) << "," << std::endl;
    out << relativeMetadataToText(cdm.relativeMetadata, mode) << "," << std::endl;
    out << "\"OBJECT1\": {" << std::endl;
    out << objectMetadataToText(cdm.object1Metadata, mode) << "," << std::endl;
    out << objectDataToText(cdm.object1Data, mode) << std::endl;
    out << "}," << std::endl;
    out << "\"OBJECT2\": {" << std::endl;
    out << objectMetadataToText(cdm.object2Metadata, mode) << "," << std::endl;
    out << objectDataToText(cdm.object2Data, mode) << std::endl;
    out << "}" << std::endl;
    out << "}" << std::endl;
    return out.str();
}

// Private auxiliary functions

std::string CDMWriter::headerToText(CDM_C::ConjunctionDataMessage cdm, outputMode mode)
{
    CDM_C::Header header = cdm.header;
    // Add a warning to the header comment if CDM is incomplete
    std::stringstream headerComment;
    if (!isComplete(cdm))
    {
        headerComment << "Warning: Incomplete CDM! Not all obligatory fields are set!" << std::endl;
    }
    headerComment << header.COMMENT;

    std::stringstream out;
    if (mode == OUT_JSON) out << "\"HEADER\": {" << std::endl;
    out << formatValue("CCSDS_CDM_VERS", header.CCSDS_CDM_VERS, "", true, mode);
    out << formatComment(headerComment.str(), mode);
    out << formatValue("CREATION_DATE", header.CREATION_DATE, "", true, mode);
    out << formatValue("ORIGINATOR", header.ORIGINATOR, "", true, mode);
    out << formatValue("MESSAGE_FOR", header.MESSAGE_FOR, "", false, mode);
    out << formatValue("MESSAGE_ID", header.MESSAGE_ID, "", true, mode);
    if (mode == OUT_JSON) { out.seekp(-2, out.cur); out << "}"; }
    return out.str();
}

std::string CDMWriter::relativeMetadataToText(CDM_C::RelativeMetadata relativeMetadata, outputMode mode)
{
    std::stringstream out;
    if (mode == OUT_JSON) out << "\"RELATIVE_METADATA\": {" << std::endl;
    out << formatComment(relativeMetadata.COMMENT, mode);
    out << formatValue("TCA", relativeMetadata.TCA, "", true, mode);
    out << formatValue("MISS_DISTANCE", relativeMetadata.MISS_DISTANCE, "m", true, mode);
    out << formatValue("RELATIVE_SPEED", relativeMetadata.RELATIVE_SPEED, "m/s", false, mode);
    out << formatValue("RELATIVE_POSITION_R", relativeMetadata.RELATIVE_POSITION_R, "m", false, mode);
    out << formatValue("RELATIVE_POSITION_T", relativeMetadata.RELATIVE_POSITION_T, "m", false, mode);
    out << formatValue("RELATIVE_POSITION_N", relativeMetadata.RELATIVE_POSITION_N, "m", false, mode);
    out << formatValue("RELATIVE_VELOCITY_R", relativeMetadata.RELATIVE_VELOCITY_R, "m/s", false, mode);
    out << formatValue("RELATIVE_VELOCITY_T", relativeMetadata.RELATIVE_VELOCITY_T, "m/s", false, mode);
    out << formatValue("RELATIVE_VELOCITY_N", relativeMetadata.RELATIVE_VELOCITY_N, "m/s", false, mode);
    out << formatValue("START_SCREEN_PERIOD", relativeMetadata.START_SCREEN_PERIOD, "", false, mode);
    out << formatValue("STOP_SCREEN_PERIOD", relativeMetadata.STOP_SCREEN_PERIOD, "", false, mode);
    out << formatValue("SCREEN_VOLUME_FRAME", relativeMetadata.SCREEN_VOLUME_FRAME, "", false, mode);
    out << formatValue("SCREEN_VOLUME_SHAPE", relativeMetadata.SCREEN_VOLUME_SHAPE, "", false, mode);
    out << formatValue("SCREEN_VOLUME_X", relativeMetadata.SCREEN_VOLUME_X, "m", false, mode);
    out << formatValue("SCREEN_VOLUME_Y", relativeMetadata.SCREEN_VOLUME_Y, "m", false, mode);
    out << formatValue("SCREEN_VOLUME_Z", relativeMetadata.SCREEN_VOLUME_Z, "m", false, mode);
    out << formatValue("SCREEN_ENTRY_TIME", relativeMetadata.SCREEN_ENTRY_TIME, "", false, mode);
    out << formatValue("SCREEN_EXIT_TIME", relativeMetadata.SCREEN_EXIT_TIME, "", false, mode);
    out << formatValue("COLLISION_PROBABILITY", relativeMetadata.COLLISION_PROBABILITY, "", false, mode);
    out << formatValue("COLLISION_PROBABILITY_METHOD", formatCollisionProbabilityMethod(relativeMetadata.COLLISION_PROBABILITY_METHOD), "", false, mode);
    if (mode == OUT_JSON) out << formatValue("EXT_COLLISION_PROBABILITY_MAX", relativeMetadata.EXT_COLLISION_PROBABILITY_MAX, "", false, mode);
    if (mode == OUT_JSON) { out.seekp(-2, out.cur); out << "}"; }
    return out.str();
}

std::string CDMWriter::objectMetadataToText(CDM_C::ObjectMetadata objectMeta, outputMode mode)
{
    std::stringstream out;
    if (mode == OUT_JSON) out << "\"OBJECT_METADATA\": {" << std::endl;
    out << formatComment(objectMeta.COMMENT, mode);
    out << formatValue("OBJECT",                   formatObject(objectMeta.OBJECT), "", true, mode);
    out << formatValue("OBJECT_DESIGNATOR",        objectMeta.OBJECT_DESIGNATOR, "", true, mode);
    out << formatValue("CATALOG_NAME",             objectMeta.CATALOG_NAME, "", true, mode);
    out << formatValue("OBJECT_NAME",              objectMeta.OBJECT_NAME, "", true, mode);
    out << formatValue("INTERNATIONAL_DESIGNATOR", objectMeta.INTERNATIONAL_DESIGNATOR, "", true, mode);
    out << formatValue("OBJECT_TYPE",              formatObjectType(objectMeta.OBJECT_TYPE), "", false, mode);
    out << formatValue("OPERATOR_CONTACT_POSITION",objectMeta.OPERATOR_CONTACT_POSITION, "", false, mode);
    out << formatValue("OPERATOR_ORGANIZATION",    objectMeta.OPERATOR_ORGANIZATION, "", false, mode);
    out << formatValue("OPERATOR_PHONE",           objectMeta.OPERATOR_PHONE, "", false, mode);
    out << formatValue("OPERATOR_EMAIL",           objectMeta.OPERATOR_EMAIL, "", false, mode);
    out << formatValue("EPHEMERIS_NAME",           objectMeta.EPHEMERIS_NAME, "", true, mode);
    out << formatValue("COVARIANCE_METHOD",        formatCovarianceMethod(objectMeta.COVARIANCE_METHOD), "", true, mode);
    out << formatValue("MANEUVERABLE",             formatYesNo(objectMeta.MANEUVERABLE, true), "", true, mode);
    out << formatValue("ORBIT_CENTER",             objectMeta.ORBIT_CENTER, "", false, mode);
    out << formatValue("REF_FRAME",                formatReferenceFrame(objectMeta.REF_FRAME), "", true, mode);
    out << formatValue("GRAVITY_MODEL",            objectMeta.GRAVITY_MODEL, "", false, mode);
    out << formatValue("ATMOSPHERIC_MODEL",        objectMeta.ATMOSPHERIC_MODEL, "", false, mode);
    out << formatValue("N_BODY_PERTURBATIONS",     objectMeta.N_BODY_PERTURBATIONS, "", false, mode);
    out << formatValue("SOLAR_RAD_PRESSURE",       formatYesNo(objectMeta.SOLAR_RAD_PRESSURE, false), "", false, mode);
    out << formatValue("EARTH_TIDES",              formatYesNo(objectMeta.EARTH_TIDES, false),"", false, mode);
    out << formatValue("INTRACK_THRUST",           formatYesNo(objectMeta.INTRACK_THRUST, false), "", false, mode);
    if (mode == OUT_JSON) { out.seekp(-2, out.cur); out << "}"; }
    return out.str();
}

std::string CDMWriter::objectDataToText(CDM_C::ObjectData objectData, outputMode mode)
{
    std::stringstream out;
    if (mode == OUT_JSON) out << "\"OBJECT_DATA\": {" << std::endl;

    out << formatComment(objectData.COMMENT, mode);

    CDM_C::OdParameters od = objectData.odParameters;
    std::stringstream odstr;

    odstr << formatComment(od.COMMENT, mode);
    odstr << formatValue("TIME_LASTOB_START", od.TIME_LASTOB_START, "", false, mode);
    odstr << formatValue("TIME_LASTOB_END", od.TIME_LASTOB_END, "", false, mode);
    odstr << formatValue("RECOMMENDED_OD_SPAN", od.RECOMMENDED_OD_SPAN, "d", false, mode);
    odstr << formatValue("ACTUAL_OD_SPAN", od.ACTUAL_OD_SPAN, "d", false, mode);
    odstr << formatValue("OBS_AVAILABLE", (int)od.OBS_AVAILABLE, "", false, mode);
    odstr << formatValue("OBS_USED", (int)od.OBS_USED, "", false, mode);
    odstr << formatValue("TRACKS_AVAILABLE", (int)od.TRACKS_AVAILABLE, "", false, mode);
    odstr << formatValue("TRACKS_USED", (int)od.TRACKS_USED, "", false, mode);
    odstr << formatValue("RESIDUALS_ACCEPTED", od.RESIDUALS_ACCEPTED, "%", false, mode);
    odstr << formatValue("WEIGHTED_RMS", od.WEIGHTED_RMS, "", false, mode);
    if (odstr.str() != "")
    {
        if (mode == OUT_JSON) out << "\"OD_PARAMETERS\": {" << std::endl;
        out << odstr.str();
        if (mode == OUT_JSON) { out.seekp(-2, out.cur); out << "}," << std::endl; }
    }

    CDM_C::AdditionalParameters ap = objectData.additionalParameters;
    std::stringstream apstr;

    apstr << formatComment(ap.COMMENT, mode);
    apstr << formatValue("AREA_PC", ap.AREA_PC, "m**2", false, mode);
    apstr << formatValue("AREA_DRG", ap.AREA_DRG, "m**2", false, mode);
    apstr << formatValue("AREA_SRP", ap.AREA_SRP, "m**2", false, mode);
    apstr << formatValue("MASS", ap.MASS, "kg", false, mode);
    apstr << formatValue("CD_AREA_OVER_MASS", ap.CD_AREA_OVER_MASS, "m**2/kg", false, mode);
    apstr << formatValue("CR_AREA_OVER_MASS", ap.CR_AREA_OVER_MASS, "m**2/kg", false, mode);
    apstr << formatValue("THRUST_ACCELERATION", ap.THRUST_ACCELERATION, "m/s**2", false, mode);
    apstr << formatValue("SEDR", ap.SEDR, "W/kg", false, mode);
    if (apstr.str() != "")
    {
        if (mode == OUT_JSON) out << "\"ADDITIONAL_PARAMETERS\": {" << std::endl;
        out << apstr.str();
        if (mode == OUT_JSON) { out.seekp(-2, out.cur); out << "}," << std::endl; }
    }

    CDM_C::StateVector objectStateVector = objectData.stateVector;
    if (mode == OUT_JSON) out << "\"STATE_VECTOR\": {" << std::endl;
    out << formatComment(objectStateVector.COMMENT, mode);
    out << formatValue("X", objectStateVector.X, "km", true, mode);
    out << formatValue("Y", objectStateVector.Y, "km", true, mode);
    out << formatValue("Z", objectStateVector.Z, "km", true, mode);
    out << formatValue("X_DOT", objectStateVector.X_DOT, "km/s", true, mode);
    out << formatValue("Y_DOT", objectStateVector.Y_DOT, "km/s", true, mode);
    out << formatValue("Z_DOT", objectStateVector.Z_DOT, "km/s", true, mode);
    if (mode == OUT_JSON) { out.seekp(-2, out.cur); out << "}," << std::endl; }

    CDM_C::CovarianceMatrix objectCovMatrix = objectData.covarianceMatrix;
    if (mode == OUT_JSON) out << "\"COVARIANCE_MATRIX\": {" << std::endl;
    out << formatComment(objectCovMatrix.COMMENT, mode);
    out << formatValue("CR_R",       objectCovMatrix.CR_R,       "m**2"     , true, mode);
    out << formatValue("CT_R",       objectCovMatrix.CT_R,       "m**2"     , true, mode);
    out << formatValue("CT_T",       objectCovMatrix.CT_T,       "m**2"     , true, mode);
    out << formatValue("CN_R",       objectCovMatrix.CN_R,       "m**2"     , true, mode);
    out << formatValue("CN_T",       objectCovMatrix.CN_T,       "m**2"     , true, mode);
    out << formatValue("CN_N",       objectCovMatrix.CN_N,       "m**2"     , true, mode);
    out << formatValue("CRDOT_R",    objectCovMatrix.CRDOT_R,    "m**2/s"   , true, mode);
    out << formatValue("CRDOT_T",    objectCovMatrix.CRDOT_T,    "m**2/s"   , true, mode);
    out << formatValue("CRDOT_N",    objectCovMatrix.CRDOT_N,    "m**2/s"   , true, mode);
    out << formatValue("CRDOT_RDOT", objectCovMatrix.CRDOT_RDOT, "m**2/s**2", true, mode);
    out << formatValue("CTDOT_R",    objectCovMatrix.CTDOT_R,    "m**2/s"   , true, mode);
    out << formatValue("CTDOT_T",    objectCovMatrix.CTDOT_T,    "m**2/s"   , true, mode);
    out << formatValue("CTDOT_N",    objectCovMatrix.CTDOT_N,    "m**2/s"   , true, mode);
    out << formatValue("CTDOT_RDOT", objectCovMatrix.CTDOT_RDOT, "m**2/s**2", true, mode);
    out << formatValue("CTDOT_TDOT", objectCovMatrix.CTDOT_TDOT, "m**2/s**2", true, mode);
    out << formatValue("CNDOT_R",    objectCovMatrix.CNDOT_R,    "m**2/s"   , true, mode);
    out << formatValue("CNDOT_T",    objectCovMatrix.CNDOT_T,    "m**2/s"   , true, mode);
    out << formatValue("CNDOT_N",    objectCovMatrix.CNDOT_N,    "m**2/s"   , true, mode);
    out << formatValue("CNDOT_RDOT", objectCovMatrix.CNDOT_RDOT, "m**2/s**2", true, mode);
    out << formatValue("CNDOT_TDOT", objectCovMatrix.CNDOT_TDOT, "m**2/s**2", true, mode);
    out << formatValue("CNDOT_NDOT", objectCovMatrix.CNDOT_NDOT, "m**2/s**2", true, mode);
    out << formatValue("CDRG_R", objectCovMatrix.CDRG_R, "m**3/kg", false, mode);
    out << formatValue("CDRG_T", objectCovMatrix.CDRG_T, "m**3/kg", false, mode);
    out << formatValue("CDRG_N", objectCovMatrix.CDRG_N, "m**3/kg", false, mode);
    out << formatValue("CDRG_RDOT", objectCovMatrix.CDRG_RDOT, "m**3/(kg*s)", false, mode);
    out << formatValue("CDRG_TDOT", objectCovMatrix.CDRG_TDOT, "m**3/(kg*s)", false, mode);
    out << formatValue("CDRG_NDOT", objectCovMatrix.CDRG_NDOT, "m**3/(kg*s)", false, mode);
    out << formatValue("CDRG_DRG", objectCovMatrix.CDRG_DRG, "m**4/kg**2", false, mode);
    out << formatValue("CSRP_R", objectCovMatrix.CSRP_R, "m**3/kg", false, mode);
    out << formatValue("CSRP_T", objectCovMatrix.CSRP_T, "m**3/kg", false, mode);
    out << formatValue("CSRP_N", objectCovMatrix.CSRP_N, "m**3/kg", false, mode);
    out << formatValue("CSRP_RDOT", objectCovMatrix.CSRP_RDOT, "m**3/(kg*s)", false, mode);
    out << formatValue("CSRP_TDOT", objectCovMatrix.CSRP_TDOT, "m**3/(kg*s)", false, mode);
    out << formatValue("CSRP_NDOT", objectCovMatrix.CSRP_NDOT, "m**3/(kg*s)", false, mode);
    out << formatValue("CSRP_DRG", objectCovMatrix.CSRP_DRG, "m**4/kg**2", false, mode);
    out << formatValue("CSRP_SRP", objectCovMatrix.CSRP_SRP, "m**4/kg**2", false, mode);
    out << formatValue("CTHR_R", objectCovMatrix.CTHR_R, "m**3/kg", false, mode);
    out << formatValue("CTHR_T", objectCovMatrix.CTHR_T, "m**3/kg", false, mode);
    out << formatValue("CTHR_N", objectCovMatrix.CTHR_N, "m**3/kg", false, mode);
    out << formatValue("CTHR_RDOT", objectCovMatrix.CTHR_RDOT, "m**3/(kg*s)", false, mode);
    out << formatValue("CTHR_TDOT", objectCovMatrix.CTHR_TDOT, "m**3/(kg*s)", false, mode);
    out << formatValue("CTHR_NDOT", objectCovMatrix.CTHR_NDOT, "m**3/(kg*s)", false, mode);
    out << formatValue("CTHR_DRG", objectCovMatrix.CTHR_DRG, "m**4/kg**2", false, mode);
    out << formatValue("CTHR_SRP", objectCovMatrix.CTHR_SRP, "m**4/kg**2", false, mode);
    out << formatValue("CTHR_THR", objectCovMatrix.CTHR_THR, "m**4/kg**2", false, mode);
    if (mode == OUT_JSON) { out.seekp(-2, out.cur); out << "}" << std::endl; }
    if (mode == OUT_JSON) out << "}" << std::endl;
    return out.str();
}

std::string CDMWriter::formatValue(std::string key, std::string value, std::string unit, bool obligatory, outputMode mode)
{
    std::stringstream line;
    if (obligatory || value.length() > 0)
    {
        if (mode == OUT_KVN)
        {
            line << std::setw(36) << std::left << key << "=" << std::setw(36) << std::left << value;
            if (unit != "") line << "[" << unit << "]";
            line << std::endl;
        }
        else {
            line << "\"" << key << "\": \"" << value << "\"";
            line << "," << std::endl;
        }
    }
    return line.str();
}

std::string CDMWriter::formatValue(std::string key, double value, std::string unit, bool obligatory, outputMode mode)
{
    std::stringstream line;
    if (obligatory || value != 0.0)
    {
        if (mode == OUT_KVN)
        {
            line << std::setw(36) << std::left << key << "=" << std::setw(36) << std::left << std::setprecision(15) << value;
            if (unit != "") line << "[" << unit << "]";
            line << std::endl;
        }
        else {
            line << "\"" << key << "\": " << std::setprecision(15) << value;
            line << "," << std::endl;
        }
    }
    return line.str();
}

std::string CDMWriter::formatValue(std::string key, int value, std::string unit, bool obligatory, outputMode mode)
{
    std::stringstream line;
    if (obligatory || value != 0)
    {
        if (mode == OUT_KVN)
        {
            line << std::setw(36) << std::left << key << "=" << std::setw(36) << std::left << value;
            if (unit != "") line << "[" << unit << "]";
            line << std::endl;
        }
        else {
            line << "\"" << key << "\": " << value;
            line << "," << std::endl;
        }
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

std::string CDMWriter::formatComment(const std::string commentString, outputMode mode)
{
    if (commentString != "")
    {
        std::stringstream formattedComment;
        if (mode == OUT_KVN)
            formattedComment << "COMMENT " << commentString << std::endl;
        else
            formattedComment << "\"COMMENT\": \"" << commentString << "\"," << std::endl;
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

std::string CDMWriter::formatCollisionProbabilityMethod(const CDM_C::CollisionProbabilityMethod method)
{
    if (method == CDM_C::AKELLAALFRIEND_2000) return "AKELLA_ALFRIEND-2000";
    else if (method == CDM_C::ALFANO_2005) return "ALFANO-2005";
    else if (method == CDM_C::ALFANO_MAX_PROBABILITY) return "ALFANO_MAX_PROBABILITY";
    else if (method == CDM_C::ALFANO_PARAL_2007) return "ALFANO_PARAL-2007";
    else if (method == CDM_C::ALFANO_TUBES_2007) return "ALFANO_TUBES-2007";
    else if (method == CDM_C::ALFANO_VOXELS_2006) return "ALFANO_VOXELS-2006";
    else if (method == CDM_C::ALFRIEND_1999) return "ALFRIEND-1999";
    else if (method == CDM_C::CHAN_1997) return "CHAN-1997";
    else if (method == CDM_C::CHAN_2003) return "CHAN-2003";
    else if (method == CDM_C::FOSTER_1992) return "FOSTER-1992";
    else if (method == CDM_C::MCKINLEY_2006) return "MCKINLEY-2006";
    else if (method == CDM_C::PATERA_2001) return "PATERA-2001";
    else if (method == CDM_C::PATERA_2003) return "PATERA-2003";
    else if (method == CDM_C::PATERA_2005) return "PATERA-2005";
    else if (method == CDM_C::ALFANO_LIN_2009) return "ALFANO_LIN-2009";
    else return "";
}
