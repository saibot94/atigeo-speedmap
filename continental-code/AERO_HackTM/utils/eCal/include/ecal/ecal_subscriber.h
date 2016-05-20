/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL subscriber interface
**/

#pragma once

#include <ecal/ecal_callback.h>

#include <string>

#ifndef ECAL_USING_DLL

namespace eCAL
{
  class CDataReader;

  /**
   * @brief eCAL subscriber class.
   *
   * The CSubscriber class is used to receive topics from matching eCAL publishers.
   * <br>
   * <br>
   * For receiving the topic payload the subscriber class provides a callback interface and overloaded receive methods.
  **/
  /**
   * @code
   *            // create subscriber, topic name "A"
   *            eCAL::CSubscriber sub("A");
   *
   *            //---------------------------------------------------------------------------------------
   *            // receive content with 100 ms timeout as standard string and read receive time stamp
   *            //---------------------------------------------------------------------------------------
   *            std::string rcv_s;
   *            long long time = 0;
   *            size_t rcv_len = sub.Receive(rcv_s, &time, 100);
   *
   *            //---------------------------------------------------------------------------------------
   *            // receive content with a callback functions
   *            //---------------------------------------------------------------------------------------
   *            void OnReceive(const char* topic_name_, const struct eCAL::SReceiveCallbackData* data_)
   *            {
   *              size_t      size = data_->size;
   *              const void* data = data_->buf;
   *              long long   time = data_->time;
   *            }
   *
   *            // add callback
   *            sub.AddReceiveCallback(std::bind(OnReceive, std::placeholders::_1, std::placeholders::_2));
   *
   *            // idle main thread
   *            while(eCAL::Ok())
   *            {
   *              // sleep 100 ms
   *              std::this_thread::sleep_for(std::chrono::milliseconds(100));
   *            }
   * @endcode
  **/
  class CSubscriber
  {
  public:
    /**
     * @brief Constructor. 
    **/
    CSubscriber();

    /**
     * @brief Constructor. 
     *
     * @param topic_name_   Unique topic name. 
     * @param topic_type_   Type name (optional for type checking by monitoring app). 
    **/
    CSubscriber(const std::string& topic_name_, const std::string& topic_type_ = "");

    /**
     * @brief Destructor. 
    **/
    virtual ~CSubscriber();

    /**
     * @brief Creates this object. 
     *
     * @param topic_name_   Unique topic name. 
     * @param topic_type_   Type name (optional for type checking by monitoring app). 
     *
     * @return  true if it succeeds, false if it fails. 
    **/
    bool Create(const std::string& topic_name_, const std::string& topic_type_ = "");

    /**
     * @brief Destroys this object. 
     *
     * @return  true if it succeeds, false if it fails. 
    **/
    bool Destroy();

    /**
     * @brief Receive a message from the publisher. 
     *
     * @param [out] buf_    Standard string for copying message content.
     * @param [out] time_   Time from publisher in us (default = nullptr).
     * @param rcv_timeout_  Maximum time before receive operation returns (in milliseconds, -1 means infinite).
     *
     * @return  Length of received buffer. 
    **/
    size_t Receive(std::string& buf_, long long* time_ = nullptr, int rcv_timeout_ = 0) const;

    /**
     * @brief Add callback function for incoming receives. 
     *
     * @param callback_  The callback function to add.
     *
     * @return  True if succeeded, false if not. 
    **/
    bool AddReceiveCallback(ReceiveCallbackT callback_);

    /**
     * @brief Remove callback function for incoming receives. 
     *
     * @return  True if succeeded, false if not. 
    **/
    bool RemReceiveCallback();

    /**
     * @brief Query if this object is created. 
     *
     * @return  true if created, false if not. 
    **/
    bool IsCreated() const {return(m_created);}

    /**
     * @brief Gets name of the connected topic. 
     *
     * @return  The topic name. 
    **/
    std::string GetTopicName() const;

    /**
     * @brief Gets type of the connected topic. 
     *
     * @return  The type name. 
    **/
    std::string GetTypeName() const;

    /**
     * @brief Gets description of the connected topic. 
     *
     * @return  The description. 
    **/
    std::string GetDescription() const;

    /**
     * @brief Dump the whole class state into a string. 
     *
     * @param indent_  Indentation used for dump. 
     *
     * @return  The dump sting. 
    **/
    std::string Dump(const std::string& indent_ = "") const;

  protected:
    // class members
    std::shared_ptr<CDataReader>  m_datareader;
    bool                          m_created;

  private:
    // this object must not be copied.
    CSubscriber(const CSubscriber&);
    CSubscriber& operator=(const CSubscriber&);
  };
};

#else /* ! ECAL_USING_DLL */

#include <ecal/ecalc.h>

namespace eCAL
{
  class CSubscriber
  {
  public:
    CSubscriber() :
      m_subscriber(nullptr),
      m_created(false)
    {
    }

    CSubscriber(const std::string& topic_name_, const std::string& topic_type_ = "") :
      m_subscriber(nullptr),
      m_created(false)
    {
      Create(topic_name_, topic_type_);
    }

    virtual ~CSubscriber()
    {
      Destroy();
    }

    bool Create(const std::string& topic_name_, const std::string& topic_type_ = "")
    {
      if(m_created) return(false);
      m_subscriber = eCAL_Sub_Create(topic_name_.c_str(), topic_type_.c_str());
      if(!m_subscriber) return(false);

      m_topic_name = topic_name_;
      m_topic_type = topic_type_;
      m_created = true;
      return(true);
    }

    bool Destroy()
    {
      if(!m_created) return(false);
      if(m_subscriber) eCAL_Sub_Destroy(m_subscriber);

      m_subscriber  = nullptr;
      m_topic_name  = "";
      m_topic_type  = "";
      m_created     = false;
      return(true);
    }

    size_t Receive(std::string& buf_, long long* time_ = nullptr, int rcv_timeout_ = 0) const
    {
      if(!m_subscriber) return(0);
      void* buf = nullptr;
      size_t buf_len = eCAL_Sub_Receive(m_subscriber, &buf, ECAL_ALLOCATE_4ME, time_, rcv_timeout_);
      if(buf_len > 0)
      {
        buf_ = std::string(static_cast<char*>(buf), buf_len);
        eCAL_FreeMem(buf);
      }
      return(buf_.size());
    }

    static void ReceiveCallback(const char* topic_name_, const struct SReceiveCallbackDataC* data_, void* par_)
    {
      if(par_ == nullptr) return;
      CSubscriber* sub = static_cast<CSubscriber*>(par_);
      SReceiveCallbackData data;
      data.buf  = data_->buf;
      data.size = data_->size;
      data.time = data_->time;
      sub->m_callback(topic_name_, &data);
    }
    bool AddReceiveCallback(ReceiveCallbackT callback_)
    {
      if(!m_subscriber) return(false);
      m_callback = callback_;
      return(eCAL_Sub_AddReceiveCallbackC(m_subscriber, &CSubscriber::ReceiveCallback, this) != 0);
    }

    bool RemReceiveCallback()
    {
      if(!m_subscriber) return(false);
      return(eCAL_Sub_RemReceiveCallback(m_subscriber) != 0);
    }

    bool IsCreated() const {return(m_created);}

    const std::string GetTopicName() const {return(m_topic_name);}

    const std::string GetTypeName() const {return(m_topic_type);}

    std::string GetDescription() const
    {
      if(!m_subscriber) return("");
      std::string desc;
      void* buf = nullptr;
      size_t buf_len = eCAL_Sub_GetDescription(m_subscriber, &buf, ECAL_ALLOCATE_4ME);
      if(buf_len > 0)
      {
        desc = std::string(static_cast<char*>(buf), buf_len);
        eCAL_FreeMem(buf);
      }
      return(desc);
    }

    std::string Dump() const
    {
      if(!m_subscriber) return("");
      void* buf = nullptr;
      size_t buf_len = eCAL_Sub_Dump(m_subscriber, &buf, ECAL_ALLOCATE_4ME);
      if(buf_len == 0) return("");
      std::string dbuf = std::string(static_cast<char*>(buf), buf_len);
      eCAL_FreeMem(buf);
      return(dbuf);
    }

  protected:
    ECAL_HANDLE      m_subscriber;
    std::string      m_topic_name;
    std::string      m_topic_type;
    ReceiveCallbackT m_callback;
    bool             m_created;

  private:
    // this object must not be copied.
    CSubscriber(const CSubscriber&);
    CSubscriber& operator=(const CSubscriber&);
  };
};

#endif /* ! ECAL_USING_DLL */
