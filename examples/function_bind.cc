// Copyright (c) 2015 libfuture-c++ authors.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
// Author: sergey.vfx@gmail.com (Sergey Sharybin)

#include <cstdlib>
#include <cstdio>

#include "future/bind.h"
#include "future/function.h"
#include "future/placeholders.h"

class MyClass {
 public:
  MyClass() {
  }
 int method() {
   printf("Class method\n");
   return 123;
 }
 int method1(int a) {
   printf("Class method\n");
   return a;
 }
};

static void foo(void) {
  printf("%s\n", __func__);
}

static int bar(int a) {
  printf("%s: %d\n", __func__, a);
  return 321;
}

static void test_pointer(int *a) {
  printf("%s: %d\n", __func__, *a);
}

static void invoke(future::function::function<void(void)> f) {
  f();
}

int main(int argc, char **argv) {
  using future::function::function;
  using future::bind::function_bind;
  function<void(void)> f0 = function_bind(foo);
  function<int(int)> f1 = function_bind(bar, _1);
  f0();
  int a = f1(123);
  printf("Return value is: %d\n", a);
  function<int(int)> f2;
  f2 = f1;
  f2(1233);
  function<int(int)> f3 = f2;
  f3(111);
  function<void(void)> p0;
  {
    function<void(void)> p = function_bind(test_pointer, &a);
    p0 = p;
    p();
    invoke(p);
  }
  invoke(p0);

  MyClass my_class;
  function<int(void)> class_method = function_bind(&MyClass::method, &my_class);
  printf("%d\n", class_method());

  function<int(int)> class_method1 = function_bind(&MyClass::method1, &my_class, _1);
  printf("%d\n", class_method1(1));

  return EXIT_SUCCESS;
}
