#!/usr/bin/env ruby

require "test-unit"

test_dir = __dir__

require "gi"
DLIB = GI.load("DLIB")

exit(Test::Unit::AutoRunner.run(true, test_dir.to_s))
