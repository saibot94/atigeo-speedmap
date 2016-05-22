/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL event interface
**/

#pragma once

#include <ecal/ecal_eventhandle.h>
#include <string>

namespace eCAL
{
  /**
   * @brief Open a named or unnamed event.
   *
   * @param [out] event_       Returned event struct.
   * @param       event_name_  Event name ("" == unnamed).
   *
   * @return  True if succeeded.
  **/
  bool gOpenEvent(eCAL::EventHandleT* event_, const std::string& event_name_ = "");

  /**
   * @brief Close an event.
   *
   * @param event_  Event struct.
   *
   * @return  True if succeeded.
  **/
  bool gCloseEvent(const EventHandleT& event_);

  /**
   * @brief Set an event active.
   *
   * @param event_  Event struct.
   *
   * @return  True if succeeded.
  **/
  bool gSetEvent(const EventHandleT& event_);

  /**
   * @brief Wait for an event with timeout.
   *
   * @param event_    Event struct.
   * @param timeout_  Timeout in ms (-1 == infinite).
   *
   * @return  True if succeeded.
  **/
  bool gWaitForEvent(const EventHandleT& event_, long timeout_);

  /**
   * @brief Check whether an event is valid or not.
   *
   * @return  True if event is valid.
  **/
  bool gEventIsValid(const EventHandleT& event_);
}

#ifdef ECAL_USING_DLL

#include <ecal/ecalc.h>

namespace eCAL
{
  inline bool gOpenEvent(eCAL::EventHandleT* event_, const std::string& event_name_)
  {
    if(event_ == nullptr) return(false);
    ECAL_HANDLE event = eCAL_Event_gOpenEvent(event_name_.c_str());
    if(event == nullptr) return(false);
    event_->handle = event;
    event_->name   = event_name_;
    return(true);
  }

  inline bool gCloseEvent(const EventHandleT& event_)
  {
    return(eCAL_Event_gCloseEvent(event_.handle) != 0);
  }

  inline bool gSetEvent(const EventHandleT& event_)
  {
    return(eCAL_Event_gSetEvent(event_.handle) != 0);
  }

  inline bool gWaitForEvent(const EventHandleT& event_, long timeout_)
  {
    return(eCAL_Event_gWaitForEvent(event_.handle, timeout_) != 0);
  }

  inline bool gEventIsValid(const EventHandleT& event_)
  {
    return(eCAL_Event_gEventIsValid(event_.handle) != 0);
  }
}

#endif /* ECAL_USING_DLL */
