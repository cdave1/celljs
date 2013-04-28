#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define XP_MACOSX
#define XP_UNIX
#include "jsapi.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern JSBool doit(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
    
    extern int dojs(const char * root);
    
    extern bool RunJS(const char * script, char * out, const int outLen);

#ifdef __cplusplus
}
#endif