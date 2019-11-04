extern "C" {
    #include <idevice/id.h>
    #include <idevice/info.h>
    #include <idevice/backup2.h>
    #include <idevice/pair.h>
}

#include <node.h>
#include <nan.h>

using namespace v8;

namespace idevice_info_node {
    Isolate *_isolate;
    Local<Function> _progressCallbackFunction;
    Nan::Callback _progressCallback(_progressCallbackFunction);
    
    char *ToCString(const Local<Value>& value) {
        if (!value->IsString()) return NULL;
        Nan::Utf8String string(value);
        char *str = (char *) malloc(string.length() - 1);
        strcpy(str, *string);
        return str;
    }
    
    void progressCallback(FILE *stream_progress) {
        Local<Value> res[2];
        // res[0] = String::NewFromUtf8(_isolate, read_stream(stream_progress));
        res[0] = Nan::New<v8::String>(read_stream(stream_progress)).ToLocalChecked();
        // _progressCallback->Call(Null(_isolate), 1, res);
        Nan::Call(_progressCallback, 1, res);
    }
    
    void backup2(const FunctionCallbackInfo<Value>& args) {
        _isolate = args.GetIsolate();
        // Local<Function> callback;
        Local<Object> object;
        
        if (args.Length() < 3) {
            fprintf(stderr, "No arguments provided, this method requires 3 parameters.\n");
            return;
        }
        
        if (!args[0]->IsObject()) {
            fprintf(stderr, "First argument is an object\n");
            return;
        }
        
        if (!args[1]->IsFunction()) {
            fprintf(stderr, "Second argument must be a function\n");
            return;
        }
        
        object = Local<Object>::Cast(args[0]);
        // callback = Local<Function>::Cast(args[1]);
        Nan::Callback *callback = new Nan::Callback(v8::Local<v8::Function>::Cast(args[1]));
        
        if (!args[2]->IsFunction()) {
            Local<Value> res[2];
            /* res[0] = String::NewFromUtf8(_isolate, "Third argument must be a function");
            res[1] = String::NewFromUtf8(_isolate, NULL); */
            res[0] = Nan::New<v8::String>("Third argument must be a function").ToLocalChecked();
            res[1] = Nan::Null();
            // callback->Call(Null(_isolate), 2, res);
            Nan::Call(*callback, 2, res);
            return;
        }
        
        // _progressCallback = Local<Function>::Cast(args[2]);
        Nan::Callback *_progressCallback = new Nan::Callback(v8::Local<v8::Function>::Cast(args[2]));
        
        /* Local<Value> debug = object->Get(String::NewFromUtf8(_isolate, "debug"));
        Local<Value> udid = object->Get(String::NewFromUtf8(_isolate, "udid"));
        Local<Value> source = object->Get(String::NewFromUtf8(_isolate, "source"));
        Local<Value> backup = object->Get(String::NewFromUtf8(_isolate, "backup"));
        Local<Value> restore = object->Get(String::NewFromUtf8(_isolate, "restore"));
        Local<Value> system = object->Get(String::NewFromUtf8(_isolate, "system"));
        Local<Value> reboot = object->Get(String::NewFromUtf8(_isolate, "reboot"));
        Local<Value> copy = object->Get(String::NewFromUtf8(_isolate, "copy"));
        Local<Value> settings = object->Get(String::NewFromUtf8(_isolate, "settings"));
        Local<Value> remove = object->Get(String::NewFromUtf8(_isolate, "remove"));
        Local<Value> password = object->Get(String::NewFromUtf8(_isolate, "password"));
        Local<Value> cloud = object->Get(String::NewFromUtf8(_isolate, "cloud"));
        Local<Value> full = object->Get(String::NewFromUtf8(_isolate, "full"));
        Local<Value> info = object->Get(String::NewFromUtf8(_isolate, "info"));
        Local<Value> list = object->Get(String::NewFromUtf8(_isolate, "list"));
        Local<Value> unback = object->Get(String::NewFromUtf8(_isolate, "unback"));
        Local<Value> encryption = object->Get(String::NewFromUtf8(_isolate, "encryption"));
        Local<Value> interactive = object->Get(String::NewFromUtf8(_isolate, "interactive"));
        Local<Value> changepw = object->Get(String::NewFromUtf8(_isolate, "changepw"));
        Local<Value> backup_directory = object->Get(String::NewFromUtf8(_isolate, "backup_directory")); */
        Local<Value> debug = Nan::Get(object, Nan::New<v8::String>("debug").ToLocalChecked()).ToLocalChecked();
        Local<Value> udid = Nan::Get(object, Nan::New<v8::String>("udid").ToLocalChecked()).ToLocalChecked();
        Local<Value> source = Nan::Get(object, Nan::New<v8::String>("source").ToLocalChecked()).ToLocalChecked();
        Local<Value> backup = Nan::Get(object, Nan::New<v8::String>("backup").ToLocalChecked()).ToLocalChecked();
        Local<Value> restore = Nan::Get(object, Nan::New<v8::String>("restore").ToLocalChecked()).ToLocalChecked();
        Local<Value> system = Nan::Get(object, Nan::New<v8::String>("system").ToLocalChecked()).ToLocalChecked();
        Local<Value> reboot = Nan::Get(object, Nan::New<v8::String>("reboot").ToLocalChecked()).ToLocalChecked();
        Local<Value> copy = Nan::Get(object, Nan::New<v8::String>("copy").ToLocalChecked()).ToLocalChecked();
        Local<Value> settings = Nan::Get(object, Nan::New<v8::String>("settings").ToLocalChecked()).ToLocalChecked();
        Local<Value> remove = Nan::Get(object, Nan::New<v8::String>("remove").ToLocalChecked()).ToLocalChecked();
        Local<Value> password = Nan::Get(object, Nan::New<v8::String>("password").ToLocalChecked()).ToLocalChecked();
        Local<Value> cloud = Nan::Get(object, Nan::New<v8::String>("cloud").ToLocalChecked()).ToLocalChecked();
        Local<Value> full = Nan::Get(object, Nan::New<v8::String>("full").ToLocalChecked()).ToLocalChecked();
        Local<Value> info = Nan::Get(object, Nan::New<v8::String>("info").ToLocalChecked()).ToLocalChecked();
        Local<Value> list = Nan::Get(object, Nan::New<v8::String>("list").ToLocalChecked()).ToLocalChecked();
        Local<Value> unback = Nan::Get(object, Nan::New<v8::String>("unback").ToLocalChecked()).ToLocalChecked();
        Local<Value> encryption = Nan::Get(object, Nan::New<v8::String>("encryption").ToLocalChecked()).ToLocalChecked();
        Local<Value> interactive = Nan::Get(object, Nan::New<v8::String>("interactive").ToLocalChecked()).ToLocalChecked();
        Local<Value> changepw = Nan::Get(object, Nan::New<v8::String>("changepw").ToLocalChecked()).ToLocalChecked();
        Local<Value> backup_directory = Nan::Get(object, Nan::New<v8::String>("backup_directory").ToLocalChecked()).ToLocalChecked();
        
        idevice_backup2_options options;
        options.debug = false;
        options.udid = NULL;
        options.source = NULL;
        options.backup = false;
        options.restore = false;
        options.system = false;
        options.reboot = false;
        options.copy = false;
        options.settings = false;
        options.remove = false;
        options.password = NULL;
        options.cloud = NULL;
        options.full = false;
        options.info = false;
        options.list = false;
        options.unback = false;
        options.interactive = false;
        options.encryption.status = NULL;
        options.encryption.password = NULL;
        options.changepw.backup_password = NULL;
        options.changepw.newpw = NULL;
        options.backup_directory = NULL;
        
        if (debug->IsBoolean()) { options.debug = Nan::To<bool>(debug).FromMaybe(options.debug); }
        if (udid->IsString()) { options.udid = ToCString(udid); }
        if (source->IsString()) { options.source = ToCString(source); }
        if (backup->IsBoolean()) { options.backup = Nan::To<bool>(backup).FromMaybe(options.backup); }
        if (restore->IsBoolean()) { options.restore = Nan::To<bool>(restore).FromMaybe(options.restore); }
        if (system->IsBoolean()) { options.system = Nan::To<bool>(system).FromMaybe(options.system); }
        if (reboot->IsBoolean()) { options.reboot = Nan::To<bool>(reboot).FromMaybe(options.reboot); }
        if (copy->IsBoolean()) { options.copy = Nan::To<bool>(copy).FromMaybe(options.copy); }
        if (settings->IsBoolean()) { options.settings = Nan::To<bool>(settings).FromMaybe(options.settings); }
        if (remove->IsBoolean()) { options.remove = Nan::To<bool>(remove).FromMaybe(options.remove); }
        if (password->IsString()) { options.password = ToCString(password); }
        if (cloud->IsString()) { options.cloud = ToCString(cloud); }
        if (full->IsBoolean()) { options.full = Nan::To<bool>(full).FromMaybe(options.full); }
        if (info->IsBoolean()) { options.info = Nan::To<bool>(info).FromMaybe(options.info); }
        if (list->IsBoolean()) { options.list = Nan::To<bool>(list).FromMaybe(options.list); }
        if (interactive->IsBoolean()) { options.interactive = Nan::To<bool>(interactive).FromMaybe(options.interactive); }
        if (unback->IsBoolean()) { options.unback = Nan::To<bool>(unback).FromMaybe(options.unback); }
        if (backup_directory->IsString()) { options.backup_directory = ToCString(backup_directory); }
        if (encryption->IsObject()) {
            Local<Object> obj = Nan::To<Object>(encryption).ToLocalChecked();
            Local<Value> status = Nan::Get(obj, Nan::New<v8::String>("status").ToLocalChecked()).ToLocalChecked();
            Local<Value> password = Nan::Get(obj, Nan::New<v8::String>("password").ToLocalChecked()).ToLocalChecked();
            if (status->IsString()) options.encryption.status = ToCString(status);
            if (password->IsString()) options.encryption.password = ToCString(password);
        }
        if (changepw->IsObject()) {
            Local<Object> obj = Nan::To<Object>(changepw).ToLocalChecked();
            Local<Value> newpw = Nan::Get(obj, Nan::New<v8::String>("newpw").ToLocalChecked()).ToLocalChecked();
            Local<Value> backup_password = Nan::Get(obj, Nan::New<v8::String>("backup_password").ToLocalChecked()).ToLocalChecked();
            if (newpw->IsString()) options.changepw.newpw = ToCString(newpw);
            if (backup_password->IsString()) options.changepw.backup_password = ToCString(backup_password);
        }
        
        FILE *stream_err = tmpfile();
        FILE *stream_out = tmpfile();
        
        idevice_backup2(options, stream_err, stream_out, &progressCallback);
        
        Local<Value> res[2];
        /* res[0] = String::NewFromUtf8(_isolate, read_stream(stream_err));
        res[1] = String::NewFromUtf8(_isolate, read_stream(stream_out)); */
        res[0] = Nan::New<v8::String>(read_stream(stream_err)).ToLocalChecked();
        res[1] = Nan::New<v8::String>(read_stream(stream_out)).ToLocalChecked();
        
        // callback->Call(Null(_isolate), 2, res);
        Nan::Call(*callback, 2, res);
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
    NODE_SET_METHOD(exports, "idevice_backup2", idevice_info_node::backup2);
    NODE_SET_METHOD(exports, "idevice_info", idevice_info_node::info);
    NODE_SET_METHOD(exports, "idevice_id", idevice_info_node::id);
    NODE_SET_METHOD(exports, "idevice_pair", idevice_info_node::pair);
}

NODE_MODULE(binding, Initialize);
