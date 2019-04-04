#include <resource/reference.h>
#include <resource/directory.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include <SDL_image.h>
#include <fstream>

ResourceDirectory* ResourceReference::_resource_directory = nullptr;


ResourceReference::ResourceReference(const resource_type t, const fs::path& path)
: _type{t}, _locator{path} {
    std::string s{path};
    std::replace(s.begin(), s.end(), '\\', ':' );
    std::replace(s.begin(), s.end(), '/', ':' );
    _name.assign(s);
}

const std::string ResourceReference::GetTypeDescription() const {
        auto it = ResourceExtensionMap.find(GetType());
        if ( it != ResourceExtensionMap.end())
            return it->second;
        return "Unknown type (should not be possible)";
}

const std::string ResourceReference::GetDirString() const {
    fs::path temp{_locator};
    return temp.remove_filename().string();
}

const std::string ResourceReference::GetIdentifierPrefix() const {
    std::string s = GetDirString();
    std::replace(s.begin(), s.end(), '\\', ':' );
    std::replace(s.begin(), s.end(), '/', ':' );
    return s;
}

std::ostream& operator<<(std::ostream& os, const ResourceReference& rs)
{
    rs.Print(os);
    return os;
}

