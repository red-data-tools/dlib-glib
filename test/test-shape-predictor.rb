class TestShapePredictor < Test::Unit::TestCase
  include Helper::Fixture

  def test_new
    assert_nothing_raised do
      predictor_path = 'shape_predictor_68_face_landmarks.dat'
      DLIB::ShapePredictor.new(fixture_path(predictor_path).to_s)
    end
  end
end
