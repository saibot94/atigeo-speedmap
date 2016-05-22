/**
 * @file    envint.cpp
 *
 * @brief   Plugin dll function interface implementation.
**/



#include <string>
#include "envint.h"
#include "baseplugin.h"


//! Creates an interface class instance 'inst_name'
extern CBasePlugIn* GetPlugIn(const char* inst_name, wxPlg_IntFunT wxw_callback);

// warning C4996: 'strncpy': This function or variable may be unsafe ..
#pragma warning(disable : 4996)


//////////////////////////////////////////////////////////
//           plugin header
//////////////////////////////////////////////////////////
//! PlugIn name (can be shown in host side INFO dialog)
extern std::string PLUGIN_NAME;
//! PlugIn description (can be shown in host side INFO dialog)
extern std::string PLUGIN_DESC;


//////////////////////////////////////////////////////////
//           C style wrapper functions
//////////////////////////////////////////////////////////
extern "C"
{
  // global callback data
  std::string                                wxPlg_Name = PLUGIN_NAME;
  std::string                                wxPlg_Desc = PLUGIN_DESC;
  std::map<std::string, class CBasePlugIn*>  wxPlg_Map;

  // get interface version and initialize globals
  WXWPLUGIN_API double wxPlg_GetVersion()
  {
    wxPlg_Name = PLUGIN_NAME;;
    wxPlg_Desc = PLUGIN_DESC;
    return(EVT_PLG_VERSION);
  }

  // get name
  WXWPLUGIN_API long wxPlg_GetName(char* pName, long max_len)
  {
    strncpy(pName, wxPlg_Name.c_str(), max_len);
    return(0);
  }
  
  // get name length
  WXWPLUGIN_API size_t wxPlg_GetNameLength()
  {
    return wxPlg_Name.length()+1;
  }

  // get description
  WXWPLUGIN_API long wxPlg_GetDescription(char* pDesc, long max_len)
  {
    strncpy(pDesc, wxPlg_Desc.c_str(), max_len);
    return(0);
  }

  // get description length
  WXWPLUGIN_API size_t wxPlg_GetDescriptionLength()
  {
    return wxPlg_Desc.length()+1;
  }

  // initialize
  WXWPLUGIN_API long wxPlg_Initialize(const char* inst_name, wxPlg_IntFunT wxw_callback)
  {
    class CBasePlugIn* evt_plugin = GetPlugIn(inst_name, wxw_callback);
    if(!evt_plugin) return(-1);
    wxPlg_Map[inst_name] = evt_plugin;
    return(0);
  }

  // finalize
  WXWPLUGIN_API long wxPlg_Finalize(const char* inst_name)
  {
    std::map<std::string, class CBasePlugIn*>::iterator iter = wxPlg_Map.find(inst_name);
    if(iter == wxPlg_Map.end()) return(-1);
    class CBasePlugIn* evt_plugin = iter->second;
    if(!evt_plugin) return(-1);
    delete evt_plugin;
    wxPlg_Map.erase(inst_name);
    return(0);
  }

  // configure
  WXWPLUGIN_API long wxPlg_Configure(const char* inst_name, const char* key, const char* value)
  {
    std::map<std::string, class CBasePlugIn*>::iterator iter = wxPlg_Map.find(inst_name);
    if(iter == wxPlg_Map.end()) return(-1);
    class CBasePlugIn* evt_plugin = iter->second;
    if(!evt_plugin) return(-1);
    return(evt_plugin->Configure(key, value));
  }

  // execute interface function
  WXWPLUGIN_API long wxPlg_IntFun(const char* inst_name, const char* fun_name, const wxPlg_Obj* arg_obj, wxPlg_Obj* ret_obj)
  {
    std::map<std::string, class CBasePlugIn*>::iterator iter = wxPlg_Map.find(inst_name);
    if(iter == wxPlg_Map.end()) return(-1);
    class CBasePlugIn* evt_plugin = iter->second;
    if(!evt_plugin) return(-1);
    std::string event_name = fun_name;
    return(evt_plugin->CallFunction(event_name, arg_obj, ret_obj));
  }
}
