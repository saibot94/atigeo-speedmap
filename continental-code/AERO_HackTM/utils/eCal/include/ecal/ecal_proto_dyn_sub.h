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

#include <ecal/ecal.h>
#include <ecal/ecal_proto_dyn.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100 4127 4244 4267 4512 4996)
#endif
#include <google/protobuf/message.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

namespace eCAL
{
  /**
   * @brief eCAL dynamic protobuf subscriber.
  **/
  class CProtoDynSubscriber
  {
  public:
    /**
     * @brief Constructor. 
    **/
    CProtoDynSubscriber();

    /**
     * @brief Constructor. 
     *
     * @param topic_name_  Unique topic name. 
     * @param topic_type_  Type name (optional). 
    **/
    CProtoDynSubscriber(const std::string& topic_name_, const std::string& topic_type_);

    /**
     * @brief Destructor. 
    **/
    virtual ~CProtoDynSubscriber();

    /**
     * @brief Creates this object. 
     *
     * @param topic_name_   Unique topic name. 
     * @param topic_type_   Type name (optional for type checking by monitoring app). 
     *
     * @return  true if it succeeds, false if it fails. 
    **/
    void Create(const std::string& topic_name_, const std::string& topic_type_);

    /**
     * @brief Destroys this object. 
     *
     * @return  true if it succeeds, false if it fails. 
    **/
    void Destroy();

    /**
     * @brief Query if this object is created. 
     *
     * @return  true if created, false if not. 
    **/
    bool IsCreated() {return(created);}
    
    typedef std::function<void(const char* topic_name_, const google::protobuf::Message& msg_ptr_, long long time_)> ProtoMsgCallbackT;
    /**
     * @brief Add callback function for incoming receives. 
     *
     * @param callback_  The callback function to add.
     *
     * @return  True if succeeded, false if not. 
    **/
    bool AddReceiveCallback(ProtoMsgCallbackT callback_);

    /**
     * @brief Remove callback function for incoming receives. 
     *
     * @return  True if succeeded, false if not. 
    **/
    bool RemReceiveCallback();

  protected:
    void OnReceive(const char* topic_name_, const struct eCAL::SReceiveCallbackData* data_);

    bool                        created;
    eCAL::CProtoDynDecoder*     msg_decoder;
    google::protobuf::Message*  msg_ptr;
    eCAL::CSubscriber           msg_sub;
    ProtoMsgCallbackT           msg_callback;

  private:
    // this object must not be copied.
    CProtoDynSubscriber(const CProtoDynSubscriber&);
    CProtoDynSubscriber& operator=(const CProtoDynSubscriber&);
  };
}
