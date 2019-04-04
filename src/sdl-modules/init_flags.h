#ifndef __V8MODULES_SDL_INIT_FLAGS_H__
#define __V8MODULES_SDL_INIT_FLAGS_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>

class SdlInitFlags : public v8Embeddable {
public:
    explicit SdlInitFlags() {}
    void Init(v8pp::module& m) override;
};

#endif