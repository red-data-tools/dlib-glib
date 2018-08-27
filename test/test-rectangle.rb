class TestRectangle < Test::Unit::TestCase
  def test_new
    assert_nothing_raised do
      DLIB::Rectangle.new
    end
  end

  def test_coordinate
    rectangle = DLIB::Rectangle.new(1, 2, 3, 4)
    assert_equal([1, 2, 3, 4],
                 [
                   rectangle.left,
                   rectangle.top,
                   rectangle.right,
                   rectangle.bottom
                 ])
  end
end
