/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL core function c interface
**/

#ifndef ecal_core_cimpl_h_included
#define ecal_core_cimpl_h_included

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/
  /**
   * @brief  Get eCAL version string. 
   *
   * @return  Full eCAL version string. 
  **/
  ECAL_API const char* eCAL_GetVersionString();

  /**
   * @brief  Get eCAL version date. 
   *
   * @return  Full eCAL version date string. 
  **/
  ECAL_API const char* eCAL_GetVersionDateString();

  /**
   * @brief  Get eCAL version as separated integer values. 
   *
   * @param [out] major_  The eCAL major version number.
   * @param [out] minor_  The eCAL minor version number.
   * @param [out] patch_  The eCAL patch version number.
   *
   * @return  Zero if succeeded.
  **/
  ECAL_API int eCAL_GetVersion(int* major_, int* minor_, int* patch_);

  /**
   * @brief Initialize eCAL API.
   *
   * @param argc_       Number of command line arguments. 
   * @param argv_       Array of command line arguments. 
   * @param unit_name_  Defines the name of the eCAL unit. 
   *
   * @return Zero if succeeded, 1 if already initialized, -1 if failed.
  **/
  ECAL_API int eCAL_Initialize(int argc_, char **argv_, const char *unit_name_);

  /**
   * @brief  Set/change the unit name of current module.
   *
   * @param unit_name_  Defines the name of the eCAL unit. 
   *
   * @return  Zero if succeeded.
  **/
  ECAL_API int eCAL_SetUnitName(const char *unit_name_);

  /**
   * @brief Finalize eCAL API.
   *
   * @return Zero if succeeded, 1 if still initialized, -1 if failed.
  **/
  ECAL_API int eCAL_Finalize();

  /**
   * @brief Check eCAL initialize state.
   *
   * @return None zero if eCAL is initialized.
  **/
  ECAL_API int eCAL_IsInitialized();

  /**
   * @brief Return the eCAL process state.
   *
   * @return  None zero if eCAL is in proper state. 
  **/
  ECAL_API int eCAL_Ok();

  /**
   * @brief  Free an eCAL memory block allocated by functions like
   *         eCAL_Monitoring_GetMonitoring, eCAL_Monitoring_GetLogging, 
   *         eCAL_Sub_Receive ... that use 'ECAL_ALLOCATE_4ME' as 
   *         buffer length parameter and let eCAL allocate 
   *         the memory internally.
   *
   **/
  /**
   * @code
   *            // let eCAL allocate memory for the subscriber buffer and return the pointer to 'buf'
   *            long long time     = 0;
   *            int       time_out = 100;   // ms
   *            void*     buf      = NULL;
   *            int       buf_len  = eCAL_Sub_Receive(subscriber_handle, &buf, ECAL_ALLOCATE_4ME, &time, timeout);
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
  ECAL_API void eCAL_FreeMem(void* mem_);
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*ecal_core_cimpl_h_included*/
