require 'xxhash/version'
require 'xxhash/xxhash'

module XXhash
  def self.xxh32(input, seed)
    Internal.xxh32(input, seed)
  end

  def self.xxh32_stream(io, seed, chunk_size = 32)
    raise 'wrong parameter type: should be Core::IO' unless io.kind_of?(IO) || io.kind_of?(StringIO)

    sh = Internal::StreamingHash.new(seed)
    until (chunk = io.read(chunk_size)).nil?
      sh.update(chunk)
    end
    sh.digest
  end
end
