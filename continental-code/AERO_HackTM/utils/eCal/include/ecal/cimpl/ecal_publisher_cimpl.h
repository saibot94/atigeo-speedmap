/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL publisher c interface
**/

#ifndef ecal_publisher_cimpl_h_included
#define ecal_publisher_cimpl_h_included

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/
  /**
   * @brief Create a publisher. 
   *
   * @param topic_name_      Unique topic name. 
   * @param topic_type_      Topic type name. 
   * @param topic_desc_      Topic type description. 
   * @param topic_desc_len_  Topic type description length. 
   *
   * @return  Handle to created publisher or NULL if failed.
  **/
  ECAL_API ECAL_HANDLE eCAL_Pub_Create(const char* topic_name_, const char* topic_type_, const char* topic_desc_, const int topic_desc_len_);

  /**
   * @brief Destroy a publisher. 
   *
   * @param handle_  Publisher handle. 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Pub_Destroy(ECAL_HANDLE handle_);

  /**
   * @brief Setup topic type description. 
   *
   * @param handle_          Publisher handle. 
   * @param topic_desc_      Topic type description. 
   * @param topic_desc_len_  Topic type description length. 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Pub_SetDescription(ECAL_HANDLE handle_, const char* topic_desc_, const int topic_desc_len_);

  /**
   * @brief Setup the publisher compression. 
   *
   * @param handle_  Publisher handle. 
   * @param mode_    Compression mode 0 = off, 1 = on, default = 0). 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Pub_SetCompression(ECAL_HANDLE handle_, const int mode_);

  /**
   * @brief Set publisher send mode via udp. 
   *
   * @param handle_  Publisher handle. 
   * @param mode_    Send mode 0 = off, 1 = on, 2 = auto, default = 2). 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Pub_SetUseUdp(ECAL_HANDLE handle_, const int mode_);

  /**
   * @brief Set publisher send mode via shared memory. 
   *
   * @param handle_  Publisher handle. 
   * @param mode_    Send mode 0 = off, 1 = on, 2 = auto, default = 2). 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Pub_SetUseShm(ECAL_HANDLE handle_, const int mode_);

  /**
   * @brief Query if the publisher is subscribed. 
   *
   * @param handle_  Publisher handle. 
   *
   * @return  None zero if subscribed. 
  **/
  ECAL_API int eCAL_Pub_IsSubscribed(ECAL_HANDLE handle_);

  /**
   * @brief Send a message to all subscribers. 
   *
   * @param handle_   Publisher handle. 
   * @param buf_      Buffer that contains content to send. 
   * @param buf_len_  Send buffer length. 
   * @param time_     Send time (-1 = use eCAL system time in us, default = -1).
   *
   * @return  Number of bytes sent. 
  **/
  ECAL_API int eCAL_Pub_Send(ECAL_HANDLE handle_, const void* const buf_, const int buf_len_, const long long time_);

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
  ECAL_API int eCAL_Pub_Dump(ECAL_HANDLE handle_, void* buf_, const int buf_len_);
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*ecal_publisher_cimpl_h_included*/
