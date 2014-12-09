#include <ruby.h>
#include "libxxhash.h"

// Use this typedef to make the compiler happy when
// calling rb_define_method()
typedef VALUE (ruby_method)(...);

extern "C" VALUE xxhash_xxh32(VALUE mod, VALUE input, VALUE seed)
{
  return ULL2NUM(XXH32(StringValuePtr(input), RSTRING_LEN(input), NUM2ULL(seed)));
}

extern "C" void xxhash_streaming_hash_free(XXH32_state_t* state)
{
  // Digest frees the memory.
  XXH32_freeState(state);
}

extern "C" VALUE xxhash_streaming_hash_new(VALUE klass, VALUE seed)
{
  XXH32_state_t* state = XXH32_createState();
  XXH_errorcode code = XXH32_reset(state, NUM2ULL(seed));
  if(code != XXH_OK) {
    rb_raise(rb_eRuntimeError, "Error during reset.");
    return Qnil;
  }
  return Data_Wrap_Struct(klass, 0, xxhash_streaming_hash_free, state);
}

extern "C" VALUE xxhash_streaming_hash_update(VALUE self, VALUE data)
{
  XXH32_state_t* state;
  Data_Get_Struct(self, XXH32_state_t, state);

  XXH_errorcode code = XXH32_update(state, StringValuePtr(data), RSTRING_LEN(data));
  if(code != XXH_OK) {
    rb_raise(rb_eRuntimeError, "Error during update.");
  }
  return Qnil;
}

extern "C" VALUE xxhash_streaming_hash_digest(VALUE self)
{
  XXH32_state_t* state;
  Data_Get_Struct(self, XXH32_state_t, state);

  // Do not free memory now.
  return ULL2NUM(XXH32_digest(state));
}

extern "C" void Init_xxhash()
{
  VALUE mXXhash = rb_define_module("XXhash");
  VALUE mInternal = rb_define_module_under(mXXhash, "Internal");

  rb_define_singleton_method(mInternal, "xxh32", (ruby_method*) &xxhash_xxh32, 2);

  VALUE cStreamingHash = rb_define_class_under(mInternal, "StreamingHash", rb_cObject);

  rb_define_singleton_method(cStreamingHash, "new", (ruby_method*) &xxhash_streaming_hash_new, 1);
  rb_define_method(cStreamingHash, "update", (ruby_method*) &xxhash_streaming_hash_update, 1);
  rb_define_method(cStreamingHash, "digest", (ruby_method*) &xxhash_streaming_hash_digest, 0);
  rb_define_method(cStreamingHash, "intermediate_digest", (ruby_method*) &xxhash_streaming_hash_digest, 0);
}
