class TestShapePredictor < Test::Unit::TestCase
  include Helper::Fixture

  def test_new
    assert_nothing_raised do
      DLIB::ShapePredictor.new
    end
  end
end
