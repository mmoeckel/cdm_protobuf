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

void ConjunctionDataMessage::setObject1Metadata(std::string designator, std::string intDesignator, std::string catName, std::string name, std::string ephemerisName, CDM::CovarianceMethod covMethod, CDM::ManeuverabilityState maneuverable, CDM::ReferenceFrame frame, std::string comment)
{
    object1Meta.set_comment(comment);
    object1Meta.set_object(CDM::OBJECT1);
    object1Meta.set_object_designator(designator);
    object1Meta.set_catalog_name(catName);
    object1Meta.set_object_name(name);
    object1Meta.set_international_designator(intDesignator);
    object1Meta.set_ephemeris_name(ephemerisName);
    object1Meta.set_covariance_method(covMethod);
    object1Meta.set_maneuverable(maneuverable);
    object1Meta.set_ref_frame(frame);
}

void ConjunctionDataMessage::setObject2Metadata(std::string designator, std::string intDesignator, std::string catName, std::string name, std::string ephemerisName, CDM::CovarianceMethod covMethod, CDM::ManeuverabilityState maneuverable, CDM::ReferenceFrame frame, std::string comment)
{
    object2Meta.set_comment(comment);
    object2Meta.set_object(CDM::OBJECT2);
    object2Meta.set_object_designator(designator);
    object2Meta.set_catalog_name(catName);
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
            && (object1Meta.maneuverable() == CDM::MANEUVERABLE || object1Meta.maneuverable() == CDM::NOT_MANEUVERABLE || object1Meta.maneuverable() == CDM::N_A)
            && (object1Meta.ref_frame() == CDM::GCRF || object1Meta.ref_frame() == CDM::EME2000 || object1Meta.ref_frame() == CDM::ITRF)

            && object2Meta.object() == CDM::OBJECT2
            && object2Meta.object_designator().length() > 0
            && object2Meta.catalog_name().length() > 0
            && object2Meta.object_name().length() > 0
            && object2Meta.international_designator().length() > 0
            && (object2Meta.covariance_method() == CDM::CALCULATED || object2Meta.covariance_method() == CDM::DEFAULT)
            && (object2Meta.maneuverable() == CDM::MANEUVERABLE || object2Meta.maneuverable() == CDM::NOT_MANEUVERABLE || object2Meta.maneuverable() == CDM::N_A)
            && (object2Meta.ref_frame() == CDM::GCRF || object2Meta.ref_frame() == CDM::EME2000 || object2Meta.ref_frame() == CDM::ITRF)

            // State vector is considered valid if at least one value is non-zero.
            // This doesn't catch invalid orbits but it catches forgetting to set it.
            && (object1StateVector.x() != 0.0 || object1StateVector.y() != 0.0 || object1StateVector.z() != 0.0 || object1StateVector.x_dot() != 0.0 || object1StateVector.y_dot() != 0.0 || object1StateVector.z_dot() != 0.0)
            && (object2StateVector.x() != 0.0 || object2StateVector.y() != 0.0 || object2StateVector.z() != 0.0 || object2StateVector.x_dot() != 0.0 || object2StateVector.y_dot() != 0.0 || object2StateVector.z_dot() != 0.0)

            );    
}

std::string ConjunctionDataMessage::toKVN()
{
    CDM::ConjunctionDataMessage cdm = buildMessage();
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
    CDM::ConjunctionDataMessage cdm = buildMessage();
    std::string result;
    google::protobuf::util::MessageToJsonString(cdm, &result);
    return result;
}

std::string ConjunctionDataMessage::toProtobufString()
{
    CDM::ConjunctionDataMessage cdm = buildMessage();
    return cdm.SerializeAsString();
}


CDM::ConjunctionDataMessage ConjunctionDataMessage::buildMessage()
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
    kvn << std::setw(36) << std::left << "CCSDS_CDM_VERS" << "=" << header.ccsds_cdm_vers() << std::endl;
    kvn << formatComment(headerComment.str());
    kvn << std::setw(36) << std::left << "CREATION_DATE" << "=" << header.creation_date() << std::endl;
    kvn << std::setw(36) << std::left << "ORIGINATOR" << "=" << header.originator() << std::endl;
    if (header.message_for().length() > 0) kvn << std::setw(36) << std::left << "MESSAGE_FOR" << "=" << header.message_for() << std::endl;
    kvn << std::setw(36) << std::left << "MESSAGE_ID" << "=" << header.message_id() << std::endl;
    return kvn.str();
}

std::string ConjunctionDataMessage::relativeMetadataToKVN(CDM::RelativeMetadata relativeMetadata)
{
    std::stringstream kvn;
    kvn << formatComment(relativeMetadata.comment());
    kvn << std::setw(36) << std::left << "TCA" << "=" << relativeMetadata.tca() << std::endl;
    kvn << std::setw(36) << std::left << "MISS_DISTANCE" << "=" << std::setw(36) << std::left << relativeMetadata.miss_distance() << "[m]" << std::endl;
    return kvn.str();
}

std::string ConjunctionDataMessage::objectMetadataToKVN(CDM::ObjectMetadata objectMeta)
{
    std::stringstream kvn;
    kvn << formatComment(objectMeta.comment());
    kvn << std::setw(36) << std::left << "OBJECT" << "=" << formatObject(objectMeta.object()) << std::endl;
    kvn << std::setw(36) << std::left << "OBJECT_DESIGNATOR" << "=" << objectMeta.object_designator() << std::endl;
    kvn << std::setw(36) << std::left << "CATALOG_NAME" << "=" << objectMeta.catalog_name() << std::endl;
    kvn << std::setw(36) << std::left << "OBJECT_NAME" << "=" << objectMeta.object_name() << std::endl;
    kvn << std::setw(36) << std::left << "INTERNATIONAL_DESIGNATOR" << "=" << objectMeta.international_designator() << std::endl;
    kvn << std::setw(36) << std::left << "EPHEMERIS_NAME" << "=" << objectMeta.ephemeris_name() << std::endl;
    kvn << std::setw(36) << std::left << "COVARIANCE_METHOD" << "=" << formatCovarianceMethod(objectMeta.covariance_method()) << std::endl;
    kvn << std::setw(36) << std::left << "MANEUVERABLE" << "=" << formatManeuverable(objectMeta.maneuverable()) << std::endl;
    kvn << std::setw(36) << std::left << "REF_FRAME" << "=" << formatReferenceFrame(objectMeta.ref_frame()) << std::endl;
    return kvn.str();
}

std::string ConjunctionDataMessage::objectDataToKVN(CDM::ObjectData objectData)
{
    std::stringstream kvn;

    CDM::StateVector objectStateVector = objectData.statevector();
    kvn << formatComment(objectStateVector.comment());
    kvn << std::setw(36) << std::left << "X" << "=" << std::setw(36) << std::left << objectStateVector.x() << "[km]" << std::endl;
    kvn << std::setw(36) << std::left << "Y" << "=" << std::setw(36) << std::left << objectStateVector.y() << "[km]" << std::endl;
    kvn << std::setw(36) << std::left << "Z" << "=" << std::setw(36) << std::left << objectStateVector.z() << "[km]" << std::endl;
    kvn << std::setw(36) << std::left << "X_DOT" << "=" << std::setw(36) << std::left << objectStateVector.x_dot() << "[km/s]" << std::endl;
    kvn << std::setw(36) << std::left << "Y_DOT" << "=" << std::setw(36) << std::left << objectStateVector.y_dot() << "[km/s]" << std::endl;
    kvn << std::setw(36) << std::left << "Z_DOT" << "=" << std::setw(36) << std::left << objectStateVector.z_dot() << "[km/s]" << std::endl;

    CDM::CovarianceMatrix objectCovMatrix = objectData.covariancematrix();
    kvn << formatComment(objectCovMatrix.comment());
    kvn << std::setw(36) << std::left << "CR_R" << "=" << std::setw(36) << std::left << objectCovMatrix.cr_r() << "[m**2]" << std::endl;
    kvn << std::setw(36) << std::left << "CT_R" << "=" << std::setw(36) << std::left << objectCovMatrix.ct_r() << "[m**2]" << std::endl;
    kvn << std::setw(36) << std::left << "CT_T" << "=" << std::setw(36) << std::left << objectCovMatrix.ct_t() << "[m**2]" << std::endl;
    kvn << std::setw(36) << std::left << "CN_R" << "=" << std::setw(36) << std::left << objectCovMatrix.cn_r() << "[m**2]" << std::endl;
    kvn << std::setw(36) << std::left << "CN_T" << "=" << std::setw(36) << std::left << objectCovMatrix.cn_t() << "[m**2]" << std::endl;
    kvn << std::setw(36) << std::left << "CN_N" << "=" << std::setw(36) << std::left << objectCovMatrix.cn_n() << "[m**2]" << std::endl;
    kvn << std::setw(36) << std::left << "CRDOT_R" << "=" << std::setw(36) << std::left << objectCovMatrix.crdot_r() << "[m**2/s]" << std::endl;
    kvn << std::setw(36) << std::left << "CRDOT_T" << "=" << std::setw(36) << std::left << objectCovMatrix.crdot_t() << "[m**2/s]" << std::endl;
    kvn << std::setw(36) << std::left << "CRDOT_N" << "=" << std::setw(36) << std::left << objectCovMatrix.crdot_n() << "[m**2/s]" << std::endl;
    kvn << std::setw(36) << std::left << "CRDOT_RDOT" << "=" << std::setw(36) << std::left << objectCovMatrix.crdot_rdot() << "[m**2/s**2]" << std::endl;
    kvn << std::setw(36) << std::left << "CTDOT_R" << "=" << std::setw(36) << std::left << objectCovMatrix.ctdot_r() << "[m**2/s]" << std::endl;
    kvn << std::setw(36) << std::left << "CTDOT_T" << "=" << std::setw(36) << std::left << objectCovMatrix.ctdot_t() << "[m**2/s]" << std::endl;
    kvn << std::setw(36) << std::left << "CTDOT_N" << "=" << std::setw(36) << std::left << objectCovMatrix.ctdot_n() << "[m**2/s]" << std::endl;
    kvn << std::setw(36) << std::left << "CTDOT_RDOT" << "=" << std::setw(36) << std::left << objectCovMatrix.ctdot_rdot() << "[m**2/s**2]" << std::endl;
    kvn << std::setw(36) << std::left << "CTDOT_TDOT" << "=" << std::setw(36) << std::left << objectCovMatrix.ctdot_tdot() << "[m**2/s**2]" << std::endl;
    kvn << std::setw(36) << std::left << "CNDOT_R" << "=" << std::setw(36) << std::left << objectCovMatrix.cndot_r() << "[m**2/s]" << std::endl;
    kvn << std::setw(36) << std::left << "CNDOT_T" << "=" << std::setw(36) << std::left << objectCovMatrix.cndot_t() << "[m**2/s]" << std::endl;
    kvn << std::setw(36) << std::left << "CNDOT_N" << "=" << std::setw(36) << std::left << objectCovMatrix.cndot_n() << "[m**2/s]" << std::endl;
    kvn << std::setw(36) << std::left << "CNDOT_RDOT" << "=" << std::setw(36) << std::left << objectCovMatrix.cndot_rdot() << "[m**2/s**2]" << std::endl;
    kvn << std::setw(36) << std::left << "CNDOT_TDOT" << "=" << std::setw(36) << std::left << objectCovMatrix.cndot_tdot() << "[m**2/s**2]" << std::endl;
    kvn << std::setw(36) << std::left << "CNDOT_NDOT" << "=" << std::setw(36) << std::left << objectCovMatrix.cndot_ndot() << "[m**2/s**2]" << std::endl;
    return kvn.str();
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

std::string ConjunctionDataMessage::formatManeuverable(const CDM::ManeuverabilityState state)
{
    if (state == CDM::MANEUVERABLE) return "YES";
    else if (state == CDM::NOT_MANEUVERABLE) return "NO";
    else return "N/A";
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
