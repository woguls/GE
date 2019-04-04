#ifndef __V8MODULES_SDLINIT_H__
#define __V8MODULES_SDLINIT_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <common-util.h>
#include <v8pp/module.hpp>

class SdlInit : public v8Embeddable {
public:
    explicit SdlInit(uint32_t flags)
    :   _flags{flags}
    {
        if (!_init) {
            SDL_SetMainReady();
            int res = SDL_Init(_flags);
            if (res != 0) {
                LOG_THREAD("Unable to initialize SDL");
                LOG(SDL_GetError());
                return;
            }
        }
        LOG_THREAD("SDL_Init succeeded");
        _init = true;
    }

    explicit SdlInit()
    :   _flags{SDL_INIT_EVERYTHING}
    {
        _init = false;
    }

    ~SdlInit() {
        SDL_Quit();
        LOG_THREAD("~SdlInit called SDL_Quit()");
    }

    void Init(v8pp::module& m) override;
private:
    uint32_t _flags;
    static bool _init;
};

#endif