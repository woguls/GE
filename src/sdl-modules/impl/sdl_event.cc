#include <sdl-modules/sdl_event.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>


void SdlEvent::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlEvent> SdlEvent_class(isolate);

    SdlEvent_class
        .ctor<>()
        .inherit<sdl_event_t>()
        .set("PollEvent", &SdlEvent::v8_PollEvent)
        .set("Type", &SdlEvent::v8_Type)
        .set_const("SDL_AUDIODEVICEADDED", SDL_AUDIODEVICEADDED)
        .set_const("SDL_AUDIODEVICEREMOVED", SDL_AUDIODEVICEREMOVED)
        .set_const("SDL_QUIT", SDL_QUIT)
        .set_const("SDL_CONTROLLERAXISMOTION", SDL_CONTROLLERAXISMOTION)
        .set_const("SDL_CONTROLLERBUTTONDOWN", SDL_CONTROLLERBUTTONDOWN)
        .set_const("SDL_CONTROLLERBUTTONUP", SDL_CONTROLLERBUTTONUP)
        .set_const("SDL_CONTROLLERDEVICEADDED", SDL_CONTROLLERDEVICEADDED)
        .set_const("SDL_CONTROLLERDEVICEREMOVED", SDL_CONTROLLERDEVICEREMOVED)
        .set_const("SDL_CONTROLLERDEVICEREMAPPED", SDL_CONTROLLERDEVICEREMAPPED)
        .set_const("SDL_DOLLARGESTURE", SDL_DOLLARGESTURE)
        .set_const("SDL_DOLLARRECORD", SDL_DOLLARRECORD)
        .set_const("SDL_DROPFILE", SDL_DROPFILE)
        .set_const("SDL_DROPTEXT", SDL_DROPTEXT)
        .set_const("SDL_DROPBEGIN", SDL_DROPBEGIN)
        .set_const("SDL_DROPCOMPLETE", SDL_DROPCOMPLETE)
        .set_const("SDL_FINGERMOTION", SDL_FINGERMOTION)
        .set_const("SDL_FINGERDOWN", SDL_FINGERDOWN)
        .set_const("SDL_FINGERUP", SDL_FINGERUP)
        .set_const("SDL_KEYDOWN", SDL_KEYDOWN)
        .set_const("SDL_KEYUP", SDL_KEYUP)
        .set_const("SDL_JOYAXISMOTION", SDL_JOYAXISMOTION)
        .set_const("SDL_JOYBALLMOTION", SDL_JOYBALLMOTION)
        .set_const("SDL_JOYHATMOTION", SDL_JOYHATMOTION)
        .set_const("SDL_JOYBUTTONDOWN", SDL_JOYBUTTONDOWN)
        .set_const("SDL_JOYBUTTONUP", SDL_JOYBUTTONUP)
        .set_const("SDL_JOYDEVICEADDED", SDL_JOYDEVICEADDED)
        .set_const("SDL_JOYDEVICEREMOVED", SDL_JOYDEVICEREMOVED)
        .set_const("SDL_MOUSEMOTION", SDL_MOUSEMOTION)
        .set_const("SDL_MOUSEBUTTONDOWN", SDL_MOUSEBUTTONDOWN)
        .set_const("SDL_MOUSEBUTTONUP", SDL_MOUSEBUTTONUP)
        .set_const("SDL_MOUSEWHEEL", SDL_MOUSEWHEEL)
        .set_const("SDL_MULTIGESTURE", SDL_MULTIGESTURE)
        .set_const("SDL_SYSWMEVENT", SDL_SYSWMEVENT)
        .set_const("SDL_TEXTEDITING", SDL_TEXTEDITING)
        .set_const("SDL_TEXTINPUT", SDL_TEXTINPUT)
        .set_const("SDL_USEREVENT", SDL_USEREVENT)
        .set_const("SDL_WINDOWEVENT", SDL_WINDOWEVENT)
        .set_const("SDL_CONTROLLERAXISMOTION", SDL_CONTROLLERAXISMOTION)
        ;

    LOG("Initialized SDL.Event()");
    m.set("Event", SdlEvent_class);
}

int SdlEvent::v8_PollEvent() {
    if (sdl_event_t::Get() != nullptr)
        return SDL_PollEvent(sdl_event_t::Get());

    return 0;
}

Uint32 SdlEvent::v8_Type() {
    if (sdl_event_t::Get() != nullptr) {
        return sdl_event_t::Get()->type;
    }
    return 0;
}