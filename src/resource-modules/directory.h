#ifndef __V8MODULES_DIRECTORY_H__
#define __V8MODULES_DIRECTORY_H__
#include <shell/v8_embeddable.h>
#include <sdl.h>
#include <v8pp/module.hpp>
#include <string>
#include <common-util.h>
#include <resource/resource_types.h>

class DirectoryModule : public v8Embeddable, public resource_directory_t {
public:
    explicit DirectoryModule(std::string path);
    explicit DirectoryModule() : resource_directory_t() { }

    ~DirectoryModule() {
        LOG_THREAD("~DirectoryModule was called");
    }

    void Init(v8pp::module& m) override;
private:

};


#endif