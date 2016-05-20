/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL timer interface
**/

#pragma once

#include <functional>

#ifndef ECAL_USING_DLL

namespace eCAL
{
  class CTimerImpl;
  typedef std::function<void(void)> TimerCallbackT;

  /**
   * @brief eCAL timer class.
   *
   * The CTimer class is used to realize simple time triggered callbacks.
  **/
  class CTimer 
  {
  public:
    /**
     * @brief Constructor. 
    **/
    CTimer();

    /**
     * @brief Constructor. 
     *
     * @param timeout_    Timer callback loop time in ms.
     * @param callback_   The callback function. 
     * @param delay_      Timer callback delay for first call in ms.
    **/
    CTimer(int timeout_, TimerCallbackT callback_, int delay_ = 0);

    /**
     * @brief Destructor. 
    **/
    virtual ~CTimer();

    /**
     * @brief Start the timer. 
     *
     * @param timeout_    Timer callback loop time in ms.
     * @param callback_   The callback function. 
     * @param delay_      Timer callback delay for first call in ms.
     *
     * @return  True if timer could be started. 
    **/
    bool Start(int timeout_, TimerCallbackT callback_, int delay_ = 0);

    /**
     * @brief Stop the timer. 
     *
     * @return  True if timer could be stopped. 
    **/
    bool Stop();

  protected:
    // class members
    CTimerImpl*  m_timer;

  private:
    // this object must not be copied.
    CTimer(const CTimer&);
    CTimer& operator=(const CTimer&);
  };
}

#else /* ! ECAL_USING_DLL */

#include <ecal/ecalc.h>

namespace eCAL
{
  class CTimer 
  {
  public:
    CTimer() : m_timer(nullptr) {}

    CTimer(int timeout_, TimerCallbackT callback_, int delay_ = 0) : m_timer(nullptr)
    {
      Start(timeout_, callback_, delay_);
    }

    virtual ~CTimer();

    static void TimerCallback(void* par_)
    {
      if(par_ == nullptr) return;
      CTimer* timer = static_cast<CTimer*>(par_);
      timer->m_callback();
    }
    bool Start(int timeout_, TimerCallbackT callback_, int delay_ = 0)
    {
      if(m_timer) return(false);
      m_timer = eCAL_Timer_Create();
      if(m_timer == NULL) return(false);
      m_callback = callback_;
      return(eCAL_Timer_Start(m_timer, timeout_, &CTimer::TimerCallback, delay_, this) != 0);
    }

    bool Stop()
    {
      if(!m_timer) return(false);
      bool ret = eCAL_Timer_Stop(m_timer) != 0;
      eCAL_Timer_Destroy(m_timer);
      m_timer = nullptr;
      return(ret);
    }

  protected:
    // class members
    ECAL_HANDLE     m_timer;
    TimerCallbackT  m_callback;

  private:
    // this object must not be copied.
    CTimer(const CTimer&);
    CTimer& operator=(const CTimer&);
  };
}

#endif /* ! ECAL_USING_DLL */
