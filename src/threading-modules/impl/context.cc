#include <threading-modules/isolate.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

array_buffer_allocator IsolateModule::array_buffer_allocator_;

bool IsolateModule::v8_QueueFunction(v8::FunctionCallbackInfo<v8::Value> const& args) {
    if (args[0]->IsFunction()) {
        LOG("Got a function!");
        _function_queue.push_back(v8::Local<v8::Function>::Cast(args[0]));
    }
    std::string message = std::to_string(args.Length()) + " arguments passed";
    LOG(message.c_str());
    return true;
}

void IsolateModule::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<IsolateModule> IsolateModule_class(isolate);

    IsolateModule_class
        .ctor<>()
        .set("QueueFunction", &IsolateModule::v8_QueueFunction)
        ;

    LOG("Initialized Threading.Isolate()");
    m.set("Isolate", IsolateModule_class);

}

