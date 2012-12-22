## xxHash

Ruby wrapper for [xxHash](http://code.google.com/p/xxhash/)

### Install

    gem install xxhash

### Usage

```ruby
require 'xxhash'

text = "test"
seed = 12345

XXhash.xxh32(text, seed) # => 3834992036
```

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

### Copyright

Copyright (c) 2012 Vasiliy Ermolovich. See LICENSE.txt for
further details.
