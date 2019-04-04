#include <sdl-modules/render_flags.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

void SdlRenderFlags::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlRenderFlags> SdlRenderFlags_class(isolate);
    SdlRenderFlags_class
        .ctor<>()
    // SDL_RenderFla
        .set_const("SDL_RENDERER_SOFTWARE", SDL_RENDERER_SOFTWARE)
        .set_const("SDL_RENDERER_ACCELERATED", SDL_RENDERER_ACCELERATED)
        .set_const("SDL_RENDERER_PRESENTVSYNC", SDL_RENDERER_PRESENTVSYNC)
        .set_const("SDL_RENDERER_TARGETTEXTURE", SDL_RENDERER_TARGETTEXTURE)
        ;

    LOG("Initialized SDL.RenderFlags()");
    m.set("RenderFlags", SdlRenderFlags_class);

}
