/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL service c interface
**/

#ifndef ecal_service_cimpl_h_included
#define ecal_service_cimpl_h_included

#include <ecal/ecal_service_info.h>

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/
  /**
   * @brief Create a server. 
   *
   * @param service_  google::protobuf rpc service. 
   *
   * @return  Handle to created server or NULL if failed.
  **/
  ECAL_API ECAL_HANDLE eCAL_Server_Create(void* service_);

  /**
   * @brief Destroy a server. 
   *
   * @param handle_  Server handle. 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Server_Destroy(ECAL_HANDLE handle_);

  /**
   * @brief Create a client. 
   *
   * @param service_name_  Service name. 
   * @param host_name_     Host name filter (empty or "*" == all hosts) 
   *
   * @return  Handle to created client or NULL if failed.
  **/
  ECAL_API ECAL_HANDLE eCAL_Client_Create(const char* service_name_, const char* host_name_);

  /**
   * @brief Destroy a client. 
   *
   * @param handle_  Client handle. 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Client_Destroy(ECAL_HANDLE handle_);

  /**
   * @brief Change the host name filter for that client instance
   *
   * @param handle_     Client handle. 
   * @param host_name_  Host name filter (empty or "*" == all hosts) 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Client_SetHostName(ECAL_HANDLE handle_, const char* host_name_);

  /**
   * @brief Call method of this service (none blocking variant with callback). 
   *
   * @param handle_       Client handle. 
   * @param method_name_  Method name. 
   * @param request_      Google::Protobuf encoded request string pointer. 
   * @param request_len_  Google::Protobuf encoded request string length. 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Client_Call(ECAL_HANDLE handle_, const char* method_name_, const char* request_, const int request_len_);

  /**
   * @brief Call method of this service (blocking variant with timeout). 
   *
   * @param       handle_        Client handle. 
   * @param       method_name_   Method name. 
   * @param       request_       Google::Protobuf encoded request message. 
   * @param       request_len_   Google::Protobuf encoded request message length. 
   * @param [out] response_      Pointer to the allocated buffer for the response message.
   * @param       response_len_  Response message buffer length or ECAL_ALLOCATE_4ME if
   *                             eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   * @param       timeout_       Response timeout in ms. 
   * @param [out] service_info_  Service info struct with additional infos like call state and
   *                             error message.
   *
   * @return  Size of response buffer if succeeded, otherwise zero.
  **/
  ECAL_API int eCAL_Client_Call_Wait(ECAL_HANDLE handle_, const char* method_name_, const char* request_, const int request_len_, void* response_, const int response_len_, const int timeout_, struct SServiceInfoC* service_info_);

  /**
   * @brief Call method of this service (blocking variant with timeout). 
   *
   * @param       handle_     Client handle. 
   * @param [out] error_      Pointer to the allocated buffer for the error message.
   * @param       error_len_  Error message buffer length or ECAL_ALLOCATE_4ME if
   *                          eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   *
   * @return  Size of error buffer if succeeded, otherwise zero.
  **/
  ECAL_API int eCAL_Client_GetLastError(ECAL_HANDLE handle_, void* error_, const int error_len_);

  /**
   * @brief Add server response callback. 
   *
   * @param handle_    Client handle. 
   * @param callback_  Callback function for server response.  
   * @param par_       User defined context that will be forwarded to the callback function.  
  **/
  ECAL_API void eCAL_Client_AddResponseCallbackC(ECAL_HANDLE handle_, ResponseCallbackCT callback_, void* par_);

  /**
   * @brief Remove server response callback. 
   *
   * @param handle_  Client handle. 
  **/
  ECAL_API void eCAL_Client_RemResponseCallback(ECAL_HANDLE handle_);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*ecal_service_cimpl_h_included*/
