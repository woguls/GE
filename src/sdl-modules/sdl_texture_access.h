#ifndef __V8MODULES_SDL_TEXTURE_ACCESS_H__
#define __V8MODULES_SDL_TEXTURE_ACCESS_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>

class SdlTextureAccess : public v8Embeddable {
public:
    explicit SdlTextureAccess() {}
    void Init(v8pp::module& m) override;
};

#endif