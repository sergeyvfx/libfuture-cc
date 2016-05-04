// Copyright (c) 2016 libfuture-c++ authors.
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

#ifndef FUTURE_CONDITION_VARIABLE_H_
#define FUTURE_CONDITION_VARIABLE_H_

#include "future/mutex.h"

#if defined(__linux__) || defined(__APPLE__)
#  include <pthread.h>
#else
#  error "Unsupported threading model on your system"
#endif

namespace future {

class condition_variable {
 public:
  condition_variable() {
    pthread_cond_init(&condition_, NULL);
  }

  ~condition_variable() {
    pthread_cond_destroy(&condition_);
  }

  void wait(mutex::scoped_lock& lock) {
    pthread_cond_wait(&condition_, &lock.mutex_->mutex_);
  }

  void notify_one() {
    pthread_cond_signal(&condition_);
  }

  void notify_all() {
    pthread_cond_broadcast(&condition_);
  }

 protected:
  pthread_cond_t condition_;
};

}  /* namespace future */

#endif  /* FUTURE_CONDITION_VARIABLE_H_ */
