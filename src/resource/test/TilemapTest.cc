#include <engine/resource/directory.h>
#include <engine/resource/tilemap.h>
#include <map>
#include <iostream>
#include <typeinfo>


int main(int argc, char** argv) {
    ::engine::resource::ResourceDirectory dir;
    dir.BuildFromPath("res");
    const ::engine::resource::ResourceReference* ref = dir.Find("res:examples:perspective_walls.tmx");
    if ( ref == nullptr ) {
        std::cout << "tilemap not found!\n";
        return 0;
    }


    engine::resource::tilemap::TileMapParser tm(&dir, *ref);

    std::unique_ptr<const ::engine::resource::tilemap::tilemap_data> tmdata = tm.Parse();
    std::cout << "TileMapParser.Parse(): " << tmdata.get() << std::endl;

    std::unique_ptr<const ::engine::resource::tilemap::tilemap_data> tmdata1 = tm.Parse();
    std::cout << "TileMapParser.Parse(): " << tmdata1.get() << std::endl;

    std::cout << *(tmdata1.get()) << std::endl;
    return 1;
}