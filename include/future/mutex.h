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

#ifndef FUTURE_MUTEX_H_
#define FUTURE_MUTEX_H_

#if defined(__linux__) || defined(__APPLE__)
#  include <pthread.h>
#else
#  error "Unsupported threading model on your system"
#endif

namespace future {

class condition_variable;

class mutex {
 public:
  class scoped_lock {
   public:
    explicit scoped_lock(mutex& mutex)
        : mutex_(&mutex),
          locked_(false) {
      lock();
    }

    ~scoped_lock() {
      if (locked_) {
        locked_ = false;
        mutex_->unlock();
      }
    }

    void lock() {
      mutex_->lock();
      locked_ = true;
    }

    void unlock() {
      locked_ = false;
      mutex_->unlock();
    }

    bool try_lock() {
      if (mutex_->try_lock()) {
        locked_ = true;
        return true;
      }
      return false;
    }
   protected:
    friend class condition_variable;
    mutex *mutex_;
    bool locked_;
  };

  mutex() {
    pthread_mutex_init(&mutex_, NULL);
  }

  ~mutex() {
    pthread_mutex_destroy(&mutex_);
  }

  void lock() {
    pthread_mutex_lock(&mutex_);
  }

  void unlock() {
    pthread_mutex_unlock(&mutex_);
  }

  bool try_lock() {
    return (pthread_mutex_trylock(&mutex_) == 0);
  }

 protected:
  friend class condition_variable;
  pthread_mutex_t mutex_;
};

}  /* namespace future */

#endif  /* FUTURE_MUTEX_H_ */
