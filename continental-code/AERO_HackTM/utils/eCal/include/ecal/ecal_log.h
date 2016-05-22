/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL logging interface
**/

#pragma once

#include <ecal/ecal_log_level.h>
#include <string>

namespace eCAL
{  
  namespace Logging
  {
    /**
     * @brief Sets the log level. 
     *
     * @param level_  The level. 
    **/
    void SetLogLevel(eCAL_Logging_eLogLevel level_);
  
    /**
     * @brief Get the current log level.
     *
     * @return   The current log level.
    **/
    eCAL_Logging_eLogLevel GetLogLevel();

    /**
     * @brief Log a message (with current log level). 
     *
     * @param msg_  The log message string.
    **/
    void Log(const std::string& msg_);

    /**
     * @brief Log a message. 
     *
     * @param level_  The level. 
     * @param msg_    The log message string.
    **/
    inline void Log(eCAL_Logging_eLogLevel level_, const std::string& msg_)
    {
      SetLogLevel(level_);
      Log(msg_);
    }

    /**
     * @brief Mark the start of the user core process. 
    **/
    void StartCoreTimer();

    /**
     * @brief Mark the stop of the user core process. 
    **/
    void StopCoreTimer();

    /**
     * @brief Set the current measured core time in s (for user implemented measuring). 
    **/
    void SetCoreTime(double time_);

    /**
     * @brief Returns the current measured core time in s. 
    **/
    double GetCoreTime();
  }
}

#ifdef ECAL_USING_DLL

#include <ecal/ecalc.h>

namespace eCAL
{  
  namespace Logging
  {
    inline void SetLogLevel(eCAL_Logging_eLogLevel level_)
    {
      eCAL_Logging_SetLogLevel(level_);
    }

    inline eCAL_Logging_eLogLevel GetLogLevel()
    {
      return(eCAL_Logging_GetLogLevel());
    }

    inline void Log(const std::string& msg_)
    {
      eCAL_Logging_Log(msg_.c_str());
    }

    inline void StartCoreTimer()
    {
      eCAL_Logging_StartCoreTimer();
    }

    inline void StopCoreTimer()
    {
      eCAL_Logging_StopCoreTimer();
    }

    inline void SetCoreTime(double time_)
    {
      eCAL_Logging_SetCoreTime(time_);
    }

    inline double GetCoreTime()
    {
      return(eCAL_Logging_GetCoreTime());
    }
  }
}

#endif /* ECAL_USING_DLL */
