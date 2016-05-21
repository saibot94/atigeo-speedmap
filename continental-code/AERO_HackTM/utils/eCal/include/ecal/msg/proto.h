/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL google::protobuf message interface
**/

#pragma once

#include <ecal/ecal_msg.h>
#include <ecal/ecal_proto_hlp.h>

// protobuf includes
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100 4127 4244 4267 4512)
#endif
#include <google/protobuf/descriptor.pb.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif


namespace eCAL
{
  /**
   * @brief eCAL google::protobuf publisher class.
   *
   * Publisher template  class for google::protobuf messages. For details see documentation of CPublisher class.
   * 
  **/
  template <typename T>
  class CProtoPublisher : public CMsgPublisher<T>
  {
  public:
    /**
     * @brief  Constructor. 
    **/
    CProtoPublisher() : CMsgPublisher<T>()
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
    **/
    CProtoPublisher(const std::string& topic_name_) : CMsgPublisher<T>(topic_name_, GetTypeName(), GetDescription())
    {
    }

    /**
     * @brief  Creates this object. 
     *
     * @param topic_name_  Unique topic name. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool Create(const std::string& topic_name_)
    {
      return(CMsgPublisher<T>::Create(topic_name_, GetTypeName(), GetDescription()));
    }

  private:
    /**
     * @brief  Get type name of the protobuf message. 
     *
     * @return  Type name. 
    **/
    std::string GetTypeName() const
    {
      static T msg;
      return("proto:" + msg.GetTypeName());
    }

    /**
     * @brief  Get file descriptor string of the protobuf message. 
     *
     * @return  Description string. 
    **/
    std::string GetDescription() const
    {
      static T msg;
      return(GetProtoMessageDescription(msg));
    }

    /**
     * @brief  Get size for serialized message object. 
     *
     * @param msg_  The message object. 
     *
     * @return  Message size. 
    **/
    size_t GetSize(const T& msg_) const
    {
      return((size_t)msg_.ByteSize());
    }

    /**
     * @brief  Serialize the message object into a preallocated char buffer. 
     *
     * @param       msg_     The message object. 
     * @param [out] buffer_  Target buffer. 
     * @param       size_    Target buffer size. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool Serialize(const T& msg_, char* buffer_, size_t size_) const
    {
      return(msg_.SerializeToArray((void*)buffer_, (int)size_));
    }

    // this object must not be copied.
    CProtoPublisher(const CProtoPublisher&);
    CProtoPublisher& operator=(const CProtoPublisher&);
  };

  /**
   * @brief  eCAL google::protobuf subscriber class.
   *
   * Subscriber template  class for google::protobuf messages. For details see documentation of CSubscriber class.
   * 
  **/
  template <typename T>
  class CProtoSubscriber : public CMsgSubscriber<T>
  {
  public:
    /**
     * @brief  Constructor. 
    **/
    CProtoSubscriber() : CMsgSubscriber<T>()
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
    **/
    CProtoSubscriber(const std::string& topic_name_) : CMsgSubscriber<T>(topic_name_, GetTypeName())
    {
    }

    /**
     * @brief  Creates this object. 
     *
     * @param topic_name_  Unique topic name. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool Create(const std::string& topic_name_)
    {
      return(CMsgSubscriber<T>::Create(topic_name_, GetTypeName()));
    }

  private:
    /**
     * @brief  Get type name of the protobuf message. 
     *
     * @return  Type name. 
    **/
    std::string GetTypeName() const
    {
      static T msg;
      return("proto:" + msg.GetTypeName());
    }

    /**
     * @brief  Deserialize the message object from a message buffer. 
     *
     * @param [out] msg_     The message object. 
     * @param       buffer_  Source buffer. 
     * @param       size_    Source buffer size. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool Deserialize(T& msg_, const void* buffer_, size_t size_) const
    {
      return(msg_.ParseFromArray(buffer_, static_cast<int>(size_)));
    }

    // this object must not be copied.
    CProtoSubscriber(const CProtoSubscriber&);
    CProtoSubscriber& operator=(const CProtoSubscriber&);
  };
}
