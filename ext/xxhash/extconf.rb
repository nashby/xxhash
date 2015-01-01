require 'mkmf'

%w{ g O3  Wno-padded }.each do |flag|
  $CFLAGS += " -#{flag}"
end

create_makefile('xxhash/xxhash')
