#ifndef __V8MODULES_TILELAYER_SURFACE_H__
#define __V8MODULES_TILELAYER_SURFACE_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <string>
#include <common-util.h>
#include <sdl-modules/sdl_surface.h>
#include <sdl-modules/types.h>
#include <resource/resource_types.h>
#include <resource-modules/tileset_surface.h>

#include <vector>

class TileLayerSurfaceModule : public SdlSurface, public resource_tilelayer_t {
public:
    TileLayerSurfaceModule()
    :   SdlSurface(), resource_tilelayer_t()
    {
        SdlSurface::dirty = false;
    }

    TileLayerSurfaceModule(std::string name, resource_tilemap_t& map);
protected:
    bool v8_AddTileSet(TileSetSurfaceModule& tileset);
    bool v8_UpdateSurface();
private:
    void Init(v8pp::module& m) override;
    std::string _name;
    int _x;
    int _y;
    int _z;
    int _width;
    int _height;
    uint8_t _opacity;
    std::vector<int> _tile_array;
    TileSetSurfaceModule* _tileset_ptr;
};


#endif