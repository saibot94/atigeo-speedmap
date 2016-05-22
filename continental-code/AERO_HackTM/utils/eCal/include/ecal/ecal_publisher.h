/**
 * Copyright (c) <2015>, Continental Corporation.
 *
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 *
**/

/**
 * @brief  eCAL publisher interface
**/

#pragma once

#include <string>
#include <memory>

#ifndef ECAL_USING_DLL

namespace eCAL
{
  class CDataWriter;

  /**
   * @brief eCAL publisher class.
   *
   * The CPublisher class is used to send topics to matching eCAL subscribers. The topic is created automatically by the constructor
   * or by the Create member function.
   * <br>
   * <br>
   * For sending the topic payload the publisher class provides an overloaded Send method. The first one is sending the payload as
   * a std::string. The second needs a preallocated buffer described by a buffer address and a buffer length. The publisher is not
   * taking the ownership for the allocated memory buffer.
   * <br>
   * <br>
   * An optional time stamp can be attached to the topic payload.
   * 
  **/
  /**
   * @code
   *            // create publisher, topic name "A"
   *            eCAL::CPublisher pub("A");
   *
   *            // send string
   *            std::string send_s = "Hello World ";
   *
   *            // send content
   *            size_t snd_len = pub.Send(send_s);
   * @endcode
  **/
  class CPublisher
  {
  public:
    /**
     * @brief Constructor. 
    **/
    CPublisher();

    /**
     * @brief Constructor. 
     *
     * @param topic_name_   Unique topic name. 
     * @param topic_type_   Type name (optional). 
     * @param topic_desc_   Type description (optional). 
    **/
    CPublisher(const std::string& topic_name_, const std::string& topic_type_ = "", const std::string& topic_desc_ = "");

    /**
     * @brief Destructor. 
    **/
    virtual ~CPublisher();

    /**
     * @brief Creates this object. 
     *
     * @param topic_name_   Unique topic name. 
     * @param topic_type_   Type name (optional). 
     * @param topic_desc_   Type description (optional). 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool Create(const std::string& topic_name_, const std::string& topic_type_ = "", const std::string& topic_desc_ = "");

    /**
     * @brief Destroys this object. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool Destroy();

    /**
     * @brief Setup topic description. 
     *
     * @param topic_desc_   Description string. 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool SetDescription(const std::string& topic_desc_);

    /**
     * @brief Setup the publisher compression. 
     *
     * @param mode_   Compression mode 0 = off, 1 = on, default = 0). 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool SetCompression(int mode_);

    /**
     * @brief Set publisher send mode via udp. 
     *
     * @param mode_   Send mode 0 = off, 1 = on, 2 = auto, default = 2). 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool SetUseUdp(int mode_);

    /**
     * @brief Set publisher send mode via shared memory. 
     *
     * @param mode_   Send mode 0 = off, 1 = on, 2 = auto, default = 2). 
     *
     * @return  True if it succeeds, false if it fails. 
    **/
    bool SetUseShm(int mode_);

    /**
     * @brief Send a message to all subscribers. 
     *
     * @param buf_    Pointer to content buffer. 
     * @param len_    Length of buffer. 
     * @param time_   Send time (-1 = use eCAL system time in us, default = -1).
     *
     * @return  Number of bytes sent. 
    **/
    size_t Send(const void* const buf_, size_t len_, long long time_ = -1) const;

    /**
     * @brief Send a message to all subscribers. 
     *
     * @param s_      String that contains content to send. 
     * @param time_   Send time (-1 = use eCAL system time in us, default = -1).
     *
     * @return  Number of bytes sent. 
    **/
    size_t Send(const std::string& s_, long long time_ = -1) const;

    /**
     * @brief Query if the publisher is created. 
     *
     * @return  True if created, false if not. 
    **/
    bool IsCreated() const {return(m_created);}

    /**
     * @brief Query if the publisher is subscribed. 
     *
     * @return  true if subscribed, false if not. 
    **/
    bool IsSubscribed() const;

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
     * @return  The dump string. 
    **/
    std::string Dump(const std::string& indent_ = "") const;

  protected:
    // class members
    std::shared_ptr<CDataWriter>  m_datawriter;
    bool                          m_compressed;
    bool                          m_created;

  private:
    // this object must not be copied.
    CPublisher(const CPublisher&);
    CPublisher& operator=(const CPublisher&);
  };
};

#else /* ! ECAL_USING_DLL */

#include <ecal/ecalc.h>

namespace eCAL
{
  class CPublisher
  {
  public:
    CPublisher() :
      m_publisher(nullptr),
      m_created(false)
    {
    }

    CPublisher(const std::string& topic_name_, const std::string& topic_type_ = "", const std::string& topic_desc_ = "") :
      m_publisher(nullptr),
      m_created(false)
    {
      Create(topic_name_, topic_type_, topic_desc_);
    }

    virtual ~CPublisher()
    {
      Destroy();
    }

    bool Create(const std::string& topic_name_, const std::string& topic_type_ = "", const std::string& topic_desc_ = "")
    {
      if(m_created) return(false);
      m_publisher = eCAL_Pub_Create(topic_name_.c_str(), topic_type_.c_str(), topic_desc_.c_str(), static_cast<int>(topic_desc_.size()));
      if(!m_publisher) return(false);

      m_topic_name = topic_name_;
      m_topic_type = topic_type_;
      m_topic_desc = topic_desc_;

      m_created = true;
      return(true);
    }

    bool Destroy()
    {
      if(!m_created) return(false);
      if(m_publisher) eCAL_Pub_Destroy(m_publisher);

      m_publisher  = nullptr;
      m_topic_name = "";
      m_topic_type = "";
      m_created    = false;
      return(true);
    }

    bool SetDescription(const std::string& topic_desc_)
    {
      m_topic_desc = topic_desc_;
      if(!m_publisher) return(false);
      return(eCAL_Pub_SetDescription(m_publisher, topic_desc_.c_str(), static_cast<int>(topic_desc_.size())) != 0);
    }

    bool SetCompression(int mode_)
    {
      if(!m_publisher) return(false);
      return(eCAL_Pub_SetCompression(m_publisher, mode_) != 0);
    }

    bool SetUseUdp(int mode_)
    {
      if(!m_publisher) return(false);
      return(eCAL_Pub_SetUseUdp(m_publisher, mode_) != 0);
    }

    bool SetUseShm(int mode_)
    {
      if(!m_publisher) return(false);
      return(eCAL_Pub_SetUseShm(m_publisher, mode_) != 0);
    }

    size_t Send(const void* const buf_, size_t len_, long long time_ = -1) const
    {
      if(!m_publisher) return(0);
      return(eCAL_Pub_Send(m_publisher, buf_, static_cast<int>(len_), time_));
    }

    size_t Send(const std::string& s_, long long time_ = -1) const
    {
      return(eCAL_Pub_Send(m_publisher, s_.data(), static_cast<int>(s_.size()), time_));
    }

    bool IsCreated() const {return(m_created);}

    bool IsSubscribed() const
    {
      if(!m_publisher) return(false);
      return(eCAL_Pub_IsSubscribed(m_publisher) != 0);
    }

    const std::string& GetTopicName() const {return(m_topic_name);}

    const std::string& GetTypeName() const {return(m_topic_type);}

    const std::string& GetDescription() const {return(m_topic_desc);}

    std::string Dump() const
    {
      if(!m_publisher) return("");
      void* buf = nullptr;
      size_t buf_len = eCAL_Pub_Dump(m_publisher, &buf, ECAL_ALLOCATE_4ME);
      if(buf_len == 0) return("");
      std::string dbuf = std::string(static_cast<char*>(buf), buf_len);
      eCAL_FreeMem(buf);
      return(dbuf);
    }

  protected:
    // class members
    ECAL_HANDLE  m_publisher;
    std::string  m_topic_name;
    std::string  m_topic_type;
    std::string  m_topic_desc;
    bool         m_created;

  private:
    // this object must not be copied.
    CPublisher(const CPublisher&);
    CPublisher& operator=(const CPublisher&);
  };
};

#endif /* ! ECAL_USING_DLL */
