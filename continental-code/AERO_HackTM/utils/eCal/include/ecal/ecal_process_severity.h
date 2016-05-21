/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL process severity
**/

#pragma once

/**
  * @brief  Process severity 
**/
enum eCAL_Process_eSeverity
{
  proc_sev_unknown   =  0,  /*!<  0 == condition unknown     */
  proc_sev_healthy   =  1,  /*!<  1 == process healthy       */
  proc_sev_warning   =  2,  /*!<  2 == process warning level */
  proc_sev_critical  =  3,  /*!<  3 == process critical      */
  proc_sev_failed    =  4,  /*!<  4 == process failed        */
};
