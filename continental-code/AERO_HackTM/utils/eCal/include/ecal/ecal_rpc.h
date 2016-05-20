/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL rpc interface
**/

#pragma once

#include <string>
#include <vector>

namespace eCAL
{
  namespace RPC
  {
    /**
     * @brief Initialize eCAL RPC API.
     *
     * @return Zero if succeeded.
    **/
    int Initialize();

    /**
     * @brief Finalize eCAL RPC API.
     *
     * @return Zero if succeeded.
    **/
    int Finalize();

    /**
     * @brief Returns eCAL RPC API state.
     *
     * @return True if initialized.
    **/
    bool IsInitialized();

    /**
     * @brief Set server / client time out.
     *
     * @param timeout_  Maximum time to wait for server response (in milliseconds, -1 means infinite).
     *
     * @return Zero if succeeded.
    **/
    int SetTimeout(int timeout_);

#ifndef ECAL_USING_DLL
    /**
     * @brief Common server response info struct.
     *
    **/
    struct SServerResponse
    {
      SServerResponse() :
        pid(0),
        success(0)
      {
      }
      std::string  host_name;  // host name
      int          pid;        // pid of started/stopped process
      int          success;    // zero if successful
    };

    /**
     * @brief Start process on defined host.
     *
     * @param host_name_      Host name ("" == on all hosts).
     * @param process_name_   Process name.
     * @param process_dir_    Process working directory.
     * @param process_args_   Process arguments. 
     * @param create_console_ Create own console window (Windows only). 
     * @param hide_process_   Start the process hidden (Windows only). 
     *
     * @return  Vector of process id's if successful, otherwise zero.
     *          (Dll interface returns number of started processes)
    **/
    std::vector<SServerResponse> StartProcess(const std::string& host_name_, const std::string& process_name_, const std::string& process_dir_, const std::string& process_args_, bool create_console_, bool hide_process_);

    /**
     * @brief Stop process on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     * @param process_name_ Process name.
     *
     * @return  Vector of process id's if successful, otherwise zero.
     *          (Dll interface returns number of stopped processes)
    **/
    std::vector<SServerResponse> StopProcess(const std::string& host_name_, const std::string& process_name_);

    /**
     * @brief Stop process on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     * @param process_id_   Process id.
     *
     * @return  Vector of process id's if successful, otherwise zero.
     *          (Dll interface returns number of stopped processes)
    **/

    std::vector<SServerResponse> StopProcess(const std::string& host_name_, int process_id_);
    /**
     * @brief Shutdown process on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     * @param process_name_ Process name.
     *
     * @return  Vector of process id's if successful, otherwise zero.
     *          (Dll interface returns number of closed processes)
    **/
    std::vector<SServerResponse> ShutdownProcess(const std::string& host_name_, const std::string& process_name_);

    /**
     * @brief Shutdown process on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     * @param process_id_   Process id.
     *
     * @return  Vector of process id's if successful, otherwise zero.
     *          (Dll interface returns number of closed processes)
    **/
    std::vector<SServerResponse> ShutdownProcess(const std::string& host_name_, int process_id_);

    /**
     * @brief Shutdown eCAL user processes on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     *
     * @return  Vector of host names on which eCAL user processes were shutdown.
     *          (Dll interface returns number of closed processes)
    **/
    std::vector<SServerResponse> ShutdownProcesses(const std::string& host_name_);

    /**
     * @brief Shutdown eCAL core on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     *
     * @return  Vector of host names on which eCAL core was shutdown.
     *          (Dll interface returns number of closed processes)
    **/
    std::vector<SServerResponse> ShutdownCore(const std::string& host_name_);

    /**
     * @brief Shutdown eCAL server on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     *
     * @return  Vector of host names on which eCAL server was shutdown.
     *          (Dll interface returns number of closed processes)
    **/
    std::vector<SServerResponse> ShutdownServer(const std::string& host_name_);
#endif /* ECAL_USING_DLL */

    /**
     * @brief Open eCAL recorder on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     * @param args_         Recorder arguments.
     *
     * @return  Zero if succeeded.
    **/
    int RecorderOpen(const std::string& host_name_, const std::string& args_);

    /**
     * @brief Close eCAL recorder on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     *
     * @return  Zero if succeeded.
    **/
    int RecorderClose(const std::string& host_name_);

    /**
     * @brief Start eCAL recorder on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     *
     * @return  Zero if succeeded.
    **/
    int RecorderStart(const std::string& host_name_);

    /**
     * @brief Open eCAL CAN recorder on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     * @param args_         Recorder arguments.
     *
     * @return  Zero if succeeded.
    **/
    int CanRecorderOpen(const std::string& host_name_, const std::string& args_);

    /**
     * @brief Close eCAL CAN recorder on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     *
     * @return  Zero if succeeded.
    **/
    int CanRecorderClose(const std::string& host_name_);

    /**
     * @brief Start eCAL CAN recorder on defined host.
     *
     * @param host_name_    Host name ("" == on all hosts).
     *
     * @return  Zero if succeeded.
    **/
    int CanRecorderStart(const std::string& host_name_);
  }
}

#ifdef ECAL_USING_DLL

#include <ecal/ecalc.h>

namespace eCAL
{
  namespace RPC
  {
    inline int Initialize()
    {
      return(eCAL_RPC_Initialize());
    }

    inline int Finalize()
    {
      return(eCAL_RPC_Finalize());
    }

    inline bool IsInitialized()
    {
      return(eCAL_RPC_IsInitialized() != 0);
    }

    inline int SetTimeout(int timeout_)
    {
      return(eCAL_RPC_SetTimeout(timeout_));
    }

    inline int StartProcess(const std::string& host_name_, const std::string& process_name_, const std::string& process_dir_, const std::string& process_args_, bool create_console_, bool hide_process_)
    {
      return(eCAL_RPC_StartProcess(host_name_.c_str(), process_name_.c_str(), process_dir_.c_str(), process_args_.c_str(), create_console_, hide_process_));
    }

    inline int StopProcess(const std::string& host_name_, const std::string& process_name_)
    {
      return(eCAL_RPC_StopProcessName(host_name_.c_str(), process_name_.c_str()));
    }

    inline int StopProcess(const std::string& host_name_, int process_id_)
    {
      return(eCAL_RPC_StopProcessID(host_name_.c_str(), process_id_));
    }

    inline int ShutdownProcess(const std::string& host_name_, const std::string& process_name_)
    {
      return(eCAL_RPC_ShutdownProcessName(host_name_.c_str(), process_name_.c_str()));
    }

    inline int ShutdownProcess(const std::string& host_name_, int process_id_)
    {
      return(eCAL_RPC_ShutdownProcessID(host_name_.c_str(), process_id_));
    }

    inline int ShutdownProcesses(const std::string& host_name_)
    {
      return(eCAL_RPC_ShutdownProcesses(host_name_.c_str()));
    }

    inline int ShutdownCore(const std::string& host_name_)
    {
     return(eCAL_RPC_ShutdownCore(host_name_.c_str()));
    }

    inline int ShutdownServer(const std::string& host_name_)
    {
      return(eCAL_RPC_ShutdownServer(host_name_.c_str()));
    }

    inline int RecorderOpen(const std::string& host_name_, const std::string& args_)
    {
      return(eCAL_RPC_RecorderOpen(host_name_.c_str(), args_.c_str()));
    }

    inline int RecorderClose(const std::string& host_name_)
    {
      return(eCAL_RPC_RecorderClose(host_name_.c_str()));
    }

    inline int RecorderStart(const std::string& host_name_)
    {
      return(eCAL_RPC_RecorderStart(host_name_.c_str()));
    }

    inline int CanRecorderOpen(const std::string& host_name_, const std::string& args_)
    {
      return(eCAL_RPC_CanRecorderOpen(host_name_.c_str(), args_.c_str()));
    }

    inline int CanRecorderClose(const std::string& host_name_)
    {
      return(eCAL_RPC_CanRecorderClose(host_name_.c_str()));
    }

    inline int CanRecorderStart(const std::string& host_name_)
    {
      return(eCAL_RPC_CanRecorderStart(host_name_.c_str()));
    }
  }
}

#endif /* ECAL_USING_DLL */
