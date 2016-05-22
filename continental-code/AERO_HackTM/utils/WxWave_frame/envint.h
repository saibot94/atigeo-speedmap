#ifndef envint_h_included
#define envint_h_included


#ifdef WXWPLUGIN_EXPORTS
#define WXWPLUGIN_API __declspec(dllexport)
#else
#define WXWPLUGIN_API __declspec(dllimport)
#endif

/**
 * Environment interface version (do not change).
 */
#define EVT_PLG_VERSION 2.2

/**
 * Predefined types for common function arguments 'wxPlg_Val'.
 */
enum IntValType
{
  ivt_none  = 0,
  ivt_uchar,
  ivt_schar,
  ivt_ushort,
  ivt_sshort,
  ivt_ulong,
  ivt_slong,
  ivt_ulonglong,
  ivt_slonglong,
  ivt_float,
  ivt_double,
  ivt_string,
  ivt_bool,
  ivt_cimg,
  ivt_devicecontext
};

/**
 * Interface argument structure.
 *
 * This is the structure of a single argument. It can be attached to an argument object 'wxPlg_Obj'. An argument can store
 * up to 'length' values of type 'type' (see enum IntValType).
 *
 */
struct SIntVal
{
  void*           value;
  enum IntValType type;
  long            length;
};

/**
 * Interface argument object.
 *
 * This is the structure of a argument object. An object can store
 * up to 'length' arguments of type 'SIntVal'.
 *
 */
struct SIntObj
{
  struct SIntVal* values;
  long            length;
  // for future extensions
  long            reserved1;
  long            reserved2;
  long            reserved3;
  long            reserved4;
};

typedef struct SIntVal wxPlg_Val;
typedef struct SIntObj wxPlg_Obj;

/*
 * Dll interface functions.
 *
 * These function names are checked when host application is loading the dll.
 *
 */
extern "C"
{
  typedef double (*wxPlg_GetVersionT)           ();
  typedef long   (*wxPlg_GetNameT)              (char* pName, long max_len);
  typedef size_t (*wxPlg_GetNameLengthT)        ();
  typedef long   (*wxPlg_GetDescriptionT)       (char* pDesc, long max_len);
  typedef size_t (*wxPlg_GetDescriptionLengthT) ();
  typedef long   (*wxPlg_IntFunT)               (const char* inst_name, const char* fun_name, const wxPlg_Obj* arg_obj, wxPlg_Obj* ret_obj);
  typedef long   (*wxPlg_InitializeT)           (const char* inst_name, wxPlg_IntFunT wxw_callback);
  typedef long   (*wxPlg_FinalizeT)             (const char* inst_name);
  typedef long   (*wxPlg_ConfigureT)            (const char* inst_name, const char* key, const char* value);

  /**
   * Get interface version.
   *
   * @return                Version number of the plugin.
   */
  WXWPLUGIN_API double wxPlg_GetVersion();

  /**
   * Get plugin name (will be defined by dll user).
   *
   * @param   pName         Pointer to char array to store the name.
   * @param   max_len       Length of the passed char array.
   *
   * @return                0
   */
  WXWPLUGIN_API long wxPlg_GetName(char* pName, long max_len);

  /**
   * Get the length of the plugin name (will be defined by dll user).
   *
   * @return  The size of the plugin name. 
  **/
  WXWPLUGIN_API size_t wxPlg_GetNameLength();

  /**
   * Get plugin description (will be defined by dll user).
   *
   * @param   pDesc         Pointer to char array to store the description.
   * @param   max_len       Length of the passed char array.
   *
   * @return                0
   */
  WXWPLUGIN_API long wxPlg_GetDescription(char* pDesc, long max_len);

  /**
   * @brief Get the size of the plugin description. 
   *
   * @return  The size of the plugin description. 
  **/
  WXWPLUGIN_API size_t wxPlg_GetDescriptionLength();

  /**
   * Initialize dll. Will be called after loading the dll by host application (for internal use).
   *
   * @param   inst_name     Unique instance name specified by the host application that is using the callback dll.
   * @param   callback      Pointer to the host application internal callback function for using these functions from within the dll.
   *
   * @return                0
   */
  WXWPLUGIN_API long wxPlg_Initialize(const char* inst_name, wxPlg_IntFunT callback);

  /**
   * Finalize dll. Will be called before unloading the dll by host application (for internal use).
   *
   * @param   inst_name     Unique instance name specified by the host application that is using the callback dll.
   *
   * @return                0
   */
  WXWPLUGIN_API long wxPlg_Finalize(const char* inst_name);

  /**
   * Configure dll. Will be called after Initialize to configure dll specific features.
   *
   * @param   inst_name     Unique instance name specified by the host application that is using the callback dll.
   * @param   key           Configuration key.
   * @param   value         Configuration value.
   *
   * @return                0
  **/
  WXWPLUGIN_API long wxPlg_Configure(const char* inst_name, const char* key, const char* value);

  /**
   * Execute single interface function.
   *
   * This is the flexible dll function interface. Functions will be hold by a function hash inside the dll and
   * are all of the same function type (argument and return values).\n
   * Every single interface function has to parse the argument object 'arg_obj' itself and has to put the 
   * function results in the return object 'ret_obj' (see envargs.h for helper functions).\n\n
   * The argument objects 'arg_obj' and 'ret_obj' are created by the caller and will be destroyed by the
   * caller after calling the function. This avoids heap memory allocation conflicts.
   *
   * @param   inst_name     Unique instance name specified by the host application that is using the callback dll.
   * @param   fun_name      Function name to call.
   * @param   arg_obj       Pointer of the input argument object (allocated by caller !)
   * @param   ret_obj       Pointer of the return argument object (allocated by caller !)
   *
   * @return                Depends from the function implementation.
   */
  WXWPLUGIN_API long wxPlg_IntFun(const char* inst_name, const char* fun_name, const wxPlg_Obj* arg_obj, wxPlg_Obj* ret_obj);
}

#endif /* envint_h_included */
