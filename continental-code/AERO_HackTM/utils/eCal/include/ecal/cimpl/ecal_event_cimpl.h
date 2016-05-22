/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL event c interface
**/

#ifndef ecal_event_cimpl_h_included
#define ecal_event_cimpl_h_included

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/
  /**
   * @brief Open a named or unnamed event.
   *
   * @param  event_name_  Event name ("" == unnamed).
   *
   * @return  Handle to opened event or NULL if failed.
  **/
  ECAL_API ECAL_HANDLE eCAL_Event_gOpenEvent(const char* event_name_);

  /**
   * @brief Close an event.
   *
   * @param handle_  Event handle.
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Event_gCloseEvent(const ECAL_HANDLE handle_);

  /**
   * @brief Set an event active.
   *
   * @param handle_  Event handle.
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Event_gSetEvent(const ECAL_HANDLE handle_);

  /**
   * @brief Wait for an event with timeout.
   *
   * @param handle_   Event handle.
   * @param timeout_  Timeout in ms (-1 == infinite).
   *
   * @return  None zero if succeeded.
  **/
  ECAL_API int eCAL_Event_gWaitForEvent(const ECAL_HANDLE handle_, const long timeout_);

  /**
   * @brief Check whether an event is valid or not.
   *
   * @param handle_  Event handle.
   *
   * @return  None zero if event is valid.
  **/
  ECAL_API int eCAL_Event_gEventIsValid(const ECAL_HANDLE handle_);
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*ecal_event_cimpl_h_included*/
