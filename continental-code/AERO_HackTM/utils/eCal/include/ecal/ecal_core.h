/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL core function interface
**/

#pragma once

namespace eCAL
{
  /**
   * @brief  Get eCAL version string. 
   *
   * @return  Full eCAL version string. 
  **/
  const char* GetVersionString();

  /**
   * @brief  Get eCAL version date. 
   *
   * @return  Full eCAL version date string. 
  **/
  const char* GetVersionDateString();

  /**
   * @brief  Get eCAL version as separated integer values. 
   *
   * @param [out] major_  The eCAL major version number.
   * @param [out] minor_  The eCAL minor version number.
   * @param [out] patch_  The eCAL patch version number.
   *
   * @return  Zero if succeeded.
  **/
  int GetVersion(int* major_, int* minor_, int* patch_);

  /**
   * @brief Initialize eCAL API.
   *
   * @param argc_       Number of command line arguments. 
   * @param argv_       Array of command line arguments. 
   * @param unit_name_  Defines the name of the eCAL unit. 
   *
   * @return Zero if succeeded, 1 if already initialized, -1 if failed.
  **/
  int Initialize(int argc_, char **argv_, const char *unit_name_);

  /**
   * @brief Finalize eCAL API.
   *
   * @return Zero if succeeded, 1 if still initialized, -1 if failed.
  **/
  int Finalize();

  /**
   * @brief Check eCAL initialize state.
   *
   * @return 1 if eCAL is initialized.
  **/
  int IsInitialized();

  /**
   * @brief  Set/change the unit name of current module.
   *
   * @param unit_name_  Defines the name of the eCAL unit. 
   *
   * @return  Zero if succeeded.
  **/
  int SetUnitName(const char *unit_name_);

  /**
   * @brief Return the eCAL process state.
   *
   * @return  True if eCAL is in proper state. 
  **/
  bool Ok();
}

#ifdef ECAL_USING_DLL

#include <ecal/ecalc.h>

namespace eCAL
{
  inline const char* GetVersionString()
  {
    return(eCAL_GetVersionString());
  }

  inline const char* GetVersionDateString()
  {
    return(eCAL_GetVersionDateString());
  }

  inline int GetVersion(int* major_, int* minor_, int* patch_)
  {
    return(eCAL_GetVersion(major_, minor_, patch_));
  }

  inline int Initialize(int argc_, char **argv_, const char *unit_name_)
  {
    return(eCAL_Initialize(argc_, argv_, unit_name_));
  }

  inline int Finalize()
  {
    return(eCAL_Finalize());
  }

  inline int IsInitialized()
  {
    return(eCAL_IsInitialized());
  }

  inline int SetUnitName(const char *unit_name_)
  {
    return(eCAL_SetUnitName(unit_name_));
  }

  inline bool Ok()
  {
    return(eCAL_Ok() != 0);
  }
}

#endif /* ECAL_USING_DLL */
