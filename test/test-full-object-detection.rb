class TestFullObjectDetection < Test::Unit::TestCase
  include Helper::Fixture

  def test_new
    assert_nothing_raised do
      rectangle = DLIB::Rectangle.new(1, 2, 3, 4)
      DLIB::FullObjectDetection.new(rectangle)
    end
  end

  def test_rectangle
    rectangle = DLIB::Rectangle.new(1, 2, 3, 4)
    full_object_detection = DLIB::FullObjectDetection.new(rectangle)
    assert_equal(full_object_detection.rectangle.left, 1)
  end

  def test_n_parts
    rectangle = DLIB::Rectangle.new(1, 2, 3, 4)
    full_object_detection = DLIB::FullObjectDetection.new(rectangle)
    assert_equal(full_object_detection.n_parts, 0)
  end
end
