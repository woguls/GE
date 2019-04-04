#ifndef __V8MODULES_SDL_RECT_H__
#define __V8MODULES_SDL_RECT_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <sdl-modules/types.h>
#include <string>
#include <common-util.h>


class SdlRect : public v8Embeddable, public sdl_rect_t
{
public:
    explicit SdlRect() : sdl_rect_t() {}
    explicit SdlRect(int x, int y, int w, int h) {
        if (sdl_rect_t::Get() == nullptr && sdl_rect_t::Set(new SDL_Rect{x,y,w,h}) ) {
            return;
        }
        else LOG("Failed to create new SDL_Rect");
    }

    int _x() { return sdl_rect_t::Get()->x; }
    int _y() { return sdl_rect_t::Get()->y; }
    int _w() { return sdl_rect_t::Get()->w; }
    int _h() { return sdl_rect_t::Get()->h; }
    ~SdlRect() {
        delete sdl_rect_t::Get();
    }
    void Init(v8pp::module& m) override;
};



#endif