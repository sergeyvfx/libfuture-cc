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

namespace future {
namespace internal {

template<typename T>
class foreach_helper {
 public:
  typedef typename T::const_iterator iterator_type;
  explicit foreach_helper(const T& range) : current_iterator_(range.begin()),
                                            end_iterator_(range.end()),
                                            value_loop_state_(LOOP_DONE) {}
  inline bool is_done() {
    return value_loop_state_ == LOOP_NEED_START ||
           current_iterator_ == end_iterator_;
  }
  inline void step() {
    ++current_iterator_;
  }

  inline iterator_type& value_loop_setup() {
    value_loop_state_ = LOOP_NEED_START;
    return current_iterator_;
  }
  inline bool is_value_loop_done() {
    return value_loop_state_ == LOOP_DONE;
  }
  inline void value_loop_step() {
    value_loop_state_ = LOOP_DONE;
  }
 protected:
  enum loop_state {
    LOOP_NEED_START = 0,
    LOOP_DONE = 1,
  };
  iterator_type current_iterator_;
  iterator_type end_iterator_;
  loop_state value_loop_state_;
};

}  /* namespace internal */

#if defined(__GNUC__) || defined(__clang__)
#  define FUTURE_FOREACH(var, range) \
  for (future::internal::foreach_helper<__typeof__(range)> helper(range); \
       !helper.is_done(); \
       helper.step()) \
  for (var = *helper.value_loop_setup(); \
       !helper.is_value_loop_done(); \
       helper.value_loop_step())
#else
#  error "No foreach loop implementation for this compiler"
#endif

}  /* namespace intenral */

#endif /* FUTURE_FOREACH_H_ */
