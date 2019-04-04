#include <sdl-modules/sdl_init.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

bool SdlInit::_init = false;

void SdlInit::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlInit> SdlInit_class(isolate);
    SdlInit_class
    .ctor<uint32_t>();

    LOG("Initialized SDL.Init()");
    m.set("Init", SdlInit_class);

}
