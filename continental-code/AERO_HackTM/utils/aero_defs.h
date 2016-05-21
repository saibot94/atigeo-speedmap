#ifndef AERO_DEFS_H
#define AERO_DEFS_H


#ifdef __cplusplus
extern "C"
{
#endif

//**************************************************************************
//define: AERO_BOOLEAN2BOOL_T
//Description: macro for converting MISRA boolean to c++ boolean to avoid warnings
#define AERO_BOOLEAN2BOOL_T(b) ((b) != 0 ? true : false)

//**************************************************************************
//define: AERO_MAX_ENUM
//Description: non-used max enum to ensure constant type size of enums no matter what compiler settings are
#define AERO_MAX_ENUM 2147483647U

//**************************************************************************
//define: AERO_MAX_UINT32
//Description: max value in range for type uint32 (0XFFFFFFFF)
#define AERO_MAX_UINT32 4294967295U
//**************************************************************************
//define: AERO_LEFT, AERO_RIGHT
//Description: fixed defines to use for indexing left and rigt side, e.g. by lane markings
#define AERO_LEFT   0U             // index of first next instance to ego position on left-hand side
#define AERO_RIGHT  1U             // index of first next instance to ego position on right-hand side
#define AERO_LEFT_2ND_NEXT 2U      // index of second next instance to ego position on left-hand side
#define AERO_RIGHT_2ND_NEXT 3U     // index of second next instance to ego position on right-hand side

//**************************************************************************
//define: AERO_MAX_NUM_MOUNTED_SENSOR
//Description: fixed define for maximal number of sensors which are installed in a vehicle
#define AERO_MAX_NUM_MOUNTED_SENSORS  20U

//**************************************************************************
//define: AERO_MAX_NUM_TRAFFIC_PARTICIPANTS
//Description: fixed define for maximal number of traffic participant list length
#define AERO_MAX_NUM_TRAFFIC_PARTICIPANTS  100U

//**************************************************************************
//define: AERO_BOUNDARYPOINT_HEIGHT_UNKNOWN
//Description: "magic number" for indicating that a boundary height is unknown at this point 
#define AERO_BOUNDARYPOINT_HEIGHT_UNKNOWN          (-128)

//**************************************************************************
//define: AERO_BOUNDARYPOINT_HEIGHT_UNDERDRIVEABLE
//Description: "magic number" for indicating that the vehicle can drive under a boundry height, to be used e.g. for bridges
#define AERO_BOUNDARYPOINT_HEIGHT_UNDERDRIVEABLE     127 

//**************************************************************************
//define: AERO_MAX_NUM_LANES_IN_DRIVING_DIRECTION
//Description: adapted from ADASIS v2 specification
#define AERO_MAX_NUM_LANES_IN_DRIVING_DIRECTION  6U

//**************************************************************************
//define: AERO_MAX_NUM_LANES_IN_DRIVING_DIRECTION
//Description: adapted from ADASIS v2 specification
#define AERO_MAX_NUM_LANES_IN_OPPOSITE_DIRECTION 2U

//**************************************************************************
//define:       AERO_MAX_NUM_LANE_MARKERS
//Description:  define for maximum number of lane markers provided by 
//              an imaging sensor, e.g. the MFC camera
#define AERO_MAX_NUM_LANE_MARKERS 2

//**************************************************************************
//define: AERO_THOUSENDTH
//Description: 1/1000 for using multiplying conversion
#define AERO_THOUSENDTH 0.001F

//**************************************************************************
//define: AERO_MILLIONTH
//Description: 1/1000000 for using multiplying conversion
#define AERO_MILLIONTH 0.000001F

//**************************************************************************
//define: AERO_MILLION
//Description: 1000000.0 for using multiplying conversion
#define AERO_MILLION 1000000.0F

//**************************************************************************
//define: AERO_HALF
//Description: 1/2 for using multiplying conversion
#define AERO_HALF 0.5F

//**************************************************************************
//define: AERO_CONV_RAD_TO_DEG
//Description: 180/PI; [°] for using multiplying conversion
#define AERO_CONV_RAD_TO_DEG 57.29577F

//**************************************************************************
//define: AERO_CONV_DEG_TO_RAD
//Description: PI/180; [rad] for using multiplying conversion
#define AERO_CONV_DEG_TO_RAD 0.01745F

//**************************************************************************
//define: AERO_CONST_G
//Description: gravitational acceleration [M/S^2]
#define AERO_CONST_G 9.81F

#ifdef __cplusplus
}
#endif

#endif // AERO_TYPE_H

