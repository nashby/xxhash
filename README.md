## xxHash [![Build Status](https://travis-ci.org/nashby/xxhash.png?branch=master)](https://travis-ci.org/nashby/xxhash)

Ruby wrapper for [xxHash](https://github.com/Cyan4973/xxHash)

### Install

    gem install xxhash

### Usage

```ruby
require 'xxhash'

text = "test"
seed = 12345

XXhash.xxh32(text, seed) # => 3834992036
```

If you do not provide a seed, it will use the default value `0`.

You can use it with `IO` objects too:

```ruby
XXhash.xxh32_stream(StringIO.new('test'), 123) # => 2758658570
```

You can use it with file path directly, avoiding costly ruby-related operations.

```ruby
XXhash.xxh32_file(__FILE__)
```

Note that you can also pass a chunk size as third param (it's 32 bytes by default)

XXH64 is also supported: you can use `xxh64`, `xxh64_stream`, `.xxh64_file`.

### Supported Ruby versions

- MRI 2.3+
- rbx-19mode

Note: It doesn't work on JRuby as it uses C extension.

### Versioning

Version 0.5.0 is equal to [0.6.2](https://github.com/Cyan4973/xxHash/tree/v0.6.2)

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

### Copyright

Copyright (c) 2022 Vasiliy Ermolovich. See LICENSE.txt for
further details.
