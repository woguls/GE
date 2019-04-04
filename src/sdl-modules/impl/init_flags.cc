#include <sdl-modules/init_flags.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

void SdlInitFlags::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlInitFlags> SdlInitFlags_class(isolate);
    SdlInitFlags_class
        .ctor<>()
// SDL_InitFlags
        .set_const("SDL_INIT_TIMER", SDL_INIT_TIMER)
        .set_const("SDL_INIT_AUDIO", SDL_INIT_AUDIO)
        .set_const("SDL_INIT_VIDEO", SDL_INIT_VIDEO)
        .set_const("SDL_INIT_JOYSTICK", SDL_INIT_JOYSTICK)
        .set_const("SDL_INIT_HAPTIC", SDL_INIT_HAPTIC)
        .set_const("SDL_INIT_GAMECONTROLLER", SDL_INIT_GAMECONTROLLER)
        .set_const("SDL_INIT_EVENTS", SDL_INIT_EVENTS)
        .set_const("SDL_INIT_EVERYTHING", SDL_INIT_EVERYTHING)
        ;

    LOG("Initialized SDL.InitFlags()");
    m.set("InitFlags", SdlInitFlags_class);

}
