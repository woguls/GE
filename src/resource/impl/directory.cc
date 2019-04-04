#include <resource/directory.h>
#include <iostream>
#include <SDL_image.h>
#include <tinyxml2.h>


std::mutex ResourceDirectory::_resource_map_mutex;
std::map<std::string, ResourceReference*> ResourceDirectory::_resource_map;

ResourceDirectory::~ResourceDirectory() {
    for (auto it: _resource_map)
        delete it.second;
}

void ResourceDirectory::Print() {
    for (auto it : _resource_map ) {
        std::cout << *(it.second) << std::endl;
    }
}

const resource_type ResourceDirectory::GetResourceTypeFromPath(fs::path const& path) {
    const std::string extension = path.extension().string();
    auto it = ExtensionResourceMap.find(extension);
    if ( it != ExtensionResourceMap.end())
        return it->second;
    return resource_unknown;
}

ResourceReference* ResourceDirectory::Find(const std::string& identifier) const {
    auto it = _resource_map.find(identifier);
    if (it != _resource_map.end())
        return it->second;
    return nullptr;
}

ResourceReference* ResourceDirectory::Match(const std::string& identifier) {
    auto it = _resource_map.find(identifier);
    if (it != _resource_map.end())
        return it->second;
    return nullptr;
}

const bool ResourceDirectory::AddReference(ResourceReference* r, std::set<resource_type>& _types_present) {
    if (r->GetResourceDirectory() == nullptr)
        r->SetResourceDirectory(this);
    _resource_map.emplace(std::make_pair(r->GetIdentifier(), r) );
    _types_present.insert(r->GetType());
    // std::cout << "key: " << r->GetIdentifier() << std::endl;
    // std::cout << "Description: " << r->GetTypeDescription() << std::endl;
    // std::cout << "found: " << *r << std::endl;
    // std::cout << std::endl;

    return true;
}

void ResourceDirectory::BuildFromPath(std::string path) {
    _root_path = fs::current_path();
    std::set<resource_type> _types_present;
    static int index = 0;
    static int count = 0;
    {
        std::lock_guard<std::mutex> lock1(_resource_map_mutex);
        for(auto& p: fs::recursive_directory_iterator(path))
        {
            if (p.is_regular_file()  ) {
                count++;
                const fs::path path = p.path();

                // try to assign a type for the file
                // currently we recognize images by their extensions,
                // or xml files by attempting to parse them
                resource_type rt = GetResourceTypeFromPath(path);
                // xml can be a tilemap or a tileset, otherwise just xml
                if (rt == resource_unknown ) rt = FindXMLType(path);

                // if it looks legit, add it to the directory
                if ( rt != resource_unknown) {
                    index++;
                    AddReference( new ResourceReference(rt, path), _types_present );
                }
            }
        }
    }

    std::cout << "registered " << index << " recognized resources of " << count << " total files under directory " << path << std::endl;
    InitSDL_image(_types_present);
}


const resource_type ResourceDirectory::FindXMLType(fs::path const& path) {

    std::ifstream ifs (path, std::ifstream::in);

    if (! ifs.good() ) {
        ifs.close();
        return resource_unknown;
    }

    std::string line;

    // check for the xml declaration first, to avoid attempting to parse every file in the directory
    std::getline(ifs, line);
    ifs.close(); // close here, because we can't pass ifstream this to tinyxml
    if ( line.find("<?xml") != std::string::npos ) {

        tinyxml2::XMLDocument doc;
        if ( doc.LoadFile( path.c_str() ) != tinyxml2::XML_SUCCESS) {
            std::cout << "Error parsing " << path << ": " << doc.ErrorName() << std::endl;
            return resource_unknown;
        }
        else {
            tinyxml2::XMLElement* root = doc.FirstChildElement( "map" );
            if (root != nullptr)
                return resource_tilemap;
            else {
                root = doc.FirstChildElement( "tileset" );
                if ( root != nullptr) 
                    return resource_tileset;
            }
        } 
    }
    return resource_unknown;
}

void ResourceDirectory::InitSDL_image(std::set<resource_type>& _types_present) {
    int flags = 0;
    for (auto& it : _types_present ) {
        switch(it) {
            case resource_jpg:
                flags |= IMG_INIT_JPG;
                break;
            case resource_png:
                flags |= IMG_INIT_PNG;
                break;
            case resource_tiff:
                flags |= IMG_INIT_TIF;
                break;
            case resource_bmp:
            default:
                break;
        }
    }
    if (flags == 0) return;
    int initted=IMG_Init(flags);
    if(initted&flags != flags) {
        std::cout << "IMG_Init: Failed to init required support!\n";
        std::cout << "IMG_Init:" << IMG_GetError() << std::endl;
        // handle error
    } else {
        std::cout << "loaded support for: "
        << (flags & IMG_INIT_JPG? "JPEG " : "")
        << (flags & IMG_INIT_PNG? "PNG " : "")
        << (flags & IMG_INIT_TIF? "TIFF " : "")
        << std::endl;
    }
}


