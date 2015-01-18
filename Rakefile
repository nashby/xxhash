require "bundler/gem_tasks"

require 'rake/testtask'
require 'rake/clean'

Rake::TestTask.new do |t|
  t.libs << 'test'
  t.pattern = 'test/*_test.rb'
  t.verbose = true
end

desc "Run tests"
task :default => :test

require 'rake/extensiontask'
Rake::ExtensionTask.new('xxhash') do |ext|
  # Customizations can be set here
  ext.lib_dir = 'lib/xxhash'
end

Rake::Task[:test].prerequisites << :compile
