class TestImage < Test::Unit::TestCase
  include Helper::Fixture

  def test_new
    assert_nothing_raised do
      DLIB::Image.new(fixture_path("sample.jpg").to_s)
    end
  end

  def test_save_jpeg
    image = DLIB::Image.new(fixture_path("sample.jpg").to_s)
    jpeg = Tempfile.new(["dlib-glib-save-jpeg", ".jpeg"])
    image.save_jpeg(jpeg.path)
  end
end
