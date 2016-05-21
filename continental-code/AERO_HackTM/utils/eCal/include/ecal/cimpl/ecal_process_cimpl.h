/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL process c interface
**/

#ifndef ecal_process_cimpl_h_included
#define ecal_process_cimpl_h_included

#include <ecal/ecal_process_severity.h>

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/
  /**
   * @brief  Dump configuration to console. 
  **/
  ECAL_API void eCAL_Process_DumpConfig();

  /**
   * @brief  Get current host name. 
   *
   * @param [out] name_      Pointer to store the host name. 
   * @param       name_len_  Length of allocated buffer or ECAL_ALLOCATE_4ME if
   *                         eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   *
   * @return  Buffer length or zero if failed. 
  **/
  ECAL_API int eCAL_Process_GetHostName(void* name_, const int name_len_);

  /**
   * @brief  Get process unit name (defined with eCAL_Initialize). 
   *
   * @param [out] name_      Pointer to store the unit name. 
   * @param       name_len_  Length of allocated buffer or ECAL_ALLOCATE_4ME if
   *                         eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   *
   * @return  Buffer length or zero if failed. 
  **/
  ECAL_API int eCAL_Process_GetUnitName(void* name_, const int name_len_);

  /**
   * @brief  Get current process parameter (defined via eCAL_Initialize(argc_, arg_v). 
   *
   * @param [out] par_      Pointer to store the process parameter. 
   * @param       par_len_  Length of allocated buffer or ECAL_ALLOCATE_4ME if
   *                        eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   * @param       sep_      Separator. 
   *
   * @return  Buffer length or zero if failed. 
  **/
  ECAL_API int eCAL_Process_GetTaskParameter(void* par_, const int par_len_, const char* sep_);

  /**
   * @brief  Get system time. 
   *
   * @return  System time in us. 
  **/
  ECAL_API long long eCAL_Process_GetMicroSeconds();

  /**
   * @brief  Returns time synchronization state. 
   *
   * @return  None zero if process is time synchronized. 
  **/
  ECAL_API int eCAL_Process_IsTimeSynchronized();

  /**
   * @brief  Sleep current thread. 
   *
   * @param  time_ms_  Time to sleep in ms. 
  **/
  ECAL_API void eCAL_Process_SleepMS(const long time_ms_);

  /**
   * @brief  Get current process id. 
   *
   * @return  The process id. 
  **/
  ECAL_API int eCAL_Process_GetProcessID();

  /**
   * @brief  Get current process name. 
   *
   * @param [out] name_      Pointer to store the process name. 
   * @param       name_len_  Length of allocated buffer or ECAL_ALLOCATE_4ME if
   *                         eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   *
   * @return  Process name length or zero if failed. 
  **/
  ECAL_API int eCAL_Process_GetProcessName(void* name_, const int name_len_);

  /**
   * @brief  Get current process parameter as string. 
   *
   * @param [out] par_      Pointer to store the process parameter. 
   * @param       par_len_  Length of allocated buffer or ECAL_ALLOCATE_4ME if
   *                        eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   *
   * @return  Process parameter length or zero if failed. 
  **/
  ECAL_API int eCAL_Process_GetProcessParameter(void* par_, const int par_len_);

  /**
   * @brief  Get CPU usage of current process. 
   *
   * @return  The CPU usage in percent. 
  **/
  ECAL_API float eCAL_Process_GetProcessCpuUsage();
  
  /**
   * @brief  Get memory usage of current process. 
   *
   * @return  The memory usage in bytes. 
  **/
  ECAL_API unsigned long eCAL_Process_GetProcessMemory();

  /**
   * @brief  Get the send clock of the current process. 
   *
   * @return  The message send count per second. 
  **/
  ECAL_API long long eCAL_Process_GetSClock();

  /**
   * @brief  Get the send bytes of the current process. 
   *
   * @return  The message send bytes per second. 
  **/
  ECAL_API long long eCAL_Process_GetSBytes();

  /**
   * @brief  Get the receive clock of the current process. 
   *
   * @return  The message receive count per second. 
  **/
  ECAL_API long long eCAL_Process_GetRClock();

  /**
   * @brief  Get the receive bytes of the current process. 
   *
   * @return  The message receive bytes per second. 
  **/
  ECAL_API long long eCAL_Process_GetRBytes();

  /**
   * @brief  Set process state info. 
   *
   * @param severity_  Severity. 
   * @param info_      Info message. 
   *
  **/
  ECAL_API void eCAL_Process_SetState(const enum eCAL_Process_eSeverity severity_, const char* info_);

  /**
   * @brief  Start specified process (windows only). 
   *
   * @param proc_name_       Process name. 
   * @param proc_args_       Process argument string. 
   * @param working_dir_     Working directory. 
   * @param create_console_  Start process in own console window. 
   * @param hide_            Start as background process. 
   * @param block_           Block until process finished. 
   *
   * @return  Process id or zero if failed. 
  **/
  ECAL_API int eCAL_Process_StartProcess(const char* proc_name_, const char* proc_args_, const char* working_dir_, const int create_console_, const int hide_, const int block_);

  /**
   * @brief  Stop specified process (windows only). 
   *
   * @param proc_name_  Process name. 
   *
   * @return  None zero if successful. 
  **/
  ECAL_API int eCAL_Process_StopProcessName(const char* proc_name_);

  /**
   * @brief  Stop specified process (windows only). 
   *
   * @param proc_id_    Process id. 
   *
   * @return  None zero if successful. 
  **/
  ECAL_API int eCAL_Process_StopProcessID(const int proc_id_);
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*ecal_process_cimpl_h_included*/
