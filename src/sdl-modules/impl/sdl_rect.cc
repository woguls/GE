#include <sdl-modules/sdl_rect.h>
#include <v8pp/class.hpp>
#include <v8pp/module.hpp>
#include <common-util.h>


void SdlRect::Init(v8pp::module& m) {
   v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlRect> SdlRect_class(isolate);
    SdlRect_class
        .inherit<sdl_rect_t>()
        .ctor<int,int,int,int>()
    ;
    LOG("Initialized SDL.Rect()");
   m.set("Rect", SdlRect_class);
}


