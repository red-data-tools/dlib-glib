#!/usr/bin/env ruby

require "test-unit"
require "pathname"

base_dir = Pathname(__dir__).parent
test_dir = base_dir + "test"

require "gi"

Dlib = GI.load("Dlib")

require "tempfile"
require_relative "helper/fixture"

exit(Test::Unit::AutoRunner.run(true, test_dir.to_s))
