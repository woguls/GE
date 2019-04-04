#include <shell/v8_platform.h>
#include <common-util.h>

v8Platform::_v8Platform*  v8Platform::_instance = nullptr;

v8Platform::v8Platform() {
  if (_instance == nullptr) {
    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();
    v8::Isolate::CreateParams createParams;
    createParams.array_buffer_allocator =
      v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    _instance = new _v8Platform{ std::move(platform) , std::move(createParams) };
    LOG_THREAD("created v8 platform");
  }
}

v8Platform::~v8Platform() {
  if(_instance != nullptr) {
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    delete _instance->_createParams.array_buffer_allocator;
    delete _instance;

    LOG_THREAD("called V8::Dispose() and V8:ShutdownPlatform()");
  }
}
