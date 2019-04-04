#include <sdl-modules/sdl_texture_access.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

void SdlTextureAccess::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlTextureAccess> SdlTextureAccess_class(isolate);
    SdlTextureAccess_class
        .ctor<>()
// SDL_InitFlags
        .set_const("SDL_TEXTUREACCESS_STATIC", SDL_TEXTUREACCESS_STATIC)
        .set_const("SDL_TEXTUREACCESS_STREAMING", SDL_TEXTUREACCESS_STREAMING)
        .set_const("SDL_TEXTUREACCESS_TARGET", SDL_TEXTUREACCESS_TARGET)
        ;

    LOG("Initialized SDL.TextureAccess()");
    m.set("TextureAccess", SdlTextureAccess_class);

}
