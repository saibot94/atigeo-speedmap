/*! \file ****************************************************************************************************************************

  COMPANY:           Continental Automotive: Advanced Driver Assistance Systems - Advanced Engineering (for HackTM participants)

  PROJECT:           ...

  MODULNAME:         aero_hacktm_task.h

  DESCRIPTION:       HackTM module reading inputs from from Stereo Camera, Long Range Radar (both front center), Vehicle Dynamics
                     and GPS data.

  CREATION DATE:     28.03.2016

  VERSION:           $Revision: 1.1 $

  -------------------------------------------------
  About ADAS Advanced Engineering:
  -------------------------------------------------
    http://tinyurl.com/ContiAdasAeInterview 
    http://tinyurl.com/ContiAutomatedDriving 
    http://tinyurl.com/ContiADAS 
	
*/


#ifndef AERO_HACK_TM_TASK_H
#define AERO_HACK_TM_TASK_H


#include "evtplugin.h"
#include "myobjects_def.h"

#include <ecal/ecal.h>
#include <ecal/msg/proto.h>
#include "aero_trafpartic_serialization.h"
#include "aero_gps_rmc_serialization.h"
#include "aero_vehicle_data_serialization.h"
#include <iomanip>


#define RAD2DEG(rad) ((180.0f * rad ) / 3.14159265359f) /* Converts RADIANS to DEGREES */

namespace Tasks
{
  namespace AERO_HACK_TM_Task
  {
    //////////////////////////////////////////////////////////
    //           class CModPlugIn declaration
    //////////////////////////////////////////////////////////
    /**
     * @class   CModPlugIn
     *
     * @brief    Widget event dll class
     *
     * @details  This class contains the widget plugin interface and wraps the
     *           widget specific event callback functions as member function.
     *           For furher details reagrding the special event names see wxWidgets
     *           documentation.
     *           Note: The calling application creates a single instance of this class
     *           for every widget that is using this callback dll. You can obtain the
     *           full path of the widget by calling the 'GetInstance' function of the
     *           base class. The global namespace of the dll (outside this class) is 
     *           shared by ALL caller widgets.
     **/

	class CModPlugIn : public CEvtPlugIn
    {
      public:
        /**
         * @brief  Default constructor. 
         *
         * @param inst_name     Name of the plugin instance.
         * @param callback      Pointer to central callback hook (for internal use).
         **/
        CModPlugIn(const char* inst_name, wxPlg_IntFunT callback);
        /**
         * @brief  Finaliser.
         **/
        ~CModPlugIn();

        /**
         * @brief  Callback functions for the widget specific events.
         *
         * @param [in]  arg_obj  The function argument values (see 'envargs.h' for argument parsing helper functions)
         * @param [out] ret_obj  The function return values.
         *
         * @return  0 if it succeeds, -1 if it fails.
         **/
        long wxEVT_OPEN        (const wxPlg_Obj* arg_obj, wxPlg_Obj* ret_obj);
        long wxEVT_CLOSE       (const wxPlg_Obj* arg_obj, wxPlg_Obj* ret_obj);
        long wxEVT_CONNECT     (const wxPlg_Obj* arg_obj, wxPlg_Obj* ret_obj);
        long wxEVT_DISCONNECT  (const wxPlg_Obj* arg_obj, wxPlg_Obj* ret_obj);
        long wxEVT_STEP        (const wxPlg_Obj* arg_obj, wxPlg_Obj* ret_obj);
        long wxEVT_DRAW2D      (const wxPlg_Obj* arg_obj, wxPlg_Obj* ret_obj);
        long wxEVT_DRAW3D      (const wxPlg_Obj* arg_obj, wxPlg_Obj* ret_obj);
        long wxEVT_SIZE        (const wxPlg_Obj* arg_obj, wxPlg_Obj* ret_obj);

		 
      private:
	    void AEROTP_TrafParticReceive_LRR_FC(const char* topic_name_, const class aero_trafpartic_protobuf::AERO_t_TrafParticList_Proto& msg_, const long long time_);
        void AEROTP_TrafParticReceive_SCAM_FC(const char* topic_name_, const class aero_trafpartic_protobuf::AERO_t_TrafParticList_Proto& msg_, const long long time_);
	    void AEROTP_DataReceive_VEH_DYN(const char* topic_name_, const class aero_vehicle_data_protobuf::AERO_t_VehicleDynamics_Proto& msg_, const long long time_);
	    void AEROTP_DataReceive_GPS(const char* topic_name_, const class aero_gps_rmc_protobuf::AERO_t_GpsRmc_Proto& msg_, const long long time_);


		eCAL::CProtoSubscriber<class aero_trafpartic_protobuf::AERO_t_TrafParticList_Proto> *mSubTP_LRR_FC;
        eCAL::CProtoSubscriber<class aero_trafpartic_protobuf::AERO_t_TrafParticList_Proto> *mSubTP_SCAM_FC;
		eCAL::CProtoSubscriber<class aero_vehicle_data_protobuf::AERO_t_VehicleDynamics_Proto> *mSub_VEH_DYN_DATA;
        eCAL::CProtoSubscriber<class aero_gps_rmc_protobuf::AERO_t_GpsRmc_Proto> *mSub_GPS_DATA;

		// Variables containing INPUT data
	    AERO_t_TrafParticList      LRR_FC_TrafParticList;   // List of sensor Traffic Participants from LongRangeRadar Front Center
		AERO_t_TrafParticList      SCAM_FC_TrafParticList;  // List of sensor Traffic Participants from Stereo Camera Front Center
		AERO_t_VehicleDynamics     VEH_DYN_Data;            // VEHicle DYNamics Data
		AERO_t_Gps_Rmc             GPS_Data;                // GPS data

    };
  }
}

#endif //  AERO_HACK_TM_TASK_H