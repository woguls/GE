#ifndef __SDL_MODULES_TYPES_H__
#define __SDL_MODULES_TYPES_H__
#include <shell/v8_type_wrapper.h>
#include <sdl.h>
#include <SDL_ttf.h>
#include <SDL_events.h>

typedef WrapPtr<SDL_Window> sdl_window_t;
typedef WrapPtr<SDL_Renderer> sdl_renderer_t;
typedef WrapPtr<SDL_Surface> sdl_surface_t;
typedef WrapPtr<SDL_Texture> sdl_texture_t;
typedef WrapPtr<SDL_Rect> sdl_rect_t;
typedef WrapPtr<SDL_PixelFormat> sdl_pixelformat_t;
typedef WrapPtr<TTF_Font> sdl_ttf_font_t;
typedef WrapPtr<SDL_Event> sdl_event_t;

#endif
