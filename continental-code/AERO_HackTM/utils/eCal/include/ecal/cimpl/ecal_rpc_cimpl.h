/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL rpc c interface
**/

#ifndef ecal_rpc_cimpl_h_included
#define ecal_rpc_cimpl_h_included

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/
  /**
   * @brief Initialize eCAL RPC API.
   *
   * @return Zero if succeeded.
  **/
  ECAL_API int eCAL_RPC_Initialize();

  /**
   * @brief Returns eCAL RPC API state.
   *
   * @return None zero if initialized.
  **/
  ECAL_API int eCAL_RPC_IsInitialized();

  /**
   * @brief Finalize eCAL RPC API.
   *
   * @return Zero if succeeded.
  **/
  ECAL_API int eCAL_RPC_Finalize();

  /**
   * @brief Set server / client time out.
   *
   * @param timeout_  Maximum time to wait for server response (in milliseconds, -1 means infinite).
   *
   * @return Zero if succeeded.
  **/
  ECAL_API int eCAL_RPC_SetTimeout(const int timeout_);

  /**
   * @brief Start process on defined host.
   *
   * @param host_name_       Host name ("" == on all hosts).
   * @param process_name_    Process name.
   * @param process_dir_     Process working directory.
   * @param process_args_    Process arguments. 
   * @param create_console_  Create own console window (Windows only). 
   * @param hide_process_    Start the process hidden (Windows only). 
   *
   * @return  Number of started processes, otherwise zero.
  **/
  ECAL_API int eCAL_RPC_StartProcess(const char* host_name_, const char* process_name_, const char* process_dir_, const char* process_args_, const int create_console_, const int hide_process_);

  /**
   * @brief Stop process via name on defined host.
   *
   * @param host_name_     Host name ("" == on all hosts).
   * @param process_name_  Process name.
   *
   * @return  Number of stopped processes, otherwise zero.
  **/
  ECAL_API int eCAL_RPC_StopProcessName(const char* host_name_, const char* process_name_);

  /**
   * @brief Stop process via id on defined host.
   *
   * @param host_name_   Host name ("" == on all hosts).
   * @param process_id_  Process id.
   *
   * @return  Number of stopped processes, otherwise zero.
  **/
  ECAL_API int eCAL_RPC_StopProcessID(const char* host_name_, const int process_id_);

  /**
   * @brief Open eCAL recorder on defined host.
   *
   * @param host_name_    Host name ("" == on all hosts).
   * @param args_         Recorder arguments.
   *
   * @return  Zero if succeeded.
  **/
  ECAL_API int eCAL_RPC_RecorderOpen(const char* host_name_, const char* args_);

  /**
   * @brief Close eCAL recorder on defined host.
   *
   * @param host_name_  Host name ("" == on all hosts).
   *
   * @return  Zero if succeeded.
  **/
  ECAL_API int eCAL_RPC_RecorderClose(const char* host_name_);

  /**
   * @brief Start eCAL recorder on defined host.
   *
   * @param host_name_  Host name ("" == on all hosts).
   *
   * @return  Zero if succeeded.
  **/
  ECAL_API int eCAL_RPC_RecorderStart(const char* host_name_);

  /**
   * @brief Open eCAL CAN recorder on defined host.
   *
   * @param host_name_  Host name ("" == on all hosts).
   * @param args_       Recorder arguments.
   *
   * @return  Zero if succeeded.
  **/
  ECAL_API int eCAL_RPC_CanRecorderOpen(const char* host_name_, const char* args_);

  /**
   * @brief Close eCAL CAN recorder on defined host.
   *
   * @param host_name_  Host name ("" == on all hosts).
   *
   * @return  Zero if succeeded.
  **/
  ECAL_API int eCAL_RPC_CanRecorderClose(const char* host_name_);

  /**
   * @brief Start eCAL CAN recorder on defined host.
   *
   * @param host_name_  Host name ("" == on all hosts).
   *
   * @return  Zero if succeeded.
  **/
  ECAL_API int eCAL_RPC_CanRecorderStart(const char* host_name_);

  /**
   * @brief Shutdown process via name on defined host.
   *
   * @param host_name_    Host name ("" == on all hosts).
   * @param process_name_ Process name.
   *
   * @return  Number of stopped processes, otherwise zero.
  **/
  ECAL_API int eCAL_RPC_ShutdownProcessName(const char* host_name_, const char* process_name_);

  /**
   * @brief Shutdown process via id on defined host.
   *
   * @param host_name_   Host name ("" == on all hosts).
   * @param process_id_  Process id.
   *
   * @return  Number of stopped processes, otherwise zero.
  **/
  ECAL_API int eCAL_RPC_ShutdownProcessID(const char* host_name_, const int process_id_);

  /**
   * @brief Shutdown eCAL user processes on defined host.
   *
   * @param host_name_  Host name ("" == on all hosts).
   *
   * @return  Number of stopped processes, otherwise zero.
  **/
  ECAL_API int eCAL_RPC_ShutdownProcesses(const char* host_name_);

  /**
   * @brief Shutdown eCAL core on defined host.
   *
   * @param host_name_  Host name ("" == on all hosts).
   *
   * @return  Number of stopped processes, otherwise zero.
  **/
  ECAL_API int eCAL_RPC_ShutdownCore(const char* host_name_);

  /**
   * @brief Shutdown eCAL server on defined host.
   *
   * @param host_name_    Host name ("" == on all hosts).
   *
   * @return  Number of stopped processes, otherwise zero.
  **/
  ECAL_API int eCAL_RPC_ShutdownServer(const char* host_name_);
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*ecal_rpc_cimpl_h_included*/
