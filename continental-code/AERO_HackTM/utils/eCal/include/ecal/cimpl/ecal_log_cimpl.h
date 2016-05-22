/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL logging c interface
**/

#ifndef ecal_log_cimpl_h_included
#define ecal_log_cimpl_h_included

#include <ecal/ecal_log_level.h>

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/
  /**
   * @brief Sets the log level. 
   *
   * @param level_  The level. 
  **/
  ECAL_API void eCAL_Logging_SetLogLevel(const enum eCAL_Logging_eLogLevel level_);

  /**
   * @brief Get the current log level.
   *
   * @return   The current log level.
  **/
  ECAL_API enum eCAL_Logging_eLogLevel eCAL_Logging_GetLogLevel();

  /**
   * @brief Log a message (with current log level). 
   *
   * @param msg_  The log message string.
  **/
  ECAL_API void eCAL_Logging_Log(const char* const msg_);

  /**
   * @brief Mark the start of the user core process. 
  **/
  ECAL_API void eCAL_Logging_StartCoreTimer();

  /**
   * @brief Mark the stop of the user core process. 
  **/
  ECAL_API void eCAL_Logging_StopCoreTimer();

  /**
   * @brief Set the current measured core time in s (for user implemented measuring). 
  **/
  ECAL_API void eCAL_Logging_SetCoreTime(const double time_);

  /**
   * @brief Returns the current measured core time in s. 
  **/
  ECAL_API double eCAL_Logging_GetCoreTime();
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*ecal_log_cimpl_h_included*/
