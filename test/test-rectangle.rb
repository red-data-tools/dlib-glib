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

  def test_intersect
    rectangle1 =
      Dlib::Rectangle.new(1, 1, 3, 3).intersect(Dlib::Rectangle.new(2, 2, 3, 3))
    assert_equal([2, 2, 3, 3],
                 [
                   rectangle1.left,
                   rectangle1.top,
                   rectangle1.right,
                   rectangle1.bottom
                 ])
    rectangle2 =
      Dlib::Rectangle.new(1, 1, 3, 3).intersect(Dlib::Rectangle.new(2, 2, 5, 5))
    assert_equal([2, 2, 3, 3],
                 [
                   rectangle2.left,
                   rectangle2.top,
                   rectangle2.right,
                   rectangle2.bottom
                 ])
    rectangle3 =
      Dlib::Rectangle.new(1, 1, 3, 3).intersect(Dlib::Rectangle.new)
    assert do
      rectangle3.empty?
    end
    rectangle4 =
      Dlib::Rectangle.new.intersect(Dlib::Rectangle.new)
    assert do
      rectangle4.empty?
    end
  end

  def test_equal
    rectangle1 = Dlib::Rectangle.new(1, 1, 3, 3)
    assert_equal(rectangle1,
                 Dlib::Rectangle.new(1, 1, 3, 3))
    rectangle2 = Dlib::Rectangle.new(2, 2, 3, 3)
    assert_not_equal(rectangle1,
                     rectangle2)
  end
end
