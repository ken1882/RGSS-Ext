#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>
#include "ruby.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <string>


/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

typedef VALUE(*VALUE_P)();
typedef VALUE(*rgss_obj_ivar_get_proto)(VALUE, VALUE);
typedef VALUE(*rgss_obj_ivar_set_proto)(VALUE, VALUE, VALUE);
typedef VALUE(*rgss_ary_at_proto)(VALUE, VALUE);
typedef VALUE(*rgss_ascii_new_cstr_proto)(const char*);

static int init_ok = false;
static rgss_obj_ivar_get_proto rgss_obj_ivar_get;
static rgss_obj_ivar_set_proto rgss_obj_ivar_set;
static rgss_ary_at_proto rgss_ary_at;
static rgss_ascii_new_cstr_proto rgss_ascii_new_cstr;

#ifdef __cplusplus
extern "C"
{
#endif

void DLL_EXPORT Initialize(HMODULE RGSSDLL) {
	rgss_obj_ivar_get = (rgss_obj_ivar_get_proto)((char*)RGSSDLL + 0x341F0);
	rgss_obj_ivar_set = (rgss_obj_ivar_set_proto)((char*)RGSSDLL + 0x34230);
	rgss_ary_at = (rgss_ary_at_proto)((char*)RGSSDLL + 0x89cc0);
	rgss_ascii_new_cstr = (rgss_ascii_new_cstr_proto)((char*)RGSSDLL + 0x365B0);
	init_ok = true;
}

DWORD DLL_EXPORT InitOK();
VALUE DLL_EXPORT HelloWorld();
VALUE DLL_EXPORT GetInstance(VALUE obj, VALUE iv);
VALUE DLL_EXPORT SetInstance(VALUE obj, VALUE iv, VALUE val);
VALUE DLL_EXPORT GetAryIndex(VALUE ary, VALUE pos);
VALUE DLL_EXPORT CheckCollision(DWORD, VALUE, DWORD, VALUE);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
