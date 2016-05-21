#ifndef _AERO_VEHICLE_DATA_H_
#define _AERO_VEHICLE_DATA_H_

#define AERO_NUMBER_OF_WHEELS 4

#include "aero_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************************************************/
/*                                   Vehicle Dynamics Section                            */
/******************************************************************************************/
typedef struct AERO_t_VehicleDynamics
{
  AERO_t_SignalHeader  SignalHeader;   // validity of data, if this is OK, ALL parameters must be set, except those which have their own signal status
  AERO_t_float32Status EngRPM;                                                 /* from car m/s, negative is backwards */
  AERO_t_float32Status SpeedDisplayed;                                                   /* shown in Kombi/Tacho m/s */
  AERO_t_float32Status RotSpeedPerWheel[AERO_NUMBER_OF_WHEELS]; /* for each wheel rad/s, negative is backwards, [0]:FL, [1]:FR, [2]:RL, [3]:RR*/
  AERO_t_float32Status LongAcc;                                                                              /* m/s2 */
  AERO_t_float32Status LatAcc;                                                                               /* m/s2 */
  AERO_t_float32Status Yawrate;                                                                             /* rad/s */
  AERO_t_float32Status SteeringWheelAngle;                                                                    /* rad */
  AERO_t_float32Status SteeringWheelAngleSpeed;                                                             /* rad/s */
  AERO_t_float32Status AccPedalPos;                                                                         /* Nm */
  AERO_t_s_Timestamp   TimeSinceLastTick;     /* [s] time since last wheel-tick at one of the 4 wheel (1 tick = 2cm) */
} AERO_t_VehicleDynamics;

/******************************************************************************************/
/*                                   WheelTicks Section                                   */
/******************************************************************************************/
typedef struct AERO_t_WheelTicks
{
  AERO_t_s_Timestamp  Timestamp;  // epoch [us]
  AERO_t_uint16Status TicksFL;   // total cnt, backwards and forwards count upwards
  AERO_t_uint16Status TicksFR;   // total cnt, backwards and forwards count upwards
  AERO_t_uint16Status TicksRL;   // total cnt, backwards and forwards count upwards
  AERO_t_uint16Status TicksRR;   // total cnt, backwards and forwards count upwards
} AERO_t_WheelTicks;

/******************************************************************************************/
/*                                   Powertrain Section                                   */
/******************************************************************************************/

#if 0
  
typedef enum AERO_t_PT_Gear
{
   AERO_VD_GEAR_N      = 0U,   //neutral
   AERO_VD_GEAR_R      = 1U,   //backwards
   AERO_VD_GEAR_P      = 2U,   //parking
   AERO_VD_GEAR_D      = 3U,   //continuous
   AERO_VD_GEAR_D1     = 4U,   //first lever
   AERO_VD_GEAR_D2     = 5U,   //second lever
   AERO_VD_GEAR_D3     = 6U,   //third lever
   AERO_VD_GEAR_D4     = 7U,   //fourth lever
   AERO_VD_GEAR_D5     = 8U,   //fifth lever
   AERO_VD_GEAR_D6     = 9U,   //sixth lever
   AERO_VD_GEAR_D7     = 10U,  //seventh lever
   AERO_VD_GEAR_SNA    = 11U,  //signal not available
   AERO_VD_GEAR_UNDEF  = 12U,   //undefined lever
   AERO_VD_GEAR_MAX    = AERO_MAX_ENUM
} AERO_t_PT_Gear;

typedef struct AERO_t_PowerTrain
{
  AERO_t_s_Timestamp   Timestamp;            /* epoch [us] */
  AERO_t_float32Status EngineSpeed;        /* [U/min] */
  AERO_t_float32Status EngineTorque;       /* [Nm] */
  AERO_t_float32Status GasPedalPos;        /* [%] Gas pedal position sent to the engine; can be initiated by driver or assist */
  AERO_t_float32Status GasPedalPosGrad;    /* [%/s] */
  AERO_t_float32Status FuelConsumption;    /* [l/h] */
  AERO_t_float32Status GasPedalPosDriver;  /* [%] Gas pedal position initiated by driver only; can be different from position sent to the engine */
  AERO_t_PT_Gear       e_Gear;              /* see enums */
  uint32              u_GearStatus;        // 0=fault, 1=ok, 2= timeout, 3=not existing
} AERO_t_PowerTrain;

/******************************************************************************************/
/*                                   Brake Section                                        */
/******************************************************************************************/

typedef enum AERO_t_ABSECS_State
{
   AERO_BR_ABSESC_OFF       = 0U,
   AERO_BR_ABSESC_STANDBY   = 1U,      /* is working fine, but control is not necessary */
   AERO_BR_ABSESC_ACTIVE    = 2U,      /* is in the moment controlling the car */
} AERO_t_ABSECS_State;

typedef struct AERO_t_Brake
{
  AERO_t_s_Timestamp   Timestamp;       // epoch [us]
  AERO_t_float32Status DriverPressure;  // [bar]
  AERO_t_booleanStatus IsBrakeApplied;  // Is braking active
  AERO_t_booleanStatus IsPanicBraking;  // Is the brake pushed very heavy
  AERO_t_ABSECS_State  ABS_Value;       // Status of ABS system
  uint32              u_ABS_Value;     // 0=fault, 1=ok, 2= timeout, 3=not existing
  AERO_t_ABSECS_State  ESC_Value;       // Status of ESC System
  uint32              u_ESC_Value;     // 0=fault, 1=ok, 2= timeout, 3=not existing
  AERO_t_ABSECS_State  TCS_Value;       // Status of Traction Control System see
  uint8               u_TCS_Value;     // 0=fault, 1=ok, 2= timeout, 3=not existing
} AERO_t_Brake;

/******************************************************************************************/
/*                                   Car Switches Section                                 */
/******************************************************************************************/

typedef enum AERO_t_CS_Wiper
{
  AERO_CS_WI_OFF             = 0U,
  AERO_CS_WI_WISCHWASCH      = 1U,
  AERO_CS_WI_SLOW            = 2U,
  AERO_CS_WI_FAST            = 3U,
  AERO_CS_WI_AUTO_WISCHWASCH = 4U,
  AERO_CS_WI_AUTO_SLOW       = 5U,
  AERO_CS_WI_AUTO_FAST       = 6U,
  AERO_CS_WI_AUTO_MAX        = AERO_MAX_ENUM
} AERO_t_CS_Wiper;

typedef enum AERO_t_CS_Blinker
{
  AERO_CS_BL_OFF   = 0U,
  AERO_CS_BL_RIGHT = 1U,
  AERO_CS_BL_LEFT  = 2U,
  AERO_CS_BL_WARN  = 3U,
  AERO_CS_BL_MAX   = AERO_MAX_ENUM
} AERO_t_CS_Blinker;

typedef enum AERO_t_CS_Lamps
{
  AERO_CS_LAMP_OFF       = 0U,
  AERO_CS_LAMP_LOWBEAM   = 1U,
  AERO_CS_LAMP_HIGHBEAM  = 2U,
  AERO_CS_LAMP_FOG_FRONT = 4U,
  AERO_CS_LAMP_FOG_REAR  = 8U,
  AERO_CS_LAMP_DAYLIGHT  = 16U,
  AERO_CS_LAMP_PARKING   = 32U,
  AERO_CS_LAMP_BRAKE     = 64U,
  AERO_CS_LAMP_MAX       = AERO_MAX_ENUM
} AERO_t_CS_Lamps;

typedef enum AERO_t_CS_Doors
{
  AERO_CS_DOOR_FRONT_DRIVER = 1U,
  AERO_CS_DOOR_FRONT_PASS   = 2U,
  AERO_CS_DOOR_REAR_DRIVER  = 4U,
  AERO_CS_DOOR_REAR_PASS    = 8U,
  AERO_CS_DOOR_REAR_TRUNK   = 16U,
  AERO_CS_DOOR_FRONT_HOOD   = 32U,
  AERO_CS_DOOR_OPENER_LEFT  = 64U,
  AERO_CS_DOOR_OPENER_RIGHT = 128U,
  AERO_CS_DOOR_CAP_SENS_FR  = 256U,
  AERO_CS_DOOR_CAP_SENS_RR  = 512U,
  AERO_CS_DOOR_CAP_SENS_RL  = 1024U,
  AERO_CS_DOOR_CAP_SENS_FL  = 2048U,
  AERO_CS_DOOR_MAX          = AERO_MAX_ENUM
} AERO_t_CS_Doors;

typedef enum AERO_t_CS_CruiseControl
{
  AERO_CS_ACC_RESUME_PRESSED   =  1U,
  AERO_CS_ACC_IS_ACTIVE        =  2U,
  AERO_CS_ACC_DRV_OVERRIDE     =  4U,    /* acc active + drv applies gas pedal more than acc needs */
  AERO_CS_ACC_INCREASE_PRESSED =  8U,
  AERO_CS_ACC_DECREASE_PRESSED =  16U,
  AERO_CS_ACC_MAX              = AERO_MAX_ENUM
} AERO_t_CS_CruiseControl;

typedef enum AERO_t_CS_ParkBarke
{
  AERO_CS_PARK_UNKNOWN    = 0U,
  AERO_CS_PARK_OPEN       = 1U,
  AERO_CS_PARK_ENAGED     = 2U,
  AERO_CS_PARK_MAX        = AERO_MAX_ENUM
}AERO_t_CS_ParkBarke;

typedef enum AERO_t_CS_GearLever
{
  AERO_CS_GL_UNKNOWN      = 0U,
  AERO_CS_GL_P            = 1U,
  AERO_CS_GL_R            = 2U,
  AERO_CS_GL_N            = 3U,
  AERO_CS_GL_D            = 4U,  /* normal automatic */
  AERO_CS_GL_MANUAL       = 5U,  /* manual mode: look at powertrainIn:gear */
  AERO_CS_GL_MAX          = AERO_MAX_ENUM
} AERO_t_CS_GearLever;

typedef enum AERO_t_CS_ActuatorStatus
{
  AERO_CS_ACT_STAT_UNKNOWN         = 0U,
  AERO_CS_ACT_STAT_CONTROLABLE     = 1U,    /* actuator controllable */
  AERO_CS_ACT_STAT_NOT_CONTROLABLE = 2U,     /* actuator not controllable */
  AERO_CS_ACT_STAT_MAX             = AERO_MAX_ENUM

} AERO_t_CS_ActuatorStatus;

typedef struct AERO_t_CS_Status
{
  uint8 u_Blinker;              /* 0=fault, 1=ok, 2= timeout, 3=not existing, see ETaccSignalQualityDefs */
  uint8 u_Lamps;
  uint8 u_WiperFront;
  uint8 u_WiperRear;
  uint8 u_CruiseControl;
  uint8 u_Doors;
  uint8 u_HandsOff;
  uint8 u_TemperatureExt;
  uint8 u_OdometerTotal;
  uint8 u_CruiseDriverSpeed;
  uint8 u_CarId;
  uint8 u_ParkBrakeState;
  uint8 u_GearLever;
  uint8 u_StatusSteeringActuator;
  uint8 u_StatusAnalogboosterActuator;
} AERO_t_CS_Status;

typedef struct AERO_t_CS_Signal
{
  uint8   u_Blinker;                      //* see enums */
  uint8   u_Lamps;                        //* bitfield: see enums */
  uint8   u_WiperFront;                   //* see enums */
  uint8   u_WiperRear;                    //* see enums */
  uint8   u_CruiseControl;                //* bitfield tempomat/ACC /* for acc-signals also look at msg "ACCStatus" */
  uint16  u_Doors;                        //* bitfield */
  sint8   s_TemperatureExt;               // [°C] */    
  uint16  u_CarId;                        // see enums */
  uint8   u_ParkBrakeState;               // see enums */
  uint8   u_GearLever;                    // position of gear-lever: see enums */
  uint8   u_StatusSteeringActuator;       // Status of electrical power steering actuator, see enum EActuatorStatus */
  uint8   u_StatusAnalogboosterActuator; // Status of analog booster actuator, see enum EActuatorStatus
} AERO_t_CS_Signal;

typedef struct AERO_t_CarSwitches
{
  AERO_t_s_Timestamp   Timestamp;            //* epoch [us] */
  AERO_t_booleanStatus handsOff;
  AERO_t_float32Status f_OdometerTotal;                //[ km ]
  AERO_t_float32Status f_CruiseDriverSpeed;            // request setSpeed of driver for cruise control m/s */
  //#tb Values are not included yet; if they are needed, uncomment Signal as well as status; use uint32 instead of uint8 in structs due to padding bytes
  // AERO_t_CS_Signal Signal;
  // AERO_t_CS_Status Status;
} AERO_t_CarSwitches;

#endif // if 0

/******************************************************************************************/
/*                                   Vehicle Pose Section                                 */
/******************************************************************************************/

typedef enum AERO_t_MotionStatus
{
  AERO_MOTIONSTATUS_UNKNOWN    = 0U,
  AERO_MOTIONSTATUS_FORWARDS   = 1U,
  AERO_MOTIONSTATUS_BACKWARDS  = 2U,
  AERO_MOTIONSTATUS_STANDSTILL = 3U,
  AERO_MOTIONSTATUS_INVALID    = 4U,
  AERO_MOTIONSTATUS_MAX        = AERO_MAX_ENUM
} AERO_t_MotionStatus;

typedef struct AERO_t_VehiclePose
{
  AERO_t_SignalHeader      SignalHeader;   // validity of data, if this is OK, ALL parameters must be set, except those which have their own signal status
  AERO_t_Pose2D            Pose;           // [m, m, rad] x,y-position of middle of front axle in world coordinates, i.e. 0|0 is start of car/world coordiantes
                                          // angle (yaw) will stay in [-2pi, 2pi]?????
  // to be commented in if set/used: AERO_t_Pose2D            sigma;
  float32                 f_SlipAngleRA;  // [rad] side slip angle for rear-axle, "Schwimmwinkel", (rad)(-30°..30°); if someone misses trackAngle_rad: use formula trackAngle_rad = yaw_rad + slipAngleRA */
  // to be commented in if set/used, maybe used float with status float32                 f_Track_rad;        // [rad] absolute yaw angle, Integral (will get bigger than +-2*PI)
 // MOVE TO DYNAMICS PART??? AERO_t_MotionStatus      e_MotionStatus;     // see enum definition 
} AERO_t_VehiclePose;


/******************************************************************************************/
/*                                   Vehicle Parameter Section                            */
/******************************************************************************************/

//**************************************************************************
//Type: AERO_t_VehicleDynParams
//Description: description of dynamic vehicle parameters, not always known/relevant, so this has a signal status of is own
//Range:       -
//Resolution:  -
//Unit:        -

typedef struct AERO_t_VehicleDynParams
{
  AERO_t_SignalStatus    e_SignalStatus;        // validity of data, if this is OK, ALL parameters must be set
  float32               f_DistCoM2FrontAxle;   // [m] distance from centre of mass to front axle
  float32               f_AvgSteeringRatio;    // [-] average conversion from steering wheel to front wheel movement
  float32               f_MassMomentOfInertia; // [kgm^2] mass moment of inertial around vertical axis
  float32               f_SlantStiffnessFront; // [N/rad] dynamic slant stiffness front
  float32               f_SlantStiffnessRear;  // [N/rad] dynamic slant stiffness rear
  float32               f_DynamicWheelRadius;  // [m] wheel radius @ 60 km/h
} AERO_t_VehicleDynParams;


//**************************************************************************
//Type: AERO_t_VehicleConfig
//Description: description of vehicle parameters, including sensor poses. If a sensor pose for some sensor is valid
//             this implicitly indicates that the vehicle has such a sensor installed, and vice versa
//Range:       -
//Resolution:  -
//Unit:        -

#define AERO_MAX_VEHICLE_INFO_TEXT_LENGTH  32U  // vehicle info string length, NOTE: If "info" shall be used at some point, e.g. car model,
                                               // this shall be done with an enum, not with text

typedef struct AERO_t_VehicleConfig
{
  AERO_t_SignalHeader     SignalHeader;                              // validity of data, if this is OK, ALL parameters must be set, except those which have their own signal status
  char                   u_LicenseNumber[AERO_MAX_VEHICLE_INFO_TEXT_LENGTH];    // license plate number as string, only for information
  float32                f_TreadWidthFront;                         // [m] Tread width is the distance between the center points of the left tire tread and the right tire tread as they come in contact with the road.
  float32                f_TreadWidthRear;                          // [m] 
  float32                f_WheelBase;                               // [m] distance between front and rear axles
  float32                f_Mass;                                    // [kg] mass of vehicle front axle
  float32                f_Length;                                  // [m] length of vehicle
  float32                f_Width;                                   // [m] width of vehicle, exclusive side mirrors
  float32                f_TotalWidth;                              // [m] width of vehicle, inclusive side mirrors
  float32                f_DistFrontAxle2Front;                     // [m] distance from front axle to frontmost point of vehicle
  AERO_t_VehicleDynParams DynamicParams;                             // additional parameters relevant for dynamic behaviour of vehicle
  AERO_t_SensorPose       SensorPoses[AERO_MAX_NUM_MOUNTED_SENSORS];  // poses of mounted sensors
} AERO_t_VehicleConfig;

#ifdef __cplusplus
}
#endif

#endif // _AERO_VEHICLE_DATA_H_
