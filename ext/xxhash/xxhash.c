#include "xxhash.h"

VALUE xxhash_xxh32(VALUE mod, VALUE input, VALUE seed)
{
  return ULL2NUM(XXH32(StringValuePtr(input), (size_t)RSTRING_LEN(input), (unsigned int)NUM2ULL(seed)));
}

void xxhash32_streaming_hash_free(XXH32_state_t* state)
{
  // Digest frees the memory.
  XXH32_freeState(state);
}

VALUE xxhash32_streaming_hash_new(VALUE klass, VALUE seed)
{
  XXH32_state_t* state = XXH32_createState();
  XXH_errorcode code = XXH32_reset(state, (unsigned int)NUM2ULL(seed));
  if(code != XXH_OK) {
    rb_raise(rb_eRuntimeError, "Error during reset.");
    return Qnil;
  }
  return Data_Wrap_Struct(klass, 0, xxhash32_streaming_hash_free, state);
}

VALUE xxhash32_streaming_hash_update(VALUE self, VALUE data)
{
  XXH32_state_t* state;
  Data_Get_Struct(self, XXH32_state_t, state);

  XXH_errorcode code = XXH32_update(state, StringValuePtr(data), (size_t)RSTRING_LEN(data));
  if(code != XXH_OK) {
    rb_raise(rb_eRuntimeError, "Error during update.");
  }
  return Qnil;
}

VALUE xxhash32_streaming_hash_digest(VALUE self)
{
  XXH32_state_t* state;
  Data_Get_Struct(self, XXH32_state_t, state);

  // Do not free memory now.
  return ULL2NUM(XXH32_digest(state));
}

VALUE xxhash_xxh64(VALUE mod, VALUE input, VALUE seed)
{
  return ULL2NUM(XXH64(StringValuePtr(input), (size_t)RSTRING_LEN(input), (unsigned int)NUM2ULL(seed)));
}

void xxhash64_streaming_hash_free(XXH64_state_t* state)
{
  // Digest frees the memory.
  XXH64_freeState(state);
}

VALUE xxhash64_streaming_hash_new(VALUE klass, VALUE seed)
{
  XXH64_state_t* state = XXH64_createState();
  XXH_errorcode code = XXH64_reset(state, NUM2ULL(seed));
  if(code != XXH_OK) {
    rb_raise(rb_eRuntimeError, "Error during reset.");
    return Qnil;
  }
  return Data_Wrap_Struct(klass, 0, xxhash64_streaming_hash_free, state);
}

VALUE xxhash64_streaming_hash_update(VALUE self, VALUE data)
{
  XXH64_state_t* state;
  Data_Get_Struct(self, XXH64_state_t, state);

  XXH_errorcode code = XXH64_update(state, StringValuePtr(data), (size_t)RSTRING_LEN(data));
  if(code != XXH_OK) {
    rb_raise(rb_eRuntimeError, "Error during update.");
  }
  return Qnil;
}

VALUE xxhash64_streaming_hash_digest(VALUE self)
{
  XXH64_state_t* state;
  Data_Get_Struct(self, XXH64_state_t, state);

  // Do not free memory now.
  return ULL2NUM(XXH64_digest(state));
}


void Init_xxhash(void)
{
  VALUE mXXhash = rb_define_module("XXhash");
  VALUE mInternal = rb_define_module_under(mXXhash, "XXhashInternal");

  rb_define_singleton_method(mInternal, "xxh32", (ruby_method*) &xxhash_xxh32, 2);
  rb_define_singleton_method(mInternal, "xxh64", (ruby_method*) &xxhash_xxh64, 2);

  VALUE cStreamingHash = rb_define_class_under(mInternal, "StreamingHash32", rb_cObject);

  rb_define_singleton_method(cStreamingHash, "new", (ruby_method*) &xxhash32_streaming_hash_new, 1);
  rb_define_method(cStreamingHash, "update", (ruby_method*) &xxhash32_streaming_hash_update, 1);
  rb_define_method(cStreamingHash, "digest", (ruby_method*) &xxhash32_streaming_hash_digest, 0);

  VALUE cStreamingHash64 = rb_define_class_under(mInternal, "StreamingHash64", rb_cObject);

  rb_define_singleton_method(cStreamingHash64, "new", (ruby_method*) &xxhash64_streaming_hash_new, 1);
  rb_define_method(cStreamingHash64, "update", (ruby_method*) &xxhash64_streaming_hash_update, 1);
  rb_define_method(cStreamingHash64, "digest", (ruby_method*) &xxhash64_streaming_hash_digest, 0);
}
