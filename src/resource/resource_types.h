#ifndef __RESOURCE_TYPES_H__
#define __RESOURCE_TYPES_H__
#include <shell/v8_type_wrapper.h>
#include <resource/reference.h>
#include <resource/directory.h>
#include <resource/tilemap.h>

typedef WrapPtr<ResourceReference> resource_reference_t;
typedef WrapPtr<ResourceDirectory> resource_directory_t;
typedef WrapPtr<const tilemap_data> resource_tilemap_t;
typedef WrapPtr<tilelayer_data> resource_tilelayer_t;

#endif
