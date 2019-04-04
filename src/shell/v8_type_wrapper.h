#ifndef __V8_SDL_TYPE_WRAPPER_H__
#define __V8_SDL_TYPE_WRAPPER_H__
#include <memory>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>
#include <string>

template<typename T>
class WrapPtr {
public:
    bool IsEmpty() { return _object == nullptr; }
    WrapPtr() :  _object{nullptr} {}
    ~WrapPtr() {
#ifdef LOG_DEBUG_MESSAGES
        std::string message("destructor for class ");
        message.append(std::string(typeid(*this).name()));
        message.append(" was called");
        LOG_THREAD(message.c_str());
#endif
    }
    T* Get() {return _object; }
    bool Set(T* obj) {
        if ( _object != nullptr  || obj == nullptr) return false;
        _object = obj;
        return true;
    }
    bool Reset(T* obj) {
        _object = obj;
        return true;
    }
private:
    T* _object;
};

template<typename T>
void InitType(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<T>  class_t(isolate);
    class_t
        .set("IsEmpty", &T::IsEmpty)
        ;
    m.set(typeid(T).name(), class_t);
    LOG_THREAD(typeid(T).name());
}
#endif