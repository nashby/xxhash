require_relative 'test_helper'
require 'stringio'

describe XXhash do
  it 'is marked as ractor-safe' do
    skip("Ractorrs are not supported in this version of ruby(#{RUBY_VERSION})") unless defined?(Ractor)

    ractor = Ractor.new do
      Ractor.yield XXhash.xxh32(Ractor.receive)
    end

    ractor.send('test')
    assert_equal ractor.take, XXhash.xxh32('test')
  end

  it 'returns 32-bit hash' do
    assert_equal 2758658570, XXhash.xxh32('test', 123)
  end

  it 'returns 32-bit hash from a file' do
    assert_equal XXhash.xxh32(File.read(__FILE__)), XXhash.xxh32_file(__FILE__)
    assert_equal XXhash.xxh32(File.read(__FILE__), 123), XXhash.xxh32_file(__FILE__, 123)
  end

  it 'returns 64-bit hash' do
    assert_equal 3134990500624303823, XXhash.xxh64('test', 123)
  end

  it 'returns 64-bit hash from a file' do
    assert_equal XXhash.xxh64(File.read(__FILE__)), XXhash.xxh64_file(__FILE__)
    assert_equal XXhash.xxh64(File.read(__FILE__), 123), XXhash.xxh64_file(__FILE__, 123)
  end

  it 'uses 0 (default value) if seed is not specified' do
    assert_equal 1042293711, XXhash.xxh32('test')
    assert_equal 5754696928334414137, XXhash.xxh64('test')
  end

  it 'raises an Errno exception for invalid file' do
    assert_raises Errno::ENOENT do
      XXhash.xxh32_file('nonexistent-file')
    end

    assert_raises Errno::ENOENT do
      XXhash.xxh64_file('nonexistent-file')
    end
  end

  describe 'XXhashInternal::StreamingHash32' do

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

  describe 'XXhashInternal::StreamingHash64' do
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

    it 'exception (not segfault) on nil' do
      begin
        XXhash.xxh64(nil)
        fail
      rescue
      end
    end
  end

  def use_external_hash hash, io, chunk_size=1024
    while chunk=io.read(chunk_size)
      hash.update(chunk)
    end
    hash.digest
  end

  describe 'Digest::XXhash32' do

    it 'returns the hash for streamed strings' do
      StringIO.open('test') do |io|
        xxhash = Digest::XXHash32.new(123)
        result = use_external_hash xxhash, io
        assert_equal 2758658570, result
      end
    end

    it 'returns the hash for streamed files' do
      h1 = XXhash.xxh32(File.read(__FILE__), 123)
      xxhash = Digest::XXHash32.new(123)
      result = use_external_hash xxhash, File.open(__FILE__)
      assert_equal h1, result
    end

    it 'returns correct hash after a reset' do
      h1 = XXhash.xxh32(File.read(__FILE__), 123)
      xxhash = Digest::XXHash32.new(123)
      assert_equal 2758658570, xxhash.digest('test')
      xxhash.reset
      result = use_external_hash xxhash, File.open(__FILE__)
      assert_equal h1, result
    end

    it 'exception (not segfault) on nil' do
      begin
        XXhash.xxh32(nil)
      rescue
      end
    end
  end

  describe 'Digest::XXhash64' do
    it 'returns the hash for streamed strings' do
      StringIO.open('test') do |io|
        xxhash = Digest::XXHash64.new(123)
        result = use_external_hash xxhash, io
        assert_equal 3134990500624303823, result
      end
    end

    it 'returns the hash for streamed files' do
      h1 = XXhash.xxh64(File.read(__FILE__), 123)
      xxhash = Digest::XXHash64.new(123)
      result = use_external_hash xxhash, File.open(__FILE__)
      assert_equal h1, result
    end

    it 'returns correct hash after reset' do
      h1 = XXhash.xxh64(File.read(__FILE__), 123)
      xxhash = Digest::XXHash64.new(123)
      assert_equal 3134990500624303823, xxhash.digest('test')
      xxhash.reset
      result = use_external_hash xxhash, File.open(__FILE__)
      assert_equal h1, result
    end
  end

end
