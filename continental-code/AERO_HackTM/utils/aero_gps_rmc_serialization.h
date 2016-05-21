#include "aeroif_gps_nmea.h"
#include "aero_gps_rmc.pb.h"

int AEROGpsRmcProto_Serialize(const AERO_t_Gps_Rmc *p_GpsRmcData, aero_gps_rmc_protobuf::AERO_t_GpsRmc_Proto *p_ProtoGpsRmcData);
int AEROGpsRmcProto_DeSerialize(const aero_gps_rmc_protobuf::AERO_t_GpsRmc_Proto *p_ProtoGpsRmcData, AERO_t_Gps_Rmc *p_GpsRmcData);
void AEROGpsRmcProto_CleanUp(aero_gps_rmc_protobuf::AERO_t_GpsRmc_Proto *p_ProtoGpsRmcData);


namespace AERO_Proto
{
  // "define" for sensor data channel names
  static const char* const AERO_GPS_RMC_Data_Channel     = "AERO_GPS_RMC_Data";

}

