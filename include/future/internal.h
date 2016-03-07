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

#ifndef FUTURE_INTERNAL_H_
#define FUTURE_INTERNAL_H_

#include <cassert>
#include <cstring>

namespace future {
namespace internal {

class argument_wrapper_base {
 public:
  argument_wrapper_base() : is_placeholder_(true),
                            placeholder_position_(-1),
                            data_size_(0),
                            data_(NULL) {}

  argument_wrapper_base(bool is_placeholder,
                        int placeholder_position)
    : is_placeholder_(is_placeholder),
      placeholder_position_(placeholder_position),
      data_size_(0),
      data_(NULL) {}

  argument_wrapper_base(const argument_wrapper_base& other) {
    is_placeholder_ = other.is_placeholder_;
    placeholder_position_ = other.placeholder_position_;
    data_size_ = other.data_size_;
    data_ = NULL;
  }

  virtual ~argument_wrapper_base() {
  }

  template <typename T>
  inline T cast() {
    assert(data_ != NULL);
    assert(data_size_ == sizeof(T));
    return *reinterpret_cast<T*>(data_);
  }

  inline bool is_placeholder() {
    return is_placeholder_;
  }

  inline int get_placeholder_position() {
    return placeholder_position_;
  }

  virtual argument_wrapper_base* clone() {
    return new argument_wrapper_base(*this);
  }

 protected:
  bool is_placeholder_;
  int placeholder_position_;
  size_t data_size_;
  void *data_;
};

template<typename T>
class argument_wrapper : public argument_wrapper_base {
 public:
  argument_wrapper() : argument_wrapper_base() {}

  argument_wrapper(T arg) : argument_wrapper_base(false, -1),
                            storage_(arg) {
    this->data_size_ = sizeof(T);
    this->data_ = &storage_;
  }

  explicit argument_wrapper(const argument_wrapper<T>& other)
      : argument_wrapper_base(other) {
    storage_ = other.storage_;
    data_ = &storage_;
  }

  virtual argument_wrapper_base* clone() {
    return new argument_wrapper<T>(*this);
  }

 protected:
  T storage_;
};

class argument_list {
 public:
  argument_list()
      : arguments_(NULL),
        num_arguments_(0),
        need_free_(true) {
    resize(0);
  }

  explicit argument_list(int num_arguments)
      : num_arguments_(num_arguments),
        arguments_(NULL),
        need_free_(true) {
    resize(num_arguments);
  }

  explicit argument_list(argument_list& other)
      : arguments_(NULL),
        need_free_(true),
        num_arguments_(0) {
    /* TODO(sergey): De-duplicate with operator=. */
    resize(other.num_arguments_);
    for (int i = 0; i < num_arguments_; ++i) {
      arguments_[i] = other.arguments_[i]->clone();
    }
  }

  argument_list(argument_wrapper_base **arguments,
                int num_arguments)
      : num_arguments_(num_arguments),
        arguments_(arguments),
        need_free_(false) {
  }

  ~argument_list() {
    clear();
  }

  void resize(int num_arguments) {
    clear();
    num_arguments_ = num_arguments;
    need_free_ = true;
    if (num_arguments != 0) {
      arguments_ = new argument_wrapper_base*[num_arguments];
      memset(arguments_, 0, sizeof(*arguments_) * num_arguments);
    }
  }

  template <typename T>
  void set(int index, T argument) {
    assert(index >= 0);
    assert(index < num_arguments_);
    assert(need_free_);
    delete arguments_[index];
    arguments_[index] = new argument_wrapper<T>(argument);
  }

  void set(int index, argument_wrapper_base& argument_wrapper) {
    assert(index >= 0);
    assert(index < num_arguments_);
    assert(need_free_);
    delete arguments_[index];
    arguments_[index] = argument_wrapper.clone();
  }

  void operator= (const argument_list& other) {
    resize(other.num_arguments_);
    for (int i = 0; i < num_arguments_; ++i) {
      arguments_[i] = other.arguments_[i]->clone();
    }
  }

  argument_wrapper_base* operator[] (int index) {
    assert(index >= 0);
    assert(index < num_arguments_);
    return arguments_[index];
  }

 protected:
  void clear() {
    if (need_free_ && arguments_) {
      for (int i = 0; i < num_arguments_; ++i) {
        delete arguments_[i];
      }
      delete [] arguments_;
    }
    num_arguments_ = 0;
    arguments_ = NULL;
  }

  int num_arguments_;
  argument_wrapper_base **arguments_;
  bool need_free_;
};

template <typename T>
struct nondeducible {
  typedef T type;
};

char (&is_lvalue_helper(...))[1];

template <typename T>
char (&is_lvalue_helper(T&, typename nondeducible<const volatile T&>::type))[2];

#define FUTURE_IS_LVALUE(x) \
    (sizeof(future::internal::is_lvalue_helper((x), (x))) == 2)

}  /* namespace internal */
}  /* namespace future */

#endif  /* FUTURE_INTERNAL_H_ */
