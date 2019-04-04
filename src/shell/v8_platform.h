#ifndef __V8_SINGLETON_OBJECT__
#define __V8_SINGLETON_OBJECT__
#include <v8/include/v8.h>
#include <v8/include/libplatform/libplatform.h>
#include <memory>

// TODO: rename v8SingletonObject to reflect that it manages v8::Platform
class v8Platform {
protected:
    ~v8Platform();
    v8Platform();
	v8::Platform* GetPlatform() { return _instance->_platform.get(); }
	v8::Isolate::CreateParams& GetCreateParams() { return _instance->_createParams; }
private:
	static struct _v8Platform {
		std::unique_ptr<v8::Platform> _platform;
		v8::Isolate::CreateParams _createParams;
	} *_instance;
};

#endif
