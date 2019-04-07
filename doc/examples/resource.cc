#include <resource/directory.h>
#include <iostream>

int main(int argc, char** argv) {
/* [ResourceDirectory-usage] */
    ResourceDirectory dir;
    dir.BuildFromPath("res");
    const ResourceReference* ref = dir.Find("res:examples:test_hexagonal_tile_60x60x30.png");
/* [ResourceDirectory-usage] */

    std::cout << "found res:examples:test_hexagonal_tile_60x60x30.png is " << *ref << std::endl;
    return 0;
}