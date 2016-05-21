/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL logging severities
**/

#pragma once

/**
  * @brief Values that represent different log level to filter on monitoring. 
**/
enum eCAL_Logging_eLogLevel
{
  log_level_none    =   0,
  log_level_all     = 255,
  log_level_info    =   1,
  log_level_warning =   2,
  log_level_error   =   4,
  log_level_fatal   =   8,
  log_level_debug1  =  16,
  log_level_debug2  =  32,
  log_level_debug3  =  64,
  log_level_debug4  = 128,
};
