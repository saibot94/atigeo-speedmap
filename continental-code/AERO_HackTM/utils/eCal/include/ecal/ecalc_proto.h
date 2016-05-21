/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * eCAL c global header file (protobuf support)
**/

#pragma once

#include <string>
#include "ecal/ecal_proto_hlp.h"

inline ECAL_HANDLE eCAL_ProtoPub_Create(const std::string& topic_name_, const google::protobuf::Message& msg_)
{
  std::string type = GetProtoMessageTypeName(msg_).c_str();
  std::string desc = GetProtoMessageDescription(msg_);
  ECAL_HANDLE h    = eCAL_Pub_Create(topic_name_.c_str(), type.c_str(), desc.c_str(), static_cast<int>(desc.size()));
  return(h);
}

inline ECAL_HANDLE eCAL_ProtoSub_Create(const std::string& topic_name_, const google::protobuf::Message& msg_)
{
  ECAL_HANDLE h = eCAL_Sub_Create(topic_name_.c_str(), GetProtoMessageTypeName(msg_).c_str());
  return(h);
}
