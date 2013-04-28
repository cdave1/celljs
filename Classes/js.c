#include "js.h"

#define XP_MACOSX
#include "jsapi.h"

static JSClass global_class = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

/* The error reporter callback. */
void reportError(JSContext *cx, const char *message, JSErrorReport *report)
{
    fprintf(stderr, "%s:%u:%s\n",
            report->filename ? report->filename : "<no filename>",
            (unsigned int) report->lineno,
            message);
}


#define DOIT_MINARGS 2

JSBool
doit(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
    JSString *str;
    str = JS_ValueToString(cx, argv[0]);
    printf("I'm totally doing it! %s\n", JS_GetStringBytes(str));
    return JS_TRUE;
}


bool RunJS(const char * script, char * out, const int outLen)
{
    JSContext * cx = NULL;
    JSRuntime * rt = JS_NewRuntime(8L * 1024L * 1024L);
    if (rt == NULL) return 0;
    cx = JS_NewContext(rt, 8192);
    if (cx == NULL) return 0;
    JS_SetOptions(cx, JSOPTION_VAROBJFIX);
    JS_SetVersion(cx, JSVERSION_1_7);
    
    JSObject * global = JS_NewObject(cx, &global_class, NULL, NULL);
    if (global == NULL) exit(1);
    if (!JS_InitStandardClasses(cx, global)) return 0;
    
    //JSFunction * f = JS_DefineFunction(cx, global, "Write", Write, Write_MINARGS, 0);
    
    jsval rval;
    JSString *str;
    JSBool ok;
    
    ok = JS_EvaluateScript(cx, global, script, strlen(script),
                           NULL, 0, &rval);
    if (ok)
    {
        str = JS_ValueToString(cx, rval);
        strncpy(out, JS_GetStringBytes(str), outLen);
    }

    if (cx != NULL) { JS_DestroyContext(cx);}
    JS_DestroyRuntime(rt);
    JS_ShutDown();
    return true;
}


int dojs(const char * root)
{
    JSContext * cx = NULL;
    JSRuntime * rt = JS_NewRuntime(8L * 1024L * 1024L);
    if (rt == NULL) return 0;
    cx = JS_NewContext(rt, 8192);
    if (cx == NULL) return 0;
    JS_SetOptions(cx, JSOPTION_VAROBJFIX);
    JS_SetVersion(cx, JSVERSION_1_7);
    
    JSObject * global = JS_NewObject(cx, &global_class, NULL, NULL);
    if (global == NULL) exit(1);
    if (!JS_InitStandardClasses(cx, global)) exit(1);
    //JS_EndRequest(cx);
    
    
    
    JSFunction * f = JS_DefineFunction(cx, global, "doit", doit, DOIT_MINARGS, 0);
    
    
    char *script = "(function fac(n){if (n <= 1) return 1; return n * fac(n-1)})(5)";
    jsval rval;
    JSString *str;
    JSBool ok;
    
    ok = JS_EvaluateScript(cx, global, script, strlen(script),
                           NULL, 0, &rval);
    str = JS_ValueToString(cx, rval);
    printf("script result: %s\n", JS_GetStringBytes(str));

    char * s2 = "doit();";
    ok = JS_EvaluateScript(cx, global, s2, strlen(s2), NULL, 0, &rval);
    
    char filepath[256];
    bzero(filepath, sizeof(char) * 256);
    snprintf(filepath, 256, "%s/test.js", root);
    
    //FILE *file = fopen(filepath, "r"); 
    
    
    
    /**
     extern JS_PUBLIC_API(JSScript *)
     JS_CompileFile(JSContext *cx, JSObject *obj, const char *filename);
     */
    JSScript *test = JS_CompileFile(cx, global, filepath);
    if (test)
    {
        /**
         extern JS_PUBLIC_API(JSBool)
         JS_ExecuteScript(JSContext *cx, JSObject *obj, JSScript *script, jsval *rval);
         */
        JS_ExecuteScript(cx, global, test, &rval);
    }
    
    
    if (cx != NULL) { JS_DestroyContext(cx);}
    JS_DestroyRuntime(rt);
    JS_ShutDown();
    
    return 0;
}