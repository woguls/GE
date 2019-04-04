#ifndef __V8MODULES_THREADING_ISOLATE_H__
#define __V8MODULES_THREADING_ISOLATE_H__
#include <shell/v8_embeddable.h>
#include <shell/shell.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <v8pp/context.hpp>
#include <v8pp/call_v8.hpp>
#include <string>
#include <common-util.h>
#include <sdl-modules/types.h>
#include <resource/resource_types.h>

struct v8FunctionInfo {
    v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> fun;
    v8::Isolate* caller_isolate;
};

struct array_buffer_allocator : v8::ArrayBuffer::Allocator
{
    void* Allocate(size_t length)
    {
        return calloc(length, 1);
    }
    void* AllocateUninitialized(size_t length)
    {
        return malloc(length);
    }
    void Free(void* data, size_t length)
    {
        free(data); (void)length;
    }
};

class IsolateModule : public v8Embeddable {
public:
    explicit IsolateModule();

    bool v8_QueueFunction( v8::FunctionCallbackInfo<v8::Value> const& args);

    static int v8_ProcessFunctionQueue(void *ptr);

    ~IsolateModule() {
        // delete _context;
        // LOG_THREAD("~IsolateModule deleted context");

    //     LOG_THREAD("~IsolateModule called Isolate::Dispose()");
    //     if (isolate != nullptr) {
    //         isolate->Dispose();
    //     }
    }

    void Init(v8pp::module& m) override;

private:
    static array_buffer_allocator array_buffer_allocator_;
    SDL_Thread* _thread;
    // v8::Isolate* isolate;
    std::vector<v8FunctionInfo> _function_queue;
    // v8pp::context* _context;
    // v8EmbeddableFactory _objects;
};


#endif