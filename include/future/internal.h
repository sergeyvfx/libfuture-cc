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

#pragma message "argument_wrapper approach will be replaced with"\
  " more c++-style invocation soon"

namespace future {
namespace internal {

class argument_wrapper {
 public:
  argument_wrapper() : position_(-1),
                       data_size_(0),
                       data_(NULL) {
    memset(data_static_, 0, sizeof(data_static_));
  }

  argument_wrapper(bool /*is_placeholder*/,
                  int position) : position_(position),
                                  data_size_(0),
                                  data_(NULL) {
    memset(data_static_, 0, sizeof(data_static_));
  }

  template <typename T>
  argument_wrapper(T arg) : position_(-1),
                            data_size_(sizeof(T)) {
    if (data_size_ > sizeof(data_static_)) {
      data_ = new unsigned char[data_size_];
    } else {
      data_ = reinterpret_cast<void*>(data_static_);
    }
    memcpy(data_, &arg, data_size_);
  }

  ~argument_wrapper() {
    free_data();
  }

  void operator= (const argument_wrapper& other) {
    if (this == &other) {
      return;
    }
    free_data();
    position_ = other.position_;
    data_size_ = other.data_size_;
    if (other.data_ != NULL) {
      if (other.data_ == other.data_static_) {
        data_ = reinterpret_cast<void*>(data_static_);
      } else {
        data_ = new unsigned char[data_size_];
      }
      memcpy(data_, other.data_, data_size_);
    } else {
      data_ = NULL;
    }
  }

  template <typename T>
  T cast() {
    assert(data_ != NULL);
    return *reinterpret_cast<T*>(data_);
  }

  bool is_placeholder() {
    return position_ != -1;
  }

  int get_position() {
    return position_;
  }

 protected:
  void free_data(void) {
    if (data_ != NULL && data_ != data_static_) {
      delete [] (unsigned char*)data_;
      data_ = NULL;
    }
  }

  int position_;
  size_t data_size_;
  unsigned char data_static_[64];
  void *data_;
};

class argument_list {
 public:
  argument_list() {
    resize(0);
  }

  explicit argument_list(int num_arguments)
    : num_arguments_(num_arguments) {
    resize(num_arguments);
  }

  ~argument_list() {
  }

  void resize(int num_arguments) {
    num_arguments_ = num_arguments;
  }

  argument_wrapper& operator[] (int index) {
    assert(index >= 0);
    assert(index < num_arguments_);
    return arguments_[index];
  }

 protected:
  int num_arguments_;
  argument_wrapper arguments_[10];
};

}  /* namespace internal */
}  /* namespace future */

#endif  /* FUTURE_INTERNAL_H_ */
