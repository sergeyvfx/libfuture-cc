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

  virtual ~argument_wrapper_base() {
  }

  template <typename T>
  T cast() {
    assert(data_ != NULL);
    assert(data_size_ == sizeof(T));
    return *reinterpret_cast<T*>(data_);
  }

  bool is_placeholder() {
    return is_placeholder_;
  }

  int get_placeholder_position() {
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

  virtual argument_wrapper_base* clone() {
    return new argument_wrapper<T>(*this);
  }

 protected:
  T storage_;
};

class argument_list {
 public:
  argument_list() : arguments_(NULL) {
    resize(0);
  }

  explicit argument_list(int num_arguments)
    : num_arguments_(num_arguments), arguments_(NULL) {
    resize(num_arguments);
  }

  explicit argument_list(argument_list& other) : arguments_(NULL) {
    /* TODO(sergey): De-duplicate with operator=. */
    resize(other.num_arguments_);
    for (int i = 0; i < num_arguments_; ++i) {
      arguments_[i] = other.arguments_[i]->clone();
    }
  }

  ~argument_list() {
    for (int i = 0; i < num_arguments_; ++i) {
      delete arguments_[i];
    }
    delete [] arguments_;
  }

  void resize(int num_arguments) {
    num_arguments_ = num_arguments;
    delete [] arguments_;
    arguments_ = new argument_wrapper_base*[num_arguments];
    memset(arguments_, 0, sizeof(*arguments_) * num_arguments);
  }

  template <typename T>
  void set(int index, T argument) {
    assert(index >= 0);
    assert(index < num_arguments_);
    delete arguments_[index];
    arguments_[index] = new argument_wrapper<T>(argument);
  }

  void set(int index, argument_wrapper_base& argument_wrapper) {
    assert(index >= 0);
    assert(index < num_arguments_);
    delete arguments_[index];
    arguments_[index] = argument_wrapper.clone();
  }

  void operator= (const argument_list& other) {
    resize(other.num_arguments_);
    for (int i = 0; i < num_arguments_; ++i) {
      arguments_[i] = other.arguments_[i]->clone();
    }
  }

  argument_wrapper_base& operator[] (int index) {
    assert(index >= 0);
    assert(index < num_arguments_);
    return *arguments_[index];
  }

 protected:
  int num_arguments_;
  argument_wrapper_base **arguments_;
};

}  /* namespace internal */
}  /* namespace future */

#endif  /* FUTURE_INTERNAL_H_ */
