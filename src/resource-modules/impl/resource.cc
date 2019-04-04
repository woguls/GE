#include <resource-modules/resource.h>
#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <common-util.h>

ResourceModule::ResourceModule(resource_directory_t& dir) {
    if ( ! _dir.Set(dir.Get()) ) {
        LOG("Failed to set resource_directory_t");
    }
}

bool ResourceModule::v8_Find(std::string what) {
    if ( _dir.Get() == nullptr ) {
        LOG("Attempted to find in empty directory");
        return false;
    }
    resource_reference_t::Set( _dir.Get()->Find(what) );
    if (resource_reference_t::Get() == nullptr ) {
        return false;
    }
    return true;
}

void ResourceModule::Init(v8pp::module& m) {
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8pp::class_<ResourceModule> ResourceModule_class(isolate);

    ResourceModule_class
        .ctor<resource_directory_t&>()
        .inherit<resource_reference_t>()
        .set("Find", &ResourceModule::v8_Find)
        ;

    LOG("Initialized Resource.Reference()");
    m.set("Reference", ResourceModule_class);

}
