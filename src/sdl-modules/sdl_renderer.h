#ifndef __V8MODULES_SDL_RENDERER_H__
#define __V8MODULES_SDL_RENDERER_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <string>
#include <sdl-modules/types.h>
#include <common-util.h>
#include <SDL_timer.h>

class SdlRenderer : public v8Embeddable, public sdl_renderer_t {
public:
    explicit SdlRenderer() : sdl_renderer_t() {}
    explicit SdlRenderer(sdl_window_t& window, int index, uint32_t flags);
    
    ~SdlRenderer() {
        LOG_THREAD("~SdlRenderer called SDL_DestroyRenderer");
        SDL_DestroyRenderer(sdl_renderer_t::Get());
    }
    bool v8_CreateRenderer(sdl_window_t& window, int index, uint32_t flags);
    bool v8_Clear();
    bool v8_Copy(sdl_texture_t& tex);
    bool v8_Present();
    bool v8_PresentPerformance();
    float GetPerformanceCounter() { return _performance_fps; }
    void Init(v8pp::module& m) override;
private:
    Uint64 _performance_counter;
    float _performance_fps;
};


#endif