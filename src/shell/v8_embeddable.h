#ifndef __V8_EMBEDDABLE_H__
#define __V8_EMBEDDABLE_H__

#include <v8.h>
#include <string>
#include <memory>
#include <vector>
#include <v8pp/module.hpp>
#include <common-util.h>

// interface class for embedding objects in the v8 shell
class v8Embeddable {
    friend class v8EmbeddableFactory;
public:
    bool IsEmpty() { return true; }
private:
    virtual void Init(v8pp::module& m) {}

};

class v8EmbeddableFactory {
    friend class v8Embeddable;
public:
    bool Init(v8pp::module& m);
    void _NewFromString(const std::string& objName);
    void NewFromString(char const* objName);
    ~v8EmbeddableFactory() {
        LOG_THREAD("~v8EmbeddableFactory was called");
        _objects.clear();
    }
private:
    static std::vector<std::unique_ptr<v8Embeddable>> _objects;
};

#endif