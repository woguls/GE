#include <sdl-modules/sdl_texture.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>


void SdlTexture::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlTexture> SdlTexture_class(isolate);

    SdlTexture_class
        .ctor<>()
        .inherit<sdl_texture_t>()
        .set("CreateTexture", &SdlTexture::v8_CreateTexture)
        .set("CreateTextureFromSurface", &SdlTexture::v8_CreateTextureFromSurface)
        .set("Update", &SdlTexture::v8_UpdateTexture)
        ;

    LOG("Initialized SDL.Texture()");
    m.set("Texture", SdlTexture_class);

}

bool SdlTexture::v8_UpdateTexture(sdl_surface_t& sur) {
    SDL_UpdateTexture(sdl_texture_t::Get(), NULL, sur.Get()->pixels, sur.Get()->pitch);
    return true;
}

bool SdlTexture::v8_CreateTextureFromSurface(sdl_renderer_t& ren, sdl_surface_t& sur) {
    if (ren.Get() == nullptr) {
        LOG("Attempted to create texture with empty renderer");
        return false;
    }
    if (sur.Get() == nullptr) {
        LOG("Attempted to create texture with empty renderer");
        return false;
    }
    if (sdl_texture_t::Get() != nullptr) {
        LOG("Attempted CreateTextureFromSurface on non empty texture");
        return false;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren.Get(), sur.Get());
    if (tex == nullptr) {
        LOG("Failed to create texture");
        LOG(SDL_GetError());
        return false;
    }
    return sdl_texture_t::Set(tex);
}

bool SdlTexture::v8_CreateTexture(
        sdl_renderer_t& renderer,
        Uint32        format,
        int           access,
        int           w,
        int           h)
{
    if ( sdl_texture_t::Get() != nullptr ) {
        LOG("Called CreateTexture on non-empty texture");
        return false;
    }
    if ( renderer.Get() == nullptr ) {
        LOG("Attempted to create texture with empty renderer");
        return false;
    }
    SDL_Texture* tex = SDL_CreateTexture(
                               renderer.Get(),
                               format,
                               access,
                               w,
                               h);
    if (tex == nullptr ) {
        std::cout << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return sdl_texture_t::Set(tex);
}