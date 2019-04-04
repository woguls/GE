#include <sdl-modules/sdl_pixelformat.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

bool SdlPixelformat::v8_FromSurface(sdl_surface_t& sur) {
    if (sur.Get() != nullptr ) {
        return sdl_pixelformat_t::Set(sur.Get()->format);
    }
    return false;
}

uint32_t SdlPixelformat::v8_format() {
    if (sdl_pixelformat_t::Get() != nullptr ) {
        return sdl_pixelformat_t::Get()->format;
    }
    return SDL_PIXELFORMAT_UNKNOWN;
}

uint8_t SdlPixelformat::v8_BitsPerPixel() {
    if (sdl_pixelformat_t::Get() != nullptr ) {
        return sdl_pixelformat_t::Get()->BitsPerPixel;
    }
    return 0;

}

uint8_t SdlPixelformat::v8_BytesPerPixel() {
    if (sdl_pixelformat_t::Get() != nullptr ) {
        return sdl_pixelformat_t::Get()->BytesPerPixel;
    }
    return 0;
}

void SdlPixelformat::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlPixelformat> SdlPixelformat_class(isolate);
    SdlPixelformat_class
        .ctor<>()
        .set("FromSurface", &SdlPixelformat::v8_FromSurface)
        .set("format", &SdlPixelformat::v8_format)
        .set("BitsPerPixel", &SdlPixelformat::v8_BitsPerPixel)
        .set("BytesPerPixel", &SdlPixelformat::v8_BytesPerPixel)
        .set_const("SDL_PIXELFORMAT_UNKNOWN", SDL_PIXELFORMAT_UNKNOWN)
        .set_const("SDL_PIXELFORMAT_INDEX1LSB", SDL_PIXELFORMAT_INDEX1LSB)
        .set_const("SDL_PIXELFORMAT_INDEX1MSB", SDL_PIXELFORMAT_INDEX1MSB)
        .set_const("SDL_PIXELFORMAT_INDEX4LSB", SDL_PIXELFORMAT_INDEX4LSB)
        .set_const("SDL_PIXELFORMAT_INDEX4MSB", SDL_PIXELFORMAT_INDEX4MSB)
        .set_const("SDL_PIXELFORMAT_INDEX8", SDL_PIXELFORMAT_INDEX8)
        .set_const("SDL_PIXELFORMAT_RGB332", SDL_PIXELFORMAT_RGB332)
        .set_const("SDL_PIXELFORMAT_RGB444", SDL_PIXELFORMAT_RGB444)
        .set_const("SDL_PIXELFORMAT_RGB555", SDL_PIXELFORMAT_RGB555)
        .set_const("SDL_PIXELFORMAT_BGR555", SDL_PIXELFORMAT_BGR555)
        .set_const("SDL_PIXELFORMAT_ARGB4444", SDL_PIXELFORMAT_ARGB4444)
        .set_const("SDL_PIXELFORMAT_RGBA4444", SDL_PIXELFORMAT_RGBA4444)
        .set_const("SDL_PIXELFORMAT_ABGR4444", SDL_PIXELFORMAT_ABGR4444)
        .set_const("SDL_PIXELFORMAT_BGRA4444", SDL_PIXELFORMAT_BGRA4444)
        .set_const("SDL_PIXELFORMAT_ARGB1555", SDL_PIXELFORMAT_ARGB1555)
        .set_const("SDL_PIXELFORMAT_RGBA5551", SDL_PIXELFORMAT_RGBA5551)
        .set_const("SDL_PIXELFORMAT_ABGR1555", SDL_PIXELFORMAT_ABGR1555)
        .set_const("SDL_PIXELFORMAT_BGRA5551", SDL_PIXELFORMAT_BGRA5551)
        .set_const("SDL_PIXELFORMAT_RGB565", SDL_PIXELFORMAT_RGB565)
        .set_const("SDL_PIXELFORMAT_BGR565", SDL_PIXELFORMAT_BGR565)
        .set_const("SDL_PIXELFORMAT_RGB24", SDL_PIXELFORMAT_RGB24)
        .set_const("SDL_PIXELFORMAT_BGR24", SDL_PIXELFORMAT_BGR24)
        .set_const("SDL_PIXELFORMAT_RGB888", SDL_PIXELFORMAT_RGB888)
        .set_const("SDL_PIXELFORMAT_RGBX8888", SDL_PIXELFORMAT_RGBX8888)
        .set_const("SDL_PIXELFORMAT_BGR888", SDL_PIXELFORMAT_BGR888)
        .set_const("SDL_PIXELFORMAT_BGRX8888", SDL_PIXELFORMAT_BGRX8888)
        .set_const("SDL_PIXELFORMAT_ARGB8888", SDL_PIXELFORMAT_ARGB8888)
        .set_const("SDL_PIXELFORMAT_RGBA8888", SDL_PIXELFORMAT_RGBA8888)
        .set_const("SDL_PIXELFORMAT_ABGR8888", SDL_PIXELFORMAT_ABGR8888)
        .set_const("SDL_PIXELFORMAT_BGRA8888", SDL_PIXELFORMAT_BGRA8888)
        .set_const("SDL_PIXELFORMAT_ARGB2101010", SDL_PIXELFORMAT_ARGB2101010)
        .set_const("SDL_PIXELFORMAT_RGBA32", SDL_PIXELFORMAT_RGBA32)
        .set_const("SDL_PIXELFORMAT_ARGB32", SDL_PIXELFORMAT_ARGB32)
        .set_const("SDL_PIXELFORMAT_BGRA32", SDL_PIXELFORMAT_BGRA32)
        .set_const("SDL_PIXELFORMAT_ABGR32", SDL_PIXELFORMAT_ABGR32)
        .set_const("SDL_PIXELFORMAT_YV12", SDL_PIXELFORMAT_YV12)
        .set_const("SDL_PIXELFORMAT_IYUV", SDL_PIXELFORMAT_IYUV)
        .set_const("SDL_PIXELFORMAT_YUY2", SDL_PIXELFORMAT_YUY2)
        .set_const("SDL_PIXELFORMAT_UYVY", SDL_PIXELFORMAT_UYVY)
        .set_const("SDL_PIXELFORMAT_YVYU", SDL_PIXELFORMAT_YVYU)
        .set_const("SDL_PIXELFORMAT_NV12", SDL_PIXELFORMAT_NV12)
        .set_const("SDL_PIXELFORMAT_NV21", SDL_PIXELFORMAT_NV21)
        ;

    LOG("Initialized SDL.Pixelformat()");
    m.set("Pixelformat", SdlPixelformat_class);

}
