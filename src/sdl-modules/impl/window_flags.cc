#include <sdl-modules/window_flags.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

void SdlWindowFlags::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlWindowFlags> SdlWindowFlags_class(isolate);
    SdlWindowFlags_class
        .ctor<>()
// SDL_WindowFlags
    .set_const("SDL_WINDOW_SHOWN", SDL_WINDOW_SHOWN)
    .set_const("SDL_WINDOW_HIDDEN", SDL_WINDOW_HIDDEN)
    .set_const("SDL_WINDOW_FULLSCREEN", SDL_WINDOW_FULLSCREEN)
    .set_const("SDL_WINDOW_OPENGL", SDL_WINDOW_OPENGL)
    .set_const("SDL_WINDOW_SHOWN", SDL_WINDOW_SHOWN)
    .set_const("SDL_WINDOW_HIDDEN", SDL_WINDOW_HIDDEN)
    .set_const("SDL_WINDOW_BORDERLESS", SDL_WINDOW_BORDERLESS)
    .set_const("SDL_WINDOW_RESIZABLE", SDL_WINDOW_RESIZABLE)
    .set_const("SDL_WINDOW_MINIMIZED", SDL_WINDOW_MINIMIZED)
    .set_const("SDL_WINDOW_MAXIMIZED", SDL_WINDOW_MAXIMIZED)
    .set_const("SDL_WINDOW_INPUT_GRABBED", SDL_WINDOW_INPUT_GRABBED)
    .set_const("SDL_WINDOW_INPUT_FOCUS", SDL_WINDOW_INPUT_FOCUS)
    .set_const("SDL_WINDOW_MOUSE_FOCUS", SDL_WINDOW_MOUSE_FOCUS)
    .set_const("SDL_WINDOW_FULLSCREEN_DESKTOP", SDL_WINDOW_FULLSCREEN_DESKTOP)
    .set_const("SDL_WINDOW_FOREIGN", SDL_WINDOW_FOREIGN)
    .set_const("SDL_WINDOW_ALLOW_HIGHDPI", SDL_WINDOW_ALLOW_HIGHDPI)
    .set_const("SDL_WINDOW_MOUSE_CAPTURE", SDL_WINDOW_MOUSE_CAPTURE)
    .set_const("SDL_WINDOW_ALWAYS_ON_TOP", SDL_WINDOW_ALWAYS_ON_TOP)
    .set_const("SDL_WINDOW_SKIP_TASKBAR", SDL_WINDOW_SKIP_TASKBAR)
    .set_const("SDL_WINDOW_UTILITY", SDL_WINDOW_UTILITY)
    .set_const("SDL_WINDOW_TOOLTIP", SDL_WINDOW_TOOLTIP)
    .set_const("SDL_WINDOW_POPUP_MENU", SDL_WINDOW_POPUP_MENU)
    .set_const("SDL_WINDOW_VULKAN", SDL_WINDOW_VULKAN)
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

    LOG("Initialized SDL.WindowFlags()");
    m.set("WindowFlags", SdlWindowFlags_class);

}
