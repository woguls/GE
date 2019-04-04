#include <resource/tilemap.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>

#define MINIZ_HEADER_FILE_ONLY
#include "miniz/miniz.c"

#include <base64/base64.h>

std::ostream& operator<< (std::ostream &o,
    const tilemap_data &a) {
  o     << "version:          " << a.version << std::endl;
  o     << "dimensions:       " << a.width << "x" << a.height << std::endl;
  o     << "next object id:   " << a.next_object_id << std::endl;
  o     << "background color: " << a.background_color << std::endl;
  o     << "render order:     " << a.render_order << std::endl;
  o     << "orientation:      " << a.orientation << std::endl;
  o     << "stagger axis:     " << a.stagger_axis << std::endl;
  o     << "stagger index:    " << a.stagger_index << std::endl;
  o     << "hex side length:  " << a.hexside_length << std::endl;
  o     << "properties: " << std::endl;
  o     << a.properties << std::endl;
  o     << a.tilesets << std::endl;
  o     << a.tilelayers << std::endl;
  o     << a.imagelayers << std::endl;

  return o;
}

std::ostream& operator<<
(std::ostream &o,const terrain_data& a) {
  o     << "name: " << a.name << std::endl;
  o     << "tileID: " << a.tileID << std::endl;
  o     << "properties: " << std::endl;
  o     << a.properties << std::endl;
  return o;
}

std::ostream& operator<<
(std::ostream &o,const tileset_data& a) {
  o     << "tileset data:" << std::endl;
  o     << std::setw(20) << "first gid: " << a.first_gid << std::endl;
  o     << std::setw(20) << "name: " << a.name << std::endl;
  o     << std::setw(20) << "tile dimensions: " << a.tile_width << "x" << a.tile_height << std::endl;
  o     << std::setw(20) << "margin: " << a.margin << std::endl;
  o     << std::setw(20) << "spacing: " << a.spacing <<std::endl;
  o     << std::setw(20) << "tile count: " << a.tile_count << std::endl;
  o     << std::setw(20) << "columns: " << a.columns << std::endl;
  o     << std::setw(20) << "offset x: " << a.offset_x << std::endl;
  o     << std::setw(20) << "offset y: " << a.offset_y << std::endl;
  o     << std::setw(20) << "transparent color: " << a.image_transparent_color << std::endl;
  o     << std::setw(20) << "image dimensions: " << a.image_width << "x" << a.image_height << std::endl;
  o     << std::setw(20) << "image data: " << a._image << std::endl;
  o     << a.terrainTypes;
  o     << "tile data list: " << std::endl;
  o     << a.tiles;
  o     << "properties: " << std::endl;
  o     << a.properties;
  return o;
}

std::ostream& operator<<
(std::ostream &o,const tile_data& a) {
  o     << "id: " << a.id << std::endl;
  o     << "type: " << a.type << std::endl;
  o     << "is animated: " << a.isAnimated << std::endl;
  o     << "has objects: " << a.hasObjects << std::endl;
  o     << "has object group: " << a.hasObjectGroup << std::endl;
  o     << "total duration: " << a.totalDuration << std::endl;
  o     << "image: " << std::endl;
  o     << a._image << std::endl;
  o     << "properties:" << std::endl;
  o     << a.properties << std::endl;
  return o;
}

std::ostream& operator<<
(std::ostream &o,const image_data& a) {
  o     << "image reference: " << (a.image != nullptr? a.image->GetIdentifier() : "null" ) << std::endl;
  o     << "image dimensions: " << a.width << "x" << a.height << std::endl;
  o     << "transparent color: " << a.transparent_color << std::endl;
  return o;
}

std::ostream& operator<< (std::ostream &o,
    const tilemap_renderorder& a) {
    if (a == renderorder_right_down)
        o << "right_down";
    else if (a == renderorder_right_up)
        o << "right_up";
    else if (a == renderorder_left_down)
        o << "left_down";
    else if (a == renderorder_left_up)
        o << "left_up";
    return o;
}

std::ostream& operator<<
(std::ostream &o, const tilemap_orientation& a) {
    if (a == orientation_orthogonal)
        o << "orthogonal";
    else if (a == orientation_isometric)
        o << "isometric";
    else if (a == orientation_staggered)
        o << "staggered";
    else if (a == orientation_hexagonal)
        o << "hexagonal";
    return o;
}

std::ostream& operator<<
(std::ostream &o, const tilemap_staggeraxis& a) {
    if (a == staggeraxis_x)
        o << "x";
    else if (a == staggeraxis_y)
        o << "y";
    return o;
}

std::ostream& operator<<
(std::ostream &o, const tilemap_staggerindex& a) {
    if (a == staggerindex_even)
        o << "even";
    else if (a == staggerindex_odd)
        o << "odd";
    return o;
}

std::ostream& operator<<
(std::ostream &o,const tilelayer_encoding& a) {
    if (a == encoding_xml)
        o << "xml";
    else if (a == encoding_base64)
        o << "base64";
    else if (a == encoding_csv)
        o << "csv";
    return o;
}

std::ostream& operator<<
(std::ostream &o, const tilelayer_compression& a) {
    if (a == compression_none)
        o << "none";
    else if (a == compression_zlib)
        o << "zlib";
    else if (a == compression_gzip)
        o << "gzip";
    return o;
}

std::ostream& operator<<
(std::ostream &o, const property_type& a) {
    if (a == property_none)
        o << "none";
    else if (a == property_string)
        o << "string";
    else if (a == property_bool)
        o << "bool";
    else if (a == property_int)
        o << "int";
    else if (a == property_float)
        o << "float";
    else if (a == property_color)
        o << "color";
    else if (a == property_file)
        o << "file";
    return o;
}

std::ostream& operator<<
(std::ostream &o, const layer_type& a) {
    if ( a & layer_tile)
        o << "tile ";
    else if (a & layer_objectgroup)
        o << "objectgroup ";
    else if ( a & layer_imagelayer)
        o << "imagelayer ";
    else if ( a & layer_grouplayer)
        o << "grouplayer";
    return o;
}

std::ostream& operator<<
(std::ostream &o, const map_property& a) {
    if (a.type == property_string)
        o <<  std::any_cast<std::string>(a.object);
    else if (a.type == property_bool)
        o <<  std::any_cast<bool>(a.object);
    else if (a.type == property_int)
        o <<  std::any_cast<int>(a.object);
    else if (a.type == property_float)
        o <<  std::any_cast<double>(a.object);
    else if (a.type == property_color)
        o <<  std::any_cast<uint32_t>(a.object);
    else if (a.type == property_file)
        o <<  "file";
    return o;
}

std::ostream& operator<<
(std::ostream &o, const tilelayer_data& a) {
    o   << "tile layer: " << std::endl;
    o   << "name: " << a.name << std::endl;
    o   << "x:" << a.x << " y:" << a.y << std::endl;
    o   << "opacity:" << a.opacity << std::endl;
    o   << "encoding: " << a.encoding << std::endl;
    o   << "compression: " << a.compression << std::endl;
    o   << "properties:\n" << a.properties;
    return o;
}

std::ostream& operator<<
(std::ostream &o,const imagelayer_data& a) {
    o   << "image layer: " << std::endl;
    o   << "name: " << a.name << std::endl;
    o   << "x:" << a.x << " y:" << a.y << std::endl;
    o   << "opacity: " << a.opacity << std::endl;
    o   << "visible: " << a.visible << std::endl;
    o   << "image data: " << a.image << std::endl;
    o   << "properties: " << a.properties << std::endl;
    return o;
}

std::ostream& operator<<
(std::ostream &o,const tilelayer_list_t& a) {
    std::cout << "tile layer list:" << std::endl;
    for (auto p = a.begin(); p != a.end(); p++ ) {
        o << *(p->get()) << std::endl;
    }
    return o;
}

std::ostream& operator<<
(std::ostream &o,const terrain_list_t& a) {
    std::cout << "terrain list:" << std::endl;
    for (auto p = a.begin(); p != a.end(); p++ ) {
        o << *(p->get()) << std::endl;
    }
    return o;
}

std::ostream& operator<<
(std::ostream &o,const tile_data_list_t& a) {
    for (auto p = a.begin(); p != a.end(); p++ ) {
        o << *(p->get()) << std::endl;
    }
    return o;
}

std::ostream& operator<<
(std::ostream &o,const property_map_t& a) {
    if (a.empty() ) {
        o << "none" << std::endl;
        return o;
    }
    for (auto p : a) {
        o << std::setw(20) << p.first << " = " << p.second << std::endl;
        o << std::setw(0);
    }
    return o;
}

std::ostream& operator<<
(std::ostream &o,const tileset_list_t& a) {
    std::cout << "tileset:" << std::endl;
    for (auto p = a.begin(); p != a.end(); p++ ) {
        o << *(p->get()) << std::endl;
    }
    return o;
}


std::ostream& operator<<
(std::ostream &o,const imagelayer_list_t& a) {
    std::cout << "iamge layer:" << std::endl;
    for (auto p = a.begin(); p != a.end(); p++ ) {
        o << *(p->get()) << std::endl;
    }
    return o;
}

std::unique_ptr<const tilemap_data> TileMapParser::Parse()
{
    tinyxml2::XMLDocument doc;
    // const std::string path { _reference.GetPath() };
    // path.assign(.c_str());
    doc.LoadFile(_reference.GetPath().c_str() );

    tilemap_data* map = new tilemap_data;

    if ( ! doc.Error())
        Parse( doc.FirstChildElement("map"), *map );

    return std::unique_ptr<const tilemap_data>(map);
}

uint32_t TileMapParser::StringToColor32(const std::string& str) {
    // We skip the first # character and then read directly the hexadecimal value
    uint32_t color = std::strtol((str.c_str() + 1), nullptr, 16);

    // If the input has the short format #RRGGBB without alpha channel we set it to 255
    if(str.length() == 7) color |= 0xff000000;

    return color;
}

std::string TileMapParser::StringToLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), 
                   [](unsigned char c){ return std::tolower(c); } // correct
                  );
    return s;
}

const bool TileMapParser::ParseProperty(const tinyxml2::XMLElement *propertyElem, map_property& prop)
{
    const tinyxml2::XMLAttribute* typeAttribute = propertyElem->FindAttribute("type");
    const char* valueAsCString = propertyElem->Attribute("value");

    std::string value;

    if (valueAsCString)
    {
        value = valueAsCString;
    }
    else
    {
        // The value of properties that contain newlines is stored in the element text.
        valueAsCString = propertyElem->GetText();
        value = valueAsCString ? valueAsCString : std::string(); 
    }

    if (typeAttribute != nullptr)
    {
        const char* typeAsCString = typeAttribute->Value();
        if (strcmp(typeAsCString, "string") == 0) {
            prop.type = property_string;
            prop.object = value;
        }
        else if (strcmp(typeAsCString, "bool") == 0) {
            prop.type = property_bool;
            value = StringToLower(value);
            if ( value == "true") prop.object = true;
            else if ( value == "false") prop.object = false;
        }
        else if (strcmp(typeAsCString, "float") == 0) {
            prop.type = property_float;
            prop.object = atof(value.c_str());
        }
        else if (strcmp(typeAsCString, "int") == 0) {
            prop.type = property_int;
            prop.object = atoi(value.c_str());
        }
        else if (strcmp(typeAsCString, "color") == 0) {
            prop.type = property_color;
            prop.object = StringToColor32(value);
        }
        else if (strcmp(typeAsCString, "file") == 0)
            prop.type = property_file;
        else {
            prop.type = property_string;
            prop.object = value;
        }
    }
    else {
        // properties without explicit types are strings in tmx files
        prop.type = property_string;
        prop.object = value;
    }

    return true;
}

const bool TileMapParser::ParseProperties(const tinyxml2::XMLNode *propertiesNode, property_map_t& map) {
    if ( propertiesNode == nullptr) return false;

    // Iterate through all of the property nodes.
    const tinyxml2::XMLNode *propertyNode = propertiesNode->FirstChildElement("property");

    while (propertyNode)
    {
        const tinyxml2::XMLElement* propertyElem = propertyNode->ToElement();

        auto nameAttrib = propertyElem->FindAttribute("name");

        if (nameAttrib == nullptr || nameAttrib->Value()[0] == 0)
        {
            propertyNode = propertyNode->NextSiblingElement("property");
            continue;
        }

        // Read the attributes of the property and add it to the map

        // this might be better:
        // std::unique_ptr<map_property> prop()
        // ParseProperty( propertyElem, prop.get())
        map_property prop;
        ParseProperty( propertyElem, prop);


        map[nameAttrib->Value()] = prop; // prob better to use unique_ptr ?
        // "Copies all the elements from x into the container, changing its size accordingly."
        // http://www.cplusplus.com/reference/map/map/operator=/

        propertyNode = propertyNode->NextSiblingElement("property");
    }

    return true;
}

const bool TileMapParser::ParseTile(const tinyxml2::XMLNode *tileNode, tile_data* tile ) {
    const tinyxml2::XMLElement *tileElem = tileNode->ToElement();
    // Parse the attributes.
    tile->id = tileElem->IntAttribute("id");
    // Parse tile type if it has one.
    if(tileElem->FindAttribute("type")) {
        tile->type = std::string(tileElem->Attribute("type"));
    }
    // Parse the properties if any.
    const tinyxml2::XMLNode *propertiesNode = tileNode->FirstChildElement( "properties");
    if (propertiesNode) {
        ParseProperties(propertiesNode, tile->properties);
    }

    // Parse the animation if there is one.
    const tinyxml2::XMLNode *animationNode = tileNode->FirstChildElement( "animation");
    // if (animationNode)
        // std::cout << "skipping animation node" << std::endl;
    // if (animationNode)
    // {
    //     isAnimated = true;

    //     const tinyxml2::XMLNode *frameNode =
    //             animationNode->FirstChildElement("frame");
    //     unsigned int durationSum = 0;

    //     while (frameNode != NULL)
    //     {
    //         const tinyxml2::XMLElement *frameElement =
    //                 frameNode->ToElement();

    //         const int tileID = frameElement->IntAttribute("tileid");
    //         const unsigned int duration = frameElement->IntAttribute(
    //                 "duration");

    //         frames.push_back(AnimationFrame(tileID, duration));
    //         durationSum += duration;

    //         frameNode = frameNode->NextSiblingElement("frame");
    //     }

    //     totalDuration = durationSum;
    // }

    const tinyxml2::XMLNode *objectGroupNode = tileNode->FirstChildElement( "objectgroup");
    if (objectGroupNode) {
                    tile->hasObjectGroup = true;
                    // std::cout << "skipping object group" << std::endl;
                    //let's only create objectGroup if it's needed, save memory
                    // objectGroup = new ObjectGroup(this);
                    // objectGroup->Parse(objectGroupNode);
                    // if (objectGroup->GetNumObjects() > 0) hasObjects = true;
    }

    const tinyxml2::XMLNode *imageNode = tileNode->FirstChildElement("image");
    if(imageNode)
        ParseImage(imageNode, &(tile->_image));

    return true;
}

const bool TileMapParser::ParseImage(const tinyxml2::XMLNode *imageNode, image_data* image) {

        const tinyxml2::XMLElement* imageElem = imageNode->ToElement();

        // Read all the attribute into member variables.
        std::string source = imageElem->Attribute("source");
        fs::path source_path = fs::path(source);
        fs::path reference_dir(_reference.GetPath());
        reference_dir.remove_filename();
        reference_dir += source_path;
        std::string s{reference_dir.lexically_normal()};
        std::replace(s.begin(), s.end(), '\\', ':' );
        std::replace(s.begin(), s.end(), '/', ':' );


        const ResourceReference* ref = _dir->Find(s);

        if (ref == nullptr) {
            const std::string id_prefix = _reference.GetIdentifierPrefix();
            const std::string fileIdentifier = id_prefix  + source;
            std::cout << "unable to find " << fileIdentifier << std::endl;
            return false;
        }
        
        std::cout << "found " << *ref << std::endl;
        image->image = ref;
        image->width = imageElem->IntAttribute("width");
        image->height = imageElem->IntAttribute("height");

        const char *trans = imageElem->Attribute("trans");
        if (trans) {
            image->transparent_color = StringToColor32(trans);
        }

        return true;
}

const bool TileMapParser::ParseTileset(const tinyxml2::XMLNode *tilesetNode, tileset_data* tileset ) {
    const tinyxml2::XMLElement *tilesetElem = tilesetNode->ToElement();

    // Read all the attributes into local variables.

    // The firstgid and source attribute are kept in the TMX map,
    // since they are map specific.
    tileset->first_gid = tilesetElem->IntAttribute("firstgid");

    // If the <tileset> node contains a 'source' tag,
    // the tileset config should be loaded from an external
    // TSX (Tile Set XML) file. That file has the same structure
    // as the <tileset> element in the TMX map.
    const char* source_name = tilesetElem->Attribute("source");
    tinyxml2::XMLDocument tileset_doc;
    if ( source_name )
    {
        const std::string id_prefix = _reference.GetIdentifierPrefix();
        const std::string fileIdentifier = id_prefix  + source_name;

        const ResourceReference* ref = _dir->Find(fileIdentifier);
        // const std::string path { _reference.GetPath() };
        // path.assign(.c_str());
        if (ref == nullptr) {
            std::cout << "unale to find " << fileIdentifier << std::endl;
            return false;
        }
        tileset_doc.LoadFile(ref->GetPath().c_str() );
        if ( tileset_doc.ErrorID() != 0) {
            std::cout << "failed to load tileset file " << ref->GetPath().c_str() << std::endl;
            return false;
        } else std::cout << "found " << *ref << std::endl;

        // Update node and element references to the new node
        tilesetNode = tileset_doc.FirstChildElement("tileset");
        if(tilesetNode == nullptr) return false;

        tilesetElem = tilesetNode->ToElement();
    }

    tileset->tile_width = tilesetElem->IntAttribute("tilewidth");
    tileset->tile_height = tilesetElem->IntAttribute("tileheight");
    tileset->margin = tilesetElem->IntAttribute("margin");
    tileset->spacing = tilesetElem->IntAttribute("spacing");
    tileset->tile_count = tilesetElem->IntAttribute("tilecount");
    tileset->columns = tilesetElem->IntAttribute("columns");
    tileset->name = tilesetElem->Attribute("name");

    // Parse the tile offset, if it exists.
    const tinyxml2::XMLNode *tileOffsetNode = tilesetNode->FirstChildElement("tileoffset");
    if (tileOffsetNode) {
        const tinyxml2::XMLElement* tileOffsetElem = tileOffsetNode->ToElement();
        tileset->offset_x = tileOffsetElem->IntAttribute("x");
        tileset->offset_y = tileOffsetElem->IntAttribute("y");
    }
    // Parse the terrain types if any.
    const tinyxml2::XMLNode *terrainTypesNode = tilesetNode->FirstChildElement("terraintypes");
    if (terrainTypesNode)  {
        const tinyxml2::XMLNode *terrainNode = terrainTypesNode->FirstChildElement("terrain");
        while (terrainNode) {
            // Read the attributes of the terrain and add it the terrainTypes vector.
            std::unique_ptr<terrain_data> terrainType = std::make_unique<terrain_data>();
            const tinyxml2::XMLElement *terrainElem = terrainNode->ToElement();
            // Parse the attributes.
            terrainType.get()->name = std::string(terrainElem->Attribute("name"));
            terrainType.get()->tileID = terrainElem->IntAttribute("tile");
            // Parse the properties if any.
            const tinyxml2::XMLNode *propertiesNode = terrainNode->FirstChildElement( "properties");
            if (propertiesNode) {
                ParseProperties(propertiesNode, terrainType.get()->properties);
            }
            tileset->terrainTypes.push_back(std::move(terrainType));

            terrainNode = terrainNode->NextSiblingElement("terrain");
        }
    }

    // Parse the image.
    const tinyxml2::XMLNode *imageNode = tilesetNode->FirstChildElement("image");
    if (imageNode) {
        ParseImage(imageNode, &(tileset->_image));
    }

    // Iterate through all of the tile elements and parse each.
    const tinyxml2::XMLNode *tileNode = tilesetNode->FirstChildElement("tile");

    int tId = 0;
    while(tileNode) {
        std::unique_ptr<tile_data> tile = std::make_unique<tile_data>();
        tile.get()->id = tId++;
        ParseTile(tileNode, tile.get());
        tileset->tiles.push_back(std::move(tile));
        tileNode = tileNode->NextSiblingElement("tile");
    }


    // Parse the properties if any.
    const tinyxml2::XMLNode *propertiesNode = tilesetNode->FirstChildElement("properties");
    if (propertiesNode) {
        ParseProperties(propertiesNode, tileset->properties);
    }
    return true;
}

const bool TileMapParser::ParseImageLayer(const tinyxml2::XMLNode *imageLayerNode, imagelayer_data* imagelayer ) {
    const tinyxml2::XMLElement *imageLayerElem = imageLayerNode->ToElement();

    // Read all the attributes into local variables.
    imagelayer->name = imageLayerElem->Attribute("name");
    imagelayer->z = z_order++;
    std::cout << "imagelayer z: " << imagelayer->z << std::endl;
    imageLayerElem->QueryIntAttribute("x", &(imagelayer->x));
    imageLayerElem->QueryIntAttribute("y", &(imagelayer->y));

    imageLayerElem->QueryFloatAttribute("opacity", &(imagelayer->opacity));
    imageLayerElem->QueryBoolAttribute("visible", &(imagelayer->visible));

    // Parse the image if there is one.
    const tinyxml2::XMLNode *imageNode = imageLayerElem->FirstChildElement("image");

    if (imageNode) {
        ParseImage(imageNode, &(imagelayer->image));
    }

    // Parse the properties if any.
    const tinyxml2::XMLNode *propertiesNode = imageLayerElem->FirstChildElement("properties");

    if (propertiesNode) {
        ParseProperties(propertiesNode, imagelayer->properties);
    }
    return true;
}


const bool TileMapParser::ParseTileLayer
(const tinyxml2::XMLNode *tileLayerNode, tilelayer_data* tilelayer,
    int width, int height) {
    const tinyxml2::XMLElement *tileLayerElem = tileLayerNode->ToElement();

    // Read the attributes.
    tilelayer->name = tileLayerElem->Attribute("name");
    tilelayer->z = z_order++;
    tileLayerElem->QueryIntAttribute("x", &(tilelayer->x));
    tileLayerElem->QueryIntAttribute("y", &(tilelayer->y));

    tileLayerElem->QueryFloatAttribute("opacity", &(tilelayer->opacity));
    tileLayerElem->QueryBoolAttribute("visible", &(tilelayer->visible));

    // Read the properties.
    const tinyxml2::XMLNode *propertiesNode = tileLayerNode->FirstChildElement("properties");
    if (propertiesNode) {
        ParseProperties(propertiesNode, tilelayer->properties);
    }

    // // Allocate memory for reading the tiles.
    (tilelayer->_tiles).resize(width * height);
    const tinyxml2::XMLElement *dataElem = tileLayerNode->FirstChildElement("data");

    const char *encodingStr = dataElem->Attribute("encoding");
    const char *compressionStr = dataElem->Attribute("compression");

    // Check for encoding.
    tilelayer->encoding = encoding_xml;
    if (encodingStr) 
    {
        if (!strcmp(encodingStr, "base64")) 
            tilelayer->encoding = encoding_base64;
        else if (!strcmp(encodingStr, "csv")) 
            tilelayer->encoding = encoding_csv;
    }

    // Check for compression.
    tilelayer->compression = compression_none;
    if (compressionStr) 
    {
        if (!strcmp(compressionStr, "gzip"))
            tilelayer->compression = compression_gzip;
        else if (!strcmp(compressionStr, "zlib")) 
            tilelayer->compression = compression_zlib;
    }

    // Decode.

    if (tilelayer->encoding == encoding_xml)
        ParseXML(dataElem, tilelayer, width, height);
    else if (tilelayer->encoding == encoding_base64)
        ParseBase64(dataElem->GetText(), tilelayer, width, height);
    else if (tilelayer->encoding == encoding_csv, tilelayer)
        ParseCSV(dataElem->GetText(), tilelayer, width, height);

    return true;

}

    // trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

    // trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}



const bool TileMapParser::ParseXML(const tinyxml2::XMLNode *dataNode, tilelayer_data* tilelayer,int width, int height) {
    return true;
}
    // {
    //     const tinyxml2::XMLNode *tileNode = dataNode->FirstChildElement("tile");
    //     int tileCount = 0;

    //     while (tileNode) 
    //     {
    //         const tinyxml2::XMLElement *tileElem = tileNode->ToElement();
            
    //         unsigned gid = 0;

    //         // Read the Global-ID of the tile.
    //         const char* gidText = tileElem->Attribute("gid");

    //         // Convert to an unsigned.
    //         sscanf(gidText, "%u", &gid);

    //         // Find the tileset index.
    //         const int tilesetIndex = map->FindTilesetIndex(gid);
    //         if (tilesetIndex != -1)
    //         {
    //             // If valid, set up the map tile with the tileset.
    //             const Tmx::Tileset* tileset = map->GetTileset(tilesetIndex);
    //             tile_map[tileCount] = MapTile(gid, tileset->GetFirstGid(), tilesetIndex);
    //         }
    //         else
    //         {
    //             // Otherwise, make it null.
    //             tile_map[tileCount] = MapTile(gid, 0, -1);
    //         }

    //         //tileNode = dataNode->IterateChildren("tile", tileNode); FIXME MAYBE
    //         tileNode = tileNode->NextSiblingElement("tile");
    //         tileCount++;
    //     }
    // }

const bool TileMapParser::ParseBase64(const std::string &innerText, tilelayer_data* tilelayer,int width, int height) {
        std::string testText = innerText;
        // trim space from both ends
        ltrim(rtrim( testText ));
        const std::string &text = base64_decode(testText);
        // Temporary array of gids to be converted to map tiles.
        unsigned *out = 0;
        if (tilelayer->compression == compression_zlib) {
            // Use zlib to uncompress the tile layer into the temporary array of tiles.
            uLongf outlen = width * height * 4;
            out = (unsigned *)malloc(outlen);
            uncompress(
                (Bytef*)out, &outlen, 
                (const Bytef*)text.c_str(), text.size());
        } 
        else if (tilelayer->compression == compression_gzip) 
        {
            // Use the utility class for decompressing (which uses zlib)
            out = (unsigned *)DecompressGZIP(
                text.c_str(), 
                text.size(), 
                width * height * 4);
        } 
        else 
        {
            out = (unsigned *)malloc(text.size());
        
            // Copy every gid into the temporary array since
            // the decoded string is an array of 32-bit integers.
            memcpy(out, text.c_str(), text.size());
        }
        // Convert the gids to map tiles.
        // std::cout << "map tiles gids: ";
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                unsigned gid = out[y * width + x];
                // std::cout << " " << gid;
                if ( y * width + x < tilelayer->_tiles.size()) {
                    tilelayer->_tiles[y * width + x] = gid;
                }
                else {
                    std::cout << "ParseBase64: tile index out of range: " << y * width + x << std::endl;
                }
                //Find the tileset index.
                // const int tilesetIndex = map->FindTilesetIndex(gid);
                // if (tilesetIndex != -1)
                // {
                //     // If valid, set up the map tile with the tileset.
                //     const Tmx::Tileset* tileset = map->GetTileset(tilesetIndex);
                //     tile_map[y * width + x] = MapTile(gid, tileset->GetFirstGid(), tilesetIndex);
                // }
                // else
                // {
                    // Otherwise, make it null.
                    // tile_map[y * width + x] = MapTile(gid, 0, -1);
                // }
            }
        }
        std::cout << std::endl;
        // Free the temporary array from memory.
        free(out);
    return true;
}
    //     




    // }

const bool TileMapParser::ParseCSV(const std::string &innerText, tilelayer_data* tilelayer, int width, int height) {
    return true;
}
    // void TileLayer::ParseCSV(const std::string &innerText) 
    // {
    //     // Duplicate the string for use with C stdio.
    //     char *csv = strdup(innerText.c_str());
        
    //     // Iterate through every token of ';' in the CSV string.
    //     char *pch = strtok(csv, ",");
    //     int tileCount = 0;
        
    //     while (pch) 
    //     {
    //         unsigned gid;
    //         sscanf(pch, "%u", &gid);

    //         // Find the tileset index.
    //         const int tilesetIndex = map->FindTilesetIndex(gid);
    //         if (tilesetIndex != -1)
    //         {
    //             // If valid, set up the map tile with the tileset.
    //             const Tmx::Tileset* tileset = map->GetTileset(tilesetIndex);
    //             tile_map[tileCount] = MapTile(gid, tileset->GetFirstGid(), tilesetIndex);
    //         }
    //         else
    //         {
    //             // Otherwise, make it null.
    //             tile_map[tileCount] = MapTile(gid, 0, -1);
    //         }

    //         pch = strtok(NULL, ",");
    //         tileCount++;
    //     }

    //     free(csv);
    // }

const bool TileMapParser::Parse(tinyxml2::XMLNode *mapNode, tilemap_data& map)
{
    if ( mapNode == nullptr ) return false;

    tinyxml2::XMLElement* mapElem = mapNode->ToElement();

    // Read the map attributes.
    map.version = mapElem->IntAttribute("version");
    map.width = mapElem->IntAttribute("width");
    map.height = mapElem->IntAttribute("height");
    map.tile_width = mapElem->IntAttribute("tilewidth");
    map.tile_height = mapElem->IntAttribute("tileheight");
    map.next_object_id = mapElem->IntAttribute("nextobjectid");

    if (mapElem->Attribute("backgroundcolor"))
        map.background_color = StringToColor32(mapElem->Attribute("backgroundcolor"));

    if( mapElem->Attribute("orientation") == nullptr )
        return false;

    // Read the orientation
    std::string orientationStr = mapElem->Attribute("orientation");

    if (!orientationStr.compare("orthogonal"))
        map.orientation = orientation_orthogonal;

    else if (!orientationStr.compare("isometric"))
        map.orientation = orientation_isometric;

    else if (!orientationStr.compare("staggered"))
        map.orientation = orientation_staggered;

    else if (!orientationStr.compare("hexagonal"))
        map.orientation = orientation_hexagonal;

    // Read the render order
    if (mapElem->Attribute("renderorder"))
    {
        std::string renderorderStr = mapElem->Attribute("renderorder");
        if (!renderorderStr.compare("right-down"))
            map.render_order = renderorder_right_down;
        else if (!renderorderStr.compare("right-up"))
            map.render_order = renderorder_right_up;
        else if (!renderorderStr.compare("left-down"))
            map.render_order = renderorder_left_down;
        else if (!renderorderStr.compare("left-down"))
            map.render_order = renderorder_left_up;
    }

    // Read the stagger axis
    if (mapElem->Attribute("staggeraxis"))
    {
        std::string staggerAxisStr = mapElem->Attribute("staggeraxis");
        if (!staggerAxisStr.compare("x"))
            map.stagger_axis = staggeraxis_x;
        else if (!staggerAxisStr.compare("y"))
            map.stagger_axis = staggeraxis_y;
    }

    // Read the stagger index
    if (mapElem->Attribute("staggerindex"))
    {
        std::string staggerIndexStr = mapElem->Attribute("staggerindex");
        if (!staggerIndexStr.compare("even"))
            map.stagger_index = staggerindex_even;
        else if (!staggerIndexStr.compare("odd"))
            map.stagger_index = staggerindex_odd;
    }

    // read the hexside length
    if (mapElem->IntAttribute("hexsidelength"))
        map.hexside_length = mapElem->IntAttribute("hexsidelength");

    // read all other attributes
    const tinyxml2::XMLNode *node = mapElem->FirstChild();
    while( node )
    {
        // Read the map properties.
        if( strcmp( node->Value(), "properties" ) == 0 ) {
            ParseProperties(node, map.properties );
        }
        // Iterate through all of the tileset elements.


        if( strcmp( node->Value(), "tileset" ) == 0 )
        {
            // Allocate a new tileset and parse it.
            std::unique_ptr<tileset_data> tileset = std::make_unique<tileset_data>();
            ParseTileset(node->ToElement(), tileset.get());
            // tileset->Parse(node->ToElement(), file_path);

            // Add the tileset to the list.
            map.tilesets.push_back(std::move(tileset));
        }

        // Iterate through all of the "layer" (tile layer) elements.
        if( strcmp( node->Value(), "layer" ) == 0 )
        {
            // Allocate a new tile layer and parse it.
            std::unique_ptr<tilelayer_data> tile_layer = std::make_unique<tilelayer_data>();
            ParseTileLayer(node, tile_layer.get(), map.width, map.height );

            // Add the tile layer to the lists.
            map.tilelayers.push_back(std::move(tile_layer));
        }

        // Iterate through all of the "imagelayer" (image layer) elements.
        if( strcmp( node->Value(), "imagelayer" ) == 0 )
        {
            // Allocate a new image layer and parse it.
            std::unique_ptr<imagelayer_data> image_layer = std::make_unique<imagelayer_data>();

            ParseImageLayer(node, image_layer.get() );

            // Add the image layer to the lists.
            map.imagelayers.push_back(std::move(image_layer));
        }

            /*

        // Iterate through all of the "objectgroup" (object layer) elements.
        if( strcmp( node->Value(), "objectgroup" ) == 0 )
        {
            // Allocate a new object group and parse it.
            ObjectGroup *objectGroup = new ObjectGroup(this);
            objectGroup->Parse(node);

            // Add the object group to the lists.
            object_groups.push_back(objectGroup);
            layers.push_back(objectGroup);
        }

        if( strcmp( node->Value(), "group") == 0 )
        {
            GroupLayer *groupLayer = new GroupLayer(this);
            groupLayer->Parse(node);

            // Add the group layer to the lists.
            group_layers.push_back(groupLayer);
            layers.push_back(groupLayer);
        }

*/
        node = node->NextSibling();

    }
    return true;
}

char* TileMapParser::DecompressGZIP(const char *data, int dataSize, int expectedSize) 
{
    int bufferSize = expectedSize;
    int ret;
    z_stream strm;
    char *out = (char*)malloc(bufferSize);

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = (Bytef*)data;
    strm.avail_in = dataSize;
    strm.next_out = (Bytef*)out;
    strm.avail_out = bufferSize;

    ret = inflateInit2(&strm, 15 + 32);

    if (ret != Z_OK) 
    {
        free(out);
        return NULL;
    }

    do 
    {
        ret = inflate(&strm, Z_SYNC_FLUSH);

        switch (ret) 
        {
            case Z_NEED_DICT:
            case Z_STREAM_ERROR:
                ret = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&strm);
                free(out);
                return NULL;
        }

        if (ret != Z_STREAM_END) 
        {
            out = (char *) realloc(out, bufferSize * 2);

            if (!out) 
            {
                inflateEnd(&strm);
                free(out);
                return NULL;
            }

            strm.next_out = (Bytef *)(out + bufferSize);
            strm.avail_out = bufferSize;
            bufferSize *= 2;
        }
    }
    while (ret != Z_STREAM_END);

    if (strm.avail_in != 0) 
    {
        free(out);
        return NULL;
    }

    inflateEnd(&strm);

    return out;
}

