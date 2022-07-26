require 'xxhash/version'
require 'xxhash/xxhash'
require 'digest'

module XXhash
  def self.xxh32(input, seed = 0)
    XXhashInternal.xxh32(input.to_s, seed.to_i)
  end

  def self.xxh64(input, seed = 0)
    XXhashInternal.xxh64(input.to_s, seed.to_i)
  end

  def self.xxh32_file(filename, seed = 0)
    XXhashInternal.xxh32_file(filename.to_s, seed.to_i)
  end

  def self.xxh64_file(filename, seed = 0)
    XXhashInternal.xxh64_file(filename.to_s, seed.to_i)
  end

  def self.xxh32_stream(io, seed = 0, chunk_size = 32)
    seed = seed.to_i
    chunk_size = chunk_size.to_i
    raise ArgumentError, 'first argument should be IO' if !io.respond_to?(:read)

    hash = XXhashInternal::StreamingHash32.new(seed)

    while chunk = io.read(chunk_size)
      hash.update(chunk.to_s)
    end

    hash.digest
  end

  def self.xxh64_stream(io, seed = 0, chunk_size = 32)
    seed = seed.to_i
    chunk_size = chunk_size.to_i
    raise ArgumentError, 'first argument should be IO' if !io.respond_to?(:read)

    hash = XXhashInternal::StreamingHash64.new(seed)

    while chunk = io.read(chunk_size)
      hash.update(chunk.to_s)
    end

    hash.digest
  end

end

module Digest
  class XXHash < Digest::Class
    attr_reader :digest_length

    def initialize(bitlen, seed = 0)
      bitlen = bitlen.to_i
      seed = seed.to_i
      @hash = case bitlen
      when 32
        XXhash::XXhashInternal::StreamingHash32.new(seed)
      when 64
        XXhash::XXhashInternal::StreamingHash64.new(seed)
      else
        raise ArgumentError, "Unsupported bit length: %s" % bitlen.inspect
      end

      @digest_length = bitlen
    end

    def update(chunk)
      @hash.update(chunk.to_s)
    end

    def digest(val = nil)
      @hash.update(val) if val

      @hash.digest
    end

    def digest!(val = nil)
      result = digest(val)
      @hash.reset

      result
    end

    def reset
      @hash.reset
    end
  end

  class XXHash32 < Digest::XXHash
    def initialize(seed = 0)
      super(32, seed.to_i)
    end
  end

  class XXHash64 < Digest::XXHash
    def initialize(seed = 0)
      super(64, seed.to_i)
    end
  end
end
