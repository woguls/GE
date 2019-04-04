#include <resource-modules/tileset_surface.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

TileSetSurfaceModule::TileSetSurfaceModule(std::string name, resource_tilemap_t& map) {
    typedef std::unique_ptr<tileset_data> tileset_vector_t;
    const tilemap_data* tilemap = map.Get();
    if (tilemap == nullptr ) {
        LOG("Attempted to get tile set from empty map");
        return;
    }

    const tileset_list_t& tileset_list = tilemap->tilesets;
    for (const tileset_vector_t& l : tileset_list) {
        const tileset_data* tileset_data_ptr = l.get();
        if (tileset_data_ptr->name == name) {
            tile_width = tileset_data_ptr->tile_width;
            tile_height = tileset_data_ptr->tile_height;
            margin = tileset_data_ptr->margin;
            spacing = tileset_data_ptr->spacing;
            tile_count = tileset_data_ptr->tile_count;
            columns = tileset_data_ptr->columns;
            offset_x = tileset_data_ptr->offset_x;
            offset_y = tileset_data_ptr->offset_y;
            first_gid = tileset_data_ptr->first_gid;
            // *(tileset_data_ptr->_image.image);
            SdlSurface::CreateSurfaceFromReference(*(tileset_data_ptr->_image.image));

        }

    }
}

bool TileSetSurfaceModule::SetTileRect(int tileId) {
    int row = (tileId - 1) % columns;
    int col = (tileId - 1) / columns;

    int x = margin + row*(tile_width + spacing);
    int y = margin + col*(tile_height + spacing);

    SdlSurface::_x() = x;
    SdlSurface::_y() = y;

    SdlSurface::_w() = tile_width;
    SdlSurface::_h() = tile_height;
    return true;
}

void TileSetSurfaceModule::Init(v8pp::module& m) {
    // SdlSurface::Init(m);
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<TileSetSurfaceModule> TileSetSurfaceModule_class(isolate);

    TileSetSurfaceModule_class
        .ctor<std::string, resource_tilemap_t&>()
        .inherit<SdlSurface>()
        .set("SetTile", &TileSetSurfaceModule::SetTileRect)
        .set("TileWidth", v8pp::property(&TileSetSurfaceModule::GetTileWidth, &TileSetSurfaceModule::SetTileWidth))
        .set("TileHeight", v8pp::property(&TileSetSurfaceModule::GetTileHeight, &TileSetSurfaceModule::SetTileHeight))
        .set("Spacing", v8pp::property(&TileSetSurfaceModule::GetSpacing, &TileSetSurfaceModule::SetSpacing))
        .set("Margin", v8pp::property(&TileSetSurfaceModule::GetMargin, &TileSetSurfaceModule::SetMargin))
        .set("TileCount", v8pp::property(&TileSetSurfaceModule::GetTileCount, &TileSetSurfaceModule::SetTileCount))
        .set("Columns", v8pp::property(&TileSetSurfaceModule::GetColumns, &TileSetSurfaceModule::SetColumns))

        ;

    LOG("Initialized TileSetSurface()");
    m.set("TileSetSurface", TileSetSurfaceModule_class);

}
