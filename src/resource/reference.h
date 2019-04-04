#ifndef __RESOURCE_REFERENCE_H__
#define __RESOURCE_REFERENCE_H__
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;


enum resource_type {
    resource_unknown    = 0x000000,
    resource_png        = 0x000001,
    resource_bmp        = 0x000002,
    resource_jpg        = 0x000004,
    resource_tiff       = 0x000008,
    resource_xml        = 0x000010,
    resource_tilemap    = 0x000020,
    resource_tileset    = 0x000040,
    resource_ttf        = 0x000080

};

// auto cmp_str = [](char const *a, char const *b) { return std::strcmp(a, b) < 0; };

static const std::map< const resource_type, const std::string>
ResourceExtensionMap =
{
    {resource_png, "PNG" },
    {resource_bmp, "BMP" },
    {resource_jpg, "JPEG"},
    {resource_tiff, "TIFF"},
    {resource_xml, "XML"},
    {resource_tilemap, "Tilemap"},
    {resource_tileset, "Tileset"},
    {resource_ttf, "TTF Font"}
};

static const std::map<const std::string, const resource_type >
ExtensionResourceMap {{
    {".png", resource_png },
    {".bmp", resource_bmp },
    {".tiff", resource_tiff},
    {".tif", resource_tiff},
    {".jpg", resource_jpg},
    {".jpeg", resource_jpg},
    {".xml", resource_xml},
    {".tmx", resource_tilemap},
    {".tsx", resource_tileset},
    {".ttf", resource_ttf}
}};


// ResourceReference is a "locator" - a path
// and a "name" - which is a way of referring to resources in the game engine
// which is independent of their path in the filesystem
// management of the actual data should be performed by another class

// ResourceDirectory 
// 
class ResourceDirectory;

class ResourceReference {
private:
        // Prevent copy constructor.
    ResourceReference(const ResourceReference &_ref);
public:
    explicit ResourceReference(const resource_type t, const fs::path& path);
    const resource_type GetType() const { return _type; }
    const fs::path GetPath() const { return _locator; }
    const std::string GetPathString() const { return _locator.string(); }
    const std::string GetDirString() const;
    void Print(std::ostream& os) const { os << GetTypeDescription() << ", " << GetIdentifier(); }
    const std::string GetTypeDescription() const;
    const std::string GetIdentifier() const { return _name; }
    const std::string GetIdentifierPrefix() const;
    friend std::ostream& operator<<(std::ostream& os, const ResourceReference& rs);
    ResourceDirectory* GetResourceDirectory() { return _resource_directory; }
    void SetResourceDirectory(ResourceDirectory* dir) { _resource_directory = dir; }
private:
    const resource_type _type;
    const fs::path _locator; 
    std::string _name; // this should be called "identifier"
    static ResourceDirectory* _resource_directory; // this is a crtp thing, perhaps better to use real crtp ?
};
#endif
