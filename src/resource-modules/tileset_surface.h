#ifndef __V8MODULES_TILESET_SURFACE_H__
#define __V8MODULES_TILESET_SURFACE_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <string>
#include <common-util.h>
#include <sdl-modules/sdl_surface.h>

class TileSetSurfaceModule : public SdlSurface {
friend class TileLayerSurfaceModule;

public:
    explicit TileSetSurfaceModule() {}
    explicit TileSetSurfaceModule(std::string name, resource_tilemap_t& map);
protected:
    // choose the next tile to be drawn
    bool SetTileRect(int tileId);

    const int GetTileWidth() { return tile_width; }
    const int GetTileHeight() { return tile_height; }
    const int GetSpacing() { return spacing; }
    const int GetMargin() { return margin; }
    const int GetTileCount() { return tile_count; }
    const int GetColumns() { return columns; }

    void SetTileWidth(int x) { tile_width = x; }
    void SetTileHeight(int x) { tile_height = x; }
    void SetSpacing(int x) { spacing = x; }
    void SetMargin(int x) { margin = x; }
    void SetTileCount(int x) { tile_count = x; }
    void SetColumns(int x) { columns = x; }

private:
    void Init(v8pp::module& m) override;
    int tile_width;
    int tile_height;
    int spacing;
    int margin;
    int tile_count;
    int columns;
    int first_gid;
    std::string name;
    int offset_x;
    int offset_y;

};


#endif