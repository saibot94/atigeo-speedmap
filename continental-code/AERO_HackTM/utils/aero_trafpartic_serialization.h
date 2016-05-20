#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100 4127 4244 4267 4512)
#endif
#include "aeroif_traffic_participants.h"
#include "aero_traffic_participants.pb.h"
#ifdef _MSC_VER
#pragma warning(pop)
#endif


int AEROTrafparticProto_Serialize(AERO_t_TrafParticList const *traffic_participants_list, aero_trafpartic_protobuf::AERO_t_TrafParticList_Proto *proto_traffic_participants_list);
int AEROTrafparticProto_DeSerialize(aero_trafpartic_protobuf::AERO_t_TrafParticList_Proto const *proto_traffic_participants_list, AERO_t_TrafParticList *traffic_participants_list);
void AEROTrafparticProto_CleanUp(aero_trafpartic_protobuf::AERO_t_TrafParticList_Proto *proto_traffic_participants_list);

namespace AERO_Proto
{

  // "define" for traffic participant channel name
  static const char* const AERO_LRR_FC_TPLChannel     = "AERO_LRR_FC_TrafParticList";
  static const char* const AERO_SCAM_FC_TPLChannel    = "AERO_SCAM_FC_TrafParticList";

}
