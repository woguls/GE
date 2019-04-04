#ifndef __V8MODULES_THREADING_ISOLATE_H__
#define __V8MODULES_THREADING_ISOLATE_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <string>
#include <common-util.h>

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
    explicit IsolateModule()
    {
        v8::Isolate::CreateParams create_params;
        create_params.array_buffer_allocator = &array_buffer_allocator_;

        isolate = v8::Isolate::New(create_params);
        LOG_THREAD("Created new isolate");
        if (isolate == nullptr ) {
            LOG_THREAD("Unable to create isolate!");
            return;
        }


    }

    bool v8_QueueFunction( v8::FunctionCallbackInfo<v8::Value> const& args);

    ~IsolateModule() {
        LOG_THREAD("~IsolateModule called Isolate::Dispose()");
        if (isolate != nullptr) {
            isolate->Dispose();
        }
    }

    void Init(v8pp::module& m) override;

private:
    static array_buffer_allocator array_buffer_allocator_;
    SDL_Thread* _thread;
    v8::Isolate* isolate;
    std::vector<v8::Local<v8::Function>> _function_queue;
    v8pp::Context* _context;
};


#endif