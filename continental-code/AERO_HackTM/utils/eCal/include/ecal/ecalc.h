/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL main c header file
**/

#ifndef ecalc_h_included
#define ecalc_h_included

#ifdef _MSC_VER
  #ifdef eCAL_EXPORTS
    #define ECAL_API __declspec(dllexport)
  #else
    #ifdef ECAL_USING_DLL
      #define ECAL_API __declspec(dllimport)
    #else
      #define ECAL_API
    #endif
  #endif
#else
  #define ECAL_API
  #include <string.h>
#endif

// global defines
#define ECAL_ALLOCATE_4ME 0

// global types
typedef void* ECAL_HANDLE;

// all ecal c includes
#include <ecal/ecal_os.h>
#include <ecal/ecal_defs.h>
#include <ecal/cimpl/ecal_core_cimpl.h>
#include <ecal/cimpl/ecal_event_cimpl.h>
#include <ecal/cimpl/ecal_log_cimpl.h>
#include <ecal/cimpl/ecal_monitoring_cimpl.h>
#include <ecal/cimpl/ecal_process_cimpl.h>
#include <ecal/cimpl/ecal_publisher_cimpl.h>
#include <ecal/cimpl/ecal_rpc_cimpl.h>
#include <ecal/cimpl/ecal_service_cimpl.h>
#include <ecal/cimpl/ecal_subscriber_cimpl.h>
#include <ecal/cimpl/ecal_timer_cimpl.h>
#include <ecal/cimpl/ecal_util_cimpl.h>

#endif /*ecalc_h_included*/
