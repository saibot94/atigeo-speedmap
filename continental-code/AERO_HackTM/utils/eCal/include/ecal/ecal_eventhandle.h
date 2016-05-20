/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL event handle
**/

#pragma once

#include <string>
#include <vector>

namespace eCAL
{
  struct SEventHandle
  {
    SEventHandle() : name(""), handle(nullptr)
    {
    };
    std::string name;
    void*       handle;

    bool operator==(const SEventHandle& rhs)
    {
      return(rhs.name == name && rhs.handle == handle);
    }
  };
  typedef SEventHandle              EventHandleT;
  typedef std::vector<EventHandleT> EventHandleVecT;
}
