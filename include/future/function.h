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

#ifndef FUTURE_FUNCTION_H_
#define FUTURE_FUNCTION_H_

namespace future {
namespace function {

template<typename Signature> class function;
}  /* namespace function */

namespace internal {

/* Base class for everyone who considers self bindable and callable. */
template <typename R>
class function_bind_base {
 public:
  function_bind_base() : num_arguments_(0) {}

  explicit function_bind_base(int num_arguments)
  : num_arguments_(num_arguments) {}

  virtual ~function_bind_base() {}

  int get_num_arguments() const {
    return num_arguments_;
  }

  virtual R invoke(argument_list& arguments) = 0;

  virtual bool is_bound() = 0;

  virtual function_bind_base* clone() = 0;

 protected:
  int num_arguments_;
};

}  /* namespace internal */

namespace function {

template<typename Signature> class function;

namespace internal {

/* Bse function, superclass for all the function. */
template<typename R>
class function_base {
  typedef ::future::internal::function_bind_base<R> bind_type;
  typedef future::internal::argument_list argument_list_type;

 public:
  function_base() : function_bind_(NULL) {}

  explicit function_base(bind_type *function_bind) : function_bind_(function_bind) {}

  explicit function_base(const function_base& other) {
    if (other.function_bind_ != NULL) {
      function_bind_ = other.function_bind_->clone();
    } else {
      function_bind_ = NULL;
    }
  }

  void operator=(function_base& other) {
    delete function_bind_;
    if (other.function_bind_ != NULL) {
      function_bind_ = other.function_bind_->clone();
    } else {
      function_bind_ = NULL;
    }
  }

  ~function_base() {
    delete function_bind_;
  }

  bool is_bound() const {
    return function_bind_ != NULL &&
           function_bind_->is_bound();
  }

  operator bool() const {
    return is_bound();
  }

#define FUNCTION_INVOKE_COMMON_PRE() \
    using future::internal::argument_wrapper; \
    using future::internal::argument_wrapper_base; \
    assert_invoke()

#define FUNCTION_INVOKE_COMMON_POST(arguments, num_arguments) \
    argument_list_type argument_list((argument_wrapper_base**)arguments, num_arguments); \
    return function_bind_->invoke(argument_list)

  R invoke() {
    FUNCTION_INVOKE_COMMON_PRE();
    FUNCTION_INVOKE_COMMON_POST(NULL, 0);
  }

  template<typename T1>
  R invoke(T1 arg1) {
    FUNCTION_INVOKE_COMMON_PRE();
    argument_wrapper<T1> a1(arg1);
    argument_wrapper_base *arguments[] = {&a1};
    FUNCTION_INVOKE_COMMON_POST(arguments, 1);
  }

  template<typename T1, typename T2>
  R invoke(T1 arg1, T2 arg2) {
    FUNCTION_INVOKE_COMMON_PRE();
    argument_wrapper<T1> a1(arg1);
    argument_wrapper<T2> a2(arg2);
    argument_wrapper_base *arguments[] = {&a1, &a2};
    FUNCTION_INVOKE_COMMON_POST(&arguments, 2);
  }

  template<typename T1, typename T2, typename T3>
  R invoke(T1 arg1, T2 arg2, T3 arg3) {
    FUNCTION_INVOKE_COMMON_PRE();
    argument_wrapper<T1> a1(arg1);
    argument_wrapper<T2> a2(arg2);
    argument_wrapper<T3> a3(arg3);
    argument_wrapper_base *arguments[] = {&a1, &a2, &a3};
    FUNCTION_INVOKE_COMMON_POST(&arguments, 3);
  }

  template<typename T1, typename T2, typename T3, typename T4>
  R invoke(T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
    FUNCTION_INVOKE_COMMON_PRE();
    argument_wrapper<T1> a1(arg1);
    argument_wrapper<T2> a2(arg2);
    argument_wrapper<T3> a3(arg3);
    argument_wrapper<T4> a4(arg4);
    argument_wrapper_base *arguments[] = {&a1, &a2, &a3, &a4};
    FUNCTION_INVOKE_COMMON_POST(&arguments, 4);
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5>
  R invoke(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5) {
    FUNCTION_INVOKE_COMMON_PRE();
    argument_wrapper<T1> a1(arg1);
    argument_wrapper<T2> a2(arg2);
    argument_wrapper<T3> a3(arg3);
    argument_wrapper<T4> a4(arg4);
    argument_wrapper<T5> a5(arg5);
    argument_wrapper_base *arguments[] = {&a1, &a2, &a3, &a4, &a5};
    FUNCTION_INVOKE_COMMON_POST(&arguments, 5);
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5,
           typename T6>
  R invoke(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
           T6 arg6) {
    FUNCTION_INVOKE_COMMON_PRE();
    argument_wrapper<T1> a1(arg1);
    argument_wrapper<T2> a2(arg2);
    argument_wrapper<T3> a3(arg3);
    argument_wrapper<T4> a4(arg4);
    argument_wrapper<T5> a5(arg5);
    argument_wrapper<T6> a6(arg6);
    argument_wrapper_base *arguments[] = {&a1, &a2, &a3, &a4, &a5,
                                          &a6};
    FUNCTION_INVOKE_COMMON_POST(&arguments, 6);
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5,
           typename T6, typename T7>
  R invoke(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
           T6 arg6, T7 arg7) {
    FUNCTION_INVOKE_COMMON_PRE();
    argument_wrapper<T1> a1(arg1);
    argument_wrapper<T2> a2(arg2);
    argument_wrapper<T3> a3(arg3);
    argument_wrapper<T4> a4(arg4);
    argument_wrapper<T5> a5(arg5);
    argument_wrapper<T6> a6(arg6);
    argument_wrapper<T7> a7(arg7);
    argument_wrapper_base *arguments[] = {&a1, &a2, &a3, &a4, &a5,
                                          &a6, &a7};
    FUNCTION_INVOKE_COMMON_POST(&arguments, 7);
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5,
           typename T6, typename T7, typename T8>
  R invoke(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
           T6 arg6, T7 arg7, T8 arg8) {
    FUNCTION_INVOKE_COMMON_PRE();
    argument_wrapper<T1> a1(arg1);
    argument_wrapper<T2> a2(arg2);
    argument_wrapper<T3> a3(arg3);
    argument_wrapper<T4> a4(arg4);
    argument_wrapper<T5> a5(arg5);
    argument_wrapper<T6> a6(arg6);
    argument_wrapper<T7> a7(arg7);
    argument_wrapper<T8> a8(arg8);
    argument_wrapper_base *arguments[] = {&a1, &a2, &a3, &a4, &a5,
                                          &a6, &a7, &a8};
    FUNCTION_INVOKE_COMMON_POST(&arguments, 8);
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5,
           typename T6, typename T7, typename T8, typename T9>
  R invoke(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
           T6 arg6, T7 arg7, T8 arg8, T9 arg9) {
    FUNCTION_INVOKE_COMMON_PRE();
    argument_wrapper<T1> a1(arg1);
    argument_wrapper<T2> a2(arg2);
    argument_wrapper<T3> a3(arg3);
    argument_wrapper<T4> a4(arg4);
    argument_wrapper<T5> a5(arg5);
    argument_wrapper<T6> a6(arg6);
    argument_wrapper<T7> a7(arg7);
    argument_wrapper<T8> a8(arg8);
    argument_wrapper<T9> a9(arg9);
    argument_wrapper_base *arguments[] = {&a1, &a2, &a3, &a4, &a5,
                                          &a6, &a7, &a8, &a9};
    FUNCTION_INVOKE_COMMON_POST(&arguments, 9);
  }

  template<typename T1, typename T2, typename T3, typename T4, typename T5,
           typename T6, typename T7, typename T8, typename T9, typename T10>
  R invoke(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
           T6 arg6, T7 arg7, T8 arg8, T9 arg9, T10 arg10) {
    FUNCTION_INVOKE_COMMON_PRE();
    argument_wrapper<T1> a1(arg1);
    argument_wrapper<T2> a2(arg2);
    argument_wrapper<T3> a3(arg3);
    argument_wrapper<T4> a4(arg4);
    argument_wrapper<T5> a5(arg5);
    argument_wrapper<T6> a6(arg6);
    argument_wrapper<T7> a7(arg7);
    argument_wrapper<T8> a8(arg8);
    argument_wrapper<T9> a9(arg9);
    argument_wrapper<T10> a10(arg10);
    argument_wrapper_base *arguments[] = {&a1, &a2, &a3, &a4, &a5,
                                          &a6, &a7, &a8, &a9, &a10};
    FUNCTION_INVOKE_COMMON_POST(&arguments, 10);
  }

#undef FUNCTION_INVOKE_COMMON_PRE
#undef FUNCTION_INVOKE_COMMON_POST

 protected:
  void assert_invoke() {
    assert(is_bound() == true);
  }

  bind_type *function_bind_;
};

/* Detailed function implementations, they know exact return type and
 * types of all placeholder arguments.
 */

#define FUNCTION_GLUE(a, b) a ## b
#define CLASS_FUNCTION_N_DECLARE(n) \
class FUNCTION_GLUE(function, n) : public function_base<R> { \
  typedef ::future::internal::function_bind_base<R> bind_type; \
 public: \
  FUNCTION_GLUE(function, n)() : function_base<R>() {} \
  FUNCTION_GLUE(function, n)(bind_type *function_bind) : function_base<R>(function_bind) {} \
}

template<typename R>
CLASS_FUNCTION_N_DECLARE(0);

template<typename R, typename T1>
CLASS_FUNCTION_N_DECLARE(1);

template<typename R, typename T1, typename T2>
CLASS_FUNCTION_N_DECLARE(2);

template<typename R, typename T1, typename T2, typename T3>
CLASS_FUNCTION_N_DECLARE(3);

template<typename R, typename T1, typename T2, typename T3, typename T4>
CLASS_FUNCTION_N_DECLARE(4);

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5>
CLASS_FUNCTION_N_DECLARE(5);

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6>
CLASS_FUNCTION_N_DECLARE(6);

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7>
CLASS_FUNCTION_N_DECLARE(7);

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8>
CLASS_FUNCTION_N_DECLARE(8);

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
CLASS_FUNCTION_N_DECLARE(9);

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9,
         typename T10>
CLASS_FUNCTION_N_DECLARE(10);

#undef CLASS_FUNCTION_N_DECLARE
#undef FUNCTION_GLUE

}  /* namespace internal */

/* Some magic which allows to use simple syntax when declaring functions,
 * making it possible to just specify desired signature only.
 */

#define CLASS_FUNCTION_DECLARE_COMMON \
  typedef function self_type; \
  typedef ::future::internal::function_bind_base<R> bind_type; \
 public: \
  function() : base_type() {} \
  function(bind_type *function_bind) : base_type(function_bind) {}

template<typename R>
class function<R(void)> : public internal::function0<R> {
  typedef internal::function0<R> base_type;
  CLASS_FUNCTION_DECLARE_COMMON
  R operator() () {
    return base_type::invoke();
  }
};

template<typename R, typename T1>
class function<R(T1)> : public internal::function1<R , T1> {
  typedef internal::function1<R, T1> base_type;
  CLASS_FUNCTION_DECLARE_COMMON
  R operator() (T1 arg1) {
    return base_type::invoke(arg1);
  }
};

template<typename R, typename T1, typename T2>
class function<R(T1, T2)> : public internal::function2<R , T1, T2> {
  typedef internal::function2<R, T1, T2> base_type;
  CLASS_FUNCTION_DECLARE_COMMON
  R operator() (T1 arg1, T2 arg2) {
    return base_type::invoke(arg1, arg2);
  }
};

template<typename R, typename T1, typename T2, typename T3>
class function<R(T1, T2, T3)> : public internal::function3<R , T1, T2, T3> {
  typedef internal::function3<R, T1, T2, T3> base_type;
  CLASS_FUNCTION_DECLARE_COMMON
  R operator() (T1 arg1, T2 arg2, T3 arg3) {
    return base_type::invoke(arg1, arg2, arg3);
  }
};

template<typename R, typename T1, typename T2, typename T3, typename T4>
class function<R(T1, T2, T3, T4)>
    : public internal::function4<R , T1, T2, T3, T4> {
  typedef internal::function4<R, T1, T2, T3, T4> base_type;
  CLASS_FUNCTION_DECLARE_COMMON
  R operator() (T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
    return base_type::invoke(arg1, arg2, arg3, arg4);
  }
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5>
class function<R(T1, T2, T3, T4, T5)>
    : public internal::function5<R , T1, T2, T3, T4, T5> {
  typedef internal::function5<R, T1, T2, T3, T4, T5> base_type;
  CLASS_FUNCTION_DECLARE_COMMON
  R operator() (T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5) {
    return base_type::invoke(arg1, arg2, arg3, arg4, arg5);
  }
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6>
class function<R(T1, T2, T3, T4, T5, T6)>
    : public internal::function6<R , T1, T2, T3, T4, T5,
                                 T6> {
  typedef internal::function6<R, T1, T2, T3, T4, T5,
                              T6> base_type;
  CLASS_FUNCTION_DECLARE_COMMON
  R operator() (T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
                T6 arg6) {
    return base_type::invoke(arg1, arg2, arg3, arg4, arg5,
                             arg6);
  }
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7>
class function<R(T1, T2, T3, T4, T5, T6, T7)>
    : public internal::function7<R , T1, T2, T3, T4, T5,
                                 T6, T7> {
  typedef internal::function7<R, T1, T2, T3, T4, T5,
                              T6, T7> base_type;
  CLASS_FUNCTION_DECLARE_COMMON
  R operator() (T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
                T6 arg6, T7 arg7) {
    return base_type::invoke(arg1, arg2, arg3, arg4, arg5,
                             arg6, arg7);
  }
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8>
class function<R(T1, T2, T3, T4, T5, T6, T7, T8)>
    : public internal::function8<R , T1, T2, T3, T4, T5,
                                 T6, T7, T8> {
  typedef internal::function8<R, T1, T2, T3, T4, T5,
                              T6, T7, T8> base_type;
  CLASS_FUNCTION_DECLARE_COMMON
  R operator() (T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
                T6 arg6, T7 arg7, T8 arg8) {
    return base_type::invoke(arg1, arg2, arg3, arg4, arg5,
                             arg6, arg7, arg8);
  }
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9>
class function<R(T1, T2, T3, T4, T5, T6, T7, T8, T9)>
    : public internal::function9<R , T1, T2, T3, T4, T5,
                                 T6, T7, T8, T9> {
  typedef internal::function9<R, T1, T2, T3, T4, T5,
                              T6, T7, T8, T9> base_type;
  CLASS_FUNCTION_DECLARE_COMMON
  R operator() (T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
                T6 arg6, T7 arg7, T8 arg8, T9 arg9) {
    return base_type::invoke(arg1, arg2, arg3, arg4, arg5,
                             arg6, arg7, arg8, arg9);
  }
};

template<typename R, typename T1, typename T2, typename T3, typename T4,
         typename T5, typename T6, typename T7, typename T8, typename T9,
         typename T10>
class function<R(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10)>
    : public internal::function10<R , T1, T2, T3, T4, T5,
                                  T6, T7, T8, T9, T10> {
  typedef internal::function10<R, T1, T2, T3, T4, T5,
                               T6, T7, T8, T9, T10> base_type;
  CLASS_FUNCTION_DECLARE_COMMON
  R operator() (T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
                T6 arg6, T7 arg7, T8 arg8, T9 arg9, T10 arg10) {
    return base_type::invoke(arg1, arg2, arg3, arg4, arg5,
                             arg6, arg7, arg8, arg9, arg10);
  }
};

#undef CLASS_FUNCTION_DECLARE_COMMON

}  /* namespace function **/
}  /* namespace future */

#endif  /* FUTURE_FUNCTION_H_ */
