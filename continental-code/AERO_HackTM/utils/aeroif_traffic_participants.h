#ifndef _AERO_TRAFFIC_PARTICIPANTS_H_
#define _AERO_TRAFFIC_PARTICIPANTS_H_

#include "aero_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************/
/*                                   Administrative Section                               */
/******************************************************************************************/

	
typedef enum AERO_t_TrafPartic_State
{
  AERO_TP_STATE_NA          = 0U,  // no state available; status not filled
  AERO_TP_STATE_MOVING      = 1U,  // principally moving, but not along same line with ego vehicle or oncoming
  AERO_TP_STATE_ONCOMING    = 2U,  // moving in opposite direction of ego vehicle
  AERO_TP_STATE_ALONG       = 3U,  // moving along same line with ego vehicle
  AERO_TP_STATE_STATIONARY  = 4U,  // stationary TP
  AERO_TP_STATE_CUTINFL     = 5U,  // moving along same line with ego vehicle and cutting in from left
  AERO_TP_STATE_CUTINFR     = 6U,  // moving along same line with ego vehicle and cutting in from right
  AERO_TP_STATE_STOPPED     = 7U,  // TP has stopped but was observed moving before
  AERO_TP_STATE_MAX         = AERO_MAX_ENUM // pseudo enum to ensure constant size
} AERO_t_TrafPartic_State;

typedef enum AERO_t_TrafPartic_Class
{
  AERO_TP_CLASS_UNKNOWN                    = 0U,   // level 1 class for type unknown; class cannot be determined
  AERO_TP_CLASS_VEHICLE                    = 1U,   // level 1 class for vehicle type with three and more wheels
  AERO_TP_CLASS_ANIMAL                     = 2U,   // level 1 class for animal
  AERO_TP_CLASS_VULNERABLEROADUSER         = 3U,   // level 1 class for vulnerable road users like pedestrian or motor-/bicycle
  AERO_TP_CLASS_OTHER                      = 4U,   // level 1 class for other moving "objects" which have no super class
  AERO_TP_CLASS_GHOST                      = 5U,   // level 1 class for ghost objects
  AERO_TP_CLASS_CAR                        = 11U,  // level 2 class (level 1 class AERO_TP_VEHICLE) for passenger car
  AERO_TP_CLASS_COMMERCIAL_VEH             = 12U,  // level 2 class (level 1 class AERO_TP_VEHICLE) for commercial vehicle like truck
  AERO_TP_CLASS_BUS                        = 13U,  // level 2 class (level 1 class AERO_TP_VEHICLE) for busses
  AERO_TP_CLASS_EMERGENCY_VEH              = 14U,  // level 2 class (level 1 class AERO_TP_VEHICLE) for emergency vehicles
  AERO_TP_CLASS_VEHICLE_OTHER              = 15U,  // level 2 class (level 1 class AERO_TP_VEHICLE) for other, not classifieable level 2 classes for level 1 class vehicle
  AERO_TP_CLASS_ANIMAL_OTHER               = 16U,  // level 2 class (level 1 class AERO_TP_ANIMALS) for other, not classifieable level 2 classes for level 1 class animals
  AERO_TP_CLASS_BICYCLE                    = 17U,  // level 2 class (level 1 class AERO_TP_VULNERABLEROADUSER) for bicycles
  AERO_TP_CLASS_MOTORCYCLE                 = 18U,  // level 2 class (level 1 class AERO_TP_VULNERABLEROADUSER) for motorcycles
  AERO_TP_CLASS_PEDESTRIAN                 = 19U,	 // level 2 class (level 1 class AERO_TP_VULNERABLEROADUSER) for pedestrian
  AERO_TP_CLASS_VULNERABLEROADUSERS_OTHER  = 20U,  // level 2 class (level 1 class AERO_TP_VULNERABLEROADUSER) for other, not classifieable level 2 classes for level 1 class vulnerable road users
  AERO_TP_CLASS_LEAVES                     = 21U,  // level 2 class (level 1 class AERO_TP_OTHER) for leaves from trees
  AERO_TP_CLASS_MAX_NUM_CLASSES            = 22U,  // INSERT NEW classes above this one and adapt
  AERO_TP_CLASS_MAX                        = AERO_MAX_ENUM // pseudo enum to ensure constant size
}AERO_t_TrafPartic_Class;

typedef struct AERO_t_TrafPartic_Classification
{
  AERO_t_SignalStatus          e_SignalStatus;                              // validity of classification data
  uint32                      u_ValidClasses;                              // number of valid classes in class vector
  AERO_t_TrafPartic_Class      e_Class[AERO_TP_CLASS_MAX_NUM_CLASSES];       // Class type which is assigned to the TP
  AERO_t_TrafPartic_Class      e_ParentClass[AERO_TP_CLASS_MAX_NUM_CLASSES]; // Parental class type of TP class type
  float32                     f_ClassProb[AERO_TP_CLASS_MAX_NUM_CLASSES];   // [0.0 ... 1.0] probability of class assignment
}AERO_t_TrafPartic_Classification;

typedef enum AERO_t_TrafPartic_Track_Status
{
  AERO_TP_TRACK_STATUS_NA          = 0U,  // no state available; status not filled
  AERO_TP_TRACK_STATUS_SENSED      = 1U,  // Traffic participant is detected and tracked in sensor only
  AERO_TP_TRACK_STATUS_FUSED       = 2U,  // Traffic participant is fused with other sensor tracks (new track) or/and with existing track
  AERO_TP_TRACK_STATUS_PREDICTED   = 3U,  // Traffic participant track is not confirmed in current cycle by sensor data, but predicted (to keep track as history)
}AERO_t_TrafPartic_Track_Status;

typedef struct AERO_t_TrafParticAdminProp
{
  AERO_t_u_Id                       Id;                           // ID, which allows unique identification
  float32                          f_Probability;                // [0.0 ... 1.0] Probability of existance of TP
  AERO_t_TrafPartic_State           e_State;                      // State of traffic participant
  AERO_t_TrafPartic_Classification  Classification;               // Classification of TP, reliability of classification and timestamp of class's assignment
  AERO_t_s_Timestamp                s_LifeTime;                   // [us] Age of the TP from first detection on
  AERO_t_s_Timestamp                s_LastConfirmationTime;       // [us] Timestamp, at which the TP was detected at last timestamp in sensor or confirmed in fusion
  AERO_t_TrafPartic_Track_Status    e_TrackStatus;                // [-] Status for track of TP; see typedef
  uint32                           u_SensorCurrent;              // Bitfield of which sensor has TP detected in current cycle
  uint32                           u_SensorOverLifetime;         // Bitfield of which sensors have TP detected since first detection
}AERO_t_TrafParticAdminProp;

/******************************************************************************************/
/*                                   Geometry Section                                     */
/*                                                                                        */
/* As basic assumption for geometry description a box model is used. If a more detailed   */
/* description of the TP geometry, an appropriate description will be integrated here,    */
/* a "mini-grid" e.g.                                                                     */
/******************************************************************************************/

typedef enum AERO_t_TrafPartic_Reference
{
  AERO_TP_REFERENCE_FRONTLEFT    = 0U, //    0_____1_____2
  AERO_TP_REFERENCE_FRONTCENTER  = 1U, //    |           |
  AERO_TP_REFERENCE_FRONTRIGHT   = 2U, //    |           |
  AERO_TP_REFERENCE_CENTERLEFT   = 3U, //  */|-----------|\*
  AERO_TP_REFERENCE_CENTER       = 4U, //    ||         ||
  AERO_TP_REFERENCE_CENTERRIGHT  = 5U, //    ||         ||
  AERO_TP_REFERENCE_REARLEFT     = 6U, //    3|    4    |5
  AERO_TP_REFERENCE_REARCENTER   = 7U, //    ||         ||
  AERO_TP_REFERENCE_REARRIGHT    = 8U, //    ||         ||
                                       //    |-----------|
                                       //    |           |
                                       //    |___________|
                                       //    6     7     8  

  AERO_TP_REFERENCE_MAX          = AERO_MAX_ENUM // pseudo enum to ensure constant size
}AERO_t_TrafPartic_Reference;

typedef struct AERO_t_TrafPartic_ReferencePoint
{
  AERO_t_SignalStatus          e_SignalStatus; // validity of reference point data
  AERO_t_TrafPartic_Reference  e_Reference;    // reference point for which position of TP is given
}AERO_t_TrafPartic_ReferencePoint;

typedef struct AERO_t_TrafParticGeomProp
{
  AERO_t_Point3D               Position;        // [m] x, y and z position of reference point in ego vehicle coordinate system
  AERO_t_Point3DStatus         PositionStdev;   // [m] standard deviation of x, y and z position
  AERO_t_float32Status         PositionXYCrossStdev; // [m] Minor diagonal elements of position standard deviation (sigma_xy)
  AERO_t_TrafPartic_ReferencePoint  ReferencePoint;  // [-] Index for reference point for position of TP 
  AERO_t_float32Status         Length;          // [m] length (x-size) of bounding box in coordinate system of TP
  AERO_t_float32Status         LengthStdev;     // [m] standard deviation of length
  AERO_t_float32Status         Width;           // [m] width (y-size) of bounding box in coordinate system of TP
  AERO_t_float32Status         WidthStdev;      // [m] standard deviation of width
  AERO_t_float32Status         Height;          // [m] height (z-size) of bounding box in coordinate system of TP
  AERO_t_float32Status         HeightStdev;     // [m] standard deviation of height
  AERO_t_float32Status         Heading;         // [rad] Heading angle of TP in ego vehicle coordinate system
  AERO_t_float32Status         HeadingStdev;    // [rad] standard deviation of heading angle
} AERO_t_TrafParticGeomProp;

/******************************************************************************************/
/*                                    Dynamic Section                                     */
/******************************************************************************************/

typedef struct AERO_t_TrafParticDynProp
{
  AERO_t_Point2DStatus  Velocity;           // [m/s] Velocity of TP in ego vehicle coordinate system
  AERO_t_Point2DStatus  VelocityStdev;      // [m/s] standard deviation of velocity in x- and y-direction
  AERO_t_float32Status  VelocityUVCrossStdev;// [m/s] Minor diagonal elements of velocity standard deviation (sigma_uv)
  AERO_t_float32Status  AccelerationX;      // [m/s^2] Acceleration of TP in x-direction of ego vehicle coordinate system
  AERO_t_float32Status  AccelerationXStdev; // [m/s^2] standard deviation of acceleration in x-direction
  AERO_t_float32Status  AccelerationY;      // [m/s^2] Acceleration of TP in y-direction of ego vehicle coordinate system
  AERO_t_float32Status  AccelerationYStdev; // [m/s^2] standard deviation of acceleration in y-direction
  AERO_t_float32Status  AccelerationXYCrossStdev;// [m/s^2] Minor diagonal elements of acceleration standard deviation (sigma_xy)
  float32              f_MaxObsSpeed;      // [m/s] Maximal observed absolute speed of TP
}AERO_t_TrafParticDynProp;

/******************************************************************************************/
/*                                    Supporting Section                                  */
/******************************************************************************************/
typedef enum AERO_t_TrafPartic_SFlag
{
  AERO_TP_SFLAG_NA               = 0x000000,
  AERO_TP_SFLAG_BRAKING_LIGHT    = 0x000001,
  AERO_TP_SFLAG_INDICATOR_LEFT   = 0x000002,
  AERO_TP_SFLAG_INDICATOR_RIGHT  = 0x000004,
  AERO_TP_SFLAG_WARNING_LIGHT    = 0x000008,
  AERO_TP_SFLAG_SIREN            = 0x000010,
  AERO_TP_SFLAG_ACC              = 0x000020, // Used as ACC relevant TP in sensor function
  AERO_TP_SFLAG_EBA              = 0x000040, // Used as EBA relevant TP in sensor function
  AERO_TP_SFLAG_BSD              = 0x000080, // Used as blind spot relevant TP in sensor function
  AERO_TP_SFLAG_MAX              = AERO_MAX_ENUM // pseudo enum to ensure constant size
}AERO_t_TrafPartic_SFlag;

typedef struct AERO_t_TrafParticSupportProp
{
  AERO_t_SignalStatus      e_SignalStatus;  // validity of supporting data
  uint32                  u_SupportFlag;   // Several flags to support prediction and analysis
} AERO_t_TrafParticSupportProp;

/******************************************************************************************/
/*                                    Debug Section                                       */
/******************************************************************************************/

typedef struct AERO_t_TrafParticDebugProp
{
  AERO_t_SignalStatus      e_SignalStatus;            // validity of supporting data
}AERO_t_TrafParticDebugProp;

/******************************************************************************************/
/*                                    Single TP	                                          */
/******************************************************************************************/

typedef struct AERO_t_TrafPartic
{
  AERO_t_SignalStatus           e_SignalStatus;  // validity of TP list entry
  AERO_t_TrafParticAdminProp    AdminProp;       // Administrative properties of TP
  AERO_t_TrafParticGeomProp     GeomProp;        // Geometric properties of TP
  AERO_t_TrafParticDynProp      DynProp;         // Dynamic properties of TP
  AERO_t_TrafParticSupportProp  SupportProp;     // Properties of TP to support subsequent analysis or function
  AERO_t_TrafParticDebugProp    DebugProp;       // Properties of TP for debugging purpose
}AERO_t_TrafPartic;

/******************************************************************************************/
/*                                    TP List		                                      */
/******************************************************************************************/

typedef struct AERO_t_TrafParticList
{
  AERO_t_SignalHeader  SignalHeader;                                // signal header
  AERO_t_SensorStatus  SensorStatus;                                // status of the sensor providing the data
  uint32              u_NumTrafficParticipants;                    // Number of all traffic participants
  AERO_t_Motion        EgoMotion;                                   // Motion vector of ego vehicle to determine precise absolute velocity of TP
  AERO_t_TrafPartic    TrafPart[AERO_MAX_NUM_TRAFFIC_PARTICIPANTS];  // List of all traffic participants with valid length of u_NumTrafficParticipants; valid TP are the first u_NumTrafficParticipants TP's
}AERO_t_TrafParticList;

#ifdef __cplusplus
}
#endif

#endif // _AERO_TRAFFIC_PARTICIPANTS_H_
