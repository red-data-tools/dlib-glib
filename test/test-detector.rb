class TestDetector < Test::Unit::TestCase
  include Helper::Fixture

  def test_new
    assert_nothing_raised do
      DLIB::Detector.new
    end
  end

  def test_detect
    image = DLIB::Image.new(fixture_path("sample.jpg").to_s)
    detector = DLIB::Detector.new
    rectangles = detector.detect(image)
    assert_equal(rectangles.size, 1)
  end
end
