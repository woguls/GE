#include <resource-modules/tilelayer_surface.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

bool TileLayerSurfaceModule::v8_UpdateSurface() {
    if (_tileset_ptr == nullptr) {
        LOG("Attempted to update tile layer without a tileset");
        return false;
    }

    if (SdlSurface::dirty) {
        int tile_width = _tileset_ptr->tile_width;
        int tile_height = _tileset_ptr->tile_height;

        for (int x = 0; x < _width; ++x) {
        for (int y = 0; y < _height; ++y) {
            int tile = _tile_array[y*_width + x];
            _tileset_ptr->SetTileRect(tile);
            SdlSurface::_x() = x*tile_width;
            SdlSurface::_y() = y*tile_height;
            SdlSurface::v8_BlitSurface( *_tileset_ptr);
        }
        }
    }

    return true;
}

TileLayerSurfaceModule::TileLayerSurfaceModule( std::string name, resource_tilemap_t& map) 
:   _name{name}
{
    SdlSurface::dirty = true;
    typedef std::unique_ptr<tilelayer_data> tilelayer_vector_t;
    const tilemap_data* tilemap = map.Get();

    if (tilemap == nullptr) {
        LOG("Attempted to get tile layer from empty map");
        return;
    }
    const tilelayer_list_t& layer_list = tilemap->tilelayers;

    for (const tilelayer_vector_t& l : layer_list) {
        const tilelayer_data* layer_data_ptr = l.get();
        if (layer_data_ptr->name == _name) {
            _x = layer_data_ptr->x;
            _y = layer_data_ptr->y;
            _z = layer_data_ptr->z;
            _width = map.Get()->width;
            _height = map.Get()->height;
            _opacity = 255* (layer_data_ptr->opacity);
            _tile_array = layer_data_ptr->_tiles;
        }
    }
}

bool TileLayerSurfaceModule::v8_AddTileSet(TileSetSurfaceModule& tileset) {
    _tileset_ptr = &tileset;
    return true;
}

void TileLayerSurfaceModule::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<TileLayerSurfaceModule> TileLayerSurfaceModule_class(isolate);

    TileLayerSurfaceModule_class
        .ctor<std::string, resource_tilemap_t&>()
        .inherit<SdlSurface>()
        .set("AddTileSet", &TileLayerSurfaceModule::v8_AddTileSet)
        .set("UpdateSurface", &TileLayerSurfaceModule::v8_UpdateSurface)
        ;

    LOG("Initialized TileLayerSurface()");
    m.set("TileLayerSurface", TileLayerSurfaceModule_class);
}
