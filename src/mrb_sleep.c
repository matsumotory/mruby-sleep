/*
** mrb_sleep - sleep class for mruby
**
** Copyright (c) mod_mruby developers 2012-
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
** [ MIT license: http://www.opensource.org/licenses/mit-license.php ]
*/

#include <unistd.h>
#include <time.h>

#include "mruby.h"

#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep(x * 1000)
#endif

mrb_value mrb_f_sleep_sleep(mrb_state *mrb, mrb_value self)
{   
    time_t beg, end;
    mrb_value seconds;
    
    beg = time(0);
    mrb_get_args(mrb, "i", &seconds);
    sleep(mrb_fixnum(seconds));
    end = time(0) - beg;

    return mrb_fixnum_value(end);
}


void mrb_mruby_sleep_gem_init(mrb_state *mrb)
{
    struct RClass *sleep;

    sleep = mrb_define_module(mrb, "Sleep");
    mrb_define_class_method(mrb, sleep, "sleep", mrb_f_sleep_sleep, ARGS_REQ(1));
}
