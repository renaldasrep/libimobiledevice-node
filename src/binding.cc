extern "C" {
    #include <idevice/id.h>
    #include <idevice/info.h>
    #include <idevice/pair.h>
}

#include <node.h>
#include <nan.h>

using namespace v8;

namespace idevice_info_node {
    Isolate *_isolate;
    
    char *ToCString(const Local<Value>& value) {
        if (!value->IsString()) return NULL;
        Nan::Utf8String string(value);
        char *str = (char *) malloc(string.length() - 1);
        strcpy(str, *string);
        return str;
    }
    
    void info(const FunctionCallbackInfo<Value>& args) {
        // Isolate* isolate = args.GetIsolate();
        
        // Local<Function> callback = Local<Function>::Cast(args[1]);
        Nan::Callback *callback = new Nan::Callback(v8::Local<v8::Function>::Cast(args[1]));
        Local<Object> object = Local<Object>::Cast(args[0]);

        /* Local<Value> debug = object->Get(String::NewFromUtf8(isolate, "debug"));
        Local<Value> domain = object->Get(String::NewFromUtf8(isolate, "domain"));
        Local<Value> key = object->Get(String::NewFromUtf8(isolate, "key"));
        Local<Value> udid = object->Get(String::NewFromUtf8(isolate, "udid"));
        Local<Value> simple = object->Get(String::NewFromUtf8(isolate, "simple")); */
        Local<Value> debug = Nan::Get(object, Nan::New<v8::String>("debug").ToLocalChecked()).ToLocalChecked();
        Local<Value> domain = Nan::Get(object, Nan::New<v8::String>("domain").ToLocalChecked()).ToLocalChecked();
        Local<Value> key = Nan::Get(object, Nan::New<v8::String>("key").ToLocalChecked()).ToLocalChecked();
        Local<Value> udid = Nan::Get(object, Nan::New<v8::String>("udid").ToLocalChecked()).ToLocalChecked();
        Local<Value> simple = Nan::Get(object, Nan::New<v8::String>("simple").ToLocalChecked()).ToLocalChecked();
        
        idevice_info_options options;
        options.debug = true;
        options.simple = false;
        options.domain = NULL;
        options.key = NULL;
        options.udid = NULL;
        
        if (debug->IsBoolean()) { options.debug = Nan::To<bool>(debug).FromMaybe(options.debug); }
        if (domain->IsString()) { options.domain = ToCString(domain); }
        if (key->IsString()) { options.key = ToCString(key); }
        if (udid->IsString()) { options.udid = ToCString(udid); }
        if (simple->IsBoolean()) { options.simple = Nan::To<bool>(simple).FromMaybe(options.simple); }
        
        FILE *err = tmpfile();
        FILE *data = tmpfile();
        
        idevice_info(options, err, data);
        
        Local<Value> res[2];
        /* res[0] = String::NewFromUtf8(isolate, read_stream(err));
        res[1] = String::NewFromUtf8(isolate, read_stream(data)); */
        res[0] = Nan::New<v8::String>(read_stream(err)).ToLocalChecked();
        res[1] = Nan::New<v8::String>(read_stream(data)).ToLocalChecked();
        
        // callback->Call(Null(isolate), 2, res);
        Nan::Call(*callback, 2, res);
    }

    void pair(const FunctionCallbackInfo<Value>& args) {
        // Isolate* isolate = args.GetIsolate();
        
        // Local<Function> callback = Local<Function>::Cast(args[1]);
        Nan::Callback *callback = new Nan::Callback(v8::Local<v8::Function>::Cast(args[1]));
        Local<Value> command = Local<Value>::Cast(args[0]);
        
        FILE *err = tmpfile();
        FILE *data = tmpfile();
        
        char* cmd = ToCString(command);
        idevice_pair(cmd, err, data);
        
        Local<Value> res[2];
        /* res[0] = String::NewFromUtf8(isolate, read_stream(err));
        res[1] = String::NewFromUtf8(isolate, read_stream(data)); */
        res[0] = Nan::New<v8::String>(read_stream(err)).ToLocalChecked();
        res[1] = Nan::New<v8::String>(read_stream(data)).ToLocalChecked();

        // callback->Call(Null(isolate), 2, res);
        Nan::Call(*callback, 2, res);
    }

    void id(const FunctionCallbackInfo<Value>& args) {
        // Isolate* isolate = args.GetIsolate();
        // Local<Function> callback = Local<Function>::Cast(args[0]);
        Nan::Callback *callback = new Nan::Callback(v8::Local<v8::Function>::Cast(args[0]));

        FILE *data = tmpfile();
        
        idevice_id(data);
        
        Local<Value> res[1];
        // res[0] = String::NewFromUtf8(isolate, read_stream(data));
        res[0] = Nan::New<v8::String>(read_stream(data)).ToLocalChecked();
        
        // callback->Call(Null(isolate), 1, res);
        Nan::Call(*callback, 1, res);
    }
}
void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "idevice_info", idevice_info_node::info);
    NODE_SET_METHOD(exports, "idevice_id", idevice_info_node::id);
    NODE_SET_METHOD(exports, "idevice_pair", idevice_info_node::pair);
}

NODE_MODULE(binding, Initialize);
