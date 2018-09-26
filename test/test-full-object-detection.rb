class TestFullObjectDetection < Test::Unit::TestCase
  include Helper::Fixture

  def test_new
    assert_nothing_raised do
      rectangle = Dlib::Rectangle.new(1, 2, 3, 4)
      Dlib::FullObjectDetection.new(rectangle)
    end
  end

  def test_rectangle
    rectangle = Dlib::Rectangle.new(1, 2, 3, 4)
    full_object_detection = Dlib::FullObjectDetection.new(rectangle)
    assert_equal(full_object_detection.rectangle.left, 1)
  end

  def test_n_parts
    rectangle = Dlib::Rectangle.new(1, 2, 3, 4)
    full_object_detection = Dlib::FullObjectDetection.new(rectangle)
    assert_equal(full_object_detection.n_parts, 0)
  end
end
