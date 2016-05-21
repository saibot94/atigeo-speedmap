/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL google::flatbuffers message interface
**/

#pragma once

#include <ecal/ecal_msg.h>

namespace eCAL
{
  /**
   * @brief eCAL google::flatbuffers publisher class.
   *
   * Publisher template  class for goggle::flatbuffers messages. For details see documentation of CPublisher class.
   * 
  **/
  template <typename T>
  class CFlatPublisher : public CMsgPublisher<T>
  {
  public:
    /**
     * @brief  Constructor. 
    **/
    CFlatPublisher() : CMsgPublisher<T>()
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
    **/
    CFlatPublisher(const std::string& topic_name_) : CMsgPublisher<T>(topic_name_, GetTypeName(), GetDescription())
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
     * @brief  Get type name of the flatbuffers message. 
     *
     * @return  Type name. 
    **/
    std::string GetTypeName() const
    {
      return("flatb:???");
    }

    /**
     * @brief  Get file descriptor string of the flatbuffers message. 
     *
     * @return  Description string. 
    **/
    std::string GetDescription() const
    {
      return("");
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
      return((size_t)msg_.GetSize());
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
      if(size_ < msg_.GetSize()) return(false);
      memcpy(buffer_, msg_.GetBufferPointer(), msg_.GetSize());
      return(true);
    }

    // this object must not be copied.
    CFlatPublisher(const CFlatPublisher&);
    CFlatPublisher& operator=(const CFlatPublisher&);
  };

  /**
   * @brief  eCAL google::flatbuffers subscriber class.
   *
   * Subscriber template  class for google::flatbuffers messages. For details see documentation of CSubscriber class.
   * 
  **/
  template <typename T>
  class CFlatSubscriber : public CMsgSubscriber<T>
  {
  public:
    /**
     * @brief  Constructor. 
    **/
    CFlatSubscriber() : CMsgSubscriber<T>()
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
    **/
    CFlatSubscriber(const std::string& topic_name_) : CMsgSubscriber<T>(topic_name_, GetTypeName())
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
     * @brief  Get type name of the flatbuffers message. 
     *
     * @return  Type name. 
    **/
    std::string GetTypeName() const
    {
      return("flatb:???");
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
      msg_.PushFlatBuffer(static_cast<const uint8_t*>(buffer_), static_cast<int>(size_));
      return(true);
    }

    // this object must not be copied.
    CFlatSubscriber(const CFlatSubscriber&);
    CFlatSubscriber& operator=(const CFlatSubscriber&);
  };
}
