/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL TaCC message interface
**/

#pragma once

#include <ecal/ecal_msg.h>

namespace eCAL
{
  /**
   * @brief  eCAL Tacc message publisher class.
   *
   * Publisher template  class for Tacc messages. For details see documentation of CPublisher class.
   * 
  **/
  template <typename T>
  class CTaccPublisher : public CMsgPublisher<T>
  {
  public:
    /**
     * @brief  Constructor. 
    **/
    CTaccPublisher() : CMsgPublisher<T>()
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
    **/
    CTaccPublisher(const std::string& topic_name_) : CMsgPublisher<T>(topic_name_, GetTypeName(), GetDescription())
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
     * @brief  Get type name of the Tacc message. 
     *
     * @return  Type name. 
    **/
    std::string GetTypeName() const
    {
      static T msg;
      return("tacc:" + std::string(msg.GetType()));
    }

    /**
     * @brief  Get description of the Tacc message. 
     *
     * @return  Empty strung. 
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
      return((size_t)((T*)&msg_)->GetSize());
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
      signed long written = ((T*)&msg_)->Serialize(buffer_, (unsigned long)size_);
      return(written > 0);
    }

    // this object must not be copied.
    CTaccPublisher(const CTaccPublisher&);
    CTaccPublisher& operator=(const CTaccPublisher&);
  };

  /**
   * @brief  eCAL Tacc subscriber class.
   *
   * Subscriber template  class for Tacc messages. For details see documentation of CSubscriber class.
   * 
  **/
  template <typename T>
  class CTaccSubscriber : public CMsgSubscriber<T>
  {
  public:
    /**
     * @brief  Constructor. 
    **/
    CTaccSubscriber() : CMsgSubscriber<T>()
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
    **/
    CTaccSubscriber(const std::string& topic_name_) : CMsgSubscriber<T>(topic_name_, GetTypeName())
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
     * @brief  Get type name of the Tacc message. 
     *
     * @return  Type name. 
    **/
    std::string GetTypeName() const
    {
      static T msg;
      return("tacc:" + std::string(msg.GetType()));
    }

    /**
     * @brief  Deserialize the message object from a message buffer. 
     *
     * @param       msg_     The message object. 
     * @param [out] buffer_  Source buffer. 
     * @param       size_    Source buffer size. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool Deserialize(T& msg_, const void* buffer_, size_t size_) const
    {
      return(msg_.Deserialize(static_cast<const char*>(buffer_), static_cast<unsigned long>(size_)) > 0);
    }

    // this object must not be copied.
    CTaccSubscriber(const CTaccSubscriber&);
    CTaccSubscriber& operator=(const CTaccSubscriber&);
  };
}
