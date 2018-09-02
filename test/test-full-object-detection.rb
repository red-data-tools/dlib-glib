class TestShapePredictor < Test::Unit::TestCase
  def test_new
    assert_nothing_raised do
      DLIB::FullObjectDetection.new
    end
  end
end
