require 'xxhash/version'
require 'xxhash/xxhash'

module XXhash
  def self.xxh32(input, seed)
    Internal.xxh32(input, seed)
  end

  def self.xxh32_stream(io, seed, chunk_size = 32)
    raise ArgumentError, 'first argument should be IO' if [IO, StringIO].none? { |t| io.kind_of?(t) }

    sh = Internal::StreamingHash.new(seed)
    while (chunk = io.read(chunk_size))
      sh.update(chunk)
    end
    sh.digest
  end
end
