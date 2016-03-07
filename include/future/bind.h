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
  typedef future::internal::argument_list argument_list_type;
 public:
  function_bind() : base_type(),
                    func_(NULL) {}
  function_bind(FuncPointer *func,
                int num_arguments) : base_type(num_arguments),
                                     func_(func),
                                     num_set_arguments_(0) {}

  inline bool is_bound() {
    return func_ != NULL;
  }

  inline void set_num_arguments(int num_arguments) {
    argument_list_.resize(num_arguments);
  }

  template <typename T>
  inline void add_argument(T argument) {
    argument_list_.set(num_set_arguments_, argument);
    ++num_set_arguments_;
  }

 protected:
  typedef future::internal::argument_wrapper_base argument_wrapper_base;
  argument_wrapper_base *get_(argument_list_type& argument_list,
                              int index)
  {
    argument_wrapper_base *arg = argument_list_[index];
    if (arg->is_placeholder()) {
      return argument_list[arg->get_placeholder_position()];
    }
    return arg;
  }

  FuncPointer *func_;
  argument_list_type argument_list_;
  int num_set_arguments_;
};

#define FUNCTION_GLUE(a, b) a ## b
#define FUNCTION_BIND_DECLARE_COMMON(n) \
  typedef ::future::internal::function_bind_base<R> base_type; \
  typedef future::internal::argument_list argument_list_type; \
  typedef future::internal::argument_wrapper_base argument_wrapper_base; \
 public: \
  explicit FUNCTION_GLUE(function_bind, n)(FuncPointer *func) \
  : function_bind<FuncPointer, R>(func, n) {} \
  base_type* clone() { \
    return new FUNCTION_GLUE(function_bind, n)(*this); \
  }

template <typename FuncPointer, typename R>
class function_bind0 : public function_bind<FuncPointer, R> {
  FUNCTION_BIND_DECLARE_COMMON(0)
  R invoke(argument_list_type& arguments) {
    return this->func_();
  }
};

template <typename FuncPointer,
          typename R,
          typename T1>
class function_bind1 : public function_bind<FuncPointer, R> {
  FUNCTION_BIND_DECLARE_COMMON(1)
  R invoke(argument_list_type& argument_list) {
    argument_wrapper_base *a1 = this->get_(argument_list, 0);
    return this->func_(a1->cast<T1>());
  }
};

template <typename FuncPointer,
          typename R,
          typename T1, typename T2>
class function_bind2 : public function_bind<FuncPointer, R> {
  FUNCTION_BIND_DECLARE_COMMON(2)

  R invoke(argument_list_type& argument_list) {
    argument_wrapper_base *a1 = this->get_(argument_list, 0),
                          *a2 = this->get_(argument_list, 1);
    return this->func_(a1->cast<T1>(),
                       a2->cast<T2>());
  }
};

template <typename FuncPointer,
          typename R,
          typename T1, typename T2, typename T3>
class function_bind3 : public function_bind<FuncPointer, R> {
  FUNCTION_BIND_DECLARE_COMMON(3)
  R invoke(argument_list_type& argument_list) {
    argument_wrapper_base *a1 = this->get_(argument_list, 0),
                          *a2 = this->get_(argument_list, 1),
                          *a3 = this->get_(argument_list, 2);
    return this->func_(a1->cast<T1>(),
                       a2->cast<T2>(),
                       a3->cast<T3>());
  }
};

template <typename FuncPointer,
          typename R,
          typename T1, typename T2, typename T3, typename T4>
class function_bind4 : public function_bind<FuncPointer, R> {
  FUNCTION_BIND_DECLARE_COMMON(4)
  R invoke(argument_list_type& argument_list) {
    argument_wrapper_base *a1 = this->get_(argument_list, 0),
                          *a2 = this->get_(argument_list, 1),
                          *a3 = this->get_(argument_list, 2),
                          *a4 = this->get_(argument_list, 3);
    return this->func_(a1->cast<T1>(),
                       a2->cast<T2>(),
                       a3->cast<T3>(),
                       a4->cast<T4>());
  }
};

template <typename FuncPointer,
          typename R,
          typename T1, typename T2, typename T3, typename T4, typename T5>
class function_bind5 : public function_bind<FuncPointer, R> {
  FUNCTION_BIND_DECLARE_COMMON(5)
  R invoke(argument_list_type& argument_list) {
    argument_wrapper_base *a1 = this->get_(argument_list, 0),
                          *a2 = this->get_(argument_list, 1),
                          *a3 = this->get_(argument_list, 2),
                          *a4 = this->get_(argument_list, 3),
                          *a5 = this->get_(argument_list, 4);
    return this->func_(a1->cast<T1>(),
                       a2->cast<T2>(),
                       a3->cast<T3>(),
                       a4->cast<T4>(),
                       a5->cast<T5>());
  }
};

template <typename FuncPointer,
          typename R,
          typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6>
class function_bind6 : public function_bind<FuncPointer, R> {
  FUNCTION_BIND_DECLARE_COMMON(6)
  R invoke(argument_list_type& argument_list) {
    argument_wrapper_base *a1 = this->get_(argument_list, 0),
                          *a2 = this->get_(argument_list, 1),
                          *a3 = this->get_(argument_list, 2),
                          *a4 = this->get_(argument_list, 3),
                          *a5 = this->get_(argument_list, 4),
                          *a6 = this->get_(argument_list, 5);
    return this->func_(a1->cast<T1>(),
                       a2->cast<T2>(),
                       a3->cast<T3>(),
                       a4->cast<T4>(),
                       a5->cast<T5>(),
                       a6->cast<T6>());
  }
};

template <typename FuncPointer,
          typename R,
          typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7>
class function_bind7 : public function_bind<FuncPointer, R> {
  FUNCTION_BIND_DECLARE_COMMON(7)
  R invoke(argument_list_type& argument_list) {
    argument_wrapper_base *a1 = this->get_(argument_list, 0),
                          *a2 = this->get_(argument_list, 1),
                          *a3 = this->get_(argument_list, 2),
                          *a4 = this->get_(argument_list, 3),
                          *a5 = this->get_(argument_list, 4),
                          *a6 = this->get_(argument_list, 5),
                          *a7 = this->get_(argument_list, 6);
    return this->func_(a1->cast<T1>(),
                       a2->cast<T2>(),
                       a3->cast<T3>(),
                       a4->cast<T4>(),
                       a5->cast<T5>(),
                       a6->cast<T6>(),
                       a7->cast<T7>());
  }
};

template <typename FuncPointer,
          typename R,
          typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8>
class function_bind8 : public function_bind<FuncPointer, R> {
  FUNCTION_BIND_DECLARE_COMMON(8)
  R invoke(argument_list_type& argument_list) {
    argument_wrapper_base *a1 = this->get_(argument_list, 0),
                          *a2 = this->get_(argument_list, 1),
                          *a3 = this->get_(argument_list, 2),
                          *a4 = this->get_(argument_list, 3),
                          *a5 = this->get_(argument_list, 4),
                          *a6 = this->get_(argument_list, 5),
                          *a7 = this->get_(argument_list, 6),
                          *a8 = this->get_(argument_list, 7);
    return this->func_(a1->cast<T1>(),
                       a2->cast<T2>(),
                       a3->cast<T3>(),
                       a4->cast<T4>(),
                       a5->cast<T5>(),
                       a6->cast<T6>(),
                       a7->cast<T7>(),
                       a8->cast<T8>());
  }
};

template <typename FuncPointer,
          typename R,
          typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9>
class function_bind9 : public function_bind<FuncPointer, R> {
  FUNCTION_BIND_DECLARE_COMMON(9)
  R invoke(argument_list_type& argument_list) {
    argument_wrapper_base *a1 = this->get_(argument_list, 0),
                          *a2 = this->get_(argument_list, 1),
                          *a3 = this->get_(argument_list, 2),
                          *a4 = this->get_(argument_list, 3),
                          *a5 = this->get_(argument_list, 4),
                          *a6 = this->get_(argument_list, 5),
                          *a7 = this->get_(argument_list, 6),
                          *a8 = this->get_(argument_list, 7),
                          *a9 = this->get_(argument_list, 8);
    return this->func_(a1->cast<T1>(),
                       a2->cast<T2>(),
                       a3->cast<T3>(),
                       a4->cast<T4>(),
                       a5->cast<T5>(),
                       a6->cast<T6>(),
                       a7->cast<T7>(),
                       a8->cast<T8>(),
                       a9->cast<T9>());
  }
};

template <typename FuncPointer,
          typename R,
          typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10>
class function_bind10 : public function_bind<FuncPointer, R> {
  FUNCTION_BIND_DECLARE_COMMON(10)
  R invoke(argument_list_type& argument_list) {
    argument_wrapper_base *a1 = this->get_(argument_list, 0),
                          *a2 = this->get_(argument_list, 1),
                          *a3 = this->get_(argument_list, 2),
                          *a4 = this->get_(argument_list, 3),
                          *a5 = this->get_(argument_list, 4),
                          *a6 = this->get_(argument_list, 5),
                          *a7 = this->get_(argument_list, 6),
                          *a8 = this->get_(argument_list, 7),
                          *a9 = this->get_(argument_list, 8),
                          *a10 = this->get_(argument_list, 9);
    return this->func_(a1->cast<T1>(),
                       a2->cast<T2>(),
                       a3->cast<T3>(),
                       a4->cast<T4>(),
                       a5->cast<T5>(),
                       a6->cast<T6>(),
                       a7->cast<T7>(),
                       a8->cast<T8>(),
                       a9->cast<T9>(),
                       a10->cast<T10>());
  }
};

#undef FUNCTION_BIND_DECLARE_COMMON
#undef FUNCTION_GLUE

}  /* namespace internal */

template <typename R>
::future::internal::function_bind_base<R>*
function_bind(R func(void)) {
  typedef R FunctionPointer(void);
  typedef internal::function_bind0<FunctionPointer, R> function_bind_type;
  function_bind_type *bind = new function_bind_type(func);
  bind->set_num_arguments(0);
  return bind;
}

template <typename R, typename T1,
                      typename A1>
::future::internal::function_bind_base<R>*
function_bind(R func(T1),
              A1 arg1) {
  typedef R FunctionPointer(T1);
  typedef internal::function_bind1<FunctionPointer, R,
                                   T1> function_bind_type;
  function_bind_type *bind = new function_bind_type(func);
  bind->set_num_arguments(1);
  bind->add_argument(arg1);
  return bind;
}

template <typename R, typename T1, typename T2,
                      typename A1, typename A2>
::future::internal::function_bind_base<R>*
function_bind(R func(T1, T2),
              A1 arg1, A2 arg2) {
  typedef R FunctionPointer(T1, T2);
  typedef internal::function_bind2<FunctionPointer, R,
                                   T1, T2> function_bind_type;
  function_bind_type *bind = new function_bind_type(func);
  bind->set_num_arguments(2);
  bind->add_argument(arg1);
  bind->add_argument(arg2);
  return bind;
}

template <typename R, typename T1, typename T2, typename T3,
                      typename A1, typename A2, typename A3>
::future::internal::function_bind_base<R>*
function_bind(R func(T1, T2, T3),
              A1 arg1, A2 arg2, A3 arg3) {
  typedef R FunctionPointer(T1, T2, T3);
  typedef internal::function_bind3<FunctionPointer, R,
                                   T1, T2, T3> function_bind_type;
  function_bind_type *bind = new function_bind_type(func);
  bind->set_num_arguments(3);
  bind->add_argument(arg1);
  bind->add_argument(arg2);
  bind->add_argument(arg3);
  return bind;
}

template <typename R, typename T1, typename T2, typename T3, typename T4,
                      typename A1, typename A2, typename A3, typename A4>
::future::internal::function_bind_base<R>*
function_bind(R func(T1, T2, T3, T4),
              A1 arg1, A2 arg2, A3 arg3, A4 arg4) {
  typedef R FunctionPointer(T1, T2, T3, T4);
  typedef internal::function_bind4<FunctionPointer, R,
                                   T1, T2, T3, T4> function_bind_type;
  function_bind_type *bind = new function_bind_type(func);
  bind->set_num_arguments(4);
  bind->add_argument(arg1);
  bind->add_argument(arg2);
  bind->add_argument(arg3);
  bind->add_argument(arg4);
  return bind;
}

template <typename R, typename T1, typename T2, typename T3, typename T4,
                      typename T5,
                      typename A1, typename A2, typename A3, typename A4,
                      typename A5>
::future::internal::function_bind_base<R>*
function_bind(R func(T1, T2, T3, T4, T5),
              A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) {
  typedef R FunctionPointer(T1, T2, T3, T4, T5);
  typedef internal::function_bind5<FunctionPointer, R,
                                   T1, T2, T3, T4, T5> function_bind_type;
  function_bind_type *bind = new function_bind_type(func);
  bind->set_num_arguments(5);
  bind->add_argument(arg1);
  bind->add_argument(arg2);
  bind->add_argument(arg3);
  bind->add_argument(arg4);
  bind->add_argument(arg5);
  return bind;
}

template <typename R, typename T1, typename T2, typename T3, typename T4,
                      typename T5, typename T6,
                      typename A1, typename A2, typename A3, typename A4,
                      typename A5, typename A6>
::future::internal::function_bind_base<R>*
function_bind(R func(T1, T2, T3, T4, T5, T6),
              A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5,
              A6 arg6) {
  typedef R FunctionPointer(T1, T2, T3, T4, T5, T6);
  typedef internal::function_bind6<FunctionPointer, R,
                                   T1, T2, T3, T4, T5,
                                   T6> function_bind_type;
  function_bind_type *bind = new function_bind_type(func);
  bind->set_num_arguments(6);
  bind->add_argument(arg1);
  bind->add_argument(arg2);
  bind->add_argument(arg3);
  bind->add_argument(arg4);
  bind->add_argument(arg5);
  bind->add_argument(arg6);
  return bind;
}

template <typename R, typename T1, typename T2, typename T3, typename T4,
                      typename T5, typename T6, typename T7,
                      typename A1, typename A2, typename A3, typename A4,
                      typename A5, typename A6, typename A7>
::future::internal::function_bind_base<R>*
function_bind(R func(T1, T2, T3, T4, T5, T6, T7),
              A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5,
              A6 arg6, A7 arg7) {
  typedef R FunctionPointer(T1, T2, T3, T4, T5, T6, T7);
  typedef internal::function_bind7<FunctionPointer, R,
                                   T1, T2, T3, T4, T5,
                                   T6, T7> function_bind_type;
  function_bind_type *bind = new function_bind_type(func);
  bind->set_num_arguments(7);
  bind->add_argument(arg1);
  bind->add_argument(arg2);
  bind->add_argument(arg3);
  bind->add_argument(arg4);
  bind->add_argument(arg5);
  bind->add_argument(arg6);
  bind->add_argument(arg7);
  return bind;
}

template <typename R, typename T1, typename T2, typename T3, typename T4,
                      typename T5, typename T6, typename T7, typename T8,
                      typename A1, typename A2, typename A3, typename A4,
                      typename A5, typename A6, typename A7, typename A8>
::future::internal::function_bind_base<R>*
function_bind(R func(T1, T2, T3, T4, T5, T6, T7, T8),
              A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5,
              A6 arg6, A7 arg7, A8 arg8) {
  typedef R FunctionPointer(T1, T2, T3, T4, T5, T6, T7, T8);
  typedef internal::function_bind8<FunctionPointer, R,
                                   T1, T2, T3, T4, T5,
                                   T6, T7, T8> function_bind_type;
  function_bind_type *bind = new function_bind_type(func);
  bind->set_num_arguments(8);
  bind->add_argument(arg1);
  bind->add_argument(arg2);
  bind->add_argument(arg3);
  bind->add_argument(arg4);
  bind->add_argument(arg5);
  bind->add_argument(arg6);
  bind->add_argument(arg7);
  bind->add_argument(arg8);
  return bind;
}

template <typename R, typename T1, typename T2, typename T3, typename T4,
                      typename T5, typename T6, typename T7, typename T8,
                      typename T9,
                      typename A1, typename A2, typename A3, typename A4,
                      typename A5, typename A6, typename A7, typename A8,
                      typename A9>
::future::internal::function_bind_base<R>*
function_bind(R func(T1, T2, T3, T4, T5, T6, T7, T8, T9),
              A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5,
              A6 arg6, A7 arg7, A8 arg8, A9 arg9) {
  typedef R FunctionPointer(T1, T2, T3, T4, T5, T6, T7, T8, T9);
  typedef internal::function_bind9<FunctionPointer, R,
                                   T1, T2, T3, T4, T5,
                                   T6, T7, T8, T9> function_bind_type;
  function_bind_type *bind = new function_bind_type(func);
  bind->set_num_arguments(9);
  bind->add_argument(arg1);
  bind->add_argument(arg2);
  bind->add_argument(arg3);
  bind->add_argument(arg4);
  bind->add_argument(arg5);
  bind->add_argument(arg6);
  bind->add_argument(arg7);
  bind->add_argument(arg8);
  bind->add_argument(arg9);
  return bind;
}

template <typename R, typename T1, typename T2, typename T3, typename T4,
                      typename T5, typename T6, typename T7, typename T8,
                      typename T9, typename T10,
                      typename A1, typename A2, typename A3, typename A4,
                      typename A5, typename A6, typename A7, typename A8,
                      typename A9, typename A10>
::future::internal::function_bind_base<R>*
function_bind(R func(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10),
              A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5,
              A6 arg6, A7 arg7, A8 arg8, A9 arg9, A10 arg10) {
  typedef R FunctionPointer(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10);
  typedef internal::function_bind10<FunctionPointer, R,
                                    T1, T2, T3, T4, T5,
                                    T6, T7, T8, T9, T10> function_bind_type;
  function_bind_type *bind = new function_bind_type(func);
  bind->set_num_arguments(10);
  bind->add_argument(arg1);
  bind->add_argument(arg2);
  bind->add_argument(arg3);
  bind->add_argument(arg4);
  bind->add_argument(arg5);
  bind->add_argument(arg6);
  bind->add_argument(arg7);
  bind->add_argument(arg8);
  bind->add_argument(arg9);
  bind->add_argument(arg10);
  return bind;
}

}  /* namespace bind */
}  /* namespace future */

#endif  /* FUTURE_BIND_H_ */
