#ifndef __V8MODULES_RESOURCE_H__
#define __V8MODULES_RESOURCE_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <string>
#include <common-util.h>
#include <resource/resource_types.h>

class ResourceModule : public v8Embeddable, public resource_reference_t {
public:
    explicit ResourceModule(resource_directory_t& dir);
    explicit ResourceModule() : resource_reference_t(), _dir{} { }

    ~ResourceModule() {
        LOG_THREAD("~resource_reference_t was called");
    }

    bool v8_Find(std::string what);
    void Init(v8pp::module& m) override;
private:
    resource_directory_t _dir;
};


#endif