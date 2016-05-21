/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL generic message interface
**/

#pragma once

#include <ecal/ecal_publisher.h>
#include <ecal/ecal_subscriber.h>

#include <string>
#include <vector>
#include <functional>
#include <assert.h>
#include <string.h>

namespace eCAL
{
  /**
   * @brief eCAL abstract message publisher class.
   *
   * Abstract publisher template class for messages. For details see documentation of CPublisher class.
   * 
  **/
  template <typename T>
  class CMsgPublisher : public CPublisher
  {
  public:
    /**
     * @brief  Constructor. 
    **/
    CMsgPublisher() : CPublisher()
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
     * @param topic_type_  Type name (optional). 
     * @param topic_desc_  Type description (optional). 
    **/
    CMsgPublisher(const std::string& topic_name_, const std::string& topic_type_, const std::string& topic_desc_) : CPublisher(topic_name_, topic_type_, topic_desc_)
    {
    }

    virtual ~CMsgPublisher() {}

    /**
     * @brief  Creates this object. 
     *
     * @param topic_name_   Unique topic name. 
     * @param topic_type_   Type name (optional). 
     * @param topic_desc_   Type description (optional). 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool Create(const std::string& topic_name_, const std::string& topic_type_ = "", const std::string& topic_desc_ = "")
    {
      return(CPublisher::Create(topic_name_, topic_type_, topic_desc_));
    }

    /**
     * @brief  Destroys this object. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool Destroy()
    {
      return(CPublisher::Destroy());
    }

    /**
     * @brief  Send serialized message. 
     *
     * @param msg_   The message object. 
     * @param time_  Optional time stamp. 
     *
     * @return  Number of bytes sent. 
    **/
    size_t Send(const T& msg_, long long time_ = -1)
    {
      size_t size = GetSize(msg_);
      if(size > 0)
      {
        m_buffer.resize(size);
        if(Serialize(msg_, &m_buffer[0], m_buffer.size()))
        {
          return(CPublisher::Send(&m_buffer[0], size, time_));
        }
      }
      return(0);
    }

  private:
    virtual std::string GetTypeName() const = 0;
    virtual std::string GetDescription() const = 0;
    virtual size_t GetSize(const T& msg_) const = 0;
    virtual bool Serialize(const T& msg_, char* buffer_, size_t size_) const = 0;

    std::vector<char> m_buffer;
  };

  /**
   * @brief  eCAL abstract message subscriber class.
   *
   * Abstract subscriber template class for messages. For details see documentation of CPublisher class.
   * 
  **/
  template <typename T>
  class CMsgSubscriber : public CSubscriber
  {
  public:
    /**
     * @brief  Constructor. 
    **/
    CMsgSubscriber() : CSubscriber() , m_cb_active(false)
    {
    }

    /**
     * @brief  Constructor. 
     *
     * @param topic_name_  Unique topic name. 
     * @param topic_type_  Type name (optional). 
    **/
    CMsgSubscriber(const std::string& topic_name_, const std::string& topic_type_ = "") : CSubscriber(topic_name_, topic_type_) , m_cb_active(false)
    {
    }

    virtual ~CMsgSubscriber() {}

    /**
     * @brief Creates this object. 
     *
     * @param topic_name_   Unique topic name. 
     * @param topic_type_   Type name (optional for type checking by monitoring app). 
     *
     * @return  true if it succeeds, false if it fails. 
    **/
    bool Create(const std::string& topic_name_, const std::string& topic_type_ = "")
    {
      return(CSubscriber::Create(topic_name_, topic_type_));
    }

    /**
     * @brief Destroys this object. 
     *
     * @return  true if it succeeds, false if it fails. 
    **/
    bool Destroy()
    {
      RemReceiveCallback();
      return(CSubscriber::Destroy());
    }

    /**
     * @brief  Receive deserialized message. 
     *
     * @param [out] msg_    The message object. 
     * @param [out] time_   Optional receive time stamp. 
     * @param rcv_timeout_  Receive timeout in ms. 
     *
     * @return  True if a message could received, false otherwise. 
    **/
    bool Receive(T& msg_, long long* time_ = nullptr, int rcv_timeout_ = 0) const
    {
      assert(IsCreated());
      std::string rec_buf;
      size_t rec_len = CSubscriber::Receive(rec_buf, time_, rcv_timeout_);
      if(rec_len == 0) return(false);
      return(Deserialize(msg_, rec_buf.c_str(), rec_buf.size()));
    }

    /**
     * @brief  Add receive callback for incoming messages. 
     *
     * @param callback_  The callback function. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    typedef std::function<void(const char* topic_name_, const T& msg_, long long time_)> MsgReceiveCallbackT;
    bool AddReceiveCallback(MsgReceiveCallbackT callback_)
    {
      assert(IsCreated());
      RemReceiveCallback();
      if(m_cb_active == true) return(false);
      m_cb_active   = true;
      m_cb_callback = callback_;
      auto callback = std::bind(&CMsgSubscriber::ReceiveCallback, this, std::placeholders::_1, std::placeholders::_2);
      return(CSubscriber::AddReceiveCallback(callback));
    }

    /**
     * @brief  Remove receive callback for incoming messages. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool RemReceiveCallback()
    {
      if(m_cb_active == false) return(false);
      m_cb_active = false;
      return(CSubscriber::RemReceiveCallback());
    }

  private:
    virtual std::string GetTypeName() const = 0;
    virtual bool Deserialize(T& msg_, const void* buffer_, size_t size_) const = 0;

    void ReceiveCallback(const char* topic_name_, const struct eCAL::SReceiveCallbackData* data_)
    {
      if(m_cb_active == false) return;
      assert(m_cb_callback != nullptr);
      if(data_->buf == nullptr) return;
      if(data_->size < 1)       return;

      T msg;
      if(Deserialize(msg, data_->buf, data_->size))
      {
        if(m_cb_callback != nullptr)
        {
          (m_cb_callback)(topic_name_, msg, data_->time);
        }
      }
    }

    bool                 m_cb_active;
    MsgReceiveCallbackT  m_cb_callback;
  };
}
