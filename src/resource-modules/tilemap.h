#ifndef __V8MODULES_TILEMAP_H__
#define __V8MODULES_TILEMAP_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <string>
#include <common-util.h>
#include <resource/resource_types.h>

class TileMapModule : public v8Embeddable, public resource_tilemap_t {
public:
    explicit TileMapModule() : resource_tilemap_t() { }
    explicit TileMapModule(resource_reference_t& ref);
    
    ~TileMapModule() {
        LOG_THREAD("~resource_tilemap_t was called");
    }

private:
    void Init(v8pp::module& m) override;

};


#endif