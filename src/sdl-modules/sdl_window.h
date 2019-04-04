#ifndef __V8MODULES_SDL_WINDOW_H__
#define __V8MODULES_SDL_WINDOW_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <sdl-modules/types.h>
#include <string>
#include <common-util.h>


class SdlWindow : public v8Embeddable, public sdl_window_t, public sdl_rect_t {
public:
    explicit SdlWindow()
    :   sdl_window_t(),
        sdl_rect_t()
    { }
    explicit SdlWindow(const std::string title,
                                    int         x,
                                    int         y,
                                    int         w,
                                    int         h,
                                    Uint32      flags);

    ~SdlWindow() {
        LOG_THREAD("~SdlWindow called SDL_DestroyWindow");
        SDL_DestroyWindow(sdl_window_t::Get());
    }
    bool v8_CreateWindow(const std::string& title,
                                    int         x,
                                    int         y,
                                    int         w,
                                    int         h,
                                    Uint32      flags);
    void Init(v8pp::module& m) override;
};


#endif