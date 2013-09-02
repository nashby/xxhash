require 'xxhash/version'
require 'xxhash/xxhash'

module XXhash
  def self.xxh32(input, seed)
    Internal.xxh32(input, seed)
  end

  def self.xxh32_stream(io, seed, chunk_size = 32)
    raise ArgumentError, 'first argument should be IO' if !io.is_a?(IO) && !io.is_a?(StringIO)

    hash = Internal::StreamingHash.new(seed)

    while chunk = io.read(chunk_size)
      hash.update(chunk)
    end

    hash.digest
  end
end
