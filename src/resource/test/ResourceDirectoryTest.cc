#include <engine/resource/directory.h>
#include <iostream>

int main(int argc, char** argv) {
    ::engine::resource::ResourceDirectory dir;
    dir.BuildFromPath("res");
    const ::engine::resource::ResourceReference* ref = dir.Find("res:examples:test_hexagonal_tile_60x60x30.png");
    std::cout << "found res:examples:test_hexagonal_tile_60x60x30.png is " << *ref << std::endl;
    return 1;
}