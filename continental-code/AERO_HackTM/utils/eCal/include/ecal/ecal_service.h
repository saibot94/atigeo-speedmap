/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL service interface
**/

#pragma once

#include <string>

#include <ecal/ecal_service_info.h>

#ifndef ECAL_USING_DLL

namespace eCAL
{
  /**
   * @brief Service Server wrapper class. 
  **/
  class CServiceServer
  {
  public:
    /**
     * @brief Constructor. 
    **/
    CServiceServer();

    /**
     * @brief Constructor. 
     *
     * @param service_  google::protobuf rpc service. 
    **/
    CServiceServer(void* service_);

    /**
     * @brief Destructor. 
    **/
    virtual ~CServiceServer();

    /**
     * @brief Creates this object. 
     *
     * @param service_  google::protobuf rpc service. 
     *
     * @return  True if successful. 
    **/
    bool Create(void* service_);

    /**
     * @brief Destroys this object. 
     *
     * @return  True if successful. 
    **/
    bool Destroy();

  protected:
    void*  m_service;
    bool   m_created;

  private:
    // this object must not be copied.
    CServiceServer(const CServiceServer&);
    CServiceServer& operator=(const CServiceServer&);
  };


  /**
   * @brief Service client wrapper class. 
  **/
  class CServiceClient
  {
  public:
    /**
     * @brief Constructor. 
    **/
    CServiceClient();

    /**
     * @brief Constructor. 
     *
     * @param service_name_  Service name. 
     * @param host_name_     Host name filter (empty or "*" == all hosts) 
    **/
    CServiceClient(const std::string& service_name_, const std::string& host_name_ = "");

    /**
     * @brief Destructor. 
    **/
    virtual ~CServiceClient();

    /**
     * @brief Creates this object. 
     *
     * @param service_name_  Service name. 
     * @param host_name_     Host name filter (empty or "*" == all hosts) 
     *
     * @return  True if successful. 
    **/
    bool Create(const std::string& service_name_, const std::string& host_name_ = "");

    /**
     * @brief Destroys this object. 
     *
     * @return  True if successful. 
    **/
    bool Destroy();

    /**
     * @brief Change the host name filter for that client instance
     *
     * @param host_name_  Host name filter (empty or "*" == all hosts) 
     *
     * @return  True if successful. 
    **/
    bool SetHostName(const std::string& host_name_);

    /**
     * @brief Call method of this service (none blocking variant with callback). 
     *
     * @param method_name_  Method name. 
     * @param request_      Google::Protobuf encoded request string. 
     *
     * @return  True if successful. 
    **/
    bool Call(const std::string& method_name_, const std::string& request_);

    /**
     * @brief Call method of this service (blocking variant). 
     *
     * @param       method_name_   Method name. 
     * @param       request_       Google::Protobuf encoded request string. 
     * @param [out] response_      Google::Protobuf encoded response string. 
     * @param       timeout_       Response timeout in ms. 
     * @param [out] service_info_  Service info struct for detailed informations. 
     *
     * @return  True if successful. 
    **/
    bool Call(const std::string& method_name_, const std::string& request_, std::string& response_, int timeout_, struct SServiceInfo& service_info_);

    /**
     * @brief Get last error message. 
     *
     * @param error_  Last error message. 
     *
     * @return  True error message available. 
    **/
    bool GetLastError(std::string& error_);

    /**
     * @brief Add server response callback. 
     *
     * @param callback_  Callback function for server response.  
    **/
    void AddResponseCallback(const ResponseCallbackT& callback_);

    /**
     * @brief Remove server response callback. 
    **/
    void RemResponseCallback();

  protected:
    void ResponseCallback(const struct SServiceInfo& service_info_, const std::string& response_);

    ResponseCallbackT  m_callback;
    int                m_session_id;

    std::string        m_service_name;
    std::string        m_service_hname;
    std::string        m_method_name;
    std::string        m_resp_hname;
    std::string        m_resp_error;
    bool               m_created;

  private:
    // this object must not be copied.
    CServiceClient(const CServiceClient&);
    CServiceClient& operator=(const CServiceClient&);
  };
} 

#else /* ! ECAL_USING_DLL */

#include <ecal/ecalc.h>

namespace eCAL
{
  class CServiceServer
  {
  public:
    CServiceServer() :
      m_service(nullptr),
      m_created(false)
    {
    }

    CServiceServer(void* service_) :
      m_service(nullptr),
      m_created(false)
    {
      Create(service_);
    }

    virtual ~CServiceServer()
    {
      Destroy();
    }

    bool Create(void* service_)
    {
      if(m_created) return(false);
      m_service = eCAL_Server_Create(service_);
      if(!m_service) return(false);

      m_created = true;
      return(true);
    }

    bool Destroy()
    {
      if(!m_created) return(false);
      if(m_service) eCAL_Server_Destroy(m_service);

      m_service = nullptr;
      m_created = false;
      return(true);
    }

  protected:
    ECAL_HANDLE  m_service;
    bool         m_created;

  private:
    // this object must not be copied.
    CServiceServer(const CServiceServer&);
    CServiceServer& operator=(const CServiceServer&);
  };


  class CServiceClient
  {
  public:
    CServiceClient() :
      m_service(nullptr),
      m_created(false)
    {
    }

    CServiceClient(const std::string& service_name_, const std::string& host_name_ = "") :
      m_service(nullptr),
      m_created(false)
    {
      Create(service_name_, host_name_);
    }

    virtual ~CServiceClient()
    {
      Destroy();
    }

    bool Create(const std::string& service_name_, const std::string& host_name_ = "")
    {
      if(m_created) return(false);
      m_service = eCAL_Client_Create(service_name_.c_str(), host_name_.c_str());
      if(!m_service) return(false);

      m_service_name  = service_name_;
      m_service_hname = host_name_;
      m_created       = true;
      return(true);
    }

    bool Destroy()
    {
      if(!m_created) return(false);
      if(m_service) eCAL_Client_Destroy(m_service);

      m_service       = nullptr;
      m_service_name  = "";
      m_service_hname = "";
      m_created       = false;
      return(true);
    }

    bool SetHostName(const std::string& host_name_)
    {
      if(!m_service) return(false);
      m_service_hname = host_name_;
      return(eCAL_Client_SetHostName(m_service, host_name_.c_str()) != 0);
    }

    bool Call(const std::string& method_name_, const std::string& request_)
    {
      if(!m_service) return(false);
      return(eCAL_Client_Call(m_service, method_name_.c_str(), request_.c_str(), int(request_.size())) != 0);
    }

    bool Call(const std::string& method_name_, const std::string& request_, std::string& response_, int timeout_, struct SServiceInfo& service_info_)
    {
      if(!m_service) return(false);
      void* response = NULL;
      struct SServiceInfoC service_info;
      int response_len = eCAL_Client_Call_Wait(m_service, method_name_.c_str(), request_.c_str(), static_cast<int>(request_.size()), &response, ECAL_ALLOCATE_4ME, timeout_, &service_info);
      if(response_len > 0)
      {
        GetLastError(m_resp_error);
        service_info_.host_name    = m_service_hname;
        service_info_.service_name = m_service_name;
        service_info_.method_name  = method_name_;
        service_info_.error_msg    = m_resp_error;
        service_info_.id           = service_info.id;
        service_info_.state        = service_info.state;
        response_ = std::string(static_cast<const char*>(response), response_len);
        eCAL_FreeMem(response);
        return(true);
      }
      return(false);
    }

    bool GetLastError(std::string& error_)
    {
      if(!m_service) return(false);
      void* error = NULL;
      int error_len = eCAL_Client_GetLastError(m_service, &error, ECAL_ALLOCATE_4ME);
      if(error_len > 0)
      {
        error_ = std::string(static_cast<const char*>(error), error_len);
        eCAL_FreeMem(error);
        return(true);
      }
      return(false);
    }

    static void ResponseCallback(const struct SServiceInfoC* service_info_, const char* response_, int response_len_, void* par_)
    {
      if(par_ == nullptr) return;
      CServiceClient* client = static_cast<CServiceClient*>(par_);
      SServiceInfo service_info;
      service_info.host_name    = service_info_->host_name;
      service_info.service_name = service_info_->service_name;
      service_info.method_name  = service_info_->method_name;
      service_info.error_msg    = service_info_->error_msg;
      service_info.id           = service_info_->id;
      service_info.state        = service_info_->state;
      client->m_callback(service_info, std::string(response_, response_len_));
    }
    void AddResponseCallback(ResponseCallbackT callback_)
    {
      if(!m_service) return;
      m_callback = callback_;
      return(eCAL_Client_AddResponseCallbackC(m_service, &CServiceClient::ResponseCallback, this));
    }

    void RemResponseCallback()
    {
      if(!m_service) return;
      return(eCAL_Client_RemResponseCallback(m_service));
    }

  protected:
    ECAL_HANDLE        m_service;
    ResponseCallbackT  m_callback;

    std::string        m_service_name;
    std::string        m_service_hname;
    std::string        m_method_name;
    std::string        m_resp_hname;
    std::string        m_resp_error;
    bool               m_created;

  private:
    // this object must not be copied.
    CServiceClient(const CServiceClient&);
    CServiceClient& operator=(const CServiceClient&);
  };
} 

#endif /* ! ECAL_USING_DLL */
