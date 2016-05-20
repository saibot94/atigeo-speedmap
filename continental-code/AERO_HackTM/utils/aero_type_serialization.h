#ifndef AERO_TYPE_SERIALIZATION_H
#define AERO_TYPE_SERIALIZATION_H

#include "aero_type.h"
/*! @todo ### XXX FIXME SK 31.08.15 10:05 --> move to vehicle data serialization */
#include "aero_vehicle_data.h" 

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100 4127 4244 4267 4512)
#endif
#include "aero_type.pb.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif

void AEROTypeProto_SerializeTimestamp(const AERO_t_s_Timestamp timestamp, aero_type_protobuf::AERO_t_s_Timestamp_Proto *proto_timestamp);
void AEROTypeProto_DeSerializeTimestamp(const aero_type_protobuf::AERO_t_s_Timestamp_Proto proto_timestamp, AERO_t_s_Timestamp *timestamp);

void AEROTypeProto_SerializeId(const AERO_t_u_Id id, aero_type_protobuf::AERO_t_u_Id_Proto *proto_id);
void AEROTypeProto_DeSerializeId(const aero_type_protobuf::AERO_t_u_Id_Proto *proto_id, AERO_t_u_Id *id);

void AEROTypeProto_SerializeSignalHeader(AERO_t_SignalHeader const *signal_header, aero_type_protobuf::AERO_t_SignalHeader_Proto *proto_signal_header);
void AEROTypeProto_DeSerializeSignalHeader(const aero_type_protobuf::AERO_t_SignalHeader_Proto& proto_signal_header, AERO_t_SignalHeader *signal_header);

aero_type_protobuf::AERO_t_SignalStatus_Proto AEROTypeProto_SerializeSignalStatus(AERO_t_SignalStatus signal_status);
AERO_t_SignalStatus AEROTypeProto_DeSerializeSignalStatus(aero_type_protobuf::AERO_t_SignalStatus_Proto signal_status_proto);

aero_type_protobuf::AERO_t_TriState_Proto AEROTypeProto_SerializeTriState(AERO_t_TriState tri_state);
AERO_t_TriState AEROTypeProto_DeSerializeTriState(aero_type_protobuf::AERO_t_TriState_Proto proto_tri_state);

int AEROTypeProto_SerializeFloat32Status(AERO_t_float32Status const *fls, aero_type_protobuf::AERO_t_float32Status_Proto *proto_fls);
void AEROTypeProto_DeSerializeFloat32Status(const aero_type_protobuf::AERO_t_float32Status_Proto &proto_fls, AERO_t_float32Status *fls);

int AEROTypeProto_Serialize2DPoint(AERO_t_Point2D const *point, aero_type_protobuf::AERO_t_Point2D_Proto *proto_point);
void AEROTypeProto_DeSerialize2DPoint(const aero_type_protobuf::AERO_t_Point2D_Proto& proto_point, AERO_t_Point2D *point);

int AEROTypeProto_Serialize2DPointStatus(AERO_t_Point2DStatus const *point, aero_type_protobuf::AERO_t_Point2DStatus_Proto *proto_point);
void AEROTypeProto_DeSerialize2DPointStatus(const aero_type_protobuf::AERO_t_Point2DStatus_Proto *proto_point, AERO_t_Point2DStatus *point);

int AEROTypeProto_Serialize2DPose(AERO_t_Pose2D const *pose, aero_type_protobuf::AERO_t_Pose2D_Proto *proto_pose);
void AEROTypeProto_DeSerialize2DPose(const aero_type_protobuf::AERO_t_Pose2D_Proto& proto_pose, AERO_t_Pose2D *pose);

int AEROTypeProto_SerializePose3D(AERO_t_Pose3D const *pose, aero_type_protobuf::AERO_t_Pose3D_Proto *proto_pose);
void AEROTypeProto_DeSerializePose3D(const aero_type_protobuf::AERO_t_Pose3D_Proto& proto_pose, AERO_t_Pose3D *pose);
void AEROTypeProto_CleanUpPose3D(aero_type_protobuf::AERO_t_Pose3D_Proto *proto_pose);

int AEROTypeProto_Serialize3DPoint(AERO_t_Point3D const *point, aero_type_protobuf::AERO_t_Point3D_Proto *proto_point);
void AEROTypeProto_DeSerialize3DPoint(const aero_type_protobuf::AERO_t_Point3D_Proto& proto_point, AERO_t_Point3D *point);

int AEROTypeProto_Serialize3DPointStatus(AERO_t_Point3DStatus const *point, aero_type_protobuf::AERO_t_Point3DStatus_Proto *proto_point);
void AEROTypeProto_DeSerialize3DPointStatus(const aero_type_protobuf::AERO_t_Point3DStatus_Proto *proto_point, AERO_t_Point3DStatus *point);

int AEROTypeProto_Serialize3DOrientation(AERO_t_Orientation3D *ori, aero_type_protobuf::AERO_t_Orientation3D_Proto *proto_ori);
void AEROTypeProto_DeSerialize3DOrientation(const aero_type_protobuf::AERO_t_Orientation3D_Proto& proto_ori, AERO_t_Orientation3D *ori);

void AEROTypeProto_SerializeClothoid(const AERO_t_Clothoid *p_clothoid, aero_type_protobuf::AERO_t_Clothoid_Proto *p_proto_clothoid);
void AEROTypeProto_DeSerializeClothoid(const aero_type_protobuf::AERO_t_Clothoid_Proto *p_proto_clothoid, AERO_t_Clothoid *p_clothoid);

int AEROTypeProto_SerializePolyChain(const AERO_t_PolyChain *p_poly_chain, aero_type_protobuf::AERO_t_PolyChain_Proto *p_proto_poly_chain);
void AEROTypeProto_DeSerializePolyChain(const aero_type_protobuf::AERO_t_PolyChain_Proto *p_proto_poly_chain, AERO_t_PolyChain *p_poly_chain);
void AEROTypeProto_CleanUpPolyChain(aero_type_protobuf::AERO_t_PolyChain_Proto *p_proto_poly_chain);

int AEROTypeProto_SerializePolyChainQuality(const AERO_t_PolyChainQuality *p_quality, uint32 num_valid_bdry_points, aero_type_protobuf::AERO_t_PolyChainQuality_Proto *p_proto_quality);
void AEROTypeProto_DeSerializePolyChainQuality(const aero_type_protobuf::AERO_t_PolyChainQuality_Proto *p_proto_quality, AERO_t_PolyChainQuality *p_quality);
void AEROTypeProto_CleanUpPolyChainQuality(aero_type_protobuf::AERO_t_PolyChainQuality_Proto *p_proto_quality);

int AEROTypeProto_SerializePolyChainSmall(const AERO_t_PolyChainSmall *p_poly_chain, aero_type_protobuf::AERO_t_PolyChain_Proto *p_proto_poly_chain);
void AEROTypeProto_DeSerializePolyChainSmall(const aero_type_protobuf::AERO_t_PolyChain_Proto *p_proto_poly_chain, AERO_t_PolyChainSmall *p_poly_chain);
void AEROTypeProto_CleanUpPolyChainSmall(aero_type_protobuf::AERO_t_PolyChain_Proto *p_proto_poly_chain);

int AEROTypeProto_SerializePolyChainSmallQuality(const AERO_t_PolyChainSmallQuality *p_quality, uint32 num_valid_bdry_points, aero_type_protobuf::AERO_t_PolyChainQuality_Proto *p_proto_quality);
void AEROTypeProto_DeSerializePolyChainSmallQuality(const aero_type_protobuf::AERO_t_PolyChainQuality_Proto *p_proto_quality, AERO_t_PolyChainSmallQuality *p_quality);
void AEROTypeProto_CleanUpPolyChainSmallQuality(aero_type_protobuf::AERO_t_PolyChainQuality_Proto *p_proto_quality);

void AEROTypeProto_SerializeBooleanStatus(AERO_t_booleanStatus const *p_booleanStatus, aero_type_protobuf::AERO_t_booleanStatus_Proto *p_proto_BooleanStatus);
void AEROTypeProto_DeSerializeBooleanStatus(const aero_type_protobuf::AERO_t_booleanStatus_Proto *p_proto_BooleanStatus, AERO_t_booleanStatus *p_booleanStatus);

void AEROTypeProto_SerializeUint16Status( AERO_t_uint16Status const *p_uis, aero_type_protobuf::AERO_t_uint16Status_Proto *p_proto_uis);
void AEROTypeProto_DeSerializeUint16Status( const aero_type_protobuf::AERO_t_uint16Status_Proto *p_proto_uis ,AERO_t_uint16Status *p_uis);

void AEROTypeProto_SerializeMotion(AERO_t_Motion const *motion, aero_type_protobuf::AERO_t_Motion_Proto *proto_motion);
void AEROTypeProto_DeSerializeMotion(const aero_type_protobuf::AERO_t_Motion_Proto& proto_motion, AERO_t_Motion *motion);

aero_type_protobuf::AERO_t_SensorMake_Proto AEROTypeProto_SerializeSensorMake(AERO_t_SensorMake sensor_make);
AERO_t_SensorMake AEROTypeProto_DeSerializeSensorMake(aero_type_protobuf::AERO_t_SensorMake_Proto sensor_make_proto);

aero_type_protobuf::AERO_t_SensorDescriptor_Proto AEROTypeProto_SerializeSensorDescriptor(AERO_t_SensorDescriptor sensor_desc);
AERO_t_SensorDescriptor AEROTypeProto_DeSerializeSensorDescriptor(aero_type_protobuf::AERO_t_SensorDescriptor_Proto sensor_desc_proto);

aero_type_protobuf::AERO_t_SensorFeature_Proto AEROTypeProto_SerializeSensorFeature(AERO_t_SensorFeature sensor_feature);
AERO_t_SensorFeature AEROTypeProto_DeSerializeSensorFeature(aero_type_protobuf::AERO_t_SensorFeature_Proto sensor_feature_proto);

void AEROTypeProto_SerializeSensorStatus(AERO_t_SensorStatus const *p_sensor_status, aero_type_protobuf::AERO_t_SensorStatus_Proto *p_proto_sensor_status);
void AEROTypeProto_DeSerializeSensorStatus(const aero_type_protobuf::AERO_t_SensorStatus_Proto& proto_sensor_status, AERO_t_SensorStatus *p_sensor_status);

int AEROTypeProto_SerializeVehicleConfig(AERO_t_VehicleConfig const *vehicle_config, aero_type_protobuf::AERO_t_VehicleConfig_Proto *proto_vehicle_config);
int AEROTypeProto_DeSerializeVehicleConfig(aero_type_protobuf::AERO_t_VehicleConfig_Proto const *proto_vehicle_config, AERO_t_VehicleConfig *vehicle_config);

void AEROTypeProto_CleanUpMotion(aero_type_protobuf::AERO_t_Motion_Proto *proto_motion);
void AEROTypeProto_CleanUpVehicleConfig(aero_type_protobuf::AERO_t_VehicleConfig_Proto *proto_vehicle_config);

namespace AERO_Proto
{
  // "define" for vehicle config data channel names
  static const char* const AERO_VehCfgChannelName = "AERO_VehicleConfigChannel";
}

#endif // AERO_TYPE_SERIALIZATION_H

