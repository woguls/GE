#include <sdl-modules/sdl_renderer.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

bool SdlRenderer::v8_Clear() {
    if ( sdl_renderer_t::Get() == nullptr ) {
        LOG("Attempted clear on an empty renderer");
        return false;
    }
    SDL_RenderClear(sdl_renderer_t::Get());
    return true;
}

bool SdlRenderer::v8_Copy(sdl_texture_t& tex) {
    if ( sdl_renderer_t::Get() == nullptr ) {
        LOG("Attempted copy on an empty renderer");
        return false;
    }
    if ( tex.Get() == nullptr ) {
        LOG("Attempted copy on an empty texture");
        return false;
    }
    SDL_RenderCopy(sdl_renderer_t::Get(), tex.Get(), NULL, NULL);
    return true;

}
bool SdlRenderer::v8_Present() {
    if ( sdl_renderer_t::Get() == nullptr ) {
        LOG("Attempted present on an empty renderer");
        return false;
    }
    SDL_RenderPresent(sdl_renderer_t::Get());
    return true;
}

bool SdlRenderer::v8_PresentPerformance() {
    bool result = v8_Present();
    static Uint64 pc = 0;
    Uint64 pc_new = SDL_GetPerformanceCounter();
    _performance_counter = pc_new - pc;
    _performance_fps = static_cast<float>(SDL_GetPerformanceFrequency()) / static_cast<float>(_performance_counter);
    pc = pc_new;
    return result;
}

void SdlRenderer::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlRenderer> SdlRenderer_class(isolate);

    SdlRenderer_class
        .ctor<>()
        .ctor<sdl_window_t&, int, uint32_t>()
        .inherit<sdl_renderer_t>()
        .set("Clear", &SdlRenderer::v8_Clear)
        .set("Copy", &SdlRenderer::v8_Copy)
        .set("Present", &SdlRenderer::v8_Present)
        .set("PresentPerformance", &SdlRenderer::v8_PresentPerformance)
        .set("PerformanceCounter", v8pp::property(&SdlRenderer::GetPerformanceCounter))

        ;

    LOG("Initialized SDL.Rederer()");
    m.set("Renderer", SdlRenderer_class);
}

SdlRenderer::SdlRenderer(sdl_window_t& window, int index, uint32_t flags)
:   _performance_counter{0},
    sdl_renderer_t()
{
    if ( window.Get() == nullptr ) return;
    SDL_Renderer* ren = SDL_CreateRenderer(window.Get(), index, flags);
    if (ren == nullptr ) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return;
    }
    if (sdl_renderer_t::Set(ren) ) {
        LOG_THREAD("created sdl renderer");
    }
    else LOG_THREAD("error setting pointer to sdl renderer");
}

bool SdlRenderer::v8_CreateRenderer(sdl_window_t& window, int index, uint32_t flags) {
    if ( sdl_renderer_t::Get() != nullptr ) {
        LOG("Called CreateRenderer on non-empty renderer");
        return false;
    }
    if ( window.Get() == nullptr ) {
        LOG("Attempted to created renderer from null window");
        return false;
    }
    SDL_Renderer* ren = SDL_CreateRenderer(window.Get(), index, flags);
    if (ren == nullptr ) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return sdl_renderer_t::Set(ren);
}

