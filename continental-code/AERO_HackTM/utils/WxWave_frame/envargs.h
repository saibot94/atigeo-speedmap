#ifndef envargs_h_included
#define envargs_h_included

#include "envint.h"
#include <string>

#include "cimg.h"
typedef cimg_library::CImg<unsigned char>  cimg_t;
typedef cimg_t*                            cimg_ptr;
typedef void*                              devicecontext_ptr;

// warning C4996: 'strncpy': This function or variable may be unsafe ..
#pragma warning(disable : 4996)

// use this macro to mark unused arguments
#define UNUSEDARG(arg)

//////////////////////////////////////////////////////////
//        INTERFACE OBJECT / ARGUMENT HANDLING
//////////////////////////////////////////////////////////
/**
 * Creates a callback function object.
 *
 * Creates a callback function object of size 'size'.
 * The object has to be destroyed with DestroyObj after usage.
 *
 * @param   size       Defines the number of values of type wxPlg_Val
 * @return             Pointer to created argument or NULL.
 */
inline wxPlg_Obj* CreateObj(const int size)
{
  wxPlg_Obj* pArg_obj = new wxPlg_Obj;
  if(!pArg_obj) return(NULL);
  wxPlg_Val* pArg_val = new wxPlg_Val[size];
  if(pArg_val)
  {
    pArg_obj->values = pArg_val;
    pArg_obj->length = size;
    for(int index = 0; index < size; index++)
    {
      pArg_obj->values[index].value  = NULL;
      pArg_obj->values[index].type   = ivt_none;
      pArg_obj->values[index].length = 0;
    }
  }
  return(pArg_obj);
};

/**
 * Check for valid object argument.
 *
 * Checks a single argument of the given argument object of consistency.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   index      Index of argument to check.
 * @return             TRUE or FALSE
 */
inline bool ValidArg(const wxPlg_Obj* pArg_obj, const int index)
{
  if(!pArg_obj)                  return(false);
  if(pArg_obj->length < index+1) return(false);
  if(!pArg_obj->values)          return(false);
  return(true);
}

/**
 * Destroy an object argument.
 *
 * Destroys a single argument of the given argument object
 * and free the allocated memory.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   index      Index of argument to delete.
 * @return             TRUE or FALSE
 */
inline bool DestroyArg(const wxPlg_Obj* pArg_obj, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  if(pArg_obj->values[index].value && (pArg_obj->values[index].type != ivt_none))
  {
    if(pArg_obj->values[index].length == 1)
    {
      delete pArg_obj->values[index].value;
    }
    else
    {
      if(pArg_obj->values[index].length > 1)
      {
        delete []pArg_obj->values[index].value;
      }
    }
    pArg_obj->values[index].value = NULL;
    pArg_obj->values[index].type  = ivt_none;
  }
  return(true);
}

/**
 * Create an object argument.
 *
 * Creates a single argument and attach it to the given argument object.
 * Allocates the needed memory depending from parameter type and length.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   type       Argument type. Available types are:\n
 *                        ivt_uchar         - unsigned char\n
 *                        ivt_schar         - signed char\n
 *                        ivt_ushort        - unsigned short\n
 *                        ivt_sshort        - signed short\n
 *                        ivt_ulong         - unsigned long\n
 *                        ivt_slong         - signed long\n
 *                        ivt_ulonglong     - unsigned long long\n
 *                        ivt_slonglong     - signed long long\n
 *                        ivt_float         - float\n
 *                        ivt_double        - double\n
 *                        ivt_string        - string (char array terminated by zero)\n
 *                        ivt_bool          - bool\n
 *                        ivt_cimg          - CImg image\n
 *                        ivt_devicecontext - device context\n
 * @param   index      Index of argument to create.
 * @param   length     Length of the argument to create.
 * @return             TRUE or FALSE
 */
inline bool CreateArg(const wxPlg_Obj* pArg_obj, enum IntValType type, const int index, const int length = 1)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  if(!pArg_obj->values[index].value || (pArg_obj->values[index].type == ivt_none))
  {
    DestroyArg(pArg_obj, index);
    switch(type)
    {
    case ivt_uchar:
      pArg_obj->values[index].value  = new unsigned char[length];
      break;
    case ivt_schar:
      pArg_obj->values[index].value  = new signed char[length];
      break;
    case ivt_ushort:
      pArg_obj->values[index].value  = new unsigned short[length];
      break;
    case ivt_sshort:
      pArg_obj->values[index].value  = new signed short[length];
      break;
    case ivt_ulong:
      pArg_obj->values[index].value  = new unsigned long[length];
      break;
    case ivt_slong:
      pArg_obj->values[index].value  = new signed long[length];
      break;
    case ivt_ulonglong:
      pArg_obj->values[index].value  = new unsigned long long[length];
      break;
    case ivt_slonglong:
      pArg_obj->values[index].value  = new signed long long[length];
      break;
    case ivt_float:
      pArg_obj->values[index].value  = new float[length];
      break;
    case ivt_double:
      pArg_obj->values[index].value  = new double[length];
      break;
    case ivt_string:
      pArg_obj->values[index].value  = new char[length];
      break;
    case ivt_bool:
      pArg_obj->values[index].value  = new bool[length];
      break;
    case ivt_cimg:
      pArg_obj->values[index].value  = new cimg_ptr;
      break;
    case ivt_devicecontext:
      pArg_obj->values[index].value  = new devicecontext_ptr;
      break;
    default:
      pArg_obj->values[index].value  = NULL;
      pArg_obj->values[index].type   = ivt_none;
      pArg_obj->values[index].length = 0;
      return(false);
    }
    pArg_obj->values[index].type   = type;
    pArg_obj->values[index].length = length;
  }
  return(true);
}

/**
 * Destroy a callback function object.
 *
 * Destroys the given object and free the 
 * allocated memory of all attached arguments.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @return             TRUE or FALSE
 */
inline bool DestroyObj(wxPlg_Obj* pArg_obj)
{
  if(!pArg_obj) return(false);
  if((pArg_obj->length > 0) && pArg_obj->values)
  {
    for(int index = 0; index < pArg_obj->length; index++)
    {
      DestroyArg(pArg_obj, index);
    }
    if(pArg_obj->length == 1) delete pArg_obj->values;
    if(pArg_obj->length >  1) delete []pArg_obj->values;
  }
  delete pArg_obj;
  return(true);
};

/**
 * Get callback function object size.
 *
 * Retrieves the number of attached arguments
 * of the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @return             Number of attached arguments.
 */
inline long GetObjSize(const wxPlg_Obj* pArg_obj)
{
  if(!pArg_obj) return(0);
  if(!pArg_obj->values) return(0);
  return(pArg_obj->length);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: BOOL
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'bool'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_Bool(const wxPlg_Obj* pArg_obj, const bool a, const int index)
{
  if(CreateArg(pArg_obj, ivt_bool, index))
  {
    ((bool*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'bool'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_Bool(const wxPlg_Obj* pArg_obj, bool& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_bool)
  {
    a = ((bool*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'bool'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_Bool(const wxPlg_Obj* pArg_obj, const bool* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(CreateArg(pArg_obj, ivt_bool, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((bool*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'bool'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_Bool(const wxPlg_Obj* pArg_obj, bool* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_bool)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((bool*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: uCHAR
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'unsigned char'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_uChar(const wxPlg_Obj* pArg_obj, const unsigned char a, const int index)
{
  if(CreateArg(pArg_obj, ivt_uchar, index))
  {
    ((unsigned char*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'unsigned char'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_uChar(const wxPlg_Obj* pArg_obj, unsigned char& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_uchar)
  {
    a = ((unsigned char*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'unsigned char'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_uChar(const wxPlg_Obj* pArg_obj, const unsigned char* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(CreateArg(pArg_obj, ivt_uchar, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((unsigned char*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'unsigned char'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_uChar(const wxPlg_Obj* pArg_obj, unsigned char* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_uchar)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((unsigned char*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: sCHAR
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'signed char'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_sChar(const wxPlg_Obj* pArg_obj, const signed char a, const int index)
{
  if(CreateArg(pArg_obj, ivt_schar, index))
  {
    ((signed char*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'signed char'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_sChar(const wxPlg_Obj* pArg_obj, signed char& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_schar)
  {
    a = ((signed char*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'signed char'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_sChar(const wxPlg_Obj* pArg_obj, const signed char* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(CreateArg(pArg_obj, ivt_schar, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((signed char*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'signed char'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_sChar(const wxPlg_Obj* pArg_obj, signed char* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_schar)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((signed char*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: uSHORT
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'unsigned short'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_uShort(const wxPlg_Obj* pArg_obj, const unsigned short a, const int index)
{
  if(CreateArg(pArg_obj, ivt_ushort, index))
  {
    ((unsigned short*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'unsigned short'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_uShort(const wxPlg_Obj* pArg_obj, unsigned short& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_ushort)
  {
    a = ((unsigned short*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'unsigned short'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_uShort(const wxPlg_Obj* pArg_obj, const unsigned short* a, const int index, const int length)
{
 if(a == NULL) return(false);
 if(CreateArg(pArg_obj, ivt_ushort, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((unsigned short*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'unsigned short'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_uShort(const wxPlg_Obj* pArg_obj, unsigned short* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_ushort)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((unsigned short*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: sSHORT
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'signed short'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_sShort(const wxPlg_Obj* pArg_obj, const signed short a, const int index)
{
  if(CreateArg(pArg_obj, ivt_sshort, index))
  {
    ((signed short*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'signed short'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_sShort(const wxPlg_Obj* pArg_obj, signed short& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_sshort)
  {
    a = ((signed short*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'signed short'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_sShort(const wxPlg_Obj* pArg_obj, const signed short* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(CreateArg(pArg_obj, ivt_sshort, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((signed short*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'signed short'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_sShort(const wxPlg_Obj* pArg_obj, signed short* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_sshort)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((signed short*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: uLONG
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'unsigned long'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_uLong(const wxPlg_Obj* pArg_obj, const unsigned long a, const int index)
{
  if(CreateArg(pArg_obj, ivt_ulong, index))
  {
    ((unsigned long*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'unsigned long'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_uLong(const wxPlg_Obj* pArg_obj, unsigned long& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_ulong)
  {
    a = ((unsigned long*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'unsigned long'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_uLong(const wxPlg_Obj* pArg_obj, const unsigned long* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(CreateArg(pArg_obj, ivt_ulong, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((unsigned long*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'unsigned long'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_uLong(const wxPlg_Obj* pArg_obj, unsigned long* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_ulong)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((unsigned long*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: sLONG
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'signed long'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_sLong(const wxPlg_Obj* pArg_obj, const signed long a, const int index)
{
  if(CreateArg(pArg_obj, ivt_slong, index))
  {
    ((signed long*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'signed long'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_sLong(const wxPlg_Obj* pArg_obj, signed long& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_slong)
  {
    a = ((signed long*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'signed long'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_sLong(const wxPlg_Obj* pArg_obj, const signed long* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(CreateArg(pArg_obj, ivt_slong, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((signed long*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'signed long'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_sLong(const wxPlg_Obj* pArg_obj, signed long* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_slong)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((signed long*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: uLONGLONG
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'unsigned long long'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_uLongLong(const wxPlg_Obj* pArg_obj, const unsigned long long a, const int index)
{
  if(CreateArg(pArg_obj, ivt_ulonglong, index))
  {
    ((unsigned long long*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'unsigned long long'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_uLongLong(const wxPlg_Obj* pArg_obj, unsigned long long& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_ulonglong)
  {
    a = ((unsigned long long*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'unsigned long long'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_uLongLong(const wxPlg_Obj* pArg_obj, const unsigned long long* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(CreateArg(pArg_obj, ivt_ulonglong, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((unsigned long long*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'unsigned long long'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_uLongLong(const wxPlg_Obj* pArg_obj, unsigned long long* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_ulonglong)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((unsigned long long*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: sLONGLONG
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'signed long long'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_sLongLong(const wxPlg_Obj* pArg_obj, const signed long long a, const int index)
{
  if(CreateArg(pArg_obj, ivt_slonglong, index))
  {
    ((signed long long*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'signed long long'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_sLongLong(const wxPlg_Obj* pArg_obj, signed long long& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_slonglong)
  {
    a = ((signed long long*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'signed long long'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_sLongLong(const wxPlg_Obj* pArg_obj, const signed long long* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(CreateArg(pArg_obj, ivt_slonglong, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((signed long long*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'signed long long'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_sLongLong(const wxPlg_Obj* pArg_obj, signed long long* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_slonglong)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((signed long long*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: FLOAT
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'float'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_Float(const wxPlg_Obj* pArg_obj, const float a, const int index)
{
  if(CreateArg(pArg_obj, ivt_float, index))
  {
    ((float*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'float'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_Float(const wxPlg_Obj* pArg_obj, float& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_float)
  {
    a = ((float*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'float'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_Float(const wxPlg_Obj* pArg_obj, const float* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(CreateArg(pArg_obj, ivt_float, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((float*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'float'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_Float(const wxPlg_Obj* pArg_obj, float* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_float)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((float*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: DOUBLE
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'double'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_Double(const wxPlg_Obj* pArg_obj, const double a, const int index)
{
  if(CreateArg(pArg_obj, ivt_double, index))
  {
    ((double*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'double'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_Double(const wxPlg_Obj* pArg_obj, double& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_double)
  {
    a = ((double*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'double'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_Double(const wxPlg_Obj* pArg_obj, const double* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(CreateArg(pArg_obj, ivt_double, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((double*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'double'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_Double(const wxPlg_Obj* pArg_obj, double* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_double)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((double*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: STRING
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'string'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @param   ssize      Buffer max length for storing the string.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_String(const wxPlg_Obj* pArg_obj, const std::string& a, const int index, const int ssize = 256)
{
  size_t ssize_max = ssize;
  if((a.length()+1) > ssize_max) ssize_max = a.length()+1;
  if(CreateArg(pArg_obj, ivt_string, index, (int)ssize_max))
  {
    strncpy((char*)pArg_obj->values[index].value, a.c_str(), ssize_max);
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'string'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_String(const wxPlg_Obj* pArg_obj, std::string& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_string)
  {
    a = (char*)arg_val.value;
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: CIMG
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'cimg'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_CImg(const wxPlg_Obj* pArg_obj, const cimg_ptr a, const int index)
{
  if(CreateArg(pArg_obj, ivt_cimg, index))
  {
    ((cimg_ptr*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'cimg'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_CImg(const wxPlg_Obj* pArg_obj, cimg_ptr& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_cimg)
  {
    a = ((cimg_ptr*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'cimg'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_CImg(const wxPlg_Obj* pArg_obj, const cimg_ptr* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(CreateArg(pArg_obj, ivt_cimg, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((cimg_ptr*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'cimg'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_CImg(const wxPlg_Obj* pArg_obj, cimg_ptr* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_cimg)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((cimg_ptr*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};


//////////////////////////////////////////////////////////
//        ARGUMENT: DEVICECONTEXT
//////////////////////////////////////////////////////////
/**
 * Set/creates single argument of type 'devicecontext'.
 *
 * Set an argument on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value.
 * @param   index      Index of argument to set/create.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_DeviceContext(const wxPlg_Obj* pArg_obj, const devicecontext_ptr a, const int index)
{
  if(CreateArg(pArg_obj, ivt_devicecontext, index))
  {
    ((devicecontext_ptr*)pArg_obj->values[index].value)[0] = a;
    return(true);
  }
  return(false);
};

/**
 * Get single argument of type 'devicecontext'.
 *
 * Get an argument on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value reference.
 * @param   index      Index of argument to get.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_DeviceContext(const wxPlg_Obj* pArg_obj, devicecontext_ptr& a, const int index)
{
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_devicecontext)
  {
    a = ((devicecontext_ptr*)arg_val.value)[0];
    return(true);
  }
  return(false);
};

/**
 * Set/creates vector argument of type 'devicecontext'.
 *
 * Set an argument array on specified index of 
 * the given object and creates it if needed.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Initialize value array.
 * @param   index      Index of argument to set/create.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool SetArg_DeviceContext(const wxPlg_Obj* pArg_obj, const devicecontext_ptr* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(CreateArg(pArg_obj, ivt_devicecontext, index, length))
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      ((devicecontext_ptr*)pArg_obj->values[index].value)[lindex] = a[lindex];
    }
    return(true);
  }
  return(false);
};

/**
 * Get vector argument of type 'devicecontext'.
 *
 * Get an argument array on specified index of 
 * the given object.
 *
 * @param   pArg_obj   Pointer to plugin object.
 * @param   a          Value array to store.
 * @param   index      Index of argument to get.
 * @param   length     Length of array a.
 * @return             TRUE or FALSE.
 */
inline bool GetArg_DeviceContext(const wxPlg_Obj* pArg_obj, devicecontext_ptr* a, const int index, const int length)
{
  if(a == NULL) return(false);
  if(!ValidArg(pArg_obj, index)) return(false);
  wxPlg_Val arg_val = pArg_obj->values[index];
  if(arg_val.value && arg_val.type == ivt_devicecontext)
  {
    for(int lindex = 0; (lindex < length) && (lindex < pArg_obj->values[index].length); lindex++)
    {
      a[lindex] = ((devicecontext_ptr*)arg_val.value)[lindex];
    }
    return(true);
  }
  return(false);
};

#endif /* envargs_h_included */
