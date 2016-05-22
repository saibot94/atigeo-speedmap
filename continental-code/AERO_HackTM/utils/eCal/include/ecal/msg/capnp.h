/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL capnp message interface
**/

#pragma once

#include <ecal/ecal_msg.h>

// capnp includes
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100 4239 4244 4245)
#endif
#include <capnp/serialize.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif


namespace eCAL
{
  /**
   * @brief eCAL capnp publisher class.
   *
   * Publisher template  class for capnp messages. For details see documentation of CPublisher class.
   * 
  **/
  template <typename T>
  class CCapnpPublisher : public CMsgPublisher<T>
  {
  public:
    /**
     * @brief  Constructor. 
    **/
    CCapnpPublisher() : CMsgPublisher<T>()
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
    **/
    CCapnpPublisher(const std::string& topic_name_) : CMsgPublisher<T>(topic_name_, GetTypeName(), GetDescription())
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
     * @brief  Get type name of the capnp message. 
     *
     * @return  Type name. 
    **/
    std::string GetTypeName() const
    {
      return("capnp:???");
    }

    /**
     * @brief  Get file descriptor string of the capnp message. 
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
      return(capnp::computeSerializedSizeInWords(const_cast<T&>(msg_)) * sizeof(capnp::word));
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
      kj::Array<capnp::word> words = capnp::messageToFlatArray(const_cast<T&>(msg_));
      kj::ArrayPtr<kj::byte> bytes = words.asBytes();
      if(size_ < bytes.size()) return(false);
      memcpy(buffer_, bytes.begin(), bytes.size());
      return(true);
    }

    // this object must not be copied.
    CCapnpPublisher(const CCapnpPublisher&);
    CCapnpPublisher& operator=(const CCapnpPublisher&);
  };

  /**
   * @brief  eCAL capnp subscriber class.
   *
   * Subscriber template  class for capnp messages. For details see documentation of CSubscriber class.
   * 
  **/
  template <typename T>
  class CCapnpSubscriber : public CMsgSubscriber<T>
  {
  public:
    /**
     * @brief  Constructor. 
    **/
    CCapnpSubscriber() : CMsgSubscriber<T>()
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
    **/
    CCapnpSubscriber(const std::string& topic_name_) : CMsgSubscriber<T>(topic_name_, GetTypeName())
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
     * @brief  Get type name of the capnp message. 
     *
     * @return  Type name. 
    **/
    std::string GetTypeName() const
    {
      return("capnp:???");
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
      kj::ArrayPtr<const capnp::word> words = kj::arrayPtr(reinterpret_cast<const capnp::word*>(buffer_), size_ / sizeof(capnp::word));
      kj::ArrayPtr<const capnp::word> rest  = initMessageBuilderFromFlatArrayCopy(words, msg_);
      return(rest.size() == 0);
    }

    // this object must not be copied.
    CCapnpSubscriber(const CCapnpSubscriber&);
    CCapnpSubscriber& operator=(const CCapnpSubscriber&);
  };
}
