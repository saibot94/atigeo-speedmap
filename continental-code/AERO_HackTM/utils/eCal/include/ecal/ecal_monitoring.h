/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL monitoring interface
**/

#pragma once

#include <string>

namespace eCAL
{
  namespace Monitoring
  {
    /**
     * @brief Initialize eCAL Monitoring API.
     *
     * @return Zero if succeeded.
    **/
    int Initialize();

    /**
     * @brief Finalize eCAL Monitoring API.
     *
     * @return Zero if succeeded.
    **/
    int Finalize();

    /**
     * @brief Returns eCAL Monitoring API state.
     *
     * @return True if initialized.
    **/
    bool IsInitialized();

    /**
     * @brief Set topics filter blacklist regular expression.
     *
     * @param filter_  Topic filter as regular expression. 
     *
     * @return Zero if succeeded.
    **/
    int SetExclFilter(const std::string& filter_);

    /**
     * @brief Set topics filter whitelist regular expression.
     *
     * @param filter_  Topic filter as regular expression. 
     *
     * @return Zero if succeeded.
    **/
    int SetInclFilter(const std::string& filter_);

    /**
     * @brief Switch topics filter using regular expression on/off.
     *
     * @param state_  Filter on / off state. 
     *
     * @return Zero if succeeded.
    **/
    int SetFilterState(bool state_);

    /**
     * @brief Get monitoring protobuf string. 
     *
     * @param [out] mon_  String to store the monitoring information. 
     *
     * @return  Monitoring buffer length or zero if failed. 
    **/
    int GetMonitoring(std::string& mon_);

    /**
     * @brief Get logging protobuf string. 
     *
     * @param [out] log_  String to store the logging information. 
     *
     * @return  Monitoring buffer length or zero if failed. 
    **/
    int GetLogging(std::string& log_);
  }
}

#ifdef ECAL_USING_DLL

#include <ecal/ecalc.h>

namespace eCAL
{
  namespace Monitoring
  {
    inline int Initialize()
    {
      return(eCAL_Monitoring_Initialize());
    }

    inline int Finalize()
    {
      return(eCAL_Monitoring_Finalize());
    }

    inline int IsInitialize()
    {
      return(eCAL_Monitoring_IsInitialized());
    }

    inline int SetExclFilter(const std::string& filter_)
    {
      return(eCAL_Monitoring_SetExclFilter(filter_.c_str()));
    }

    inline int SetInclFilter(const std::string& filter_)
    {
      return(eCAL_Monitoring_SetInclFilter(filter_.c_str()));
    }

    inline int SetFilterState(bool state_)
    {
      return(eCAL_Monitoring_SetFilterState(state_));
    }

    inline int GetMonitoring(std::string& mon_)
    {
      void* buf = nullptr;
      size_t buf_len = eCAL_Monitoring_GetMonitoring(&buf, ECAL_ALLOCATE_4ME);
      if(buf_len > 0)
      {
        mon_ = std::string(static_cast<char*>(buf), buf_len);
        eCAL_FreeMem(buf);
      }
      return(static_cast<int>(mon_.size()));
    }

    inline int GetLogging(std::string& mon_)
    {
      void* buf = nullptr;
      size_t buf_len = eCAL_Monitoring_GetLogging(&buf, ECAL_ALLOCATE_4ME);
      if(buf_len > 0)
      {
        mon_ = std::string(static_cast<char*>(buf), buf_len);
        eCAL_FreeMem(buf);
      }
      return(static_cast<int>(mon_.size()));
    }
  }
}

#endif /* ECAL_USING_DLL */
