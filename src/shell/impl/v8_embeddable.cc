#include <shell/v8_embeddable.h>
#include <common-util.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <sdl-modules/window_flags.h>
#include <sdl-modules/render_flags.h>
#include <sdl-modules/init_flags.h>
#include <sdl-modules/sdl_pixelformat.h>
#include <sdl-modules/sdl_init.h>
#include <sdl-modules/sdl_window.h>
#include <sdl-modules/sdl_renderer.h>
#include <sdl-modules/sdl_surface.h>
#include <sdl-modules/sdl_texture_access.h>
#include <sdl-modules/sdl_texture.h>
#include <sdl-modules/sdl_rect.h>
#include <sdl-modules/sdl_ttf.h>
#include <sdl-modules/sdl_event.h>
#include <threading-modules/isolate.h>
#include <resource-modules/resource.h>
#include <resource-modules/directory.h>
#include <resource-modules/tileset_surface.h>
#include <resource-modules/tilelayer_surface.h>
#include <resource-modules/tilemap.h>
#include <sdl.h>

std::vector<std::unique_ptr<v8Embeddable>> v8EmbeddableFactory::_objects = {};


void v8EmbeddableFactory::_NewFromString(const std::string& objName) {
    LOG( (std::string("Initializing new v8 module: ") + objName).c_str()); 
    if (objName == "Isolate") {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8pp::module m(isolate);
        _objects.back().get()->Init(m);
        isolate->GetCurrentContext()->Global()->Set(
            v8::String::NewFromUtf8(isolate, "Isolate"), m.new_instance());
        LOG("Initializied Isolate");
    }

    else if (objName == "Threading") {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8pp::module m(isolate);
        _objects.push_back(std::make_unique<IsolateModule>());
        _objects.back().get()->Init(m);
        isolate->GetCurrentContext()->Global()->Set(
            v8::String::NewFromUtf8(isolate, "Threading"), m.new_instance());
        LOG("Initializied Threading");

    }
    else if (objName == "Resource") {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8pp::module m(isolate);

        InitType<resource_reference_t>(m);
        InitType<resource_directory_t>(m);
        InitType<resource_tilemap_t>(m);
        InitType<resource_tilelayer_t>(m);

        _objects.push_back(std::make_unique<ResourceModule>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<DirectoryModule>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<TileSetSurfaceModule>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<TileLayerSurfaceModule>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<TileMapModule>());
        _objects.back().get()->Init(m);

        isolate->GetCurrentContext()->Global()->Set(
            v8::String::NewFromUtf8(isolate, "Resource"), m.new_instance());
        LOG("Initializied Resource");
    }

    else if (objName == "SDL") {
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8pp::module m(isolate);
        
        InitType<sdl_window_t>(m);
        InitType<sdl_renderer_t>(m);
        InitType<sdl_surface_t>(m);
        InitType<sdl_texture_t>(m);
        InitType<sdl_rect_t>(m);
        InitType<sdl_ttf_font_t>(m);
        InitType<sdl_event_t>(m);
        // SDL.flags
        _objects.push_back(std::make_unique<SdlWindowFlags>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<SdlPixelformat>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<SdlRenderFlags>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<SdlInitFlags>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<SdlInit>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<SdlWindow>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<SdlRenderer>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<SdlSurface>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<SdlTextureAccess>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<SdlTexture>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<SdlRect>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<SdlTTF>());
        _objects.back().get()->Init(m);

        _objects.push_back(std::make_unique<SdlEvent>());
        _objects.back().get()->Init(m);

        isolate->GetCurrentContext()->Global()->Set(
            v8::String::NewFromUtf8(isolate, "SDL"), m.new_instance());
        LOG("Initializied SDL");
    }

}

void v8EmbeddableFactory::NewFromString(char const* objName) {
    _NewFromString(std::string(objName));
}

bool v8EmbeddableFactory::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<v8EmbeddableFactory> v8EmbeddableFactory_class(isolate);

    v8EmbeddableFactory_class
        .ctor<>()
        .set("require",  &v8EmbeddableFactory::NewFromString )
        ;
    // Create a module to add classes and functions to and return a
    // new instance of the module to be embedded into the v8 context
    m.set("Modules", v8EmbeddableFactory_class);

    return true;
}