/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  dynamic protobuf message decoder
**/

#pragma once

#include <string>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100 4127 4244 4267 4512 4996)
#endif
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/tokenizer.h>
#include <google/protobuf/compiler/parser.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#include <ecal/ecal_proto_hlp.h>

namespace eCAL
{
  /**
   * @brief eCAL dynamic protobuf decoder.
   *
   * The CProtoDynDecoder class is used to decode a protobuf message using protobuf reflection interface.
   * 
  **/
  /**
   * @code
   *            // create dynamic decoder
   *            std::string error_s;
   *            eCAL::CProtoDynDecoder decoder;
   *            google::protobuf::Message* msg_obj = decoder.GetProtoMessageFromFile("foo.proto", "FooMessage", error_s);
   * 
   *            // receive a message
   *            std::string msg_s = ReceiveMessageFromAnyWhere("foo");
   * 
   *            // decode message
   *            msg_obj->ParseFromString(msg_s);
   * 
   *            // print message
   *            std::cout << msg_obj->DebugString() << std::endl;
   * @endcode
  **/
  class CProtoDynDecoder
  {
  public:
    /**
     * @brief Create message from proto file. 
     *
     * @param       proto_filename_  Proto file name. 
     * @param       msg_type_        Type name. 
     * @param [out] error_s_         Error string. 
    **/
    google::protobuf::Message* GetProtoMessageFromFile(const std::string& proto_filename_, const std::string& msg_type_, std::string& error_s_);

    /**
     * @brief Create message from proto string. 
     *
     * @param       proto_string_  Proto string. 
     * @param       msg_type_      Type name. 
     * @param [out] error_s_       Error string. 
    **/
    google::protobuf::Message* GetProtoMessageFromString(const std::string& proto_string_, const std::string& msg_type_, std::string& error_s_);

    /**
     * @brief Create message from proto descriptor. 
     *
     * @param       proto_desc_  Proto descriptor. 
     * @param       msg_type_    Type name. 
     * @param [out] error_s_     Error string. 
    **/
    google::protobuf::Message* GetProtoMessageFromDescriptor(const google::protobuf::FileDescriptorProto& proto_desc_, const std::string& msg_type_, std::string& error_s_);

    /**
     * @brief Create message from proto descriptor set. 
     *
     * @param       proto_desc_set_  Proto descriptor set. 
     * @param       msg_type_        Type name. 
     * @param [out] error_s_         Error string. 
    **/
    google::protobuf::Message* GetProtoMessageFromDescriptorSet(const google::protobuf::FileDescriptorSet& proto_desc_set_, const std::string& msg_type_, std::string& error_s_);

    /**
     * @brief Create proto descriptor from proto file. 
     *
     * @param       proto_filename_   Proto file name. 
     * @param [out] file_desc_proto_  Type name. 
     * @param [out] error_s_          Error string. 
    **/
    static bool GetFileDescriptorFromFile(const std::string& proto_filename_, google::protobuf::FileDescriptorProto* file_desc_proto_, std::string& error_s_);

    /**
     * @brief Create proto descriptor from proto string. 
     *
     * @param       proto_string_     Proto string. 
     * @param [out] file_desc_proto_  Type name. 
     * @param [out] error_s_          Error string. 
    **/
    static bool GetFileDescriptorFromString(const std::string& proto_string_, google::protobuf::FileDescriptorProto* file_desc_proto_, std::string& error_s_);

  protected:
    google::protobuf::DescriptorPool         m_descriptor_pool;
    google::protobuf::DynamicMessageFactory  m_message_factory;
  };
}
