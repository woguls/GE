#include <sdl-modules/sdl_window.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

SdlWindow::SdlWindow
(   const std::string title,
    int         x,
    int         y,
    int         w,
    int         h,
    Uint32      flags)
{
    SDL_Window* win;
    if (sdl_rect_t::Get() == nullptr && sdl_rect_t::Set(new SDL_Rect) && sdl_rect_t::Get() != nullptr ) {
        sdl_rect_t::Get()->x = x;
        sdl_rect_t::Get()->y = y;
        sdl_rect_t::Get()->w = w;
        sdl_rect_t::Get()->h = h;

        win = SDL_CreateWindow(
            title.c_str(),
            sdl_rect_t::Get()->x,
            sdl_rect_t::Get()->y,
            sdl_rect_t::Get()->w,
            sdl_rect_t::Get()->h,
            flags);
    }
    else {
        LOG("Error creating new SDL_Rect");
        return;
    }

    if (win == nullptr ) {
        LOG("SDL_CreateWindow:");
        LOG(SDL_GetError());
    }
    else sdl_window_t::Set(win);
}

void SdlWindow::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlWindow> SdlWindow_class(isolate);

    SdlWindow_class
        .ctor<std::string, int, int, int, int, Uint32>()
        .inherit<sdl_window_t>()
        ;

    LOG("Initialized SDL.Window()");
    m.set("Window", SdlWindow_class);

}

