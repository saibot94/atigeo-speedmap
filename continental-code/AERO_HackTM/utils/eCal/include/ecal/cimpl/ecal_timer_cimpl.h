/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL timer c interface
**/

#ifndef ecal_timer_cimpl_h_included
#define ecal_timer_cimpl_h_included

#include <ecal/ecal_callback.h>

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/
  /**
   * @brief Create a timer. 
   *
   * @return  Handle to created timer or NULL if failed.
  **/
  ECAL_API ECAL_HANDLE eCAL_Timer_Create();

  /**
   * @brief Create a timer. 
   *
   * @param handle_  Timer handle. 
   *
   * @return  Handle to created timer or NULL if failed.
  **/
  ECAL_API int eCAL_Timer_Destroy(ECAL_HANDLE handle_);

  /**
   * @brief Start the timer. 
   *
   * @param handle_    Timer handle. 
   * @param timeout_   Timer callback loop time in ms.
   * @param callback_  The callback function. 
   * @param delay_     Timer callback delay for first call in ms.
   * @param par_       User defined context that will be forwarded to the callback function.  
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Timer_Start(ECAL_HANDLE handle_, const int timeout_, TimerCallbackCT callback_, const int delay_, void* par_);

  /**
   * @brief Stop the timer. 
   *
   * @param handle_  Timer handle. 
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Timer_Stop(ECAL_HANDLE handle_);
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*ecal_timer_cimpl_h_included*/
