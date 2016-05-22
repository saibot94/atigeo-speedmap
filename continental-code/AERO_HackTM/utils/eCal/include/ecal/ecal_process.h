/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL process interface
**/

#pragma once

#include <string>

#include <ecal/ecal_process_severity.h>

namespace eCAL
{
  namespace Process
  {
    /**
     * @brief  Dump configuration to console. 
    **/
    void DumpConfig();

    /**
     * @brief  Get current host name. 
     *
     * @return  Host name or empty string if failed. 
    **/
    std::string GetHostName();

    /**
     * @brief  Get current unit name (defined via eCAL::Initialize). 
     *
     * @return  Unit name or empty string if failed. 
    **/
    std::string GetUnitName();

    /**
     * @brief  Get current process parameter (defined via eCAL::Initialize(argc_, arg_v). 
     *
     * @param sep_  Separator. 
     *
     * @return  Task parameter separated by 'sep_' or zero string if failed. 
    **/
    std::string GetTaskParameter(const char* sep_);

    /**
     * @brief  Get system time. 
     *
     * @return  System time in us. 
    **/
    long long GetMicroSeconds();

    /**
     * @brief  Returns time synchronization state. 
     *
     * @return  True if process is time synchronized. 
    **/
    bool IsTimeSynchronized();

    /**
     * @brief  Sleep current thread. 
     *
     * @param  time_ms_  Time to sleep in ms. 
    **/
    void SleepMS(long time_ms_);

    /**
     * @brief  Get current process id. 
     *
     * @return  The process id. 
    **/
    int GetProcessID();

    /**
     * @brief  Get current process name. 
     *
     * @return  Process name length or zero if failed. 
    **/
    std::string GetProcessName();

    /**
     * @brief  Get current process parameter. 
     *
     * @return  Process parameter or empty string if failed. 
    **/
    std::string GetProcessParameter();

    /**
     * @brief  Get CPU usage of current process. 
     *
     * @return  The CPU usage in percent. 
    **/
    float GetProcessCpuUsage();

    /**
     * @brief  Get memory usage of current process. 
     *
     * @return  The memory usage in bytes. 
    **/
    unsigned long GetProcessMemory();

    /**
     * @brief  Get the send clock of the current process. 
     *
     * @return  The message send count per second. 
    **/
    long long GetSClock();

    /**
     * @brief  Get the send bytes of the current process. 
     *
     * @return  The message send bytes per second. 
    **/
    long long GetSBytes();

    /**
     * @brief  Get the receive clock of the current process. 
     *
     * @return  The message receive count per second. 
    **/
    long long GetRClock();

    /**
     * @brief  Get the receive bytes of the current process. 
     *
     * @return  The message receive bytes per second. 
    **/
    long long GetRBytes();

    /**
     * @brief  Set process state info. 
     *
     * @param severity_  Severity. 
     * @param info_      Info message. 
     *
    **/
    void SetState(eCAL_Process_eSeverity severity_, const char* info_);

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
    int StartProcess(const char* proc_name_, const char* proc_args_, const char* working_dir_, bool create_console_, bool hide_, bool block_);

    /**
     * @brief  Stop specified process (windows only). 
     *
     * @param proc_name_  Process name. 
     *
     * @return  True if successful. 
    **/
    bool StopProcess(const char* proc_name_);

    /**
     * @brief  Stop specified process (windows only). 
     *
     * @param proc_id_    Process id. 
     *
     * @return  True if successful. 
    **/
    bool StopProcess(int proc_id_);
  }
}

#ifdef ECAL_USING_DLL

#include <ecal/ecalc.h>

namespace eCAL
{
  namespace Process
  {
    inline void DumpConfig()
    {
      eCAL_Process_DumpConfig();
    }

    inline std::string GetHostName()
    {
      void* buf = nullptr;
      std::string name;
      size_t buf_len = eCAL_Process_GetHostName(&buf, ECAL_ALLOCATE_4ME);
      if(buf_len > 0)
      {
        name = std::string(static_cast<char*>(buf), buf_len);
        eCAL_FreeMem(buf);
      }
      return(name);
    }

    inline std::string GetUnitName()
    {
      void* buf = nullptr;
      std::string name;
      size_t buf_len = eCAL_Process_GetUnitName(&buf, ECAL_ALLOCATE_4ME);
      if(buf_len > 0)
      {
        name = std::string(static_cast<char*>(buf), buf_len);
        eCAL_FreeMem(buf);
      }
      return(name);
    }

    inline std::string GetTaskParameter(const char* sep_)
    {
      void* buf = nullptr;
      std::string par;
      size_t buf_len = eCAL_Process_GetTaskParameter(&buf, ECAL_ALLOCATE_4ME, sep_);
      if(buf_len > 0)
      {
        par = std::string(static_cast<char*>(buf), buf_len);
        eCAL_FreeMem(buf);
      }
      return(par);
    }

    inline long long GetMicroSeconds()
    {
      return(eCAL_Process_GetMicroSeconds());
    }

    inline bool IsTimeSynchronized()
    {
      return(eCAL_Process_IsTimeSynchronized() != 0);
    }

    inline void SleepMS(long time_ms_)
    {
      eCAL_Process_SleepMS(time_ms_);
    }

    inline int GetProcessID()
    {
      return(eCAL_Process_GetProcessID());
    }

    inline std::string GetProcessName()
    {
      void* buf = nullptr;
      std::string name;
      size_t buf_len = eCAL_Process_GetProcessName(&buf, ECAL_ALLOCATE_4ME);
      if(buf_len > 0)
      {
        name = std::string(static_cast<char*>(buf), buf_len);
        eCAL_FreeMem(buf);
      }
      return(name);
    }

    inline std::string GetProcessParameter()
    {
      void* buf = nullptr;
      std::string par;
      size_t buf_len = eCAL_Process_GetProcessParameter(&buf, ECAL_ALLOCATE_4ME);
      if(buf_len > 0)
      {
        par = std::string(static_cast<char*>(buf), buf_len);
        eCAL_FreeMem(buf);
      }
      return(par);
    }

    inline float GetProcessCpuUsage()
    {
      return(eCAL_Process_GetProcessCpuUsage());
    }

    inline unsigned long GetProcessMemory()
    {
      return(eCAL_Process_GetProcessMemory());
    }

    inline long long GetSClock()
    {
      return(eCAL_Process_GetSClock());
    }

    inline long long GetSBytes()
    {
      return(eCAL_Process_GetSBytes());
    }

    inline long long GetRClock()
    {
      return(eCAL_Process_GetRClock());
    }

    inline long long GetRBytes()
    {
      return(eCAL_Process_GetRBytes());
    }

    inline void SetState(eCAL_Process_eSeverity severity_, const char* info_)
    {
      eCAL_Process_SetState(severity_, info_);
    }

    inline int StartProcess(const char* proc_name_, const char* proc_args_, const char* working_dir_, bool create_console_, bool hide_, bool block_)
    {
      return(eCAL_Process_StartProcess(proc_name_, proc_args_, working_dir_, create_console_, hide_, block_));
    }

    inline bool StopProcess(const char* proc_name_)
    {
      return(eCAL_Process_StopProcessName(proc_name_) != 0);
    }

    inline bool StopProcess(int proc_id_)
    {
      return(eCAL_Process_StopProcessID(proc_id_) != 0);
    }
  }
}

#endif /* ECAL_USING_DLL */
