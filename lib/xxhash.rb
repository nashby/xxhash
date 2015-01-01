require 'xxhash/version'
require 'xxhash/xxhash'

module XXhash
  def self.xxh32(input, seed = 0)
    XXhashInternal.xxh32(input, seed)
  end

  def self.xxh64(input, seed = 0)
    XXhashInternal.xxh64(input, seed)
  end

  def self.xxh32_stream(io, seed = 0, chunk_size = 32)
    raise ArgumentError, 'first argument should be IO' if !io.is_a?(IO) && !io.is_a?(StringIO)

    hash = XXhashInternal::StreamingHash32.new(seed)

    while chunk = io.read(chunk_size)
      hash.update(chunk)
    end

    hash.digest
  end

  def self.xxh64_stream(io, seed = 0, chunk_size = 32)
    raise ArgumentError, 'first argument should be IO' if !io.is_a?(IO) && !io.is_a?(StringIO)

    hash = XXhashInternal::StreamingHash64.new(seed)

    while chunk = io.read(chunk_size)
      hash.update(chunk)
    end

    hash.digest
  end
end
