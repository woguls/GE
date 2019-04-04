#include <threading-modules/isolate.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

array_buffer_allocator IsolateModule::array_buffer_allocator_;

IsolateModule::IsolateModule() {
    // v8::Isolate::CreateParams create_params;
    // create_params.array_buffer_allocator = &array_buffer_allocator_;

    // isolate = v8::Isolate::New(create_params);
    // LOG_THREAD("Created new isolate");
    // if (isolate == nullptr ) {
    //     LOG_THREAD("Unable to create isolate!");
    //     return;
    // }

    // bool add_default_global_methods = false;
    // _context = new v8pp::context{isolate, &array_buffer_allocator_,add_default_global_methods };

    // isolate->Enter();
    // {
    //     v8::Isolate::Scope isolate_scope(_context->isolate());
    //     v8::HandleScope scope(_context->isolate());
    //     v8pp::module m(_context->isolate());
    //     _context->set("quit", v8pp::wrap_function(_context->isolate(), "quit", &v8Shell::Quit));
    //     _context->set("print", v8pp::wrap_function(_context->isolate(), "print", &v8Shell::Print));
    //     InitType<IsolateModule>(m);
    //     InitType<resource_reference_t>(m);
    //     InitType<resource_directory_t>(m);
    //     InitType<resource_tilemap_t>(m);
    //     InitType<resource_tilelayer_t>(m);
    //     InitType<sdl_window_t>(m);
    //     InitType<sdl_renderer_t>(m);
    //     InitType<sdl_surface_t>(m);
    //     InitType<sdl_texture_t>(m);
    //     InitType<sdl_rect_t>(m);
    //     InitType<sdl_ttf_font_t>(m);
    //     InitType<sdl_event_t>(m);

    //     _objects.Init(m);
    //     _context->isolate()->GetCurrentContext()->Global()->Set(
    //       v8::String::NewFromUtf8(_context->isolate(), "GE"), m.new_instance());
    // }
    // isolate->Exit();

    _thread = SDL_CreateThread(&IsolateModule::v8_ProcessFunctionQueue, "ProcessQueue", (void *)this);
}

int IsolateModule::v8_ProcessFunctionQueue(void *ptr) {
    IsolateModule* m = static_cast<IsolateModule*>(ptr);
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = &m->array_buffer_allocator_;

    m->isolate = v8::Isolate::New(create_params);
    if (isolate == nullptr ) {
        LOG_THREAD("Unable to create isolate!");
        return;
    }
    else LOG_THREAD("Created new isolate");

    bool add_default_global_methods = false;
    m->_context = new v8pp::context{m->isolate, &m->array_buffer_allocator_,add_default_global_methods };

    m->isolate->Enter();
    v8::HandleScope scope(m->isolate);
    m->isolate->Exit();
    return 0;
}

bool IsolateModule::v8_QueueFunction(v8::FunctionCallbackInfo<v8::Value> const& args) {
    v8::HandleScope scope(args.GetIsolate());
    if (args[0]->IsFunction()) {
        v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> fn;
        fn.Reset(args.GetIsolate(), args[0].As<v8::Function>());
 
        LOG("Got a function!");
        // std::string fname =  v8pp::from_v8<std::string>(args.GetIsolate(), f.GetInferredName());
        // LOG(fname.c_str());
        _function_queue.push_back(
            v8FunctionInfo{
                fn,
                args.GetIsolate()
            }
        );
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
        // .set("Process1", &IsolateModule::v8_ProcessFunctionQueue)
        ;

    LOG("Initialized Threading.Isolate()");
    m.set("Isolate", IsolateModule_class);

}

