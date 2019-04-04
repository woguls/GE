#ifndef __SHELL_H__
#define __SHELL_H__
#include <v8/include/v8.h>
#include <v8/include/libplatform/libplatform.h>

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <future>
#include <vector>

#include <shell/v8_platform.h>
#include <shell/v8_embeddable.h>
#include <v8pp/context.hpp>

const char* ToCString(const v8::String::Utf8Value& value);


class v8Shell : v8Platform
{
public:
	explicit v8Shell() { }
	int Run();
	bool Running();
    int _run();
    int _run_args(int argc = 0, char** argv = nullptr);

    void SetContextProperties(v8pp::context& context);

	static bool should_exit;
	std::future<int> _run_shell_future;
	// ScriptableApplication* _app;
	// HeapStatisticsObject heapStatistics;
	
	v8EmbeddableFactory _objects;
	void ShouldExit();

	void RunShell( v8::Platform* platform);

	int RunMain(v8::Platform* platform, int argc,
	            char* argv[]);
	static bool ExecuteString(v8::Isolate* isolate, v8::Local<v8::String> source,
	                   v8::Local<v8::Value> name, bool print_result,
	                   bool report_exceptions);
	static void Load(const v8::FunctionCallbackInfo<v8::Value>& args);
	static v8::MaybeLocal<v8::String> ReadFile(v8::Isolate* isolate, const char* name);
	static void Print(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Read(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void Quit(const v8::FunctionCallbackInfo<v8::Value>& args);
	// static void Quit();
	static void Version(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void ReportException(v8::Isolate* isolate, v8::TryCatch* handler);

};

#endif