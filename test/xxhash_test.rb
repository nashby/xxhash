require 'test_helper'

describe XXhash do
  it 'returns hash' do
    assert_equal 2758658570, XXhash.xxh32('test', 123)
  end
end
