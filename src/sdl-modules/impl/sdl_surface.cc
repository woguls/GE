#include <sdl-modules/sdl_surface.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

void SdlSurface::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlSurface> SdlSurface_class(isolate);

    SdlSurface_class
        .ctor<>()
        .inherit<sdl_surface_t>()
        .inherit<sdl_rect_t>()
        .set("Dimensions", &SdlSurface::v8_Dimensions)
        .set("Format", &SdlSurface::v8_Format)
        .set("CreateRGBSurfaceWithFormat", &SdlSurface::v8_CreateRGBSurfaceWithFormat)
        .set("CreateRGBSurface", &SdlSurface::v8_SDL_CreateRGBSurface)
        .set("CreateSurfaceFromResource", &SdlSurface::v8_CreateSurfaceFromReference)
        .set("CreateTTFSurface", &SdlSurface::v8_CreateTTFSurface)
        .set("ReformatForWindow", &SdlSurface::v8_ReformatForWindow)
        .set("GetSurfaceAlphaMod", &SdlSurface::v8_GetSurfaceAlphaMod)
        .set("SetSurfaceAlphaMod", &SdlSurface::v8_SetSurfaceAlphaMod)
        .set("BlitSurface", &SdlSurface::v8_BlitSurface)
        ;

    LOG("Initialized SDL.Surface()");
    m.set("Surface", SdlSurface_class);
}

bool SdlSurface::v8_BlitSurface(SdlSurface& surf) {
    if (surf.sdl_surface_t::Get() == nullptr || sdl_surface_t::Get() == nullptr ) {
        LOG("Attempted to blit empty surface");
        return false;
    }

    if ( SDL_BlitSurface(
        surf.sdl_surface_t::Get(),
        surf.sdl_rect_t::Get(),
        sdl_surface_t::Get(),
        sdl_rect_t::Get() ) !=0 )
    {
        LOG(SDL_GetError());
        return false;
    }
    return true;
}

bool SdlSurface::v8_CreateTTFSurface(sdl_ttf_font_t& font, std::string text) {
    const SDL_Color fg={0,0,0,255};
    if ( font.Get() == nullptr) {
        LOG("Attempted to render text with empty font");
        return false;
    }
    SDL_Surface* surf = sdl_surface_t::Get();
    SDL_FreeSurface(surf);
    surf = TTF_RenderText_Solid(font.Get(),text.c_str(),fg);
    if ( surf == nullptr) {
        LOG(TTF_GetError());
        return false;
    }
        sdl_rect_t::Get()->x = 0;
        sdl_rect_t::Get()->y = 0;
        sdl_rect_t::Get()->w = surf->w;
        sdl_rect_t::Get()->h = surf->h;
        SDL_UnlockSurface(surf);
    sdl_surface_t::Reset(surf);
    return true;
}

bool SdlSurface::v8_CreateRGBSurfaceWithFormat(uint32_t flags,
                                            int    width,
                                            int    height,
                                            int    depth,
                                            uint32_t format)
{
    SDL_Surface* surf;
    surf = SDL_CreateRGBSurfaceWithFormat(flags, width, height, depth, format);
    if (surf == nullptr) {
        LOG("SDL_CreateRGBSurfaceWithFormat() failed:");
        LOG(SDL_GetError());
        return false;
    }
    return sdl_surface_t::Set(surf);
}

bool SdlSurface::CreateSurfaceFromReference(const ResourceReference& ref) {
    if (sdl_surface_t::Get() != nullptr) {
        LOG("Attempted to load image to non empty surface");
        return false;
    }
    resource_type rt = ref.GetType();
    if ( rt == resource_png || rt == resource_bmp || rt == resource_jpg || rt == resource_tiff ) {
        SDL_Surface* sur;
        std::string path{ref.GetPath()};
        sur = IMG_Load( path.c_str() );
        if (sur == nullptr ) {
            LOG("unable to load image:");
            LOG(path.c_str());
        }
        sdl_rect_t::Get()->x = 0;
        sdl_rect_t::Get()->y = 0;
        sdl_rect_t::Get()->w = sur->w;
        sdl_rect_t::Get()->h = sur->h;

        return sdl_surface_t::Set( sur );
    }
    else {
       std::string message = "Reference of type " + std::to_string(ref.GetType()) + std::string(" is not an image");
        LOG(message.c_str());
        return false;
    }
    return false;
}

bool SdlSurface::v8_CreateSurfaceFromReference(resource_reference_t& ref) {
    if (sdl_surface_t::Get() != nullptr) {
        LOG("Attempted to load image to non empty surface");
        return false;
    }
    if (ref.Get() == nullptr ) {
        LOG("Attempted to create surface from empty reference");
        return false;
    }
    resource_type rt = ref.Get()->GetType();
    if ( rt == resource_png || rt == resource_bmp || rt == resource_jpg || rt == resource_tiff ) {
        SDL_Surface* sur;
        std::string path{ref.Get()->GetPath()};
        sur = IMG_Load( path.c_str() );
        if (sur == nullptr ) {
            LOG("unable to load image:");
            LOG(path.c_str());
        }
        sdl_rect_t::Get()->x = 0;
        sdl_rect_t::Get()->y = 0;
        sdl_rect_t::Get()->w = sur->w;
        sdl_rect_t::Get()->h = sur->h;

        return sdl_surface_t::Set( sur );
    }
    else {
       std::string message = "Reference is of type " + std::to_string(ref.Get()->GetType()) + std::string(" not an image");
        LOG(message.c_str());
        return false;
    }
    return false;
}

std::map<std::string, int> SdlSurface::v8_Dimensions() {
    if ( sdl_surface_t::Get() != nullptr) {
            return { {"w", sdl_surface_t::Get()->w},
                     {"h", sdl_surface_t::Get()->h} };
    }
    return { {"w", 0},
         {"h", 0} };

}

uint8_t SdlSurface::v8_GetSurfaceAlphaMod() {
    if ( sdl_surface_t::Get() == nullptr ) {
        LOG("Attempted to get transparency of empty surface");
        return 0;
    }
    Uint8 alpha;
    if (SDL_GetSurfaceAlphaMod( sdl_surface_t::Get(), &alpha) != 0) {
        LOG(SDL_GetError());
        return 0;
    }
    return alpha;
}

bool SdlSurface::v8_SetSurfaceAlphaMod(uint8_t alpha) {
    if ( sdl_surface_t::Get() == nullptr ) {
        LOG("Attempted to set transparency of empty surface");
        return false;
    }
    if (SDL_SetSurfaceAlphaMod( sdl_surface_t::Get(), alpha) != 0) {
        LOG(SDL_GetError());
        return false;
    }
    return true;
}

uint32_t SdlSurface::v8_Format() {
    if (sdl_surface_t::Get() != nullptr ) {
        return sdl_surface_t::Get()->format->format;
    }
    return 0;
}

bool SdlSurface::v8_ReformatForWindow(sdl_window_t& win) {
    if (sdl_surface_t::Get() == nullptr) {
        LOG("Attempted format empty surface");
        return false;
    }
    if (win.Get() == nullptr ) {
        LOG("Attempted to find format of empty window");
        return false;
    }
    SDL_Surface* ws = SDL_GetWindowSurface(win.Get());
    if (ws == nullptr ) {
        LOG(SDL_GetError());
        return false;
    }
    SDL_Surface* newsurface = SDL_ConvertSurface( sdl_surface_t::Get(), ws->format, 0 );
    if (newsurface == nullptr) {
        LOG(SDL_GetError());
        return false;
    }
    SDL_FreeSurface(sdl_surface_t::Get());
        sdl_rect_t::Get()->x = 0;
        sdl_rect_t::Get()->y = 0;
        sdl_rect_t::Get()->w = newsurface->w;
        sdl_rect_t::Get()->h = newsurface->h;

    return sdl_surface_t::Reset(newsurface);
}

bool SdlSurface::v8_SDL_CreateRGBSurface(Uint32 flags,
                                  int    width,
                                  int    height,
                                  int    depth,
                                  Uint32 Rmask,
                                  Uint32 Gmask,
                                  Uint32 Bmask,
                                  Uint32 Amask)
{
    SDL_Surface* surf;
    surf = SDL_CreateRGBSurface(flags,width,height,depth,Rmask,Gmask,Bmask,Amask);
    if (surf == nullptr) {
        LOG("SDL_CreateRGBSurfaceWithFormat() failed:");
        LOG(SDL_GetError());
        return false;
    }
    return sdl_surface_t::Set(surf);

}
