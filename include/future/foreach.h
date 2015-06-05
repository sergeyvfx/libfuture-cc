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

#ifndef FUTURE_FOREACH_H_
#define FUTURE_FOREACH_H_

#include "future/internal.h"

namespace future {
namespace internal {

template<typename T>
class foreach_iterator_helper {
 public:
  typedef typename T::iterator type;
};

template<typename T>
class foreach_iterator_helper<T const> {
 public:
  typedef typename T::const_iterator type;
};

template<typename T, bool need_copy> class foreach_helper;


template<typename T>
class foreach_helper<T, false> {
 public:
  typedef typename foreach_iterator_helper<T>::type iterator_type;
  foreach_helper(T& range, bool /*unused*/) : current_iterator_(range.begin()),
                                              end_iterator_(range.end()) {}
  inline bool is_done() {
    return current_iterator_ == end_iterator_;
  }
  inline void step() {
    ++current_iterator_;
  }
  inline iterator_type& current_iterator() {
    return current_iterator_;
  }
 protected:
  iterator_type current_iterator_;
  iterator_type end_iterator_;
};

template<typename T>
class foreach_helper<T, true> {
 public:
  typedef typename foreach_iterator_helper<T>::type iterator_type;
  foreach_helper(T range, bool /*unused*/) : range_(range),
                                             current_iterator_(range.begin()),
                                             end_iterator_(range.end()) {}
  inline bool is_done() {
    return current_iterator_ == end_iterator_;
  }
  inline void step() {
    ++current_iterator_;
  }
  inline iterator_type& current_iterator() {
    return current_iterator_;
  }
 protected:
  T range_;
  iterator_type current_iterator_;
  iterator_type end_iterator_;
};

}  /* namespace internal */

#if defined(__GNUC__) || defined(__clang__)
#  define FUTURE_FOREACH(var, range) \
  if (bool global_stop = false) {} else \
  for (future::internal::foreach_helper<__typeof__(range), \
                                        !FUTURE_IS_LVALUE(range)> \
          helper(range, false); \
       !helper.is_done() && !global_stop; \
       helper.step()) \
  if(bool stop = false) {} else \
  if(!(global_stop = true)) {} else \
  for (var = *helper.current_iterator(); !stop; stop = true, global_stop = false)
#else
#  error "No foreach loop implementation for this compiler"
#endif

}  /* namespace future */

#endif /* FUTURE_FOREACH_H_ */
