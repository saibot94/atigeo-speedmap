#ifndef AERO_TYPE_H
#define AERO_TYPE_H

#include "glob_type.h"
#include "aero_defs.h"

#ifdef __cplusplus
extern "C"
{
#endif

//**************************************************************************
//Type: AERO_t_s_Timestamp
//Description: timestamp to be used throughout AERO component
//Range:       (-9223372036854775808...9223372036854775807)
//Resolution:  1
//Unit:        us
typedef sint64 AERO_t_s_Timestamp;

//**************************************************************************
//Type: AERO_t_u_CycleCounter
//Description: cycle counter to be used throughout AERO component
//Range:       (0...4294967295)
//Resolution:  1
//Unit:        - (calls)
typedef uint32 AERO_t_u_CycleCounter;

//**************************************************************************
//Type: AERO_t_u_Id
//Description: ID type to be used throughout AERO component
//Range:       (0...4294967295)
//Resolution:  1
//Unit:        - (calls)
typedef uint32 AERO_t_u_Id;

//**************************************************************************
//Type: AERO_t_SignalStatus
//Description: signal status to be used throughout AERO component to indicate signal validity
//Range:       (0...2)
//Resolution:  -
//Unit:        -
typedef enum AERO_t_SignalStatus
{
  AERO_SIGNAL_STATUS_INIT    = 0U,
  AERO_SIGNAL_STATUS_OK      = 1U,
  AERO_SIGNAL_STATUS_INVALID = 2U,
  AERO_SIGNAL_STATUS_TIMEOUT = 3U,
  AERO_SIGNAL_STATUS_MAX     = AERO_MAX_ENUM  // pseudo enum to ensure constant size
} AERO_t_SignalStatus;

typedef enum AERO_t_TriState
{
  AERO_TRISTATE_UNKNOWN      =  0U,  // state is unknown
  AERO_TRISTATE_TRUE         =  1U,  // state is known and true
  AERO_TRISTATE_FALSE        =  2U,  // state is known and false
  AERO_TRISTATE_MAX          = AERO_MAX_ENUM  // pseudo enum to ensure constant size
} AERO_t_TriState;

//**************************************************************************
//Type: AERO_t_float32Status
//Description: Signal definition for float32 including signal status for validity
//Range:       -
//Resolution:  -
//Unit:        m
typedef struct AERO_t_float32Status
{
  AERO_t_SignalStatus  e_SignalStatus;  // validity of point data
  float32             f_Value;         // default unit [m] if nothing else is defined
} AERO_t_float32Status;

//**************************************************************************
//Type: AERO_t_uint16Status
//Description: Signal definition for uint16 including signal status for validity
//Range:       -
//Resolution:  -
//Unit:        -
typedef struct AERO_t_uint16Status
{
  AERO_t_SignalStatus  e_SignalStatus;  // validity of point data
  uint16              u_Value;         // value of signal
} AERO_t_uint16Status;

//**************************************************************************
//Type: AERO_t_booleanStatus
//Description: Signal definition for boolean including signal status for validity;
//Range:       -
//Resolution:  -
//Unit:        -
typedef struct AERO_t_booleanStatus
{
  AERO_t_SignalStatus  e_SignalStatus;  // validity of point data
  boolean             b_Value;         // value of signal
} AERO_t_booleanStatus;

//**************************************************************************
//Type: AERO_t_Point2D
//Description: 2-dimensional point definition, in SI units and x- and y direction of AUTOSAR coordinates unless otherwise explicitly noted
//Range:       -
//Resolution:  -
//Unit:        meters
typedef struct AERO_t_Point2D
{
  float32 f_X;     // default: [m] distance
  float32 f_Y;     // default: [m] lateral offset
} AERO_t_Point2D;

//**************************************************************************
//Type: AERO_t_Point2DStatus
//Description: 2-dimensional point definition, in SI units and AUTOSAR coordinates unless otherwise explicitly noted; signal status is added for validity
//Range:       -
//Resolution:  -
//Unit:        meters
typedef struct AERO_t_Point2DStatus
{
  AERO_t_SignalStatus  e_SignalStatus;  // validity of point data
  float32             f_X;             // default: [m] distance
  float32             f_Y;             // default: [m] lateral offset
} AERO_t_Point2DStatus;

//Type: AERO_t_BoundaryPoint
//Description: 2-dimensional pose with additional height definition, in SI units and AUTOSAR coordinates unless otherwise explicitly noted
//Range:       -
//Resolution:  -
//Unit:        meters
typedef struct AERO_t_BoundaryPoint
{

  AERO_t_Point2D                   Position;      // x, y and height coordinate of the controlpoint in m
  sint8                           s_Height;      // [cm], over ground, from -127 centimeters to +126 cm, -128 means unknown height, 127 means vehicle can drive under obstacle
                                                 // see/use defines from aero_defs.h
} AERO_t_BoundaryPoint;

//**************************************************************************
//Type: AERO_t_Point3D
//Description: 3-dimensional point definition, in SI units and AUTOSAR coordinates unless otherwise explicitly noted
//Range:       -
//Resolution:  -
//Unit:        meters
typedef struct AERO_t_Point3D
{
  float32 f_X;     // default: [m] distance
  float32 f_Y;     // default: [m] lateral offset
  float32 f_Z;     // default: [m] height over ground
} AERO_t_Point3D;

//**************************************************************************
//Type: AERO_t_Point3DStatus
//Description: 3-dimensional point definition, in SI units and AUTOSAR coordinates unless otherwise explicitly noted; signal status is added for validity
//Range:       -
//Resolution:  -
//Unit:        meters
typedef struct AERO_t_Point3DStatus
{
  AERO_t_SignalStatus  e_SignalStatus;  // validity of point data
  float32             f_X;             // default: [m] distance
  float32             f_Y;             // default: [m] lateral offset
  float32             f_Z;             // default: [m] height over ground
} AERO_t_Point3DStatus;

//**************************************************************************
//Type: AERO_t_Orientation3D
//Description: 3-dimensional orientation (angle) definition, in SI units and AUTOSAR coordinates unless otherwise explicitly noted
//Range:       -
//Resolution:  -
//Unit:        radians
typedef struct AERO_t_Orientation3D
{
  // angles are in "Z-Y-X Euler angles" (mathematically equal to "X-Y-Z fixed angles") i.e. rotations refer to a moving coordinate system (jf. J. C. Craig, "Robotics - Mechanics and Control").
  float32 f_Roll;  // default: [rad] roll, i.e. rotation arond x axis, right handed coordinate system, i.e. positive when you "look into the axis"
  float32 f_Pitch; // default: [rad] pitch, i.e. rotation arond y axis, right handed coordinate system, i.e. positive when you "look into the axis"
  float32 f_Yaw;   // default: [rad] yaw, i.e. rotation arond z axis, right handed coordinate system, i.e. positive when you "look into the axis"
} AERO_t_Orientation3D;

//**************************************************************************
//Type: AERO_t_Pose2D
//Description: 2-dimensional pose definition (in the plane), in SI units and AUTOSAR coordinates unless otherwise explicitly noted
//Range:       -
//Resolution:  -
//Unit:        meters, radians
typedef struct AERO_t_Pose2D
{
  float32             f_X;             // default: [m] distance
  float32             f_Y;             // default: [m] lateral offset
  float32             f_Yaw;           // default: [rad] yaw, i.e. rotation arond z axis, right handed coordinate system, i.e. positive counter-clockwise
} AERO_t_Pose2D;

//**************************************************************************
//Type: AERO_t_Pose3D
//Description: 3-dimensional pose definition, in SI units and AUTOSAR coordinates unless otherwise explicitly noted
//Range:       -
//Resolution:  -
//Unit:        meters, radians
typedef struct AERO_t_Pose3D
{
  AERO_t_SignalStatus   e_SignalStatus; // validity of pose data
  AERO_t_Point3D        Position;       // [meters] position part of pose
  AERO_t_Orientation3D  Orientation;    // [rad] orientation part of pose
} AERO_t_Pose3D;

//**************************************************************************
//Type: AERO_t_Motion
//Description: Motion vector in SI units and AUTOSAR coordinates unless otherwise explicitly noted
//Range:       -
//Resolution:  -
//Unit:        meter/s, radians/s
typedef struct AERO_t_Motion
{
  AERO_t_SignalStatus  e_SignalStatus; // validity of point data
  AERO_t_Point2D       Velocity;       // [meter/s] position part of pose
  float32             f_YawRate;        // [rad/s] yaw rate
} AERO_t_Motion;

//**************************************************************************
//Type: AERO_t_SignalHeader
//Description: signal header to be used throughout AERO component to pass on timestamps, track signal flow, etc.
//Range:       (0...2)
//Resolution:  -
//Unit:        -
typedef struct AERO_t_SignalHeader
{
  AERO_t_s_Timestamp    s_Timestamp;
  AERO_t_u_CycleCounter u_CycleCounter;
  AERO_t_SignalStatus   e_SignalStatus;
} AERO_t_SignalHeader;

//**************************************************************************
//Type: AERO_t_SensorDescriptor
//Description: Sensor descriptor, this describes a technology of sensor and it position on the vehicle, it is convieved as a bit-field to accomodate for the fact that objects, points
//             etc. can be seen by several sensors
//Range:       -
//Resolution:  -
//Unit:        meters, radians
typedef enum AERO_t_SensorDescriptor
{
  AERO_SENSORDESC_NONE                           = 0x00000000,  // no sensor
  // range 0x01-0x1F reserved for front looking cameras
  AERO_SENSORDESC_STEREO_CAM_FRONT_LEFT          = 0x00000001,  // left camera of a stereo cam system
  AERO_SENSORDESC_STEREO_CAM_FRONT_RIGHT         = 0x00000002,  // right camera of a stereo cam system
  AERO_SENSORDESC_MONO_CAM_FRONT_LONG_RANGE      = 0x00000004,  // long range front looking mono cam
  AERO_SENSORDESC_MONO_CAM_FRONT_STD_RANGE       = 0x00000008,  // standard range (mfc type) front looking mono cam
  // range 0x20-0x100 reserved for long range radar
  AERO_SENSORDESC_RADAR_FRONT_LONG_RANGE         = 0x00000020,  // long range front looking radar (ars style)
  AERO_SENSORDESC_RADAR_REAR_CENTRE_LONG_RANGE   = 0x00000040,  // long range rear looking radar, centered (ars style)
  AERO_SENSORDESC_RADAR_REAR_LEFT_LONG_RANGE     = 0x00000080,  // long range rear looking radar, looking to the left, i.e. negative yaw (ars style)
  AERO_SENSORDESC_RADAR_REAR_RIGHT_LONG_RANGE    = 0x00000100,  // long range rear looking radar, looking to the right, i.e. positive yaw (ars style)
  // range 0x200-0x1000 reserved for short range radar
  AERO_SENSORDESC_RADAR_FRONT_LEFT_SHORT_RANGE   = 0x00000200,  // short range front looking radar, looking to the left (srr style)
  AERO_SENSORDESC_RADAR_REAR_LEFT_SHORT_RANGE    = 0x00000400,  // short range rear looking radar, looking to the left (srr style)
  AERO_SENSORDESC_RADAR_REAR_RIGHT_SHORT_RANGE   = 0x00000800,  // short range rear looking radar, looking to the right (srr style)
  AERO_SENSORDESC_RADAR_FRONT_RIGHT_SHORT_RANGE  = 0x00001000,  // short range front looking radar, looking to the right (srr style)
  // range 0x2000-0x20000 reserved for lidar
  AERO_SENSORDESC_LIDAR_FRONT                    = 0x00002000,  // front looking lidar (Ibeo style)
  AERO_SENSORDESC_LIDAR_LEFT                     = 0x00004000,  // left looking lidar (Ibeo style)
  AERO_SENSORDESC_LIDAR_REAR                     = 0x00008000,  // rear looking lidar (Ibeo style)
  AERO_SENSORDESC_LIDAR_RIGHT                    = 0x00010000,  // right looking lidar (Ibeo style)
  AERO_SENSORDESC_LIDAR_CENTRE                   = 0x00020000,  // central lidar, could be "dome" (Velodyne style) or "virtual" fused lidar
  // virtual sensors
  AERO_SENSORDESC_MAP_INPUT                      = 0x00040000,  // information from SD map
  AERO_SENSORDESC_MODEL_ASSUMPTION               = 0x00080000,  // information is based on assumptions/model knowledge

  // AERO modules to describe data provided by them
  AERO_SENSORDESC_AERO_TP                         = 0x00100000,  // information from the traffic participant module
  AERO_SENSORDESC_AERO_RM                         = 0x00200000,  // information from the road model module
  AERO_SENSORDESC_AERO_SE                         = 0x00400000,  // information from the static environment module

  AERO_SENSORDESC_MAX                            = AERO_MAX_ENUM  // pseudo enum to ensure constant size
} AERO_t_SensorDescriptor;

//**************************************************************************
//Type: AERO_t_SensorMake
//Description: Sensor make, this describes a brand and model of a sensor. Do NOT chakge these IDs, add new if necessary
//             Bitfield may seem a bit strange here, but e.g. some model parameters could apply to several sensor makes
//Range:       -
//Resolution:  -
//Unit: -
typedef enum AERO_t_SensorMake
{
  AERO_SENSORMAKE_UNKNOWN                        = 0x00000000,  // unknown sensor
  // front looking cameras
  AERO_SENSORMAKE_CONTI_STEREO_CAM_MFC3XX        = 0x00000001,  // conti stereo cam, 3rd gen., ini file string "Conti_SMFC3XX"
  AERO_SENSORMAKE_CONTI_STEREO_CAM_MFC4XX        = 0x00000002,  // conti stereo cam, 4th gen., ini file string "Conti_SMFC4XX"
  AERO_SENSORMAKE_CONTI_MONO_CAM_MFC3XX          = 0x00000004,  // conti mono cam, 3rd gen., ini file string "Conti_MFC3XX"
  AERO_SENSORMAKE_CONTI_MONO_CAM_MFC4XX          = 0x00000008,  // conti mono cam, 4th gen., ini file string "Conti_MFC4XX"
  // long range radar
  AERO_SENSORMAKE_CONTI_LRR_ARS3XX               = 0x00000100, // conti long range radar, 3rd gen., ini file string "Conti_ARS3XX"
  AERO_SENSORMAKE_CONTI_LRR_ARS4XX               = 0x00000200, // conti long range radar, 4th gen., ini file string "Conti_ARS4XX"
  // short range radar
  AERO_SENSORMAKE_CONTI_SRR_SRR2XX               = 0x00010000, // conti short range radar, 2nd gen., ini file string "Conti_SRR2XX"
  AERO_SENSORMAKE_CONTI_SRR_SRR3XX               = 0x00020000, // conti short range radar, 3rd gen., ini file string "Conti_SRR3XX"
  // lidar
  AERO_SENSORMAKE_IBEO_LIDAR_LUX3                = 0x01000000, // ibeo lux lidar, 3rd gen., ini file string "IBEO_Lux3"

  AERO_SENSORMAKE_MAX                            = AERO_MAX_ENUM  // pseudo enum to ensure constant size
} AERO_t_SensorMake;

//**************************************************************************
//Type: AERO_t_SensorFeature
//Description: enum for representing the feature capabilities (outputs) of a physical sensor (model)
//             The various features are not necessarily disjunct (e.g. "traffic participants" and "pedestrians")
//Range:       -
//Resolution:  -
//Unit:        -
typedef enum AERO_t_SensorFeature
{
  AERO_SENSORFEATURE_NONE                        = 0x0000000000,  // no features
  AERO_SENSORFEATURE_POINTCLOUD                  = 0x0000000001,  // sensor can output point cloud (typ. lidar, could also be disparities from stereo cam)
  AERO_SENSORFEATURE_CLUSTERS                    = 0x0000000002,  // sensor can output clusters (typ. radar), if sensor can deliver more types of clusters, there are the fefault ones, for radar near scan
  AERO_SENSORFEATURE_CLUSTERS_FAR                = 0x0000000004,  // sensor can output clusters, far scan (typ. radar)
  AERO_SENSORFEATURE_TRAFPART                    = 0x0000000008,  // sensor can output traffic participants (aka. objects)
  AERO_SENSORFEATURE_PEDESTRIANS                 = 0x0000000010,  // sensor can output pedestrians
  AERO_SENSORFEATURE_VEHICLES                    = 0x0000000020,  // sensor can output vehicles
  AERO_SENSORFEATURE_PEAKS                       = 0x0000000040,  // sensor can output peaks (typ. radar)

  AERO_SENSORFEATURE_MAX                         = AERO_MAX_ENUM  // pseudo enum to ensure constant size
} AERO_t_SensorFeature;

//**************************************************************************
//Type: AERO_t_SensorTechnology
//Description: enum for representing the technology a (logical/feature) sensor uses
//             The various technologies are not necessarily disjunct since e.g. an object from the licam can be based on lidar and camera,
//             therefore a bitfield is used. Space is left between the "main" technologies to leave space for sub-technologies, e.g. 24 or 77 GHz.
//Range:       -
//Resolution:  -
//Unit:        -
typedef enum AERO_t_SensorTechnology
{
  AERO_SENSORTECHNOLOGY_NONE                     = 0x0000000000,  // no tech
  AERO_SENSORTECHNOLOGY_RADAR                    = 0x0000000001,  // radar technology
  AERO_SENSORTECHNOLOGY_RADAR_24GHZ              = 0x0000000002,  // radar 24 GHz
  AERO_SENSORTECHNOLOGY_RADAR_77GHZ              = 0x0000000004,  // radar 77 GHz
  AERO_SENSORTECHNOLOGY_CAMERA                   = 0x0000000100,  // camera technology
  AERO_SENSORTECHNOLOGY_CAMERA_MONO              = 0x0000000200,  // mono camera technology
  AERO_SENSORTECHNOLOGY_CAMERA_STEREO            = 0x0000000400,  // stereo camera technology
  AERO_SENSORTECHNOLOGY_LIDAR                    = 0x0000010000,  // lidar technology

  AERO_SENSORTECHNOLOGY_MAX                      = AERO_MAX_ENUM  // pseudo enum to ensure constant size
} AERO_t_SensorTechnology;

//**************************************************************************
//Type: AERO_t_SensorOperationStatus
//Description: enum for representing the operation status of a sensor;
//             the enum is sorted by severity, from low to high.
//Range:       -
//Resolution:  -
//Unit:        -
typedef enum AERO_t_SensorOperationStatus
{
  AERO_SENSOROPERATIONSTATUS_NA          = 0,    // no operation status available
  AERO_SENSOROPERATIONSTATUS_OK          = 1,    // sensor operation status is ok
  AERO_SENSOROPERATIONSTATUS_REDUCED     = 2,    // sensor performance is reduced
  AERO_SENSOROPERATIONSTATUS_FAILURE     = 3,    // failure occured

  AERO_SENSOROPERATIONSTATUS_MAX       = AERO_MAX_ENUM  // pseudo enum to ensure constant size
} AERO_t_SensorOperationStatus;

//**************************************************************************
//Type: AERO_t_SensorDisturbanceState
//Description: Bitfield for representing the disturbance state of a sensor
//Range:       -
//Resolution:  -
//Unit:        -
typedef enum AERO_t_SensorDisturbanceState
{
  AERO_SENSORDISTURBANCESTATE_NONE               = 0x00000000,    // no failure
  // failures due to blockage
  AERO_SENSORDISTURBANCESTATE_PARTIALLY_BLOCKED  = 0x00000001,    // sensor is partially blocked
  AERO_SENSORDISTURBANCESTATE_BLOCKED            = 0x00000002,    // sensor is blocked
  // miscellaneous failures
  AERO_SENSORDISTURBANCESTATE_DEADJUSTED         = 0x00000100,    // sensor is deadjusted
  AERO_SENSORDISTURBANCESTATE_HW_FAILURE         = 0x00000200,    // sensor has hardware failure
  AERO_SENSORDISTURBANCESTATE_EXT_DISTURBANCE    = 0x00000400,    // sensor is disturbed externally, e.g.
  AERO_SENSORDISTURBANCESTATE_OFF_TEMPERATURE    = 0x00000800,    // sensor is off temperature
  // reduced performance due to environment
  AERO_SENSORDISTURBANCESTATE_RAIN               = 0x00010000,    // sensor performance reduced due to rain
  AERO_SENSORDISTURBANCESTATE_SNOW               = 0x00020000,    // sensor performance reduced due to snow
  AERO_SENSORDISTURBANCESTATE_FOG                = 0x00040000,    // sensor performance reduced due to fog
  AERO_SENSORDISTURBANCESTATE_GLARE              = 0x00080000,    // sensor performance reduced due to glare
  AERO_SENSORDISTURBANCESTATE_DARKNESS           = 0x00100000,    // sensor performance reduced due to darkness
  AERO_SENSORDISTURBANCESTATE_TUNNEL             = 0x00200000,    // sensor performance reduced due to tunnel
  // other failures
  AERO_SENSORDISTURBANCESTATE_OTHER              = 0x10000000,    // other failure that is not further specified

  AERO_SENSORDISTURBANCESTATE_MAX                = AERO_MAX_ENUM   // pseudo enum to ensure constant size
} AERO_t_SensorDisturbanceState;

//**************************************************************************
//Type: AERO_t_SensorStatus
//Description: struct describing the status of a sensor
//Range:       -
//Resolution:  -
//Unit:        -
typedef struct AERO_t_SensorStatus
{
  AERO_t_SignalStatus          e_SignalStatus;         // signal status
  AERO_t_SensorOperationStatus e_OperationStatus;      // operation status
  uint32                      u_DisturbanceState;     // (accumulated) disturbance state
} AERO_t_SensorStatus;

//**************************************************************************
//Type: AERO_t_Clothoid
//Description: clothoid description to be used throughout AERO component to describe lane markings etc. (where applicable);
//             the clothoid is approximated by the following polynomial of degree three
//             y(x) = f_LateralDistance + tan(f_YawAngle) * x + 0.5*f_curvature*x^2 + 1/6*f_curvature_change*x^3,
//             where x and y are given in the SAR coordinate system.
//Range:       -
//Resolution:  -
//Unit:        -
typedef struct AERO_t_Clothoid
{
  AERO_t_SignalStatus    e_SignalStatus;        // validity of data, if this is OK, ALL clothoid parameters must be set
  float32               f_LateralDistance;    // [m] lateral distance from vehicle to clothoid along the longitudinal axis, in AUTOSAR coordinates, i.e. left side is positive
  float32               f_YawAngle;           // [rad] yaw angle from vehicle's x-axis to clothoid (positive anti-clockwise)
  float32               f_curvature;          // [1/m] curvature at vehicle position
  float32               f_curvatureChange;    // [1/m²] change of curvature
} AERO_t_Clothoid;

//**************************************************************************
//Type: AERO_t_PolyChain
//Description: Chain of polygonals (quadrilaterals) description to be used throughout AERO component to describe lane markings etc. (where applicable)
//Range:       -
//Resolution:  -
//Unit:        meters

typedef enum AERO_t_PolyChainFreeSide
{
  AERO_POLYCHAIN_FREESIDE_UNKNOWN  =  0U,  // free side is unknown
  AERO_POLYCHAIN_POSITIVE_NORMAL   =  1U,  // free side is on the side pointed to by the normal vector
  AERO_POLYCHAIN_NEGATIVE_NORMAL   =  2U,  // free side is on the opposite side as pointed to by the normal vector
  AERO_POLYCHAIN_FREESIDE_NA       =  3U,  // free side is not relevant
  AERO_POLYCHAIN_MAX               = AERO_MAX_ENUM  // pseudo enum to ensure constant size
} AERO_t_PolyChainFreeSide;

#define AERO_MAX_NUM_POLYCHAIN_POINTS 256

typedef struct AERO_t_PolyChain
{
  AERO_t_SignalStatus      e_SignalStatus;  // validity of data, if this is OK, ALL polychain parameters must be set
  AERO_t_PolyChainFreeSide e_FreeSide;      // on which side is the free space?
  uint32                  u_NumPoints;     // number of valid control points
  AERO_t_BoundaryPoint     BoundaryPoints[AERO_MAX_NUM_POLYCHAIN_POINTS]; // the boundary points, i.e., the control points plus height data
} AERO_t_PolyChain;

typedef struct AERO_t_PolyChainQuality
{
  AERO_t_SignalStatus      e_SignalStatus;  // validity of data, if this is OK, ALL polychain quality parameters must be set
  uint32                  u_ContribSensors[AERO_MAX_NUM_POLYCHAIN_POINTS];  // contributing sensors, ORing of AERO_t_SensorDescriptor types (the result itself cannot be an enum)
  sint8                   s_Quality[AERO_MAX_NUM_POLYCHAIN_POINTS];         // [%] 0..100
} AERO_t_PolyChainQuality;

#define AERO_MAX_NUM_POLYCHAIN_SMALL_POINTS 20

typedef struct AERO_t_PolyChainSmall
{
  AERO_t_SignalStatus      e_SignalStatus;  // validity of data, if this is OK, ALL polychain parameters must be set
  AERO_t_PolyChainFreeSide e_FreeSide;      // on which side is the free space?
  uint32                  u_NumPoints;     // number of valid control points
  AERO_t_BoundaryPoint     BoundaryPoints[AERO_MAX_NUM_POLYCHAIN_SMALL_POINTS]; // the boundary points, i.e., the control points plus height data
} AERO_t_PolyChainSmall;

typedef struct AERO_t_PolyChainSmallQuality
{
  AERO_t_SignalStatus      e_SignalStatus;  // validity of data, if this is OK, ALL polychain quality parameters must be set
  uint32                  u_ContribSensors[AERO_MAX_NUM_POLYCHAIN_SMALL_POINTS];  // contributing sensors, ORing of AERO_t_SensorDescriptor types (the result itself cannot be an enum)
  sint8                   s_Quality[AERO_MAX_NUM_POLYCHAIN_SMALL_POINTS];         // [%] 0..100
} AERO_t_PolyChainSmallQuality;

//**************************************************************************
//Type: AERO_t_SensorPose
//Description: 3-dimensional sensor pose definition, in SI units and AUTOSAR coordinates, relative to middle front axis
//Range:       -
//Resolution:  -
//Unit:        meters, radians
typedef struct AERO_t_SensorPose
{
  AERO_t_SignalStatus      e_SignalStatus;  // validity of data, if this is OK, ALL parameters must be set from current sensor data,
                                           // otherwise INIT shall indicate that values from an ini file were used
  AERO_t_SensorDescriptor  e_Descriptor;    // enum describing which sensor on the vehicle this information refers to
  AERO_t_SensorMake        e_Make;          // enum describing which brand/model of sensor this information refers to
  AERO_t_Pose3D            Pose;            // [meters, rad] sensor pose
} AERO_t_SensorPose;

//**************************************************************************
//Type: AERO_t_AlgoStatus
//Description: algorithm status to be used throughout AERO component to indicate algorithm validity
//Range:       (0...4)
//Resolution:  -
//Unit:        -
typedef enum AERO_t_AlgoStatus
{
  AERO_ALGO_STATUS_INIT      = 0U,
  AERO_ALGO_STATUS_OK        = 1U,
  AERO_ALGO_STATUS_WARNING   = 2U,
  AERO_ALGO_STATUS_ERROR     = 3U,
  AERO_ALGO_STATUS_EXIT      = 4U,
  AERO_ALGO_STATUS_MAX       = AERO_MAX_ENUM  // pseudo enum to ensure constant size
} AERO_t_AlgoStatus;

#ifdef __cplusplus
}
#endif

#endif // AERO_TYPE_H

