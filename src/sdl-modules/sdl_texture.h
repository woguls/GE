#ifndef __V8MODULES_SDL_TEXTURE_H__
#define __V8MODULES_SDL_TEXTURE_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <sdl-modules/types.h>
#include <string>
#include <common-util.h>


class SdlTexture : public v8Embeddable, public sdl_texture_t {
public:
    explicit SdlTexture() : sdl_texture_t() {}
    ~SdlTexture() {
        LOG_THREAD("~SdlTexture called SDL_DestroyTexture");
        SDL_DestroyTexture(sdl_texture_t::Get());
    }

    bool v8_CreateTextureFromSurface(sdl_renderer_t& ren, sdl_surface_t& sur );

    bool v8_CreateTexture(sdl_renderer_t& renderer,
                               Uint32        format,
                               int           access,
                               int           w,
                               int           h);

    bool v8_UpdateTexture(sdl_surface_t& sur);
    
    void Init(v8pp::module& m) override;
};


#endif