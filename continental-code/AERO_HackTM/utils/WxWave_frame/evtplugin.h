#ifndef evtplugin_h_included
#define evtplugin_h_included

#include "envint.h"
#include "envargs.h"
#include "baseplugin.h"

#include <string>
#include <vector>
#include <list>
#include <map>


//////////////////////////////////////////////////////////
//           function declaring
//////////////////////////////////////////////////////////
/**
 * Declare plugin function (macro).
 *
 * Declare function 'fun_ptr' as dll function 'fun_name'.
 *
 * Declares the function 'fun_ptr' as dll function that is callable from host application.
 *
 * @param   fun_name  Function name.
 * @param   fun_ptr   Function address.
 *
 * @return            1.
 */
#define DEC_EVT(fun_name, fun_ptr) DeclareFunction(fun_name, &CEvtPlugIn::fun_ptr)


//////////////////////////////////////////////////////////
//           plugin interface class
//////////////////////////////////////////////////////////
/**
 * @class   CEvtPlugIn
 * 
 * Widget dll base class
 *
 * This class that contains the Widget specific interface and wraps the 
 * Widget callback functions as member function.
 */
class CEvtPlugIn : public CBasePlugIn
{
  typedef long (CEvtPlugIn::*FunCallbackT)(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj));
  typedef std::map<std::string, FunCallbackT> EvtMapT;

public:
  CEvtPlugIn(const char* inst_name, wxPlg_IntFunT callback) : CBasePlugIn(inst_name, callback) {};
  virtual ~CEvtPlugIn() {};

  ///////////////////////////////////////////////
  // plugin interface functions
  ///////////////////////////////////////////////
  /**
   * Declare plugin dll function.
   *
   * Declares the function 'fun_ptr' as dll function that is callable from host application.
   *
   * @param   fun_name    Function name.
   * @param   dll_fun     Member function.
   *
   * @return              1.
   */
  int DeclareFunction(const std::string& fun_name, FunCallbackT dll_fun)
  {
    plg_functions[fun_name] = dll_fun;
    return(1);
  };

  /**
   * Check function name (internal use).
   *
   * Checks whether the specified dll function is defined for this dll or not.
   *
   * @param   fun_name  Function name.
   *
   * @return            TRUE or FALSE.
   */
  int HasFunction(const std::string& fun_name)
  {
    return(plg_functions.find(fun_name) != plg_functions.end());
  }

  /**
   * Call dll function (internal use).
   *
   * Execute function 'fun_name' with the specified argument and return objects.
   *
   * @param   fun_name       Function name.
   * @param   arg_obj        Function argument object.
   * @param   ret_obj        Function return object.
   *
   * @return                 Depends from function implementation.
   */
  int CallFunction(const std::string& fun_name, const wxPlg_Obj* arg_obj, wxPlg_Obj* ret_obj)
  {
    if(plg_functions.find(fun_name) != plg_functions.end())
    {
      FunCallbackT ptr = plg_functions[fun_name];
      int res = (this->*ptr)(arg_obj, ret_obj);
      return(res);
    }
    else
    {
      return(0);
    }
  };

  ///////////////////////////////////////////////
  // plugin events
  ///////////////////////////////////////////////
  // wxWavE Widget events
  virtual long wxEVT_COMMAND_TEXT_UPDATED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_TEXT_ENTER(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_TEXT_URL(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_TEXT_MAXLEN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_COMMAND_MENU_SELECTED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_SLIDER_UPDATED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_RADIOBOX_SELECTED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_RADIOBUTTON_SELECTED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_COMMAND_BUTTON_CLICKED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_CHECKBOX_CLICKED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_CHOICE_SELECTED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_LISTBOX_SELECTED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_LISTBOX_DOUBLECLICKED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_CHECKLISTBOX_TOGGLED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_COMMAND_VLBOX_SELECTED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_COMBOBOX_SELECTED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_TOOL_RCLICKED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_TOOL_ENTER(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_SPINCTRL_UPDATED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_SOCKET(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_TIMER (const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_LEFT_DOWN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_LEFT_UP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_MIDDLE_DOWN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_MIDDLE_UP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_RIGHT_DOWN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_RIGHT_UP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_MOTION(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_ENTER_WINDOW(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_LEAVE_WINDOW(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_LEFT_DCLICK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_MIDDLE_DCLICK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_RIGHT_DCLICK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SET_FOCUS(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_KILL_FOCUS(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_CHILD_FOCUS(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_MOUSEWHEEL(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_NC_LEFT_DOWN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NC_LEFT_UP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NC_MIDDLE_DOWN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NC_MIDDLE_UP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NC_RIGHT_DOWN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NC_RIGHT_UP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NC_MOTION(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NC_ENTER_WINDOW(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NC_LEAVE_WINDOW(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NC_LEFT_DCLICK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NC_MIDDLE_DCLICK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NC_RIGHT_DCLICK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_CHAR(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_CHAR_HOOK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NAVIGATION_KEY(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_KEY_DOWN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_KEY_U(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_SET_CURSOR(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_SCROLL_TOP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLL_BOTTOM(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLL_LINEUP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLL_LINEDOWN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLL_PAGEUP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLL_PAGEDOWN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLL_THUMBTRACK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLL_THUMBRELEASE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLL_CHANGED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_SCROLLWIN_TOP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLLWIN_BOTTOM(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLLWIN_LINEUP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLLWIN_LINEDOWN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLLWIN_PAGEUP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLLWIN_PAGEDOWN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLLWIN_THUMBTRACK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SCROLLWIN_THUMBRELEASE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_SIZE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_MOVE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_CLOSE_WINDOW(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_END_SESSION(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_QUERY_END_SESSION(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_ACTIVATE_APP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_POWER(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_ACTIVATE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_CREATE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_DESTROY(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SHOW(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_ICONIZE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_MAXIMIZE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_MOUSE_CAPTURE_CHANGED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_PAINT(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_ERASE_BACKGROUND(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_NC_PAINT(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_PAINT_ICON(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_MENU_OPEN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_MENU_CLOSE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_MENU_HIGHLIGHT(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_CONTEXT_MENU(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SYS_COLOUR_CHANGED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_DISPLAY_CHANGED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_SETTING_CHANGED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_QUERY_NEW_PALETTE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_PALETTE_CHANGED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_JOY_BUTTON_DOWN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_JOY_BUTTON_UP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_JOY_MOVE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_JOY_ZMOVE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_DROP_FILES(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_DRAW_ITEM(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_MEASURE_ITEM(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMPARE_ITEM(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_INIT_DIALOG(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_UPDATE_UI(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_COMMAND_DIRPICKER_CHANGED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_FILEPICKER_CHANGED(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_COMMAND_LEFT_CLICK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_LEFT_DCLICK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_RIGHT_CLICK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_RIGHT_DCLICK(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_SET_FOCUS(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_KILL_FOCUS(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_COMMAND_ENTER(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  virtual long wxEVT_HELP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_DETAILED_HELP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

  // wxWavE custom events
  virtual long wxEVT_IDLE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_OPEN(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_CLOSE(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_CONNECT(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_DISCONNECT(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_PRESTEP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_STEP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_POSTSTEP(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_RENDER(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_DRAW2D(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};
  virtual long wxEVT_DRAW3D(const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);};

private:
  EvtMapT plg_functions;
};

#endif /* evtplugin_h_included */
