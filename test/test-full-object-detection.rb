class TestFullObjectDetection < Test::Unit::TestCase
  include Helper::Fixture

  def test_rectangle
    rectangle = Dlib::Rectangle.new(1, 2, 3, 4)
    full_object_detection = Dlib::FullObjectDetection.new(rectangle)
    assert_equal([1, 2, 3, 4],
                 [
                   full_object_detection.rectangle.left,
                   full_object_detection.rectangle.top,
                   full_object_detection.rectangle.right,
                   full_object_detection.rectangle.bottom
                 ])
  end

  def test_n_parts
    rectangle = Dlib::Rectangle.new(1, 2, 3, 4)
    full_object_detection = Dlib::FullObjectDetection.new(rectangle)
    assert_equal(full_object_detection.n_parts, 0)
  end
end
