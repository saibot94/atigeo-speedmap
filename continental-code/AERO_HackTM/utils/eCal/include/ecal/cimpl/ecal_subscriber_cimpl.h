/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL subscriber c interface
**/

#ifndef ecal_subscriber_cimpl_h_included
#define ecal_subscriber_cimpl_h_included

#include <ecal/ecal_callback.h>

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/
  /**
   * @brief Create a subscriber. 
   *
   * @param topic_name_  Unique topic name. 
   * @param topic_type_  Topic type name. 
   *
   * @return  Handle to created subscriber or NULL if failed.
  **/
  ECAL_API ECAL_HANDLE eCAL_Sub_Create(const char* topic_name_, const char* topic_type_);

  /**
   * @brief Destroy a subscriber. 
   *
   * @param handle_  Subscriber handle. 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Sub_Destroy(ECAL_HANDLE handle_);

  /**
   * @brief Receive a message from the publisher. 
   *
   * @param       handle_       Subscriber handle. 
   * @param [out] buf_          Buffer to store the received message content.
   * @param       buf_len_      Length of the receive buffer or ECAL_ALLOCATE_4ME if
   *                            eCAL should allocate the buffer for you (see eCAL_FreeMem).
   * @param [out] time_         Time from publisher in us.
   * @param       rcv_timeout_  Maximum time before receive operation returns (in milliseconds, -1 means infinite).
   *
   * @return  Length of received buffer. 
  **/
  ECAL_API int eCAL_Sub_Receive(ECAL_HANDLE handle_, void* buf_, const int buf_len_, long long* time_, const int rcv_timeout_);

  /**
   * @brief Add callback function for incoming receives. 
   *
   * @param handle_    Subscriber handle. 
   * @param callback_  The callback function to add.
   * @param par_       User defined context that will be forwarded to the callback function.  
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Sub_AddReceiveCallbackC(ECAL_HANDLE handle_, ReceiveCallbackCT callback_, void* par_);

  /**
   * @brief Remove callback function for incoming receives. 
   *
   * @param  handle_  Subscriber handle. 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Sub_RemReceiveCallback(ECAL_HANDLE handle_);

  /**
   * @brief Gets description of the connected topic. 
   *
   * @param       handle_   Subscriber handle. 
   * @param [out] buf_      Pointer to store the subscriber description string. 
   * @param       buf_len_  Length of allocated buffer or ECAL_ALLOCATE_4ME if
   *                        eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   *
   * @return  Description buffer length or zero if failed. 
  **/
  ECAL_API int eCAL_Sub_GetDescription(ECAL_HANDLE handle_, void* buf_, int buf_len_);

  /**
   * @brief Dump the whole class state into a string buffer. 
   *
   * @param handle_         Publisher handle. 
   * @param [out] buf_      Pointer to store the monitoring information. 
   * @param       buf_len_  Length of allocated buffer or ECAL_ALLOCATE_4ME if
   *                        eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   *
   * @return  Dump buffer length or zero if failed. 
  **/
  ECAL_API int eCAL_Sub_Dump(ECAL_HANDLE handle_, void* buf_, const int buf_len_);
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*ecal_subscriber_cimpl_h_included*/
