//
// Copyright (c) 2013-2016 Pavel Medvedev. All rights reserved.
//
// This file is part of v8pp (https://github.com/pmed/v8pp) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <v8.h>

class MyObject {
 public:
  static void Init(v8::Handle<v8::Object> exports);

  explicit MyObject(const v8::FunctionCallbackInfo<v8::Value>& args);

 private:
  double PlusOne();
  double value_;
};

#endif
