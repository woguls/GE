#include <resource-modules/directory.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

DirectoryModule::DirectoryModule(std::string path) 
: resource_directory_t()
{
    if ( resource_directory_t::Get() != nullptr) return;

    ResourceDirectory* dir = new ResourceDirectory;
    if (dir == nullptr) {
        std::cout << "Engine Error: " << "Unable to create new ResourceDirectory" << std::endl;
        return;
    }
    dir->BuildFromPath(path);
    if ( !resource_directory_t::Set(dir))
        std::cout << "Engine Error: " << "Unable to create ResourceDirectory from path" << std::endl;
}

void DirectoryModule::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<DirectoryModule> DirectoryModule_class(isolate);

    DirectoryModule_class
        .ctor<std::string>()
        .inherit<resource_directory_t>()
        ;

    LOG("Initialized Resource.Directory()");
    m.set("Directory", DirectoryModule_class);

}
