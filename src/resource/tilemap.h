#ifndef __ENGINE_TILEMAP_H__
#define __ENGINE_TILEMAP_H__

#include <resource/reference.h>
#include <resource/directory.h>
#include <any>
#include <cctype>
#include <algorithm>
#include <memory>
#include <tinyxml2.h>
#include <sdl.h>

class TileArray {
public:
    explicit TileArray(size_t size) {
        _tiles.reserve(size);
    }
    void SetTile(size_t index, int id ) { _tiles[index] = id; }
    int GetTile(size_t index) { return _tiles[index]; }

    std::vector<int> _tiles;
};

// TODO: why is this laid out like bitmasks?
enum layer_type
{
    layer_tile        = 0X01,
    layer_objectgroup = 0X02,
    layer_imagelayer  = 0X04,
    layer_grouplayer  = 0X08,
    layer_null        = 0x10
};

enum property_type
{
    property_none,
    property_string,
    property_bool,
    property_int,
    property_float,
    property_color,
    property_file
};

enum tilemap_renderorder {
    renderorder_right_down,
    renderorder_right_up,
    renderorder_left_down,
    renderorder_left_up
};

enum tilemap_orientation {
    orientation_orthogonal,
    orientation_isometric,
    orientation_staggered,
    orientation_hexagonal
};

enum tilemap_staggeraxis {
    staggeraxis_x,
    staggeraxis_y
};

enum tilemap_staggerindex {
    staggerindex_even,
    staggerindex_odd
};

enum tilelayer_encoding {
    encoding_xml,
    encoding_base64,
    encoding_csv
};

enum tilelayer_compression  {
    compression_none,
    compression_zlib,
    compression_gzip
};

struct map_property {
    std::any object;
    property_type type;
};

typedef std::map<std::string, map_property> property_map_t;

struct image_data {
    const ResourceReference* image;
    int width;
    int height;
    uint32_t transparent_color;
};

struct terrain_data {
    std::string name;
    int tileID;
    property_map_t properties;
};

struct tile_data {
    int id;

    property_map_t properties;

    bool isAnimated;
    bool hasObjects;
    bool hasObjectGroup;
    // Tmx::ObjectGroup *objectGroup;
    unsigned int totalDuration;
    // std::vector<AnimationFrame> frames;
    // ResourceReference* image;
    image_data _image;
    std::string type;
};

typedef std::vector<std::unique_ptr<terrain_data>> terrain_list_t;
typedef std::vector<std::unique_ptr<tile_data>> tile_data_list_t;

struct tileset_data {
    int first_gid;

    std::string name;

    int tile_width;
    int tile_height;
    int margin;
    int spacing;
    int tile_count;
    int columns;

    int offset_x;
    int offset_y;

    const ResourceReference* image;
    uint32_t image_transparent_color;
    int image_width;
    int image_height;

    image_data _image;

    terrain_list_t terrainTypes;
    tile_data_list_t tiles;

    property_map_t properties;
};

struct imagelayer_data {
    std::string name;
    int x;
    int y;
    int z;
    float opacity;
    bool visible;
    property_map_t properties;
    image_data image;
};

struct tilelayer_data {
    std::string name;
    int x;
    int y;
    int z;
    float opacity;
    bool visible;
    property_map_t properties;
    tilelayer_encoding encoding;
    tilelayer_compression compression;
    std::vector<int> _tiles;
};

typedef std::vector<std::unique_ptr<tileset_data>> tileset_list_t;
typedef std::vector<std::unique_ptr<imagelayer_data>> imagelayer_list_t;
typedef std::vector<std::unique_ptr<tilelayer_data>> tilelayer_list_t;

struct tilemap_data {
    double version;
    int width;
    int height;
    int tile_width;
    int tile_height;
    int next_object_id;
    uint32_t background_color;
    tilemap_renderorder render_order;
    tilemap_orientation orientation;
    tilemap_staggeraxis stagger_axis;
    tilemap_staggerindex stagger_index;
    int hexside_length;
    property_map_t properties;
    tileset_list_t tilesets;
    imagelayer_list_t imagelayers;
    tilelayer_list_t tilelayers;
/*
        std::vector< Tmx::ObjectGroup* > object_groups;
        std::vector< Tmx::GroupLayer* > group_layers;
*/
    bool has_error;
    unsigned char error_code;
    std::string error_text;
};



class TileMapParser {
    friend class TileMap;
public:
    TileMapParser() = delete;
    explicit TileMapParser( ResourceDirectory* dir,
        const ResourceReference& reference)
    :   _dir{dir},
        _reference{reference},
        z_order{0}
        { }
    explicit TileMapParser(const ResourceReference& reference)
    :   _reference{reference},
        z_order{0}
        { }

    std::unique_ptr<const tilemap_data> Parse();

private:
    const bool Parse(tinyxml2::XMLNode *node, tilemap_data& map);
    const bool ParseProperties(const tinyxml2::XMLNode *node, property_map_t& map);
    const bool ParseProperty(const tinyxml2::XMLElement *propertyElem, map_property& prop);
    const bool ParseImage(const tinyxml2::XMLNode *imageElem, image_data* image);
    const bool ParseTileset(const tinyxml2::XMLNode *tilesetNode, tileset_data* tileset );
    const bool ParseTileLayer(const tinyxml2::XMLNode *tilelayerNode, tilelayer_data* tilelayer, int width, int height );
    const bool ParseImageLayer(const tinyxml2::XMLNode *tileLayerNode, imagelayer_data* imagelayer );
    const bool ParseTile(const tinyxml2::XMLNode *tileNode, tile_data* tileset );
    const bool ParseXML(const tinyxml2::XMLNode *dataNode, tilelayer_data* tilelayer,int width, int height);
    const bool ParseBase64(const std::string &innerText, tilelayer_data* tilelayer,int width, int height);
    const bool ParseCSV(const std::string &innerText, tilelayer_data* tilelayer,int width, int height);
    char *DecompressGZIP(const char *data, int dataSize, int expectedSize);

    ResourceDirectory* _dir;
    const ResourceReference& _reference;
    uint32_t StringToColor32(const std::string& s);
    std::string StringToLower(std::string s);
    int z_order;
};

std::ostream& operator<<
(std::ostream &o,const image_data& a);

std::ostream& operator<< (std::ostream &o,
    const tilemap_data &a);

std::ostream& operator<< (std::ostream &o,
    const tilemap_renderorder& a);

std::ostream& operator<< (std::ostream &o,
    const tilemap_orientation& a);

std::ostream& operator<< (std::ostream &o,
    const tilemap_staggeraxis& a);

std::ostream& operator<< (std::ostream &o,
    const tilemap_staggerindex& a);

std::ostream& operator<< (std::ostream &o,
    const tilelayer_encoding& a);

std::ostream& operator<<
(std::ostream &o,const tilelayer_list_t& a);

std::ostream& operator<< (std::ostream &o,
    const tilelayer_compression& a);


std::ostream& operator<< (std::ostream &o,
    const property_type& a);

std::ostream& operator<< (std::ostream &o,
    const layer_type& a);

std::ostream& operator<< (std::ostream &o,
    const map_property& a);

std::ostream& operator<< (std::ostream &o,
    const property_map_t& a);

std::ostream& operator<< (std::ostream &o,
    const terrain_data& a);

std::ostream& operator<<
(std::ostream &o,const tileset_list_t& a);

std::ostream& operator<<
(std::ostream &o,const terrain_list_t& a);

std::ostream& operator<<
(std::ostream &o,const tile_data_list_t& a);


std::ostream& operator<<
(std::ostream &o,const tilelayer_data& a);


std::ostream& operator<<
(std::ostream &o,const imagelayer_list_t& a);

std::ostream& operator<<
(std::ostream &o,const imagelayer_data& a);


// typedef common::Object<
//     ::TileMap,
//     common::engine_resource_tilemap_t>
// resource_tilemap_t;


#endif