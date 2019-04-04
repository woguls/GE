#ifndef __V8MODULES_SDL_EVENT_H__
#define __V8MODULES_SDL_EVENT_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <sdl-modules/types.h>
#include <string>
#include <common-util.h>


class SdlEvent : public v8Embeddable, public sdl_event_t {
public:
    explicit SdlEvent() : sdl_event_t() {
      sdl_event_t::Set(&event);
    }
    ~SdlEvent() {
        LOG_THREAD("~SdlEvent called");
    }
    
    int v8_PollEvent();

    Uint32 v8_Type();
    
    void Init(v8pp::module& m) override;
private:
  SDL_Event event;
};


#endif