/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL service info
**/

#pragma once

enum eCallState
{
  call_state_none = 0,
  call_state_executed,
  call_state_failed,
  call_state_timeout
};

#ifdef __cplusplus

#include <functional>

namespace eCAL
{
  /**
   * @brief eCAL service info struct.
  **/
  struct SServiceInfo
  {
    SServiceInfo()
    {
      id    = 0;
      state = call_state_none;
    };
    std::string  host_name;
    std::string  service_name;
    std::string  method_name;
    std::string  error_msg;
    int          id;
    eCallState   state;
  };

  typedef std::function<void(const struct SServiceInfo& service_info_, const std::string& response_)> ResponseCallbackT;
};

#endif /* __cplusplus */

#ifdef _MSC_VER
#pragma pack(push, 8)
#endif

struct SServiceInfoC
{
  const char*      host_name;
  const char*      service_name;
  const char*      method_name;
  const char*      error_msg;
  int              id;
  enum eCallState  state;
};

#ifdef _MSC_VER
#pragma pack(pop)
#endif

typedef void (*ResponseCallbackCT)(const struct SServiceInfoC* service_info_, const char* response_, int response_len_, void* par_);
