require_relative 'test_helper'
require 'stringio'

describe XXhash do
  it 'returns 32-bit hash' do
    assert_equal 2758658570, XXhash.xxh32('test', 123)
  end

  it 'returns 64-bit hash' do
    assert_equal 3134990500624303823, XXhash.xxh64('test', 123)
  end

  it 'uses 0 (default value) if seed is not specified' do
    assert_equal 1042293711, XXhash.xxh32('test')
    assert_equal 5754696928334414137, XXhash.xxh64('test')
  end

  describe 'StreamingHash32' do

    it 'rises ArgumentError if first argument is not IO object' do
      assert_raises(ArgumentError) do
        XXhash.xxh32_stream('test', 123)
      end
    end

    it 'returns the hash for streamed strings' do
      assert_equal 2758658570, XXhash.xxh32_stream(StringIO.new('test'), 123)
    end

    it 'returns the hash for streamed files' do
      h1 = XXhash.xxh32(File.read(__FILE__), 123)
      h2 = XXhash.xxh32_stream(File.open(__FILE__), 123)
      assert_equal h1, h2
    end
  end

  describe 'StreamingHash64' do
    it 'rises ArgumentError if first argument is not IO object' do
      assert_raises(ArgumentError) do
        XXhash.xxh64_stream('test', 123)
      end
    end

    it 'returns the hash for streamed strings' do
      assert_equal 3134990500624303823, XXhash.xxh64_stream(StringIO.new('test'), 123)
    end

    it 'returns the hash for streamed files' do
      h1 = XXhash.xxh64(File.read(__FILE__), 123)
      h2 = XXhash.xxh64_stream(File.open(__FILE__), 123)
      assert_equal h1, h2
    end
  end
end
