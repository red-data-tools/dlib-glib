class TestRectangle < Test::Unit::TestCase
  def test_new
    assert_nothing_raised do
      DLIB::Rectangle.new
    end
  end
end
