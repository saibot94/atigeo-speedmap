// **********************************************************************
// 
//Description:        Global type definitions for all C types
//Integration notes:  The types defined here are always to be used instead of standard ANSI C types
// 
// **********************************************************************         


#ifndef glob_type_H
#define glob_type_H

/*## package Types_Pkg */

/*## class TopLevel::glob_type */
/*#[ ignore */
//Description:        Global type definitions for all C types
//Integration notes:  The types defined here are always to be used instead of standard ANSI C types
//Package prefix:     -
/*#]*/

#ifdef __cplusplus
extern "C"
{
#endif

//**************************************************************************
//Type: boolean
//Description: Predefined void
//Range:       (0...1)
//Resolution:  1
//Unit:        none
/*## type boolean */
typedef unsigned char boolean;

//**************************************************************************
//Type: sint8
//Description: signed byte
//Range:       (-128...127)
//Resolution:  1
//Unit:        none
/*#[ type sint8 */
typedef signed char sint8;
/*#]*/

//**************************************************************************
//Type: uint8
//Description: unsigned byte
//Range:       (0...255)
//Resolution:  1
//Unit:        none
/*## type uint8 */
typedef unsigned char uint8;

//**************************************************************************
//Type: sint16
//Description: signed short integer
//Range:       (-32768...32767)
//Resolution:  1
//Unit:        none
/*#[ type sint16 */
typedef signed short sint16;
/*#]*/

//**************************************************************************
//Type: uint16
//Description: unsigned short integer
//Range:       (0...65535)
//Resolution:  1
//Unit:        none
/*## type uint16 */
typedef unsigned short uint16;

//**************************************************************************
//Type: sint32
//Description: signed long integer
//Range:       (-2147483648...2147483647)
//Resolution:  1
//Unit:        none
/*#[ type sint32 */
typedef signed int sint32;
/*#]*/

//**************************************************************************
//Type: uint32
//Description: unsigned long integer
//Range:       (0...4294967295)
//Resolution:  1
//Unit:        none
/*## type uint32 */
typedef unsigned int uint32;

//**************************************************************************
//Type: float32
//Description: 32-bit IEEE 754 floating point number
//Range:       -
//Resolution:  -
//Unit:        none
/*## type float32 */
typedef float float32;

//**************************************************************************
//Type: float64
//Description: 64-bit IEEE 754 floating point number
//Range:       -
//Resolution:  -
//Unit:        none
/*#[ type float64 */
#if (defined(_TMS320C6X) || defined(__TMS470__))
typedef double float64;
#endif
/*#]*/

//**************************************************************************
//Type: ubit8
//typedef uint8 %s
/*## type ubit8 */
typedef uint8 ubit8;

//**************************************************************************
//Type: psint8
//Description: Pointer to a signed 8-bit integer
//Range:       -
//Resolution:  -
//Unit:        none
/*## type psint8 */
typedef sint8* psint8;

//**************************************************************************
//Type: puint8
//Description: Pointer to an unsigned 8-bit integer
//Range:       -
//Resolution:  -
//Unit:        none
/*## type puint8 */
typedef uint8* puint8;

//**************************************************************************
//Type: psint16
//Description: Pointer to a signed 16-bit integer
//Range:       -
//Resolution:  -
//Unit:        none
/*## type psint16 */
typedef sint16* psint16;

//**************************************************************************
//Type: puint16
//Description: Pointer to an unsigned 16-bit integer
//Range:       -
//Resolution:  -
//Unit:        none
/*## type puint16 */
typedef uint16* puint16;

//**************************************************************************
//Type: psint32
//Description: Pointer to a signed 32-bit integer
//Range:       -
//Resolution:  -
//Unit:        none
/*## type psint32 */
typedef sint32* psint32;

//**************************************************************************
//Type: puint32
//Description: Pointer to an unsigned 32-bit integer
//Range:       -
//Resolution:  -
//Unit:        none
/*## type puint32 */
typedef uint32* puint32;

//**************************************************************************
//Type: pvoid
//Description: A void pointer
//Range:       -
//Resolution:  -
//Unit:        none
/*## type pvoid */
typedef void* pvoid;

//**************************************************************************
//Type: sint64
//Description: signed long integer
//Range:       (-2147483648...2147483647)
//Resolution:  1
//Unit:        none
/*#[ type sint64 */
typedef signed long long sint64;
/*#]*/

//**************************************************************************
//Type: uint64
//Description: unsigned long integer
//Range:       (0...4294967295)
//Resolution:  1
//Unit:        none
/*#[ type uint64 */
typedef unsigned long long uint64;
/*#]*/

//**************************************************************************
//Type: ubit32
//typedef uint32 %s
//
/*## type ubit32 */
typedef uint32 ubit32;

//**************************************************************************
//Type: NULL
//- Description:	short description, meaning, usage
//- Range:		range of variable (Min - Max) based on raw value
//- Resolution:	resolution (e.g.: 0.1), only for integer (for float "-")
//- Unit:		physical unit (e.g. m/s^2)
//
/*#[ type NULL */
#ifndef NULL
  #ifdef __cplusplus
    #define NULL (0)
  #else
    #define NULL ((void *)0)
  #endif
#endif
/*#]*/

//**************************************************************************
//b_FALSE: boolean
//Description: Boolean constant false (FALSE = boolean 0)
//Range:       constant (boolean)0
//Resolution:  1
//Unit:        none
/*## attribute b_FALSE */
#ifndef b_FALSE
#define b_FALSE ((boolean)0)
#endif

//**************************************************************************
//FALSE: boolean
//Description: Legacy - use b_FALSE wherever possible.
//Range:       constant (boolean)0
//Resolution:  1
//Unit:        none
/*## attribute FALSE */
#ifndef FALSE
#define FALSE b_FALSE
#endif

//**************************************************************************
//b_TRUE: boolean
//Description: Boolean constant true (TRUE = boolean 1)
//Range:       constant (boolean)1
//Resolution:  1
//Unit:        none
/*## attribute b_TRUE */
#ifndef b_TRUE
#define b_TRUE ((boolean)1)
#endif

//**************************************************************************
//TRUE: boolean
//Description: Legacy - use b_TRUE wherever possible
//Range:       constant (boolean)1
//Resolution:  1
//Unit:        none
/*## attribute TRUE */
#ifndef TRUE
#define TRUE b_TRUE
#endif

//**************************************************************************
//AS_EVE_IFVERSION: AS_t_IfVersionNum
//Version number of eve interface
/*## attribute AS_EVE_IFVERSION */
#define AS_EVE_IFVERSION 1u

/***    User explicit entries    ***/


#ifdef __cplusplus
}
#endif

/*## package Types_Pkg */

/*## class TopLevel::glob_type */

#endif

