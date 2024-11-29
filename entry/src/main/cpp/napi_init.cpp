#include "napi/native_api.h"
#include "dynamic_api.h"

dynamic_ExportedSymbols *lib = dynamic_symbols();

void KNObject_Finalizer(napi_env env, void *data, void *hint) { lib->DisposeStablePointer(data); }

static napi_value ObjBridge_create(napi_env env, napi_callback_info info) {
    dynamic_kref_KNObject kno = lib->kotlin.root.KNObject.KNObject();
    napi_value result;
    napi_create_external(env, (void *)kno.pinned, KNObject_Finalizer, NULL, &result);
    return result;
}

static napi_value ObjBridge_foo(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    // get the pointer of KNObject

    dynamic_KNativePtr *obj;
    napi_get_value_external(env, args[0], obj);
    
    // get the String
    char buf[512];
    size_t copied_len;
    napi_get_value_string_utf8(env, args[1], buf, 512, &copied_len);

    dynamic_kref_KNObject o = {.pinned = obj};
    const char *res = lib->kotlin.root.KNObject.foo(o, buf);

    napi_value result_js_string;
    napi_create_string_utf8(env, res, 5, &result_js_string);
    lib->DisposeString(res);
    return result_js_string;
}


static napi_value Add(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    napi_value sum;
    napi_create_double(env, value0 + value1, &sum);

    return sum;
}


EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"ObjBridge_create", nullptr, ObjBridge_create, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"ObjBridge_foo", nullptr, ObjBridge_foo, nullptr, nullptr, nullptr, napi_default, nullptr}};
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
