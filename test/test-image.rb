class TestImage < Test::Unit::TestCase
  def test_new
    assert_nothing_raised do
      DLIB::Image.new(File.join(__dir__, "fixture/sample.jpg"))
    end
  end
end
