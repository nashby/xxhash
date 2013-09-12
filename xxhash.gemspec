# -*- encoding: utf-8 -*-
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'xxhash/version'

Gem::Specification.new do |gem|
  gem.name          = "xxhash"
  gem.version       = XXhash::VERSION
  gem.authors       = ["Vasiliy Ermolovich"]
  gem.email         = ["younash@gmail.com"]
  gem.description   = %q{Ruby wrapper for xxHash lib}
  gem.summary       = %q{Ruby wrapper for xxHash lib}
  gem.homepage      = "http://github.com/nashby/xxhash"
  gem.license       = 'MIT'
  
  gem.files         = `git ls-files`.split($/)
  gem.executables   = gem.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.require_paths = ["lib"]
  gem.extensions    = ["ext/xxhash/extconf.rb"]
end
