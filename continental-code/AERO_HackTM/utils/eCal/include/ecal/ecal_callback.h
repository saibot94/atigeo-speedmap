/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL subscriber callback interface
**/

#pragma once

#ifdef __cplusplus

#include <functional>

namespace eCAL
{
  /**
   * @brief eCAL subscriber receive callback struct.
  **/
  struct SReceiveCallbackData
  {
    SReceiveCallbackData()
    {
      buf  = nullptr;
      size = 0;
      time = 0;
    };
    void*     buf;
    long      size;
    long long time;
  };

  typedef std::function<void(const char* topic_name_, const struct SReceiveCallbackData* data_)> ReceiveCallbackT;
  typedef std::function<void(void)> TimerCallbackT;
};

#endif /* __cplusplus */

/**
  * @brief eCAL subscriber receive callback struct (C variant).
**/
#ifdef _MSC_VER
#pragma pack(push, 8)
#endif

struct SReceiveCallbackDataC
{
  void*     buf;
  long      size;
  long long time;
};

#ifdef _MSC_VER
#pragma pack(pop)
#endif

typedef void (*ReceiveCallbackCT)(const char* topic_name_, const struct SReceiveCallbackDataC* data_, void* par_);
typedef void (*TimerCallbackCT)(void* par_);
