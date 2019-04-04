#ifndef __V8MODULES_SDL_WINDOW_FLAGS_H__
#define __V8MODULES_SDL_WINDOW_FLAGS_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>

class SdlWindowFlags : public v8Embeddable {
public:
    explicit SdlWindowFlags() {}
    void Init(v8pp::module& m) override;
};

#endif