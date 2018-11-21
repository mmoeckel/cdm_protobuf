#include "ConjunctionDataMessage.h"

#include "google/protobuf/util/json_util.h"

#include <iomanip>
#include <sstream>

ConjunctionDataMessage::ConjunctionDataMessage()
{

}

ConjunctionDataMessage::ConjunctionDataMessage(std::string received)
{
    CDM::ConjunctionDataMessage cdm;
    cdm.ParseFromString(received);
    header = cdm.header();
    relativeMetadata = cdm.relativemetadata();
    object1Meta = cdm.object1metadata();
    object1ODParams = cdm.object1data().odparameters();
    object1AdditionalParams = cdm.object1data().additionalparameters();
    object1StateVector = cdm.object1data().statevector();
    object1CovMatrix = cdm.object1data().covariancematrix();
    object2Meta = cdm.object2metadata();
    object2ODParams = cdm.object2data().odparameters();
    object2AdditionalParams = cdm.object2data().additionalparameters();
    object2StateVector = cdm.object2data().statevector();
    object2CovMatrix = cdm.object2data().covariancematrix();
}

void ConjunctionDataMessage::setHeader(std::string version, std::string creationDate, std::string originator, std::string messageID, std::string messageFor, std::string comment)
{
    header.set_ccsds_cdm_vers(version);
    header.set_creation_date(creationDate);
    header.set_originator(originator);
    header.set_message_for(messageFor);
    header.set_message_id(messageID);
    header.set_comment(comment);
}

void ConjunctionDataMessage::setRelativeMetadata(std::string tca, double missDistance, std::string comment)
{
    relativeMetadata.set_comment(comment);
    relativeMetadata.set_tca(tca);
    relativeMetadata.set_miss_distance(missDistance);
}

void ConjunctionDataMessage::setObject1Metadata(std::string designator, std::string intDesignator, std::string catalogName, std::string name, std::string ephemerisName, CDM::CovarianceMethod covMethod, CDM::YesOrNo maneuverable, CDM::ReferenceFrame frame, std::string comment)
{
    object1Meta.set_comment(comment);
    object1Meta.set_object(CDM::OBJECT1);
    object1Meta.set_object_designator(designator);
    object1Meta.set_catalog_name(catalogName);
    object1Meta.set_object_name(name);
    object1Meta.set_international_designator(intDesignator);
    object1Meta.set_ephemeris_name(ephemerisName);
    object1Meta.set_covariance_method(covMethod);
    object1Meta.set_maneuverable(maneuverable);
    object1Meta.set_ref_frame(frame);
}

void ConjunctionDataMessage::setObject2Metadata(std::string designator, std::string intDesignator, std::string catalogName, std::string name, std::string ephemerisName, CDM::CovarianceMethod covMethod, CDM::YesOrNo maneuverable, CDM::ReferenceFrame frame, std::string comment)
{
    object2Meta.set_comment(comment);
    object2Meta.set_object(CDM::OBJECT2);
    object2Meta.set_object_designator(designator);
    object2Meta.set_catalog_name(catalogName);
    object2Meta.set_object_name(name);
    object2Meta.set_international_designator(intDesignator);
    object2Meta.set_ephemeris_name(ephemerisName);
    object2Meta.set_covariance_method(covMethod);
    object2Meta.set_maneuverable(maneuverable);
    object2Meta.set_ref_frame(frame);
}

void ConjunctionDataMessage::setObject1StateVector(double positionX, double positionY, double positionZ, double velocityX, double velocityY, double velocityZ, std::string comment)
{
    object1StateVector.set_comment(comment);
    object1StateVector.set_x(positionX);
    object1StateVector.set_y(positionY);
    object1StateVector.set_z(positionZ);
    object1StateVector.set_x_dot(velocityX);
    object1StateVector.set_y_dot(velocityY);
    object1StateVector.set_z_dot(velocityZ);
}

void ConjunctionDataMessage::setObject2StateVector(double positionX, double positionY, double positionZ, double velocityX, double velocityY, double velocityZ, std::string comment)
{
    object2StateVector.set_comment(comment);
    object2StateVector.set_x(positionX);
    object2StateVector.set_y(positionY);
    object2StateVector.set_z(positionZ);
    object2StateVector.set_x_dot(velocityX);
    object2StateVector.set_y_dot(velocityY);
    object2StateVector.set_z_dot(velocityZ);
}

void ConjunctionDataMessage::setObject1CovarianceMatrix(std::vector<double> covarianceMatrix, std::string comment)
{
    object1CovMatrix.set_comment(comment);
    if (covarianceMatrix.size() > 20)
    {
        object1CovMatrix.set_cr_r(covarianceMatrix[0]);
        object1CovMatrix.set_ct_r(covarianceMatrix[1]);
        object1CovMatrix.set_ct_t(covarianceMatrix[2]);
        object1CovMatrix.set_cn_r(covarianceMatrix[3]);
        object1CovMatrix.set_cn_t(covarianceMatrix[4]);
        object1CovMatrix.set_cn_n(covarianceMatrix[5]);
        object1CovMatrix.set_crdot_r(covarianceMatrix[6]);
        object1CovMatrix.set_crdot_t(covarianceMatrix[7]);
        object1CovMatrix.set_crdot_n(covarianceMatrix[8]);
        object1CovMatrix.set_crdot_rdot(covarianceMatrix[9]);
        object1CovMatrix.set_ctdot_r(covarianceMatrix[10]);
        object1CovMatrix.set_ctdot_t(covarianceMatrix[11]);
        object1CovMatrix.set_ctdot_n(covarianceMatrix[12]);
        object1CovMatrix.set_ctdot_rdot(covarianceMatrix[13]);
        object1CovMatrix.set_ctdot_tdot(covarianceMatrix[14]);
        object1CovMatrix.set_cndot_r(covarianceMatrix[15]);
        object1CovMatrix.set_cndot_t(covarianceMatrix[16]);
        object1CovMatrix.set_cndot_n(covarianceMatrix[17]);
        object1CovMatrix.set_cndot_rdot(covarianceMatrix[18]);
        object1CovMatrix.set_cndot_tdot(covarianceMatrix[19]);
        object1CovMatrix.set_cndot_ndot(covarianceMatrix[20]);
        if (covarianceMatrix.size() > 21) object1CovMatrix.set_cdrg_r(covarianceMatrix[21]);
        if (covarianceMatrix.size() > 22) object1CovMatrix.set_cdrg_t(covarianceMatrix[22]);
        if (covarianceMatrix.size() > 23) object1CovMatrix.set_cdrg_n(covarianceMatrix[23]);
        if (covarianceMatrix.size() > 24) object1CovMatrix.set_cdrg_rdot(covarianceMatrix[24]);
        if (covarianceMatrix.size() > 25) object1CovMatrix.set_cdrg_tdot(covarianceMatrix[25]);
        if (covarianceMatrix.size() > 26) object1CovMatrix.set_cdrg_ndot(covarianceMatrix[26]);
        if (covarianceMatrix.size() > 27) object1CovMatrix.set_cdrg_drg(covarianceMatrix[27]);
        if (covarianceMatrix.size() > 28) object1CovMatrix.set_csrp_r(covarianceMatrix[28]);
        if (covarianceMatrix.size() > 29) object1CovMatrix.set_csrp_t(covarianceMatrix[29]);
        if (covarianceMatrix.size() > 30) object1CovMatrix.set_csrp_n(covarianceMatrix[30]);
        if (covarianceMatrix.size() > 31) object1CovMatrix.set_csrp_rdot(covarianceMatrix[21]);
        if (covarianceMatrix.size() > 32) object1CovMatrix.set_csrp_tdot(covarianceMatrix[32]);
        if (covarianceMatrix.size() > 33) object1CovMatrix.set_csrp_ndot(covarianceMatrix[33]);
        if (covarianceMatrix.size() > 34) object1CovMatrix.set_csrp_drg(covarianceMatrix[34]);
        if (covarianceMatrix.size() > 35) object1CovMatrix.set_csrp_srp(covarianceMatrix[35]);
        if (covarianceMatrix.size() > 36) object1CovMatrix.set_cthr_r(covarianceMatrix[36]);
        if (covarianceMatrix.size() > 37) object1CovMatrix.set_cthr_t(covarianceMatrix[37]);
        if (covarianceMatrix.size() > 38) object1CovMatrix.set_cthr_n(covarianceMatrix[38]);
        if (covarianceMatrix.size() > 39) object1CovMatrix.set_cthr_rdot(covarianceMatrix[39]);
        if (covarianceMatrix.size() > 40) object1CovMatrix.set_cthr_tdot(covarianceMatrix[40]);
        if (covarianceMatrix.size() > 41) object1CovMatrix.set_cthr_ndot(covarianceMatrix[41]);
        if (covarianceMatrix.size() > 42) object1CovMatrix.set_cthr_drg(covarianceMatrix[42]);
        if (covarianceMatrix.size() > 43) object1CovMatrix.set_cthr_srp(covarianceMatrix[43]);
        if (covarianceMatrix.size() > 44) object1CovMatrix.set_cthr_srp(covarianceMatrix[44]);
        if (covarianceMatrix.size() > 45) object1CovMatrix.set_cthr_thr(covarianceMatrix[45]);
    }
}

void ConjunctionDataMessage::setObject2CovarianceMatrix(std::vector<double> covarianceMatrix, std::string comment)
{
    object2CovMatrix.set_comment(comment);
    if (covarianceMatrix.size() > 20)
    {
        object2CovMatrix.set_cr_r(covarianceMatrix[0]);
        object2CovMatrix.set_ct_r(covarianceMatrix[1]);
        object2CovMatrix.set_ct_t(covarianceMatrix[2]);
        object2CovMatrix.set_cn_r(covarianceMatrix[3]);
        object2CovMatrix.set_cn_t(covarianceMatrix[4]);
        object2CovMatrix.set_cn_n(covarianceMatrix[5]);
        object2CovMatrix.set_crdot_r(covarianceMatrix[6]);
        object2CovMatrix.set_crdot_t(covarianceMatrix[7]);
        object2CovMatrix.set_crdot_n(covarianceMatrix[8]);
        object2CovMatrix.set_crdot_rdot(covarianceMatrix[9]);
        object2CovMatrix.set_ctdot_r(covarianceMatrix[10]);
        object2CovMatrix.set_ctdot_t(covarianceMatrix[11]);
        object2CovMatrix.set_ctdot_n(covarianceMatrix[12]);
        object2CovMatrix.set_ctdot_rdot(covarianceMatrix[13]);
        object2CovMatrix.set_ctdot_tdot(covarianceMatrix[14]);
        object2CovMatrix.set_cndot_r(covarianceMatrix[15]);
        object2CovMatrix.set_cndot_t(covarianceMatrix[16]);
        object2CovMatrix.set_cndot_n(covarianceMatrix[17]);
        object2CovMatrix.set_cndot_rdot(covarianceMatrix[18]);
        object2CovMatrix.set_cndot_tdot(covarianceMatrix[19]);
        object2CovMatrix.set_cndot_ndot(covarianceMatrix[20]);
        if (covarianceMatrix.size() > 21) object2CovMatrix.set_cdrg_r(covarianceMatrix[21]);
        if (covarianceMatrix.size() > 22) object2CovMatrix.set_cdrg_t(covarianceMatrix[22]);
        if (covarianceMatrix.size() > 23) object2CovMatrix.set_cdrg_n(covarianceMatrix[23]);
        if (covarianceMatrix.size() > 24) object2CovMatrix.set_cdrg_rdot(covarianceMatrix[24]);
        if (covarianceMatrix.size() > 25) object2CovMatrix.set_cdrg_tdot(covarianceMatrix[25]);
        if (covarianceMatrix.size() > 26) object2CovMatrix.set_cdrg_ndot(covarianceMatrix[26]);
        if (covarianceMatrix.size() > 27) object2CovMatrix.set_cdrg_drg(covarianceMatrix[27]);
        if (covarianceMatrix.size() > 28) object2CovMatrix.set_csrp_r(covarianceMatrix[28]);
        if (covarianceMatrix.size() > 29) object2CovMatrix.set_csrp_t(covarianceMatrix[29]);
        if (covarianceMatrix.size() > 30) object2CovMatrix.set_csrp_n(covarianceMatrix[30]);
        if (covarianceMatrix.size() > 31) object2CovMatrix.set_csrp_rdot(covarianceMatrix[21]);
        if (covarianceMatrix.size() > 32) object2CovMatrix.set_csrp_tdot(covarianceMatrix[32]);
        if (covarianceMatrix.size() > 33) object2CovMatrix.set_csrp_ndot(covarianceMatrix[33]);
        if (covarianceMatrix.size() > 34) object2CovMatrix.set_csrp_drg(covarianceMatrix[34]);
        if (covarianceMatrix.size() > 35) object2CovMatrix.set_csrp_srp(covarianceMatrix[35]);
        if (covarianceMatrix.size() > 36) object2CovMatrix.set_cthr_r(covarianceMatrix[36]);
        if (covarianceMatrix.size() > 37) object2CovMatrix.set_cthr_t(covarianceMatrix[37]);
        if (covarianceMatrix.size() > 38) object2CovMatrix.set_cthr_n(covarianceMatrix[38]);
        if (covarianceMatrix.size() > 39) object2CovMatrix.set_cthr_rdot(covarianceMatrix[39]);
        if (covarianceMatrix.size() > 40) object2CovMatrix.set_cthr_tdot(covarianceMatrix[40]);
        if (covarianceMatrix.size() > 41) object2CovMatrix.set_cthr_ndot(covarianceMatrix[41]);
        if (covarianceMatrix.size() > 42) object2CovMatrix.set_cthr_drg(covarianceMatrix[42]);
        if (covarianceMatrix.size() > 43) object2CovMatrix.set_cthr_srp(covarianceMatrix[43]);
        if (covarianceMatrix.size() > 44) object2CovMatrix.set_cthr_srp(covarianceMatrix[44]);
        if (covarianceMatrix.size() > 45) object2CovMatrix.set_cthr_thr(covarianceMatrix[45]);
    }
}

bool ConjunctionDataMessage::isComplete()
{
    return (header.ccsds_cdm_vers().length() > 0
            && header.creation_date().length() > 0
            && header.originator().length() > 0
            && header.message_id().length() > 0

            && relativeMetadata.tca().length() > 0
            && relativeMetadata.miss_distance() > 0.0

            && object1Meta.object() == CDM::OBJECT1
            && object1Meta.object_designator().length() > 0
            && object1Meta.catalog_name().length() > 0
            && object1Meta.object_name().length() > 0
            && object1Meta.international_designator().length() > 0
            && (object1Meta.covariance_method() == CDM::CALCULATED || object1Meta.covariance_method() == CDM::DEFAULT)
            && (object1Meta.maneuverable() == CDM::YES || object1Meta.maneuverable() == CDM::NO || object1Meta.maneuverable() == CDM::N_A)
            && (object1Meta.ref_frame() == CDM::GCRF || object1Meta.ref_frame() == CDM::EME2000 || object1Meta.ref_frame() == CDM::ITRF)

            && object2Meta.object() == CDM::OBJECT2
            && object2Meta.object_designator().length() > 0
            && object2Meta.catalog_name().length() > 0
            && object2Meta.object_name().length() > 0
            && object2Meta.international_designator().length() > 0
            && (object2Meta.covariance_method() == CDM::CALCULATED || object2Meta.covariance_method() == CDM::DEFAULT)
            && (object2Meta.maneuverable() == CDM::YES || object2Meta.maneuverable() == CDM::NO || object2Meta.maneuverable() == CDM::N_A)
            && (object2Meta.ref_frame() == CDM::GCRF || object2Meta.ref_frame() == CDM::EME2000 || object2Meta.ref_frame() == CDM::ITRF)

            // State vector is considered valid if at least one value is non-zero.
            // This doesn't catch invalid orbits but it catches forgetting to set it.
            && (object1StateVector.x() != 0.0 || object1StateVector.y() != 0.0 || object1StateVector.z() != 0.0 || object1StateVector.x_dot() != 0.0 || object1StateVector.y_dot() != 0.0 || object1StateVector.z_dot() != 0.0)
            && (object2StateVector.x() != 0.0 || object2StateVector.y() != 0.0 || object2StateVector.z() != 0.0 || object2StateVector.x_dot() != 0.0 || object2StateVector.y_dot() != 0.0 || object2StateVector.z_dot() != 0.0)

            );
}

// Non-obligatory setters follow

void ConjunctionDataMessage::setRelativeSpeed(double v)
{
    relativeMetadata.set_relative_speed(v);
}

void ConjunctionDataMessage::setRelativePosition(double r, double t, double n)
{
    relativeMetadata.set_relative_position_r(r);
    relativeMetadata.set_relative_position_t(t);
    relativeMetadata.set_relative_position_n(n);
}

void ConjunctionDataMessage::setRelativeVelocity(double r, double t, double n)
{
    relativeMetadata.set_relative_velocity_r(r);
    relativeMetadata.set_relative_velocity_t(t);
    relativeMetadata.set_relative_velocity_n(n);
}



// Output functions

std::string ConjunctionDataMessage::toKVN()
{
    CDM::ConjunctionDataMessage cdm = toProtobufMessage();
    std::stringstream kvn;

    // Write header
    kvn << headerToKVN(cdm.header());
    kvn << relativeMetadataToKVN(cdm.relativemetadata());
    kvn << objectMetadataToKVN(cdm.object1metadata());
    kvn << objectDataToKVN(cdm.object1data());
    kvn << objectMetadataToKVN(cdm.object2metadata());
    kvn << objectDataToKVN(cdm.object2data());
    // Return completed KVN CDM
    return kvn.str();
}

std::string ConjunctionDataMessage::toJSON()
{
    CDM::ConjunctionDataMessage cdm = toProtobufMessage();
    std::string result;
    google::protobuf::util::MessageToJsonString(cdm, &result);
    return result;
}

std::string ConjunctionDataMessage::toProtobufString()
{
    CDM::ConjunctionDataMessage cdm = toProtobufMessage();
    return cdm.SerializeAsString();
}

CDM::ConjunctionDataMessage ConjunctionDataMessage::toProtobufMessage()
{
    CDM::ObjectData* object1Data = new CDM::ObjectData(); //FIXME Comment field missing
    CDM::ObjectData* object2Data = new CDM::ObjectData();
    object1Data->set_allocated_odparameters(new CDM::OdParameters(object1ODParams));
    object2Data->set_allocated_odparameters(new CDM::OdParameters(object2ODParams));
    object1Data->set_allocated_additionalparameters(new CDM::AdditionalParameters(object1AdditionalParams));
    object2Data->set_allocated_additionalparameters(new CDM::AdditionalParameters(object2AdditionalParams));
    object1Data->set_allocated_statevector(new CDM::StateVector(object1StateVector));
    object2Data->set_allocated_statevector(new CDM::StateVector(object2StateVector));
    object1Data->set_allocated_covariancematrix(new CDM::CovarianceMatrix(object1CovMatrix));
    object2Data->set_allocated_covariancematrix(new CDM::CovarianceMatrix(object2CovMatrix));
    CDM::ConjunctionDataMessage cdm;
    cdm.set_allocated_header(new CDM::Header(header));
    cdm.set_allocated_relativemetadata(new CDM::RelativeMetadata(relativeMetadata));
    cdm.set_allocated_object1metadata(new CDM::ObjectMetadata(object1Meta));
    cdm.set_allocated_object2metadata(new CDM::ObjectMetadata(object2Meta));
    cdm.set_allocated_object1data(object1Data);
    cdm.set_allocated_object2data(object2Data);
    return cdm;
}

// Private auxiliary functions

std::string ConjunctionDataMessage::headerToKVN(CDM::Header header)
{
    // Add a warning to the header comment if CDM is incomplete
    std::stringstream headerComment;
    if (!isComplete())
    {
        headerComment << "Warning: Incomplete CDM! Not all obligatory fields are set!" << std::endl;
    }
    headerComment << header.comment();

    std::stringstream kvn;
    kvn << formatValue("CCSDS_CDM_VERS", header.ccsds_cdm_vers(), "", true);
    kvn << formatComment(headerComment.str());
    kvn << formatValue("CREATION_DATE", header.creation_date(), "", true);
    kvn << formatValue("ORIGINATOR", header.originator(), "", true);
    kvn << formatValue("MESSAGE_FOR", header.message_for(), "", false);
    kvn << formatValue("MESSAGE_ID", header.message_id(), "", true);
    return kvn.str();
}

std::string ConjunctionDataMessage::relativeMetadataToKVN(CDM::RelativeMetadata relativeMetadata)
{
    std::stringstream kvn;
    kvn << formatComment(relativeMetadata.comment());
    kvn << formatValue("TCA", relativeMetadata.tca(), "", true);
    kvn << formatValue("MISS_DISTANCE", relativeMetadata.miss_distance(), "m", true);
    kvn << formatValue("RELATIVE_SPEED", relativeMetadata.relative_speed(), "m/s", false);
    kvn << formatValue("RELATIVE_POSITION_R", relativeMetadata.relative_position_r(), "m", false);
    kvn << formatValue("RELATIVE_POSITION_T", relativeMetadata.relative_position_t(), "m", false);
    kvn << formatValue("RELATIVE_POSITION_N", relativeMetadata.relative_position_n(), "m", false);
    kvn << formatValue("RELATIVE_VELOCITY_R", relativeMetadata.relative_velocity_r(), "m/s", false);
    kvn << formatValue("RELATIVE_VELOCITY_T", relativeMetadata.relative_velocity_t(), "m/s", false);
    kvn << formatValue("RELATIVE_VELOCITY_N", relativeMetadata.relative_velocity_n(), "m/s", false);
    kvn << formatValue("START_SCREEN_PERIOD", relativeMetadata.start_screen_period(), "", false);
    kvn << formatValue("STOP_SCREEN_PERIOD", relativeMetadata.stop_screen_period(), "", false);
    kvn << formatValue("SCREEN_VOLUME_FRAME", relativeMetadata.screen_volume_frame(), "", false);
    kvn << formatValue("SCREEN_VOLUME_SHAPE", relativeMetadata.screen_volume_shape(), "", false);
    kvn << formatValue("SCREEN_VOLUME_X", relativeMetadata.screen_volume_x(), "m", false);
    kvn << formatValue("SCREEN_VOLUME_Y", relativeMetadata.screen_volume_y(), "m", false);
    kvn << formatValue("SCREEN_VOLUME_Z", relativeMetadata.screen_volume_z(), "m", false);
    kvn << formatValue("SCREEN_ENTRY_TIME", relativeMetadata.screen_entry_time(), "", false);
    kvn << formatValue("SCREEN_EXIT_TIME", relativeMetadata.screen_exit_time(), "", false);
    kvn << formatValue("COLLISION_PROBABILITY", relativeMetadata.collision_probability(), "", false);
    kvn << formatValue("COLLISION_PROBABILITY_METHOD", relativeMetadata.collision_probability_method(), "", false);
    return kvn.str();
}

std::string ConjunctionDataMessage::objectMetadataToKVN(CDM::ObjectMetadata objectMeta)
{
    std::stringstream kvn;
    kvn << formatComment(objectMeta.comment());
    kvn << formatValue("OBJECT",                   formatObject(objectMeta.object()), "", true);
    kvn << formatValue("OBJECT_DESIGNATOR",        objectMeta.object_designator(), "", true);
    kvn << formatValue("CATALOG_NAME",             objectMeta.catalog_name(), "", true);
    kvn << formatValue("OBJECT_NAME",              objectMeta.object_name(), "", true);
    kvn << formatValue("INTERNATIONAL_DESIGNATOR", objectMeta.international_designator(), "", true);
    kvn << formatValue("OBJECT_TYPE",              formatObjectType(objectMeta.object_type()), "", false);
    kvn << formatValue("OPERATOR_CONTACT_POSITION",objectMeta.operator_contact_position(), "", false);
    kvn << formatValue("OPERATOR_ORGANIZATION",    objectMeta.operator_organization(), "", false);
    kvn << formatValue("OPERATOR_PHONE",           objectMeta.operator_phone(), "", false);
    kvn << formatValue("OPERATOR_EMAIL",           objectMeta.operator_email(), "", false);
    kvn << formatValue("EPHEMERIS_NAME",           objectMeta.ephemeris_name(), "", true);
    kvn << formatValue("COVARIANCE_METHOD",        formatCovarianceMethod(objectMeta.covariance_method()), "", true);
    kvn << formatValue("MANEUVERABLE",             formatYesNo(objectMeta.maneuverable(), true), "", true);
    kvn << formatValue("ORBIT_CENTER",             objectMeta.orbit_center(), "", false);
    kvn << formatValue("REF_FRAME",                formatReferenceFrame(objectMeta.ref_frame()), "", true);
    kvn << formatValue("GRAVITY_MODEL",            objectMeta.gravity_model(), "", false);
    kvn << formatValue("ATMOSPHERIC_MODEL",        objectMeta.atmospheric_model(), "", false);
    kvn << formatValue("N_BODY_PERTURBATIONS",     objectMeta.n_body_perturbations(), "", false);
    kvn << formatValue("SOLAR_RAD_PRESSURE",       formatYesNo(objectMeta.solar_rad_pressure(), false), "", false);
    kvn << formatValue("EARTH_TIDES",              formatYesNo(objectMeta.earth_tides(), false),"", false);
    kvn << formatValue("INTRACK_THRUST",           formatYesNo(objectMeta.intrack_thrust(), false), "", false);
    return kvn.str();
}

std::string ConjunctionDataMessage::objectDataToKVN(CDM::ObjectData objectData)
{
    std::stringstream kvn;

    kvn << formatComment(objectData.comment());

    CDM::OdParameters od = objectData.odparameters();
    kvn << formatComment(od.comment());
    kvn << formatValue("TIME_LASTOB_START", od.time_lastob_start(), "", false);
    kvn << formatValue("TIME_LASTOB_END", od.time_lastob_end(), "", false);
    kvn << formatValue("RECOMMENDED_OD_SPAN", od.recommended_od_span(), "d", false);
    kvn << formatValue("ACTUAL_OD_SPAN", od.actual_od_span(), "d", false);
    kvn << formatValue("OBS_AVAILABLE", (int)od.obs_available(), "", false);
    kvn << formatValue("OBS_USED", (int)od.obs_used(), "", false);
    kvn << formatValue("TRACKS_AVAILABLE", (int)od.tracks_available(), "", false);
    kvn << formatValue("TRACKS_USED", (int)od.tracks_used(), "", false);
    kvn << formatValue("RESIDUALS_ACCEPTED", od.residuals_accepted(), "%", false);
    kvn << formatValue("WEIGHTED_RMS", od.weighted_rms(), "", false);

    CDM::AdditionalParameters ap = objectData.additionalparameters();
    kvn << formatComment(ap.comment());
    kvn << formatValue("AREA_PC", ap.area_pc(), "m**2", false);
    kvn << formatValue("AREA_DRG", ap.area_drg(), "m**2", false);
    kvn << formatValue("AREA_SRP", ap.area_srp(), "m**2", false);
    kvn << formatValue("MASS", ap.mass(), "kg", false);
    kvn << formatValue("CD_AREA_OVER_MASS", ap.cd_area_over_mass(), "m**2/kg", false);
    kvn << formatValue("CR_AREA_OVER_MASS", ap.cr_area_over_mass(), "m**2/kg", false);
    kvn << formatValue("THRUST_ACCELERATION", ap.thrust_acceleration(), "m/s**2", false);
    kvn << formatValue("SEDR", ap.sedr(), "W/kg", false);

    CDM::StateVector objectStateVector = objectData.statevector();
    kvn << formatComment(objectStateVector.comment());
    kvn << formatValue("X", objectStateVector.x(), "km", true);
    kvn << formatValue("Y", objectStateVector.y(), "km", true);
    kvn << formatValue("Z", objectStateVector.z(), "km", true);
    kvn << formatValue("X_DOT", objectStateVector.x_dot(), "km/s", true);
    kvn << formatValue("Y_DOT", objectStateVector.y_dot(), "km/s", true);
    kvn << formatValue("Z_DOT", objectStateVector.z_dot(), "km/s", true);

    CDM::CovarianceMatrix objectCovMatrix = objectData.covariancematrix();
    kvn << formatComment(objectCovMatrix.comment());
    kvn << formatValue("CR_R",       objectCovMatrix.cr_r(),       "m**2"     , true);
    kvn << formatValue("CT_R",       objectCovMatrix.ct_r(),       "m**2"     , true);
    kvn << formatValue("CT_T",       objectCovMatrix.ct_t(),       "m**2"     , true);
    kvn << formatValue("CN_R",       objectCovMatrix.cn_r(),       "m**2"     , true);
    kvn << formatValue("CN_T",       objectCovMatrix.cn_t(),       "m**2"     , true);
    kvn << formatValue("CN_N",       objectCovMatrix.cn_n(),       "m**2"     , true);
    kvn << formatValue("CRDOT_R",    objectCovMatrix.crdot_r(),    "m**2/s"   , true);
    kvn << formatValue("CRDOT_T",    objectCovMatrix.crdot_t(),    "m**2/s"   , true);
    kvn << formatValue("CRDOT_N",    objectCovMatrix.crdot_n(),    "m**2/s"   , true);
    kvn << formatValue("CRDOT_RDOT", objectCovMatrix.crdot_rdot(), "m**2/s**2", true);
    kvn << formatValue("CTDOT_R",    objectCovMatrix.ctdot_r(),    "m**2/s"   , true);
    kvn << formatValue("CTDOT_T",    objectCovMatrix.ctdot_t(),    "m**2/s"   , true);
    kvn << formatValue("CTDOT_N",    objectCovMatrix.ctdot_n(),    "m**2/s"   , true);
    kvn << formatValue("CTDOT_RDOT", objectCovMatrix.ctdot_rdot(), "m**2/s**2", true);
    kvn << formatValue("CTDOT_TDOT", objectCovMatrix.ctdot_tdot(), "m**2/s**2", true);
    kvn << formatValue("CNDOT_R",    objectCovMatrix.cndot_r(),    "m**2/s"   , true);
    kvn << formatValue("CNDOT_T",    objectCovMatrix.cndot_t(),    "m**2/s"   , true);
    kvn << formatValue("CNDOT_N",    objectCovMatrix.cndot_n(),    "m**2/s"   , true);
    kvn << formatValue("CNDOT_RDOT", objectCovMatrix.cndot_rdot(), "m**2/s**2", true);
    kvn << formatValue("CNDOT_TDOT", objectCovMatrix.cndot_tdot(), "m**2/s**2", true);
    kvn << formatValue("CNDOT_NDOT", objectCovMatrix.cndot_ndot(), "m**2/s**2", true);
    kvn << formatValue("CDRG_R", objectCovMatrix.cdrg_r(), "m**3/kg", false);
    kvn << formatValue("CDRG_T", objectCovMatrix.cdrg_t(), "m**3/kg", false);
    kvn << formatValue("CDRG_N", objectCovMatrix.cdrg_n(), "m**3/kg", false);
    kvn << formatValue("CDRG_RDOT", objectCovMatrix.cdrg_rdot(), "m**3/(kg*s)", false);
    kvn << formatValue("CDRG_TDOT", objectCovMatrix.cdrg_tdot(), "m**3/(kg*s)", false);
    kvn << formatValue("CDRG_NDOT", objectCovMatrix.cdrg_ndot(), "m**3/(kg*s)", false);
    kvn << formatValue("CDRG_DRG", objectCovMatrix.cdrg_drg(), "m**4/kg**2", false);
    kvn << formatValue("CSRP_R", objectCovMatrix.csrp_r(), "m**3/kg", false);
    kvn << formatValue("CSRP_T", objectCovMatrix.csrp_t(), "m**3/kg", false);
    kvn << formatValue("CSRP_N", objectCovMatrix.csrp_n(), "m**3/kg", false);
    kvn << formatValue("CSRP_RDOT", objectCovMatrix.csrp_rdot(), "m**3/(kg*s)", false);
    kvn << formatValue("CSRP_TDOT", objectCovMatrix.csrp_tdot(), "m**3/(kg*s)", false);
    kvn << formatValue("CSRP_NDOT", objectCovMatrix.csrp_ndot(), "m**3/(kg*s)", false);
    kvn << formatValue("CSRP_DRG", objectCovMatrix.csrp_drg(), "m**4/kg**2", false);
    kvn << formatValue("CSRP_SRP", objectCovMatrix.csrp_srp(), "m**4/kg**2", false);
    kvn << formatValue("CTHR_R", objectCovMatrix.cthr_r(), "m**3/kg", false);
    kvn << formatValue("CTHR_T", objectCovMatrix.cthr_t(), "m**3/kg", false);
    kvn << formatValue("CTHR_N", objectCovMatrix.cthr_n(), "m**3/kg", false);
    kvn << formatValue("CTHR_RDOT", objectCovMatrix.cthr_rdot(), "m**3/(kg*s)", false);
    kvn << formatValue("CTHR_TDOT", objectCovMatrix.cthr_tdot(), "m**3/(kg*s)", false);
    kvn << formatValue("CTHR_NDOT", objectCovMatrix.cthr_ndot(), "m**3/(kg*s)", false);
    kvn << formatValue("CTHR_DRG", objectCovMatrix.cthr_drg(), "m**4/kg**2", false);
    kvn << formatValue("CTHR_SRP", objectCovMatrix.cthr_srp(), "m**4/kg**2", false);
    kvn << formatValue("CTHR_THR", objectCovMatrix.cthr_thr(), "m**4/kg**2", false);
    return kvn.str();
}

std::string ConjunctionDataMessage::formatValue(std::string key, std::string value, std::string unit, bool obligatory)
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

std::string ConjunctionDataMessage::formatValue(std::string key, double value, std::string unit, bool obligatory)
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

std::string ConjunctionDataMessage::formatValue(std::string key, int value, std::string unit, bool obligatory)
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

std::string ConjunctionDataMessage::formatDate(const int year, const int month, const int day, const int hour, const int minute, const double second)
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

std::string ConjunctionDataMessage::formatComment(const std::string commentString)
{
    if (commentString != "")
    {
        std::stringstream formattedComment;
        formattedComment << "COMMENT " << commentString << std::endl;
        return formattedComment.str();
    }
    else return "";
}

std::string ConjunctionDataMessage::formatObject(const CDM::ObjectNumber object)
{
    if (object == CDM::OBJECT1) return "OBJECT1";
    else return "OBJECT2";
}

std::string ConjunctionDataMessage::formatCovarianceMethod(const CDM::CovarianceMethod covmeth)
{
    if (covmeth == CDM::CALCULATED) return "CALCULATED";
    else return "DEFAULT";
}

std::string ConjunctionDataMessage::formatReferenceFrame(const CDM::ReferenceFrame frame)
{
    if (frame == CDM::GCRF) return "GCRF";
    else if (frame == CDM::EME2000) return "EME2000";
    else return "ITRF";
}

std::string ConjunctionDataMessage::formatYesNo(const CDM::YesOrNo value, bool allowNA)
{
    if (value == CDM::NO) return "NO";
    else if (value == CDM::YES) return "YES";
    else return (allowNA ? "N/A" : "");
}

std::string ConjunctionDataMessage::formatObjectType(const CDM::ObjectType type)
{
    if (type == CDM::PAYLOAD) return "PAYLOAD";
    else if (type == CDM::ROCKET_BODY) return "ROCKET BODY";
    else if (type == CDM::DEBRIS) return "DEBRIS";
    else if (type == CDM::UNKNOWN) return "UNKNOWN";
    else return "OTHER";
}
