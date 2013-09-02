require 'test_helper'

describe XXhash do
  it 'returns hash' do
    assert_equal 2758658570, XXhash.xxh32('test', 123)
  end

  describe 'StreamingHash' do
    it 'returns the hash for streamed strings' do
      assert_equal 2758658570, XXhash.xxh32_stream(StringIO.new('test'), 123)
    end

    it 'returns the hash for streamed files' do
      h1 = XXhash.xxh32(File.read(__FILE__), 123)
      h2 = XXhash.xxh32_stream(File.open(__FILE__), 123)
      assert_equal h1, h2
    end
  end
end
