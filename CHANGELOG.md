### 0.5.0 (July 28, 2022)
  * Mark extension as Ractor-safe (by [@kreynolds](https://github.com/kreynolds))
  * Add ability to hash files by path directly with `XXhash.xxh32_file` and `XXhash.xxh64_file` (by [@kreynolds](https://github.com/kreynolds))

### 0.4.0 (December 11, 2016)
  * Add xxHash to `Digest` module and make it more compatieble
    with another hash functions from `Digest`. (by [@justinwsmith](https://github.com/justinwsmith))
  * Add a `StreamingHash` class that's externally instantiatable. (by [@justinwsmith](https://github.com/justinwsmith))
  * Fix segfault when nil is passed as param (https://github.com/nashby/xxhash/issues/13) (by [@justinwsmith](https://github.com/justinwsmith))
  * Update libxxhash to 0.6.2.

### 0.3.0 (January 18, 2015)
  * make seed param optional (by [@weakish](https://github.com/weakish))
  * add 64-bit xxhash function (by [@justinwsmith](https://github.com/justinwsmith))

### 0.2.0 (September 4, 2013)
  * xxHash updated to [r32](https://code.google.com/p/xxhash/source/detail?r=32)
  * add `XXhash.xxh32_stream` method (by [@maltoe](https://github.com/maltoe))

### 0.1.1 (June 4, 2013)
  * remove .bundle from gem

### 0.1.0 (May 16, 2013)
  * xxHash updated to [r29](https://code.google.com/p/xxhash/source/detail?r=29)
