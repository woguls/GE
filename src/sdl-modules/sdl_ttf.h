#ifndef __V8MODULES_SDL_TTF_H__
#define __V8MODULES_SDL_TTF_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <sdl-modules/types.h>
#include <string>
#include <common-util.h>
#include <resource/resource_types.h>

class SdlTTF : public v8Embeddable, public sdl_ttf_font_t {
public:
    explicit SdlTTF()
    :   sdl_ttf_font_t()
    {}
    explicit SdlTTF(resource_reference_t& ref, int ptsize);
    ~SdlTTF() {
        LOG_THREAD("~SdlTTF called.");
    }
    void Init(v8pp::module& m) override;
};


#endif