/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL monitoring c interface
**/

#ifndef ecal_monitoring_cimpl_h_included
#define ecal_monitoring_cimpl_h_included

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/
  /**
   * @brief Initialize eCAL Monitoring API.
   *
   * @return Zero if succeeded.
  **/
  ECAL_API int eCAL_Monitoring_Initialize();

  /**
   * @brief Returns eCAL Monitoring API state.
   *
   * @return None zero if initialized.
  **/
  ECAL_API int eCAL_Monitoring_IsInitialized();

  /**
   * @brief Finalize eCAL Monitoring API.
   *
   * @return Zero if succeeded.
  **/
  ECAL_API int eCAL_Monitoring_Finalize();

  /**
   * @brief Set topics filter blacklist regular expression.
   *
   * @param filter_  Topic filter as regular expression. 
   *
   * @return Zero if succeeded.
  **/
  ECAL_API int eCAL_Monitoring_SetExclFilter(const char* filter_);

  /**
   * @brief Set topics filter whitelist regular expression.
   *
   * @param filter_  Topic filter as regular expression. 
   *
   * @return Zero if succeeded.
  **/
  ECAL_API int eCAL_Monitoring_SetInclFilter(const char* filter_);

  /**
   * @brief Switch topics filter using regular expression on/off.
   *
   * @param state_  Filter on / off state. 
   *
   * @return Zero if succeeded.
  **/
  ECAL_API int eCAL_Monitoring_SetFilterState(int const state_);

  /**
   * @brief Get monitoring protobuf string. 
   *
   * @param [out] buf_      Pointer to store the monitoring information. 
   * @param       buf_len_  Length of allocated buffer or ECAL_ALLOCATE_4ME if
   *                        eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   *
   * @return  Monitoring buffer length or zero if failed. 
  **/
  /**
   * @code
   *            // let eCAL allocate memory for the monitoring buffer and return the pointer to 'buf'
   *            void*     buf      = NULL;
   *            int       buf_len  = eCAL_Monitoring_GetLogging(subscriber_handle, &buf, ECAL_ALLOCATE_4ME);
   *            if(buf_len > 0)
   *            {
   *              ...
   *              // PROCESS THE BUFFER CONTENT HERE
   *              ...
   *              // finally free the allocated memory
   *              eCAL_FreeMem(buf);
   *            }
   * @endcode
  **/
  ECAL_API int eCAL_Monitoring_GetMonitoring(void* buf_, const int buf_len_);

  /**
   * @brief Get logging string.
   *
   * @param [out] buf_      Pointer to store the logging information. 
   * @param       buf_len_  Length of allocated buffer or ECAL_ALLOCATE_4ME if
   *                        eCAL should allocate the buffer for you (see eCAL_FreeMem). 
   *
   * @return  Logging buffer length or zero if failed. 
  **/
  ECAL_API int eCAL_Monitoring_GetLogging(void* buf_, const int buf_len_);
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*ecal_monitoring_cimpl_h_included*/
