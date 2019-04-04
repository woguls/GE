#include <sdl-modules/sdl_ttf.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>


SdlTTF::SdlTTF
( resource_reference_t& ref, int ptsize )
{
    ResourceReference* ref_ptr = ref.Get();
    if (ref_ptr == nullptr) {
        LOG("Attempted to create ttf from empty reference");
        return;
    }
    resource_type rt = ref_ptr->GetType();
    if ( rt == resource_ttf ) {
        if(!TTF_WasInit() && TTF_Init()==-1) {
            LOG(TTF_GetError());
            return;
        }
        TTF_Font *font;
        std::string path{ref_ptr->GetPath()};
        font = TTF_OpenFont(path.c_str(), ptsize);
        if (font == nullptr) {
            LOG("SdlTTF:");
            LOG(SDL_GetError());
            return;
        }
        else sdl_ttf_font_t::Set(font);
        return;
    }
    else {
        std::string message = "Reference of type " + std::to_string(rt) + std::string(" is not ttf");
        LOG(message.c_str());
    }
}

void SdlTTF::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<SdlTTF> SdlTTF_class(isolate);

    SdlTTF_class
        .inherit<sdl_ttf_font_t>()
        .ctor<resource_reference_t&, int>()
        ;

    LOG("Initialized SDL.TTF()");
    m.set("TTF", SdlTTF_class);

}

