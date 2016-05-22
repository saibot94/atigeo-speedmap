/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL utility interface
**/

#pragma once

#include <string>

#ifndef ECAL_USING_DLL

namespace eCAL
{
  namespace Util
  {
    /**
     * @brief Send shutdown event to specified local user process using it's unit name.
     *
     * @param unit_name_   Process unit name. 
    **/
    void ShutdownProcess(const std::string& unit_name_);

    /**
     * @brief Send shutdown event to specified local user process using it's process id.
     *
     * @param process_id_   Process id. 
    **/
    void ShutdownProcess(int process_id_);

    /**
     * @brief Send shutdown event to all local user processes.
    **/
    void ShutdownProcesses();

    /**
     * @brief Send shutdown event to all local core components.
    **/
    void ShutdownCore();

    /**
     * @brief Send shutdown event to local eCAL server.
    **/
    void ShutdownServer();

    /**
     * @brief Enable eCAL message loop back,
     *          that means subscriber will receive messages from
     *          publishers of the same process (default == false).
     *
     * @param state_  Switch on message loop back.. 
    **/
    void EnableLoopback(bool state_);

    /**
     * @brief Gets type name of the specified topic. 
     *
     * @param topic_name_   Topic name. 
     * @param topic_type_   String to store type name. 
     *
     * @return  True if succeeded. 
    **/
    bool GetTypeName(const std::string& topic_name_, std::string& topic_type_);

    /**
     * @brief Gets type name of the specified topic. 
     *
     * @param topic_name_   Topic name. 
     *
     * @return  Topic type name. 
    **/
    std::string GetTypeName(const std::string& topic_name_);

    /**
     * @brief Gets description of the specified topic. 
     *
     * @param topic_name_   Topic name. 
     * @param topic_desc_   String to store description. 
     *
     * @return  True if succeeded. 
    **/
    bool GetDescription(const std::string& topic_name_, std::string& topic_desc_);

    /**
     * @brief Gets description of the specified topic. 
     *
     * @param topic_name_   Topic name. 
     *
     * @return  Topic description. 
    **/
    std::string GetDescription(const std::string& topic_name_);

    /**
     * @brief Open local eCAL Recorder working application.
     *
     * @param args_   Command line arguments. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool RecorderOpen(const char* args_);

    /**
     * @brief Close local eCAL Recorder working application.
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool RecorderClose();

    /**
     * @brief Start local eCAL Recording.
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool RecorderStart();

    /**
     * @brief Open local eCAL CAN Recorder working application.
     *
     * @param args_   Command line arguments. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool CanRecorderOpen(const char* args_);

    /**
     * @brief Close local eCAL CAN Recorder working application.
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool CanRecorderClose();

    /**
     * @brief Start local eCAL CAN Recording.
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool CanRecorderStart();

    /**
    * @brief Open eCALServer application.
    *
    * @return  True if it succeeds, false if it fails. 
    **/
    bool ServerOpen();
  }
}

#else /* ! ECAL_USING_DLL */

#include <ecal/ecalc.h>

namespace eCAL
{
  namespace Util
  {
    inline void ShutdownProcess(const std::string& unit_name_)
    {
      eCAL_Util_ShutdownUnitName(unit_name_.c_str());
    }

    inline void ShutdownProcess(int process_id_)
    {
      eCAL_Util_ShutdownProcessID(process_id_);
    }

    inline void ShutdownProcesses()
    {
      eCAL_Util_ShutdownProcesses();
    }

    inline void ShutdownCore()
    {
      eCAL_Util_ShutdownCore();
    }

    inline void ShutdownServer()
    {
      eCAL_Util_ShutdownServer();
    }

    inline void EnableLoopback(bool state_)
    {
      eCAL_Util_EnableLoopback(state_);
    }

    inline bool GetTypeName(const std::string& topic_name_, std::string& topic_type_)
    {
      void* buf = nullptr;
      std::string type;
      size_t buf_len = eCAL_Util_GetTypeName(topic_name_.c_str(), &buf, ECAL_ALLOCATE_4ME);
      if(buf_len > 0)
      {
        type = std::string(static_cast<char*>(buf), buf_len);
        eCAL_FreeMem(buf);
      }
      topic_type_ = type;
      return(!type.empty());
    }

    inline std::string GetTypeName(const std::string& topic_name_)
    {
      std::string topic_type;
      GetTypeName(topic_name_, topic_type);
      return(topic_type);
    }

    inline bool GetDescription(const std::string& topic_name_, std::string& topic_desc_)
    {
      void* buf = nullptr;
      std::string desc;
      size_t buf_len = eCAL_Util_GetDescription(topic_name_.c_str(), &buf, ECAL_ALLOCATE_4ME);
      if(buf_len > 0)
      {
        desc = std::string(static_cast<char*>(buf), buf_len);
        eCAL_FreeMem(buf);
      }
      topic_desc_ = desc;
      return(!desc.empty());
    }

    inline std::string GetDescription(const std::string& topic_name_)
    {
      std::string topic_desc;
      GetDescription(topic_name_, topic_desc);
      return(topic_desc);
    }

    inline bool RecorderOpen(const char* args_)
    {
      return(eCAL_Util_RecorderOpen(args_) != 0);
    }

    inline bool RecorderClose()
    {
      return(eCAL_Util_RecorderClose() != 0);
    }

    inline bool RecorderStart()
    {
      return(eCAL_Util_RecorderStart() != 0);
    }

    inline bool CanRecorderOpen(const char* args_)
    {
      return(eCAL_Util_CanRecorderOpen(args_) != 0);
    }

    inline bool CanRecorderClose()
    {
      return(eCAL_Util_CanRecorderClose() != 0);
    }

    inline bool CanRecorderStart()
    {
      return(eCAL_Util_CanRecorderStart() != 0);
    }

    inline bool ServerOpen()
    {
      return(eCAL_Util_ServerOpen() != 0);
    }
  }
}

#endif /* ! ECAL_USING_DLL */
