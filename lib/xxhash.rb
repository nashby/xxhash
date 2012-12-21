require 'xxhash/version'
require 'xxhash/xxhash'

module XXhash
  def self.xxh32(input, seed)
    Internal.xxh32(input, seed)
  end
end
