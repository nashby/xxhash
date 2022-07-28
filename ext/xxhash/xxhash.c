#include "xxhash.h"

VALUE xxhash_xxh32_file(VALUE mod, VALUE filename, VALUE seed)
{
  StringValue(filename);

  XXH32_state_t* state = XXH32_createState();
  if (state == NULL) {
    rb_raise(rb_eRuntimeError, "%s", "Cannot create state, out of memory");
  }

  XXH32_reset(state, NUM2INT(seed));

  char buffer[16384];
  size_t count;
  FILE *fp = fopen(RSTRING_PTR(filename), "rb");
  if (fp == NULL) {
    XXH32_freeState(state);
    VALUE error = INT2FIX(errno);
    rb_exc_raise(rb_class_new_instance(1, &error, rb_eSystemCallError));
  }

  while ((count = fread(buffer, 1, sizeof(buffer), fp)) != 0) {
    XXH32_update(state, buffer, count);
  }
  fclose(fp);

  XXH32_hash_t result = XXH32_digest(state);

  XXH32_freeState(state);
  return ULL2NUM(result);
}

VALUE xxhash_xxh64_file(VALUE mod, VALUE filename, VALUE seed)
{
  StringValue(filename);

  XXH64_state_t* state = XXH64_createState();
  if (state == NULL) {
    rb_raise(rb_eRuntimeError, "%s", "Cannot create state, out of memory");
  }

  XXH64_reset(state, NUM2INT(seed));

  char buffer[16384];
  size_t count;
  FILE *fp = fopen(RSTRING_PTR(filename), "rb");
  if (fp == NULL) {
    XXH64_freeState(state);
    VALUE error = INT2FIX(errno);
    rb_exc_raise(rb_class_new_instance(1, &error, rb_eSystemCallError));
  }

  while ((count = fread(buffer, 1, sizeof(buffer), fp)) != 0) {
    XXH64_update(state, buffer, count);
  }
  fclose(fp);

  XXH64_hash_t result = XXH64_digest(state);

  XXH64_freeState(state);
  return ULL2NUM(result);
}

VALUE xxhash_xxh32(VALUE mod, VALUE input, VALUE seed)
{
  return ULL2NUM(XXH32(StringValuePtr(input), (size_t)RSTRING_LEN(input), (unsigned int)NUM2ULL(seed)));
}

void xxhash32_streaming_hash_free(xxhash_xxh32_t* storage)
{
  // Digest frees the memory.
  XXH32_freeState(storage->state);
  xfree(storage);
}

VALUE xxhash32_streaming_hash_new(VALUE klass, VALUE seed)
{
  XXH_errorcode code;
  xxhash_xxh32_t* storage;
  storage = ALLOC(xxhash_xxh32_t);
  storage->state = XXH32_createState();
  storage->seed = (unsigned int)NUM2ULL(seed);
  code = XXH32_reset(storage->state, storage->seed);
  if(code != XXH_OK) {
    rb_raise(rb_eRuntimeError, "Error during reset.");
    return Qnil;
  }
  return Data_Wrap_Struct(klass, 0, xxhash32_streaming_hash_free, storage);
}

VALUE xxhash32_streaming_hash_reset(VALUE self)
{
  XXH_errorcode code;
  xxhash_xxh32_t* storage;
  Data_Get_Struct(self, xxhash_xxh32_t, storage);

  code = XXH32_reset(storage->state, storage->seed);
  if(code != XXH_OK) {
    rb_raise(rb_eRuntimeError, "Error during reset.");
  }
  return Qnil;
}


VALUE xxhash32_streaming_hash_update(VALUE self, VALUE data)
{
  XXH_errorcode code;
  xxhash_xxh32_t* storage;
  Data_Get_Struct(self, xxhash_xxh32_t, storage);

  code = XXH32_update(storage->state, StringValuePtr(data), (size_t)RSTRING_LEN(data));
  if(code != XXH_OK) {
    rb_raise(rb_eRuntimeError, "Error during update.");
  }
  return Qnil;
}

VALUE xxhash32_streaming_hash_digest(VALUE self)
{
  xxhash_xxh32_t* storage;
  Data_Get_Struct(self, xxhash_xxh32_t, storage);

  // Do not free memory now.
  return ULL2NUM(XXH32_digest(storage->state));
}

VALUE xxhash_xxh64(VALUE mod, VALUE input, VALUE seed)
{
  return ULL2NUM(XXH64(StringValuePtr(input), (size_t)RSTRING_LEN(input), (unsigned int)NUM2ULL(seed)));
}

void xxhash64_streaming_hash_free(xxhash_xxh64_t* storage)
{
  // Digest frees the memory.
  XXH64_freeState(storage->state);
  xfree(storage);
}

VALUE xxhash64_streaming_hash_new(VALUE klass, VALUE seed)
{
  XXH_errorcode code;
  xxhash_xxh64_t* storage;
  storage = ALLOC(xxhash_xxh64_t);
  storage->state = XXH64_createState();
  storage->seed = (unsigned int)NUM2ULL(seed);

  code = XXH64_reset(storage->state, storage->seed);
  if(code != XXH_OK) {
    rb_raise(rb_eRuntimeError, "Error during reset.");
    return Qnil;
  }
  return Data_Wrap_Struct(klass, 0, xxhash64_streaming_hash_free, storage);
}

VALUE xxhash64_streaming_hash_reset(VALUE self)
{
  XXH_errorcode code;
  xxhash_xxh64_t* storage;
  Data_Get_Struct(self, xxhash_xxh64_t, storage);

  code = XXH64_reset(storage->state, storage->seed);
  if(code != XXH_OK) {
    rb_raise(rb_eRuntimeError, "Error during reset.");
  }
  return Qnil;
}

VALUE xxhash64_streaming_hash_update(VALUE self, VALUE data)
{
  XXH_errorcode code;
  xxhash_xxh64_t* storage;
  Data_Get_Struct(self, xxhash_xxh64_t, storage);

  code = XXH64_update(storage->state, StringValuePtr(data), (size_t)RSTRING_LEN(data));
  if(code != XXH_OK) {
    rb_raise(rb_eRuntimeError, "Error during update.");
  }
  return Qnil;
}

VALUE xxhash64_streaming_hash_digest(VALUE self)
{
  xxhash_xxh64_t* storage;
  Data_Get_Struct(self, xxhash_xxh64_t, storage);

  // Do not free memory now.
  return ULL2NUM(XXH64_digest(storage->state));
}


void Init_xxhash(void)
{
  #ifdef HAVE_RB_EXT_RACTOR_SAFE
    rb_ext_ractor_safe(true);
  #endif

  VALUE cStreamingHash;
  VALUE cStreamingHash64;
  VALUE mXXhash;
  VALUE mInternal;

  mXXhash = rb_define_module("XXhash");
  mInternal = rb_define_module_under(mXXhash, "XXhashInternal");

  rb_define_singleton_method(mInternal, "xxh32", (ruby_method*) &xxhash_xxh32, 2);
  rb_define_singleton_method(mInternal, "xxh32_file", (ruby_method*) &xxhash_xxh32_file, 2);
  rb_define_singleton_method(mInternal, "xxh64", (ruby_method*) &xxhash_xxh64, 2);
  rb_define_singleton_method(mInternal, "xxh64_file", (ruby_method*) &xxhash_xxh64_file, 2);

  cStreamingHash = rb_define_class_under(mInternal, "StreamingHash32", rb_cObject);

  rb_define_singleton_method(cStreamingHash, "new", (ruby_method*) &xxhash32_streaming_hash_new, 1);
  rb_define_method(cStreamingHash, "update", (ruby_method*) &xxhash32_streaming_hash_update, 1);
  rb_define_method(cStreamingHash, "digest", (ruby_method*) &xxhash32_streaming_hash_digest, 0);
  rb_define_method(cStreamingHash, "reset", (ruby_method*) &xxhash32_streaming_hash_reset, 0);

  cStreamingHash64 = rb_define_class_under(mInternal, "StreamingHash64", rb_cObject);

  rb_define_singleton_method(cStreamingHash64, "new", (ruby_method*) &xxhash64_streaming_hash_new, 1);
  rb_define_method(cStreamingHash64, "update", (ruby_method*) &xxhash64_streaming_hash_update, 1);
  rb_define_method(cStreamingHash64, "digest", (ruby_method*) &xxhash64_streaming_hash_digest, 0);
  rb_define_method(cStreamingHash64, "reset", (ruby_method*) &xxhash64_streaming_hash_reset, 0);
}
