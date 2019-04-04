#ifndef __RESOURCE_DIRECTORY_H__
#define __RESOURCE_DIRECTORY_H__

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <mutex>

#include <resource/reference.h>

namespace fs = std::filesystem;

class ResourceDirectory {
// because all ResourceReferences have a static pointer to a ResourceDirectory, this class must be a singleton!
public:
    explicit ResourceDirectory( ) {}
    ~ResourceDirectory();
    void BuildFromPath(std::string path);
    ResourceReference* Find(const std::string& identifier) const;
    ResourceReference* Match(const std::string& identifier);
    std::string GetPath() { return std::string(_root_path); }
    int Size() { return _resource_map.size(); }
    void Print();
private:
    void InitSDL_image(std::set<resource_type>& _types_present);
    const resource_type GetResourceTypeFromPath(fs::path const& p);
    const resource_type FindXMLType(fs::path const& p);
    const bool IsTileMap(fs::path const& path);
    const bool AddReference( ResourceReference* ref, std::set<resource_type>& _types_present);

    static std::mutex _resource_map_mutex;
    static std::map<std::string, ResourceReference*> _resource_map;
    fs::path _root_path;
};

#endif