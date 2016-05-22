/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL std::string message interface
**/

#pragma once

#include <ecal/ecal_msg.h>

#include <string>
#include <memory.h>

namespace eCAL
{
  /**
   * @brief  eCAL publisher class for standard strings.
   *
   * Publisher class for STL standard strings. For details see documentation of CPublisher class.
   * 
  **/
  template <typename T>
  class CStringPublisher : public CMsgPublisher<T>
  {
  public:
    /**
     * @brief  Constructor. 
    **/
    CStringPublisher() : CMsgPublisher<T>()
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
    **/
    CStringPublisher(const std::string& topic_name_) : CMsgPublisher<T>(topic_name_, GetTypeName(), GetDescription())
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
     * @param topic_type_  Type name (optional). 
     * @param topic_desc_  Type description (optional). 
    **/
    CStringPublisher(const std::string& topic_name_, const std::string& topic_type_, const std::string& topic_desc_) : CMsgPublisher<T>(topic_name_, topic_type_, topic_desc_)
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
     * @brief  Get type name. 
     *
     * @return  Always returns "base:std::string". 
    **/
    std::string GetTypeName() const
    {
      return("base:std::string");
    }

    /**
     * @brief  Get description. 
     *
     * @return  Empty string. 
    **/
    std::string GetDescription() const
    {
      return("");
    }

    /**
     * @brief  Get size of the string object. 
     *
     * @param msg_  The message object. 
     *
     * @return  String site. 
    **/
    size_t GetSize(const T& msg_) const
    {
      return(msg_.size());
    }

    /**
     * @brief  Copy the string object into a preallocated char buffer. 
     *
     * @param       msg_     The message object. 
     * @param [out] buffer_  Target buffer. 
     * @param       size_    Target buffer size. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool Serialize(const T& msg_, char* buffer_, size_t size_) const
    {
      if(msg_.size() <= size_)
      {
        memcpy(buffer_, msg_.c_str(), msg_.size());
        return(true);
      }
      return(false);
    }

    // this object must not be copied.
    CStringPublisher(const CStringPublisher&);
    CStringPublisher& operator=(const CStringPublisher&);
  };

  /**
   * @brief  eCAL subscriber class for standard strings.
   *
   * Subscriber class for STL standard strings. For details see documentation of CSubscriber class.
   * 
  **/
  template <typename T>
  class CStringSubscriber : public CMsgSubscriber<T>
  {
  public:
    /**
     * @brief  Constructor. 
    **/
    CStringSubscriber() : CMsgSubscriber<T>()
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
    **/
    CStringSubscriber(const std::string& topic_name_) : CMsgSubscriber<T>(topic_name_, GetTypeName())
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
     * @brief  Get type name. 
     *
     * @return  Always returns "base:std::string". 
    **/
    std::string GetTypeName() const
    {
      return("base:std::string");
    }

    /**
     * @brief  Copy the string object from char buffer. 
     *
     * @param [out] msg_     The message object. 
     * @param       buffer_  Target buffer. 
     * @param       size_    Target buffer size. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool Deserialize(T& msg_, const void* buffer_, size_t size_) const
    {
      msg_ = std::string(static_cast<const char*>(buffer_), size_);
      return(!msg_.empty());
    }

    // this object must not be copied.
    CStringSubscriber(const CStringSubscriber&);
    CStringSubscriber& operator=(const CStringSubscriber&);
  };
}
