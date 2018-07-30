require "test-unit"

require "gi"
DLIB = GI.load("DLIB")

class TestDetector < Test::Unit::TestCase
  def test_new
    assert_nothing_raised do
      DLIB::Detector.new
    end
  end
end
