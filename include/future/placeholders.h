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

#ifndef FUTURE_PLACEHOLDERS_H_
#define FUTURE_PLACEHOLDERS_H_

namespace future {
namespace placeholders {

#define _1 ::future::internal::argument_wrapper_base(true, 0)
#define _2 ::future::internal::argument_wrapper_base(true, 1)
#define _3 ::future::internal::argument_wrapper_base(true, 2)
#define _4 ::future::internal::argument_wrapper_base(true, 3)
#define _5 ::future::internal::argument_wrapper_base(true, 4)
#define _6 ::future::internal::argument_wrapper_base(true, 5)
#define _7 ::future::internal::argument_wrapper_base(true, 6)
#define _8 ::future::internal::argument_wrapper_base(true, 7)
#define _9 ::future::internal::argument_wrapper_base(true, 8)
#define _10 ::future::internal::argument_wrapper_base(true, 9)

}  /*  namespace placeholders */
}  /* namespace future */

#endif  /* FUTURE_PLACEHOLDERS_H_ */
