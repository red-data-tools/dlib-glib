class TestRectangle < Test::Unit::TestCase
  def test_empty
    rectangle = Dlib::Rectangle.new
    assert_equal([0, 0, -1, -1],
                 [
                   rectangle.left,
                   rectangle.top,
                   rectangle.right,
                   rectangle.bottom
                 ])
  end

  def test_coordinate
    rectangle = Dlib::Rectangle.new(1, 2, 3, 4)
    assert_equal([1, 2, 3, 4],
                 [
                   rectangle.left,
                   rectangle.top,
                   rectangle.right,
                   rectangle.bottom
                 ])
  end

  def test_set_coordinate
    rectangle = Dlib::Rectangle.new
    rectangle.left = 1
    rectangle.top = 2
    rectangle.right = 3
    rectangle.bottom = 4
    assert_equal([1, 2, 3, 4],
                 [
                   rectangle.left,
                   rectangle.top,
                   rectangle.right,
                   rectangle.bottom
                 ])
  end
end
