class TestImage < Test::Unit::TestCase
  include Helper::Fixture

  def setup
    @image = Dlib::Image.new(fixture_path("sample.jpg").to_s)
  end

  def test_save_jpeg
    jpeg = Tempfile.new(["dlib-glib-save-jpeg", ".jpeg"])
    assert_nothing_raised do
      @image.save_jpeg(jpeg.path)
    end
  end

  def test_draw_rectangle
    assert_nothing_raised do
      @image.draw_rectangle(Dlib::Rectangle.new(187, 138, 633, 584),
                                                0, 0, 255)
    end
  end

  def test_find_candidate_object_locations
    rectangles1 = @image.find_candidate_object_locations(0, 0)
    rectangles2 = @image.find_candidate_object_locations(20, 50)
    assert_not_equal(rectangles1.size, rectangles2.size)
  end

  def test_n_columns
    assert_equal(820, @image.n_columns)
  end

  def test_n_rows
    assert_equal(700, @image.n_rows)
  end
end
