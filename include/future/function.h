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

  virtual void prepare(argument_list& arguments) = 0;
  virtual R invoke(argument_list& arguments) = 0;

  virtual bool is_bound() = 0;

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
  function_base() {}

  function_base(bind_type *function_bind) : function_bind_(function_bind) {}

  ~function_base() {
    delete function_bind_;
  }

  bool is_bound() {
    return function_bind_ != NULL &&
           function_bind_->is_bound();
  }

  R invoke() {
    assert_invoke();
    argument_list_type argument_list(function_bind_->get_num_arguments());
    function_bind_->prepare(argument_list);
    return function_bind_->invoke(argument_list);
  }

  template<typename T1>
  R invoke(T1 arg0) {
    assert_invoke();
    argument_list_type argument_list(function_bind_->get_num_arguments());
    function_bind_->prepare(argument_list);
    set_argument(argument_list, 0, arg0);
    check_arguments(argument_list);
    return function_bind_->invoke(argument_list);
  }

 protected:
  void assert_invoke() {
    assert(is_bound() == true);
  }

  template <typename T>
  void set_argument(argument_list_type& argument_list,
                    int position,
                    T& value) {
    int num_arguments = function_bind_->get_num_arguments();
    for (int i = 0; i < num_arguments; ++i) {
      if (argument_list[i].is_placeholder() &&
          argument_list[i].get_position() == position) {
        argument_list[i] = ::future::internal::argument_wrapper(value);
        return;
      }
    }
  }

  void check_arguments(argument_list_type& argument_list) {
    int num_arguments = function_bind_->get_num_arguments();
    for (int i = 0; i < num_arguments; ++i) {
      assert(!argument_list[i].is_placeholder());
    }
  }

  bind_type *function_bind_;
};

/* Detailed function implementations, they know exact return type and
 * types of all placeholder arguments.
 */

template<typename R>
class function0 : public function_base<R> {
  typedef ::future::internal::function_bind_base<R> bind_type;
 public:
  function0() : function_base<R>() {}
  function0(bind_type *function_bind) : function_base<R>(function_bind) {}
};

template<typename R, typename T1>
class function1 : public function_base<R> {
  typedef ::future::internal::function_bind_base<R> bind_type;
 public:
  function1() : function_base<R>() {}
  function1(bind_type *function_bind) : function_base<R>(function_bind) {}
};

}  /* namespace internal */

/* Some magic which allows to use simple syntax when declaring functions,
 * making it possible to just specify desired signature only.
 */

template<typename R>
class function<R(void)> : public internal::function0<R> {
  typedef internal::function0<R> base_type;
  typedef function self_type;
  typedef ::future::internal::function_bind_base<R> bind_type;
 public:
  function() : base_type() {}
  function(bind_type *function_bind) : base_type(function_bind) {}
  R operator() () {
    return base_type::invoke();
  }
};

template<typename R, typename T0>
class function<R(T0)> : public internal::function1<R , T0> {
  typedef internal::function1<R , T0> base_type;
  typedef function self_type;
  typedef ::future::internal::function_bind_base<R> bind_type;
 public:
  function() : base_type() {}
  function(bind_type *function_bind) : base_type(function_bind) {}
  R operator() (T0 arg0) {
    return base_type::invoke(arg0);
  }
};

}  /* namespace function **/
}  /* namespace future */

#endif  /* FUTURE_FUNCTION_H_ */
