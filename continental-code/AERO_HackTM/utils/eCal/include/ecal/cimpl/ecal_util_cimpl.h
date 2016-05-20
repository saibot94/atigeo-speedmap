/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL utility c interface
**/

#ifndef ecal_util_cimpl_h_included
#define ecal_util_cimpl_h_included

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/
  /**
   * @brief Send shutdown event to specified local user process using it's unit name.
   *
   * @param unit_name_  Process unit name. 
  **/
  ECAL_API void eCAL_Util_ShutdownUnitName(const char* unit_name_);

  /**
   * @brief Send shutdown event to specified local user process using it's process id.
   *
   * @param process_id_  Process id. 
  **/
  ECAL_API void eCAL_Util_ShutdownProcessID(const int process_id_);

  /**
   * @brief Send shutdown event to all local user processes.
  **/
  ECAL_API void eCAL_Util_ShutdownProcesses();

  /**
   * @brief Send shutdown event to all local core components.
  **/
  ECAL_API void eCAL_Util_ShutdownCore();

  /**
   * @brief Send shutdown event to local eCAL server.
  **/
  ECAL_API void eCAL_Util_ShutdownServer();

  /**
   * @brief Enable eCAL message loop back,
   *          that means subscriber will receive messages from
   *          publishers of the same process (default == false).
   *
   * @param state_  Switch on message loop back.. 
  **/
  ECAL_API void eCAL_Util_EnableLoopback(const int state_);

  /**
   * @brief Gets type name of the specified topic. 
   *
   * @param       topic_name_      Topic name. 
   * @param [out] topic_type_      Pointer to store the type name information. 
   * @param       topic_type_len_  Length of allocated buffer or ECAL_ALLOCATE_4ME if
   *                               eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   *
   * @return  Type name buffer length or zero if failed. 
  **/
  ECAL_API int  eCAL_Util_GetTypeName(const char* topic_name_, void* topic_type_, const int topic_type_len_);

  /**
   * @brief Gets type description of the specified topic. 
   *
   * @param       topic_name_      Topic name. 
   * @param [out] topic_desc_      Pointer to store the type description information. 
   * @param       topic_desc_len_  Length of allocated buffer or ECAL_ALLOCATE_4ME if
   *                               eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   *
   * @return  Type description buffer length or zero if failed. 
  **/
  ECAL_API int  eCAL_Util_GetDescription(const char* topic_name_, void* topic_desc_, const int topic_desc_len_);

  /**
   * @brief Open local eCAL Recorder application.
   *
   * @param args_   Command line arguments. 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int  eCAL_Util_RecorderOpen(const char* args_);

  /**
   * @brief Close local eCAL Recorder application.
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int  eCAL_Util_RecorderClose();

  /**
   * @brief Start local eCAL Recorder application.
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int  eCAL_Util_RecorderStart();

  /**
   * @brief Open local eCAL CAN Recorder application.
   *
   * @param args_   Command line arguments. 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int  eCAL_Util_CanRecorderOpen(const char* args_);

  /**
   * @brief Close local eCAL CAN Recorder application.
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int  eCAL_Util_CanRecorderClose();

  /**
   * @brief Start local eCAL CAN Recorder application.
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int  eCAL_Util_CanRecorderStart();

  /**
   * @brief Open local eCAL server application.
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int  eCAL_Util_ServerOpen();
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*ecal_util_cimpl_h_included*/
