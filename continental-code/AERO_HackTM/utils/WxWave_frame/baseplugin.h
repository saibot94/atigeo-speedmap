#ifndef baseplugin_h_included
#define baseplugin_h_included

#include "envint.h"
#include "envargs.h"

#include <string>
#include <vector>
#include <list>
#include <map>


//////////////////////////////////////////////////////////
//           global callback data
//////////////////////////////////////////////////////////
extern std::string   wxPlg_Name;
extern std::string   wxPlg_Desc;


//////////////////////////////////////////////////////////
//           typedefs
//////////////////////////////////////////////////////////
typedef std::vector<std::string> StrVecT;
typedef std::list<std::string>   StrListT;


//////////////////////////////////////////////////////////
//           plugin interface class
//////////////////////////////////////////////////////////
/**
 * @class   CBasePlugIn
 * 
 * Dll base class
 *
 */
class CBasePlugIn
{
public:
  CBasePlugIn(const char* inst_name, wxPlg_IntFunT callback) {plg_inst_name = inst_name; plg_callback = callback;};
  virtual ~CBasePlugIn() {};

  ///////////////////////////////////////////////
  // plugin property functions
  ///////////////////////////////////////////////
  /**
   * Return the plugin name.
   */
  std::string GetName() {return(wxPlg_Name);};

  /**
   * Return the plugin description.
   */
  std::string GetDescription() {return(wxPlg_Desc);};

  /**
   * Return the plugin instance name.
   */
  std::string GetInstance() {return(plg_inst_name);}

  /**
   * Return the host application name.
   */
  std::string GetHostAppName()
  {
    // create argument and return object
    wxPlg_Obj* ret_obj = CreateObj(1);

    // create output arguments
    SetArg_String(ret_obj, "", 0, 1024);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "GetHostAppName", NULL, ret_obj);
    if(ret_state != 0) return("");

    // retrieve return arguments
    std::string host_name;
    GetArg_String(ret_obj, host_name, 0);

    // destroy argument and return object
    DestroyObj(ret_obj);

    return(host_name);
  };

  /**
   * Return complete configuration.
   */
  std::map<std::string, std::string> GetConfig()
  {
    return(plg_config);
  }

  /**
   * Return a specific configuration value.
   */
  std::string GetConfig(const std::string key)
  {
    std::map<std::string, std::string>::iterator iter = plg_config.find(key);
    if(iter == plg_config.end()) return("");
    return(iter->second);
  }

  /**
   * Configure dll.
   *
   * Configure dll specific features.
   *
   * @param   key           Configuration key.
   * @param   value         Configuration value.
   *
   * @return                0
   */
  virtual int Configure(const std::string key, const std::string value)
  {
    plg_config[key] = value;
    return(0);
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
  virtual int CallFunction(const std::string& UNUSEDARG(fun_name), const wxPlg_Obj* UNUSEDARG(arg_obj), wxPlg_Obj* UNUSEDARG(ret_obj)) {return(0);}

  ///////////////////////////////////////////////
  // variable pool access functions
  ///////////////////////////////////////////////
  /**
   * Get the number of variable groups.
   *
   * Get the number of all actual created wxWavE variable groups.\n
   * Internal used to allocate the string vector argument for VarGetGroupTable.
   *
   * @return             Number of variable groups.
   */
  long VarGetGroupTableSize()
  {
    // execute callback function
    return(*plg_callback)(plg_inst_name.c_str(), "VarGetGroupTableSize", NULL, NULL);
  }

  /**
   * Get all variable group names.
   *
   * Get the names of all actual created wxWavE variable groups.
   *
   * @param   grp_table  String vector reference to store the group names.
   */
  long VarGetGroupTable(StrVecT& grp_table)
  {
    long grp_table_size = VarGetGroupTableSize();
    if(grp_table_size < 1) return(-1);

    // create argument and return object
    wxPlg_Obj* ret_obj = CreateObj(grp_table_size);

    // create output arguments
    for(int index = 0; index < grp_table_size; index++)
    {
      SetArg_String(ret_obj, "", index);
    }

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarGetGroupTable", NULL, ret_obj);

    // retrieve return arguments
    if(ret_state > 0)
    {
      grp_table.resize(ret_state);
      for(int index = 0; index < ret_state; index++)
      {
        std::string grp_name;
        if(GetArg_String(ret_obj, grp_name, index))
        {
          grp_table[index] = grp_name;
        }
      }
      return(ret_state);
    }
    else
    {
      return(-1);
    }
  }

  /**
   * Get the number of number variables (values).
   *
   * Get the number of all actual created wxWavE number variables.\n
   * Internal used to allocate the string vector argument for VarGetValueTable.
   *
   * @param   grp_name   Count the variables of a specific variable group only or of all groups (grp_name == "")
   *
   * @return             Number of variables.
   */
  long VarGetValueTableSize(const std::string grp_name = "")
  {
    // create argument and return object
    wxPlg_Obj* arg_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, grp_name, 0);

    return(*plg_callback)(plg_inst_name.c_str(), "VarGetValueTableSize", arg_obj, NULL);
  }

  /**
   * Get number variable names.
   *
   * Get the names of all actual created wxWavE number variables.
   *
   * @param   val_table  String vector reference to store the variable names.
   * @param   grp_name   Get the variables of a specific variable group only or of all groups (grp_name == "")
   *
   * @return             Number of variables.
   */
  long VarGetValueTable(StrVecT& val_table, const std::string grp_name = "")
  {
    long val_table_size = VarGetValueTableSize(grp_name);
    if(val_table_size < 1) return(-1);

    // create argument and return object
    wxPlg_Obj* ret_obj = CreateObj(val_table_size);

    // create output arguments
    for(int index = 0; index < val_table_size; index++)
    {
      SetArg_String(ret_obj, "", index);
    }

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarGetValueTable", NULL, ret_obj);

    // retrieve return arguments
    if(ret_state > 0)
    {
      val_table.resize(ret_state);
      for(int index = 0; index < ret_state; index++)
      {
        std::string grp_name;
        if(GetArg_String(ret_obj, grp_name, index))
        {
          val_table[index] = grp_name;
        }
      }
      return(ret_state);
    }
    else
    {
      return(-1);
    }
  }

  /**
   * Get the number of string variables.
   *
   * Get the number of all actual created wxWavE string variables.\n
   * Internal used to allocate the string vector argument for VarGetStringTable.
   *
   * @param   grp_name   Count the variables of a specific variable group only or of all groups (grp_name == "")
   *
   * @return             Number of variables.
   */
  long VarGetStringTableSize(const std::string grp_name = "")
  {
    // create argument and return object
    wxPlg_Obj* arg_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, grp_name, 0);

    return(*plg_callback)(plg_inst_name.c_str(), "VarGetStringTableSize", arg_obj, NULL);
  }

  /**
   * Get string variable names.
   *
   * Get the names of all actual created wxWavE string variables.
   *
   * @param   str_table  String vector reference to store the variable names.
   * @param   grp_name   Get the variables of a specific variable group only or of all groups (grp_name == "")
   *
   * @return             Number of variables.
   */
  long VarGetStringTable(StrVecT& str_table, const std::string grp_name = "")
  {
    long str_table_size = VarGetStringTableSize(grp_name);
    if(str_table_size < 1) return(-1);

    // create argument and return object
    wxPlg_Obj* ret_obj = CreateObj(str_table_size);

    // create output arguments
    for(int index = 0; index < str_table_size; index++)
    {
      SetArg_String(ret_obj, "", index);
    }

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarGetStringTable", NULL, ret_obj);

    // retrieve return arguments
    if(ret_state > 0)
    {
      str_table.resize(ret_state);
      for(int index = 0; index < ret_state; index++)
      {
        std::string grp_name;
        if(GetArg_String(ret_obj, grp_name, index))
        {
          str_table[index] = grp_name;
        }
      }
      return(ret_state);
    }
    else
    {
      return(-1);
    }
  }

  /**
   * Create a number variable.
   *
   * Create a single number variable in the wxWavE variable pool.
   *
   * @param   var_name    Variable name.
   * @param   grp_name    Group name (empty strings will use wxPlg_Name as group name).
   * @param   var_unit    Variable unit.
   * @param   var_comment Variable comment.
   * @param   var_length  Variable length (1 == scalar variable, > 1 == vector variable).
   * @param   var_init    Variable initialization value (in case of vector variables all values will be initialized).
   *
   * @return              TRUE or FALSE.
   */
  bool VarCreateValue(const std::string& var_name, const std::string& grp_name = "", const std::string var_unit = "", const std::string var_comment = "", long var_length = 1, double var_init = 0.0)
  {
    // check grp_name
    std::string group_name = grp_name;
    if(grp_name.empty())
    {
      group_name = GetName();
    }

    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(6);

    // create input arguments
    SetArg_String(arg_obj, var_name,    0);
    SetArg_String(arg_obj, group_name,  1);
    SetArg_String(arg_obj, var_unit,    2);
    SetArg_String(arg_obj, var_comment, 3);
    SetArg_sLong(arg_obj,  var_length,  4);
    SetArg_Double(arg_obj, var_init,    5);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarCreateValue", arg_obj, NULL);

    // destroy argument object
    DestroyObj(arg_obj);

    return(ret_state == 0);
  }

  /**
   * Create a string variable.
   *
   * Create a single string variable in the wxWavE variable pool.
   *
   * @param   var_name    Variable name.
   * @param   grp_name    Group name (empty strings will use wxPlg_Name as group name).
   * @param   var_unit    Variable unit.
   * @param   var_comment Variable comment.
   * @param   var_length  Variable length (1 == scalar variable, > 1 == vector variable).
   * @param   var_init    Variable initialization string (in case of vector variables all values will be initialized).
   *
   * @return              TRUE or FALSE.
   */
  bool VarCreateString(const std::string& var_name, const std::string& grp_name = "", const std::string var_unit = "", const std::string var_comment = "", long var_length = 1, std::string var_init = "")
  {
    // check grp_name
    std::string group_name = grp_name;
    if(grp_name.empty())
    {
      group_name = GetName();
    }

    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(6);

    // create input arguments
    SetArg_String(arg_obj, var_name,    0);
    SetArg_String(arg_obj, group_name,  1);
    SetArg_String(arg_obj, var_unit,    2);
    SetArg_String(arg_obj, var_comment, 3);
    SetArg_sLong(arg_obj,  var_length,  4);
    SetArg_String(arg_obj, var_init,    5);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarCreateString", arg_obj, NULL);

    // destroy argument object
    DestroyObj(arg_obj);

    return(ret_state == 0);
  }

  /**
   * Destroy a variable.
   *
   * Removes a single variable from the wxWavE variable pool. The group name is needed because a variable
   * can be attached to more then one group. In this case the variable still remains in the pool until
   * it's removed from all variable groups.
   *
   * @param   var_name    Variable name.
   * @param   grp_name    Group name.
   *
   * @return              TRUE or FALSE.
   */
  bool VarDestroy(const std::string& var_name, const std::string& grp_name)
  {
    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(2);

    // create input arguments
    SetArg_String(arg_obj, var_name,  0);
    SetArg_String(arg_obj, grp_name,  1);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarDestroy", arg_obj, NULL);
    if(ret_state != 0) return(false);

    // destroy argument object
    DestroyObj(arg_obj);

    return(true);
  };

  /**
   * Variable exists.
   *
   * Check whether a single variable exists in the wxWavE variable pool or not.
   *
   * @param   var_name    Variable name.
   *
   * @return              TRUE or FALSE.
   */
  bool VarExist(const std::string& var_name)
  {
    // create argument and return object
    wxPlg_Obj* arg_obj = CreateObj(1);
    wxPlg_Obj* ret_obj = CreateObj(1);
    
    // create input arguments
    SetArg_String(arg_obj, var_name, 0);

    // create output arguments
    SetArg_Bool(ret_obj, false, 0);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarExist", arg_obj, ret_obj);
    if(ret_state != 0) return(false);

    // retrieve return arguments
    bool var_exists = false;
    GetArg_Bool(ret_obj, var_exists, 0);
    
    // destroy argument and return object
    DestroyObj(arg_obj);
    DestroyObj(ret_obj);

    return(var_exists);
  };

  /**
   * Variable is value.
   *
   * Check whether a single variable is a number variable or not.
   *
   * @param   var_name    Variable name.
   *
   * @return              TRUE or FALSE.
   */
  bool VarIsValue(const std::string& var_name)
  {
    // create argument and return object
    wxPlg_Obj* arg_obj = CreateObj(1);
    wxPlg_Obj* ret_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, var_name,  0);

    // create output arguments
    SetArg_Bool(ret_obj, false,  0);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarIsValue", arg_obj, ret_obj);
    if(ret_state != 0) return(false);

    // retrieve return arguments
    bool var_is_value = false;
    GetArg_Bool(ret_obj, var_is_value, 0);

    // destroy argument and return object
    DestroyObj(arg_obj);
    DestroyObj(ret_obj);

    return(var_is_value);
  };

  /**
   * Variable is string.
   *
   * Check whether a single variable is a string variable or not.
   *
   * @param   var_name    Variable name.
   *
   * @return              TRUE or FALSE.
   */
  bool VarIsString(const std::string& var_name)
  {
    // create argument and return object
    wxPlg_Obj* arg_obj = CreateObj(1);
    wxPlg_Obj* ret_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, var_name,  0);

    // create output arguments
    SetArg_Bool(ret_obj, false,  0);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarIsString", arg_obj, ret_obj);
    if(ret_state != 0) return(false);

    // retrieve return arguments
    bool var_is_string = false;
    GetArg_Bool(ret_obj, var_is_string, 0);

    // destroy argument and return object
    DestroyObj(arg_obj);
    DestroyObj(ret_obj);

    return(var_is_string);
  };

  /**
   * Get variable length.
   *
   * Get the variable length of a single variable.
   *
   * @param   var_name    Variable name.
   *
   * @return              Variable length (1 == scalar variable, > 1 == vector variable).
   */
  long VarGetLength(const std::string& var_name)
  {
    // create argument and return object
    wxPlg_Obj* arg_obj = CreateObj(1);
    wxPlg_Obj* ret_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, var_name,  0);

    // create output arguments
    SetArg_sLong(ret_obj, 0, 0);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarGetLength", arg_obj, ret_obj);
    // unfortunatly old wxWavE versions return variable length in return value AND ret_obj
    // so do not check this for equal zero
    //if(ret_state != 0) return(0);
    ret_state = ret_state;

    // retrieve return arguments
    long var_length = 0;
    GetArg_sLong(ret_obj, var_length, 0);

    // destroy argument and return object
    DestroyObj(arg_obj);
    DestroyObj(ret_obj);

    return(var_length);
  };

  /**
   * Set number variable.
   *
   * Set the value of a number variable on specified index (in case of vector variable).
   *
   * @param   var_name    Variable name.
   * @param   value_in    Variable value.
   * @param   var_index   Variable index.
   *
   * @return              TRUE or FALSE.
   */
  bool VarSetValue(const std::string& var_name, double value_in, int var_index = 0)
  {
    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(3);

    // create input arguments
    SetArg_String(arg_obj, var_name,  0);
    SetArg_Double(arg_obj, value_in,  1);
    SetArg_sLong( arg_obj, var_index, 2);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarSetValue", arg_obj, NULL);

    // destroy argument object
    DestroyObj(arg_obj);

    return(ret_state == 0);
  };
  
  /**
   * Set number variable array.
   *
   * Set the value of a complete number vector variable.
   *
   * @param   var_name      Variable name.
   * @param   val_array     Variable value array (created by caller).
   * @param   array_length  Length of the value array.
   *
   * @return                Number of succesful written values.
   */
  long VarSetValueArray(const std::string& var_name, const double* val_array, const int array_length)
  {
    long val_length = VarGetLength(var_name);
    if(val_length < 1) return(-1);

    long ret_state = 0;
    for(int var_index = 0; (var_index < array_length) && (var_index < val_length); var_index++)
    {
      if(VarSetValue(var_name, val_array[var_index], var_index))
      {
        ret_state++;
      }
    }
    return(ret_state);
  };

  /**
   * Get number variable.
   *
   * Get the value of a number variable on specified index (in case of vector variable).
   *
   * @param   var_name    Variable name.
   * @param   value_out   Value reference for storing the value.
   * @param   var_index   Variable index.
   *
   * @return              TRUE or FALSE.
   */
  bool VarGetValue(const std::string& var_name, double* value_out, int var_index = 0)
  {
    if(!value_out) return(false);

    // create argument and return object
    wxPlg_Obj* arg_obj = CreateObj(2);
    wxPlg_Obj* ret_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, var_name,  0);
    SetArg_sLong( arg_obj, var_index, 1);

    // create output arguments
    SetArg_Double(ret_obj, 0.0, 0);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarGetValue", arg_obj, ret_obj);

    // retrieve return arguments
    GetArg_Double(ret_obj, *value_out, 0);

    // destroy argument and return object
    DestroyObj(arg_obj);
    DestroyObj(ret_obj);

    return(ret_state == 0);
  };

  /**
   * Get number variable.
   *
   * Get the value of a number variable on specified index (in case of vector variable).
   *
   * @param   var_name    Variable name.
   * @param   var_index   Variable index.
   *
   * @return              Variable value.
   */
  double VarGetValue(const std::string& var_name, int var_index = 0)
  {
    double value_out = 0.0;
    VarGetValue(var_name, &value_out, var_index);
    return(value_out);
  };

  /**
   * Get number variable array.
   *
   * Set the value of a complete number vector variable.
   *
   * @param   var_name      Variable name.
   * @param   val_array     Variable value array (has to be created by caller !).
   * @param   array_length  Length of the value array.
   *
   * @return                Number of succesful read values.
   */
  long VarGetValueArray(const std::string& var_name, double* val_array, const int array_length)
  {
    long val_length = VarGetLength(var_name);
    if(val_length < 1) return(-1);

    long ret_state = 0;
    for(int var_index = 0; (var_index < array_length) && (var_index < val_length); var_index++)
    {
      double value_out = 0.0;
      if(VarGetValue(var_name, &value_out, var_index))
      {
        val_array[var_index] = value_out;
        ret_state++;
      }
    }
    return(ret_state);
  };

  /**
   * Set string variable.
   *
   * Set the value of a string variable on specified index (in case of vector variable).
   *
   * @param   var_name    Variable name.
   * @param   value_in    Variable string.
   * @param   var_index   Variable index.
   *
   * @return              TRUE or FALSE.
   */
  bool VarSetString(const std::string& var_name, const std::string& value_in, int var_index = 0)
  {
    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(3);

    // create input arguments
    SetArg_String(arg_obj, var_name,  0);
    SetArg_String(arg_obj, value_in,  1);
    SetArg_sLong( arg_obj, var_index, 2);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarSetString", arg_obj, NULL);

    // destroy argument object
    DestroyObj(arg_obj);

    return(ret_state == 0);
  };
  
  /**
   * Get string variable.
   *
   * Get the value of a string variable on specified index (in case of vector variable).
   *
   * @param   var_name    Variable name.
   * @param   value_out   Value reference for storing the string.
   * @param   var_index   Variable index.
   *
   * @return              TRUE or FALSE.
   */
  bool VarGetString(const std::string& var_name, std::string* value_out, int var_index = 0)
  {
    if(!value_out) return(false);

    // create argument and return object
    wxPlg_Obj* arg_obj = CreateObj(2);
    wxPlg_Obj* ret_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, var_name,  0);
    SetArg_sLong( arg_obj, var_index, 1);

    // create output arguments
    SetArg_String(ret_obj, "", 0, 1024);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "VarGetString", arg_obj, ret_obj);

    // retrieve return arguments
    GetArg_String(ret_obj, *value_out, 0);

    // destroy argument and return object
    DestroyObj(arg_obj);
    DestroyObj(ret_obj);

    return(ret_state == 0);
  };

  /**
   * Get string variable.
   *
   * Get the value of a string variable on specified index (in case of vector variable).
   *
   * @param   var_name    Variable name.
   * @param   var_index   Variable index.
   *
   * @return              Variable value.
   */
  std::string VarGetString(const std::string& var_name, int var_index = 0)
  {
    std::string value_str = "";
    VarGetString(var_name, &value_str, var_index);
    return(value_str);
  };

  ///////////////////////////////////////////////
  // widget access functions
  ///////////////////////////////////////////////
  /**
   * Create an object.
   *
   * Create a wxWavE object (widget) on the specified object path (e.g. 'Window_01/Button_01').\n
   * The object type ('Button', 'Slider' ..) and the associated properties are defined in the
   * configuration string 'obj_config'. The configuraion string contains tupels of property keys
   * and property values. Every property tuple is seperated by newline.\n\n
   * Example:\n\n
   * // create a button in window 'Window_01', position = 10.0/10.0, width/height = 30.0/10.0, title = 'HELLO WORLD'\n
   * std::string obj_config = "Type Button\nSize 10.0 10.0 30.0 20.0\nTitle \"HELLO WORLD\"";\n
   * bool success = ObjCreate("Window_01/Button_01', obj_config);
   *
   * @param   obj_path    Object path.
   * @param   obj_config  Object configuration.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjCreate(const std::string& obj_path, const std::string& obj_config)
  {
    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(2);

    // create input arguments
    SetArg_String(arg_obj, obj_path,   0);
    SetArg_String(arg_obj, obj_config, 1);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "ObjCreate", arg_obj, NULL);

    // destroy argument object
    DestroyObj(arg_obj);

    return(ret_state == 0);
  }

  /**
   * Destroy the dll object.
   *
   * Destroy the dll object. This will finalize and unload the dll.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjDestroy()
  {
    return(ObjDestroy(GetInstance()));
  }

  /**
   * Destroy the specified object.
   *
   * Destroy the object of the specified object path.
   *
   * @param   obj_path    Object path.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjDestroy(const std::string& obj_path)
  {
    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, obj_path,   0);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "ObjDestroy", arg_obj, NULL);

    // destroy argument object
    DestroyObj(arg_obj);

    return(ret_state == 0);
  }

  /**
   * Open the dll object.
   *
   * Open the dll object.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjOpen()
  {
    return(ObjOpen(GetInstance()));
  }

  /**
   * Close the dll object.
   *
   * Close the dll object.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjClose()
  {
    return(ObjClose(GetInstance()));
  }

  /**
   * Open the specified object.
   *
   * Open the object of the specified object path.
   *
   * @param   obj_path    Object path.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjOpen(const std::string& obj_path)
  {
    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, obj_path,   0);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "ObjOpen", arg_obj, NULL);

    // destroy argument object
    DestroyObj(arg_obj);

    return(ret_state == 0);
  }

  /**
   * Close the specified object.
   *
   * Close the object of the specified object path.
   *
   * @param   obj_path    Object path.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjClose(const std::string& obj_path)
  {
    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, obj_path,   0);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "ObjClose", arg_obj, NULL);

    // destroy argument object
    DestroyObj(arg_obj);

    return(ret_state == 0);
  }

  /**
   * Show the dll object.
   *
   * Show the dll object.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjShow()
  {
    return(ObjShow(GetInstance()));
  }

  /**
   * Hide the dll object.
   *
   * Show the dll object.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjHide()
  {
    return(ObjHide(GetInstance()));
  }

  /**
   * Show the specified object.
   *
   * Show the object of the specified object path.
   *
   * @param   obj_path    Object path.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjShow(const std::string& obj_path)
  {
    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, obj_path,   0);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "ObjShow", arg_obj, NULL);

    // destroy argument object
    DestroyObj(arg_obj);

    return(ret_state == 0);
  }

  /**
   * Hide the specified object.
   *
   * Hide the object of the specified object path.
   *
   * @param   obj_path    Object path.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjHide(const std::string& obj_path)
  {
    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, obj_path,   0);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "ObjHide", arg_obj, NULL);

    // destroy argument object
    DestroyObj(arg_obj);

    return(ret_state == 0);
  }

  /**
   * Set a property of the dll object.
   *
   * Set a specified property of the dll object to 'prop_value'.
   *
   * @param   prop_key    Property key.
   * @param   prop_value  Property value.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjSet(const std::string& prop_key, const std::string& prop_value)
  {
    return(ObjSet(GetInstance(), prop_key, prop_value));
  }

  /**
   * Get a property of the dll object.
   *
   * Get a specified property of the dll object.
   *
   * @param   prop_key    Property key.
   * @param   prop_value  Pointer to property value.
   * @return              TRUE or FALSE.
   */
  bool ObjGet(const std::string& prop_key, std::string* prop_value)
  {
    return(ObjGet(GetInstance(), prop_key, prop_value));
  }

  /**
   * Get a property of the dll object.
   *
   * Get a specified property of the dll object.
   *
   * @param   prop_key    Property key.
   *
   * @return  prop_value  Property value.
   */
  std::string ObjGet(const std::string& prop_key)
  {
    std::string prop_value = "";
    bool ret_state = ObjGet(prop_key, &prop_value);
    if(ret_state == false) return("");
    return(prop_value);
  }

  /**
   * Set a property of the specified object.
   *
   * Set a specified property of the specified object to 'prop_value'.
   *
   * @param   obj_path    Object path.
   * @param   prop_key    Property key.
   * @param   prop_value  Property value.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjSet(const std::string& obj_path, const std::string& prop_key, std::string  prop_value)
  {
    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(3);

    // create input arguments
    SetArg_String(arg_obj, obj_path,   0);
    SetArg_String(arg_obj, prop_key,   1);
    SetArg_String(arg_obj, prop_value, 2);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "ObjSet", arg_obj, NULL);

    // destroy argument object
    DestroyObj(arg_obj);

    return(ret_state == 0);
  }

  /**
   * Get a property of the specified object.
   *
   * Get a specified property of the specified object.
   *
   * @param   obj_path    Object path.
   * @param   prop_key    Property key.
   * @param   prop_value  Pointer to property value.
   *
   * @return              TRUE or FALSE.
   */
  bool ObjGet(const std::string& obj_path, const std::string& prop_key, std::string* prop_value)
  {
    // create argument and return object
    wxPlg_Obj* arg_obj = CreateObj(2);
    wxPlg_Obj* ret_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, obj_path,   0);
    SetArg_String(arg_obj, prop_key,   1);

    // create output arguments
    SetArg_String(ret_obj, "" , 0, 1024);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "ObjGet", arg_obj, ret_obj);

    // retrieve return arguments
    GetArg_String(ret_obj, *prop_value, 0);

    // destroy argument and return object
    DestroyObj(arg_obj);
    DestroyObj(ret_obj);

    return(ret_state == 0);
  }

  /**
   * Get a property of the specified object.
   *
   * Get a specified property of the specified object.
   *
   * @param   obj_path    Object path.
   * @param   prop_key    Property key.
   *
   * @return  prop_value  Property value.
   */
  std::string ObjGet(const std::string& obj_path, const std::string& prop_key)
  {
    std::string prop_value = "";
    bool ret_state = ObjGet(obj_path, prop_key, &prop_value);
    if(ret_state == false) return("");
    return(prop_value);
  }

  ///////////////////////////////////////////////
  // common functions
  ///////////////////////////////////////////////
  /**
   * Execute host application command.
   *
   * Execute a host application internal string command (experts only).
   *
   * @param   command     Command string.
   * @param   answer      Pointer for answer string (can be NULL).
   *
   * @return              TRUE or FALSE.
   */
  bool ExecCommand(const std::string& command, std::string* answer = NULL)
  {
    // create argument and return object
    wxPlg_Obj* arg_obj = CreateObj(1);
    wxPlg_Obj* ret_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, command, 0);

    // create output arguments
    SetArg_String(ret_obj, "" , 0, 1024);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "ExecCommand", arg_obj, ret_obj);

    // retrieve return arguments
    if(answer) GetArg_String(ret_obj, *answer, 0);

    // destroy argument and return object
    DestroyObj(arg_obj);
    DestroyObj(ret_obj);

    return(ret_state == 0);
  }

  /**
   * Print string to console.
   *
   * Print a string in host application's log window.
   *
   * @param   msg_str     String to print.
   *
   * @return              TRUE or FALSE.
   */
  bool TextPrint2Con(const std::string& msg_str)
  {
    // create argument object
    wxPlg_Obj* arg_obj = CreateObj(1);

    // create input arguments
    SetArg_String(arg_obj, msg_str, 0);

    // execute callback function
    long ret_state = (*plg_callback)(plg_inst_name.c_str(), "TextPrint2Con", arg_obj, NULL);

    // destroy argument object
    DestroyObj(arg_obj);

    return(ret_state == 0);
  }

protected:
  std::string                         plg_inst_name;
  wxPlg_IntFunT                       plg_callback;
  std::map<std::string, std::string>  plg_config;
};

#endif /* baseplugin_h_included */
