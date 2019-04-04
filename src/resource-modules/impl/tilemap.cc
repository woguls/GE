#include <resource-modules/tilemap.h>
#include <resource/tilemap.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

TileMapModule::TileMapModule(resource_reference_t& ref) {
    if (ref.Get() == nullptr ) {
        LOG("Attempted to create Tilemap from empty resource");
        return;
    }
    TileMapParser parser(*ref.Get());
    std::unique_ptr<const tilemap_data> tm = parser.Parse();
    resource_tilemap_t::Set(tm.release());
}

void TileMapModule::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<TileMapModule> TileMapModule_class(isolate);

    TileMapModule_class
        .ctor<resource_reference_t&>()
        .inherit<resource_tilemap_t>()
        ;

    LOG("Initialized Resource.Tilemap()");
    m.set("Tilemap", TileMapModule_class);

}
