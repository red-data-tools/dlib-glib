class TestFrontalFaceDetector < Test::Unit::TestCase
  include Helper::Fixture

  def test_new
    assert_nothing_raised do
      Dlib::FrontalFaceDetector.new
    end
  end

  def test_detect
    image = Dlib::Image.new(fixture_path("sample.jpg").to_s)
    detector = Dlib::FrontalFaceDetector.new
    rectangles = detector.detect(image)
    assert_equal(rectangles.size, 1)
  end
end
