#ifndef __V8MODULES_SDL_PIXELFORMAT_H__
#define __V8MODULES_SDL_PIXELFORMAT_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <sdl-modules/types.h>

class SdlPixelformat : public v8Embeddable, public sdl_pixelformat_t {
public:
    explicit SdlPixelformat() {}
    bool v8_FromSurface(sdl_surface_t& sur);
    uint8_t v8_BitsPerPixel() ;
    uint8_t v8_BytesPerPixel();
    uint32_t v8_format();
    void Init(v8pp::module& m) override;
};

#endif