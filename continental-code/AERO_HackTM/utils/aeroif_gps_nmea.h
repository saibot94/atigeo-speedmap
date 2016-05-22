#ifndef AEROIF_GPS_NMEA_H
#define AEROIF_GPS_NMEA_H

#include "aero_type.h"


#ifdef __cplusplus
extern "C" 
{
#endif


//*************************************************************************//
//*                   GPS NMEA RMC message definition                      */
//*************************************************************************//

typedef struct AERO_t_Gps_Rmc
{
  AERO_t_SignalHeader		      signalHeader; 

  sint8					s_GpsStatus;							        //A - valid; V - NAV warning
  uint64			  u_UTCTime;							      //s		
  double				f_LatitudeRad;						    //radians
  double				f_Latitude;							      //degrees dddmm.mmmm
  sint8					s_LatitudeHemi;					    	//N - north; S - south
  double				f_LongitudeRad;						    //radians
  double				f_Longitude;							    //degrees dddmm.mmmm
  sint8					s_LongitudeHemi;						  //W - west; E - east
  double				f_SpeedOverGround;					  //knots
  double				f_CourseOverGround;					  //knots - is actually degrees as it seems.
  double				f_MagneticVariationRad;				//rad
  double				f_MagneticVariation;					//degrees dddmm.mmmm
  sint8					s_MagneticVariationDir;				//W - west; E - east
  sint8					s_Mode;								        //A - autonomous; D - differential; ...
                           
} AERO_t_Gps_Rmc;

#ifdef __cplusplus
}               
#endif

#endif  // AEROIF_GPS_NMEA_H
