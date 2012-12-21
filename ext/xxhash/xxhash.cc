#include <ruby.h>
#include "libxxhash.h"

// Use this typedef to make the compiler happy when
// calling rb_define_method()
typedef VALUE (ruby_method)(...);

extern "C" VALUE xxhash_xxh32(VALUE mod, VALUE input, VALUE seed)
{
  return ULL2NUM(XXH32(StringValuePtr(input), RSTRING_LEN(input), NUM2ULL(seed)));
}

extern "C" void Init_xxhash()
{
  VALUE mXXhash = rb_define_module("XXhash");
  VALUE mInternal = rb_define_module_under(mXXhash, "Internal");

  rb_define_singleton_method(mInternal, "xxh32", (ruby_method*) &xxhash_xxh32, 2);
}
