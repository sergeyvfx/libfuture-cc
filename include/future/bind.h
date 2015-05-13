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

#ifndef FUTURE_BIND_H_
#define FUTURE_BIND_H_

#include "future/internal.h"
#include "future/function.h"

namespace future {
namespace bind {
namespace internal {

/* Base class for binable entities which are based on real function pointer. */
template<typename FuncPointer, typename R>
class function_bind : public ::future::internal::function_bind_base<R> {
  typedef ::future::internal::function_bind_base<R> base_type;
  typedef future::internal::argument_wrapper wrapper_type;
  typedef future::internal::argument_list argument_list_type;
 public:
  function_bind() : base_type(),
                    func_(NULL) {}
  function_bind(FuncPointer *func,
                int num_arguments) : base_type(num_arguments),
                                     func_(func),
                                     num_set_arguments_(0) {}

  void prepare(argument_list_type& argument_list) {
    for (int i = 0; i < this->num_arguments_; ++i) {
      argument_list[i] = argument_list_[i];
    }
  }

  bool is_bound() {
    return func_ != NULL;
  }

  template <typename T>
  void add_argument(T arg) {
    argument_list_[num_set_arguments_] = wrapper_type(arg);
    ++num_set_arguments_;
  }

 protected:
  FuncPointer *func_;
  argument_list_type argument_list_;
  int num_set_arguments_;
};

template <typename FuncPointer, typename R>
class function_bind0 : public function_bind<FuncPointer, R> {
  typedef future::internal::argument_list argument_list_type;
 public:
  explicit function_bind0(FuncPointer *func)
  : function_bind<FuncPointer, R>(func, 0) {}
  R invoke(argument_list_type& arguments) {
    return this->func_();
  }
};

template <typename FuncPointer,
          typename R,
          typename T1>
class function_bind1 : public function_bind<FuncPointer, R> {
  typedef future::internal::argument_list argument_list_type;
 public:
  explicit function_bind1(FuncPointer *func)
  : function_bind<FuncPointer, R>(func, 1) {}
  R invoke(argument_list_type& argument_list) {
    return this->func_(argument_list[0].cast<T1>());
  }
};

}  /* namespace internal */

template <typename R>
::future::internal::function_bind_base<R>*
function_bind(R func(void)) {
  typedef R FunctionPointer(void);
  internal::function_bind0<FunctionPointer, R> *bind =
    new internal::function_bind0<FunctionPointer, R>(func);
  return bind;
}

template <typename R, typename T1,
                      typename A1>
::future::internal::function_bind_base<R>*
function_bind(R func(T1),
              A1 arg) {
  typedef R FunctionPointer(T1);
  internal::function_bind1<FunctionPointer, R, T1> *bind =
    new internal::function_bind1<FunctionPointer, R, T1>(func);
  bind->add_argument(arg);
  return bind;
}

}  /* namespace bind */
}  /* namespace future */

#endif  /* FUTURE_BIND_H_ */
