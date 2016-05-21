#ifndef AERO_VEHICLE_DATA_SERIALIZATION_H
#define AERO_VEHICLE_DATA_SERIALIZATION_H

#include "aero_vehicle_data.h"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100)
#endif
#include "aero_vehicle_data.pb.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif


#if 0
int AEROVehicleDataProto_SerializeCarSwitches(const AERO_t_CarSwitches *p_CS, aero_vehicle_data_protobuf::AERO_t_CarSwitches_Proto *p_proto_CS);
void AEROVehicleDataProto_DeSerializeCarSwitches(const aero_vehicle_data_protobuf::AERO_t_CarSwitches_Proto *p_proto_CS, AERO_t_CarSwitches *p_CS);
void AEROVehicleDataProto_CleanUpCarSwitches(aero_vehicle_data_protobuf::AERO_t_CarSwitches_Proto *proto_CS);

int AEROVehicleDataProto_SerializeCSSignal(const AERO_t_CS_Signal *p_CS_Signal, aero_vehicle_data_protobuf::AERO_t_CS_Signal_Proto *p_proto_CS_Signal); 
void AEROVehicleDataProto_DeSerializeCSSignal(const aero_vehicle_data_protobuf::AERO_t_CS_Signal_Proto *p_proto_CS_Signal, AERO_t_CS_Signal *p_CS_Signal);
void AEROVehicleDataProto_CleanUpCSSignal(aero_vehicle_data_protobuf::AERO_t_CS_Signal_Proto *proto_CS_Signal);

int AEROVehicleDataProto_SerializeCSStatus(const AERO_t_CS_Status *p_CS_Signal, aero_vehicle_data_protobuf::AERO_t_CS_Status_Proto *p_proto_CS_Signal); 
void AEROVehicleDataProto_DeSerializeCSStatus(const aero_vehicle_data_protobuf::AERO_t_CS_Status_Proto *p_proto_CS_Signal, AERO_t_CS_Status *p_CS_Signal);
void AEROVehicleDataProto_CleanUpCSStatus(aero_vehicle_data_protobuf::AERO_t_CS_Status_Proto *proto_CS_Signal);

int AEROVehicleDataProto_SerializeBrake(const AERO_t_Brake *p_Brake, aero_vehicle_data_protobuf::AERO_t_Brake_Proto *p_proto_Brake);
void AEROVehicleDataProto_DeSerializeBrake(const aero_vehicle_data_protobuf::AERO_t_Brake_Proto *p_proto_Brake, AERO_t_Brake *p_Brake);
void AEROVehicleDataProto_CleanUpBrake(aero_vehicle_data_protobuf::AERO_t_Brake_Proto *p_proto_Brake);

int AEROVehicleDataProto_SerializePowerTrain(const AERO_t_PowerTrain *p_PowerTrain, aero_vehicle_data_protobuf::AERO_t_PowerTrain_Proto *p_proto_PowerTrain);
void AEROVehicleDataProto_DeSerializePowerTrain(const aero_vehicle_data_protobuf::AERO_t_PowerTrain_Proto *p_proto_PowerTrain, AERO_t_PowerTrain *p_PowerTrain);
void AEROVehicleDataProto_CleanUpPowerTrain(aero_vehicle_data_protobuf::AERO_t_PowerTrain_Proto *p_proto_PowerTrain);
#endif

int AEROVehicleDataProto_SerializeWheelTicks(const AERO_t_WheelTicks *p_WheelTicks, aero_vehicle_data_protobuf::AERO_t_WheelTicks_Proto *p_proto_WheelTicks);
void AEROVehicleDataProto_DeSerializeWheelTicks(const aero_vehicle_data_protobuf::AERO_t_WheelTicks_Proto *p_proto_WheelTicks, AERO_t_WheelTicks *p_WheelTicks);
void AEROVehicleDataProto_CleanUpWheelTicks(aero_vehicle_data_protobuf::AERO_t_WheelTicks_Proto *p_proto_WheelTicks);

int AEROVehicleDataProto_SerializeVehicleDynamics(const AERO_t_VehicleDynamics *p_VD, aero_vehicle_data_protobuf::AERO_t_VehicleDynamics_Proto *p_proto_VD);
void AEROVehicleDataProto_DeSerializeVehicleDynamics(const aero_vehicle_data_protobuf::AERO_t_VehicleDynamics_Proto *p_proto_VD, AERO_t_VehicleDynamics *p_VD);
void AEROVehicleDataProto_CleanUpVehicleDynamics(aero_vehicle_data_protobuf::AERO_t_VehicleDynamics_Proto *p_proto_VD);

int AEROVehicleDataProto_SerializeVehiclePose(const AERO_t_VehiclePose *p_VehPose, aero_vehicle_data_protobuf::AERO_t_VehiclePose_Proto *p_proto_VehPose);
void AEROVehicleDataProto_DeSerializeVehiclePose(const aero_vehicle_data_protobuf::AERO_t_VehiclePose_Proto *p_proto_VehPose ,AERO_t_VehiclePose *p_VehPose);
void AEROVehicleDataProto_CleanUpVehiclePose(aero_vehicle_data_protobuf::AERO_t_VehiclePose_Proto *proto_VehPose);

namespace AERO_Proto
{
  // "define" for vehicle data channel names
  static const char* const AERO_Vehicle_Pose_Channel        = "AERO_VehPose";
  static const char* const AERO_Vehicle_Dynamics_Channel    = "AERO_VehDyn";
  static const char* const AERO_WheelTicks_Channel          = "AERO_WheelTicks";

}

#endif //AERO_VEHICLE_DATA_SERIALIZATION_H