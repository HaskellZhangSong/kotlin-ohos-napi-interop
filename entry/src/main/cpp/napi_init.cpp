#include "napi/native_api.h"
#include "dynamic_api.h"
#include "hilog/log.h"
#include <string.h>
#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0x0000
#define LOG_TAG "testTag"

static napi_value inc(napi_env env, napi_callback_info info) {
    OH_LOG_INFO(LOG_APP, "called inc");
    dynamic_ExportedSymbols *lib = dynamic_symbols();
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    dynamic_KInt value0;
    napi_get_value_int32(env, args[0], &value0);
    
    dynamic_KInt res = lib->kotlin.root.inc(value0);
    
    napi_value result;
    napi_create_int32(env, res, &result);
    return result;
}


static napi_value Add(napi_env env, napi_callback_info info)
{
    OH_LOG_INFO(LOG_APP, "called add");
    dynamic_ExportedSymbols* lib = dynamic_symbols();
    
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);
    
    dynamic_KInt value0;
    napi_get_value_int32(env, args[0], &value0);

    dynamic_KInt value1;
    napi_get_value_int32(env, args[1], &value1);
    
    dynamic_KInt value = lib->kotlin.root.add(value0, value1) + 1;

    napi_value result;
    napi_create_int32(env, value, &result);
    return result;
}


static napi_value get5(napi_env env, napi_callback_info info) {
    dynamic_ExportedSymbols *lib = dynamic_symbols();
    dynamic_KInt res = lib->kotlin.root.get5();
    napi_value result;
    napi_create_int32(env, res, &result);
    return result;
}

void KNObject_Finalizer(napi_env env, void *data, void *hint) { 
    dynamic_ExportedSymbols *lib = dynamic_symbols();
    lib->DisposeStablePointer(data); 
}

static napi_value ObjBridge_create(napi_env env, napi_callback_info info) {
    dynamic_ExportedSymbols *lib = dynamic_symbols();
    dynamic_kref_KNObject kno = lib->kotlin.root.KNObject.KNObject();
    napi_value result;
    napi_create_external(env, (void *)kno.pinned, KNObject_Finalizer, NULL, &result);
    return result;
}

static napi_value ObjBridge_foo(napi_env env, napi_callback_info info) {
    dynamic_ExportedSymbols *lib = dynamic_symbols();
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    // get the pointer of KNObject

    dynamic_KNativePtr *obj;
    napi_get_value_external(env, args[0], (void**)&obj);
    
    // get the String
    char buf[512];
    size_t copied_len;
    napi_get_value_string_utf8(env, args[1], buf, 512, &copied_len);

    dynamic_kref_KNObject o = {.pinned = obj};
    const char *res = lib->kotlin.root.KNObject.foo(o, buf);

    napi_value result_js_string;
    napi_create_string_utf8(env, res, strlen(res), &result_js_string);
    lib->DisposeString(res);
    return result_js_string;
}



EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"ObjBridge_create", nullptr, ObjBridge_create, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"ObjBridge_foo", nullptr, ObjBridge_foo, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"get5", nullptr, get5, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"inc", nullptr, inc, nullptr, nullptr, nullptr, napi_default, nullptr}
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void *)0),
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void) { napi_module_register(&demoModule); }
