class TestDetector < Test::Unit::TestCase
  include Helper::Fixture

  def test_new
    assert_nothing_raised do
      Dlib::Detector.new
    end
  end

  def test_detect
    image = Dlib::Image.new(fixture_path("sample.jpg").to_s)
    detector = Dlib::Detector.new
    rectangles = detector.detect(image)
    assert_equal(rectangles.size, 1)
  end
end
