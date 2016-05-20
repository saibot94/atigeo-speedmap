#ifndef rt_modplugin_h_included
#define rt_modplugin_h_included

// plugin includes
#include "stdafx.h"
#include "evtplugin.h"
#include "myobjects_def.h"


//////////////////////////////////////////////////////////
//           class CModPlugIn declaration
//////////////////////////////////////////////////////////
/**
 * @class   CModPlugIn
 *
 * @brief    Widget event dll class
 *
 * @details  This class contains the widget plugin interface and wraps the
 *           widget specific event callback functions as member function.
 *           For furher details reagrding the special event names see wxWidgets
 *           documentation.
 *           Note: The calling application creates a single instance of this class
 *           for every widget that is using this callback dll. You can obtain the
 *           full path of the widget by calling the 'GetInstance' function of the
 *           base class. The global namespace of the dll (outside this class) is 
 *           shared by ALL caller widgets.
**/
class CModPlugIn : public CEvtPlugIn
{
public:
   /**
   * @brief  Default constructor. 
   *
   * @param inst_name     Name of the plugin instance.
   * @param callback      Pointer to central callback hook (for internal use).
  **/
  CModPlugIn(const char* inst_name, wxPlg_IntFunT callback);
  /**
   * @brief  Finaliser.
  **/
  ~CModPlugIn();

  /**
   * @brief  Callback functions for the widget specific events.
   *
   * @param [in]  arg_obj  The function argument values (see 'envargs.h' for argument parsing helper functions)
   * @param [out] ret_obj  The function return values.
   *
   * @return  0 if it succeeds, -1 if it fails.
  **/
  long wxEVT_OPEN        (const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj));
  long wxEVT_CLOSE       (const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj));
  long wxEVT_CONNECT     (const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj));
  long wxEVT_DISCONNECT  (const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj));
  long wxEVT_STEP        (const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj));
  long wxEVT_DRAW2D      (const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj));
  long wxEVT_DRAW3D      (const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj));
};

#endif /* rt_modplugin_h_included */
