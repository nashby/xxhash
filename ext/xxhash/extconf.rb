require 'mkmf'

%w{ g O3 std=c11 Weverything Wno-padded Wno-documentation-unknown-command Wno-used-but-marked-unused }.each do |flag|
  $CFLAGS += " -#{flag}"
end

create_makefile('xxhash/xxhash')
