#ifndef __V8MODULES_SDL_SURFACE_H__
#define __V8MODULES_SDL_SURFACE_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <string>
#include <sdl-modules/types.h>
#include <common-util.h>
#include <resource/resource_types.h>
#include <map>
#include <shell/v8_type_wrapper.h>

class SdlSurface
:   public v8Embeddable,
    public sdl_surface_t,
    public sdl_rect_t
{
friend class TileSetSurfaceModule;
friend class TileLayerSurfaceModule;
public:
    explicit SdlSurface()
    :   dirty{false},
        sdl_surface_t()
    {
      SDL_Rect* rect = new SDL_Rect;
      if (rect == nullptr) {
        LOG(SDL_GetError());
      }
      if ( ! sdl_rect_t::Set(rect)) {
        LOG("Error setting sdl_rect_t");
      }
    }

    ~SdlSurface() {
        LOG_THREAD("~SdlSurface called SDL_FreeSurface");
        SDL_FreeSurface(sdl_surface_t::Get());
    }

    std::map<std::string, int> v8_Dimensions();
    uint32_t v8_Format();

    bool v8_ReformatForWindow(sdl_window_t& win);

    bool v8_CreateTTFSurface(sdl_ttf_font_t& font, std::string text);
    
    bool v8_CreateRGBSurfaceWithFormat(uint32_t flags,
                                            int    width,
                                            int    height,
                                            int    depth,
                                            uint32_t format);

    bool v8_SDL_CreateRGBSurface(Uint32 flags,
                                  int    width,
                                  int    height,
                                  int    depth,
                                  Uint32 Rmask,
                                  Uint32 Gmask,
                                  Uint32 Bmask,
                                  Uint32 Amask);

    bool v8_BlitFrom(const v8::FunctionCallbackInfo<v8::Value>& args);
    bool v8_UpdateBlits();
    bool v8_BlitSurface(SdlSurface& surf);
    bool v8_CreateSurfaceFromReference(resource_reference_t& ref);
    bool CreateSurfaceFromReference(const ResourceReference& ref);

    uint8_t v8_GetSurfaceAlphaMod();
    bool v8_SetSurfaceAlphaMod(uint8_t alpha);
    // SDL_LockSurface
    // SDL_MUSTLOCK

private:
    int& _w() { return sdl_rect_t::Get()->w; }
    int& _h() { return sdl_rect_t::Get()->h; }
    int& _x() { return sdl_rect_t::Get()->x; }
    int& _y() { return sdl_rect_t::Get()->y; }

    void Init(v8pp::module& m) override;

    bool dirty;
};


#endif