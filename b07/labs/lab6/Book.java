public class Book extends BaseBook implements PhysicalItem {
	double length;
	double width;
	double height;

	public Book(String isbn, String title, double length, double width, double height) {
		super(isbn, title);
		this.length = length;
		this.width = width;
		this.height = height;
	}

	public double getLength() {
		return length;
	}

	public double getHeight() {
		return height;
	}

	public double getWidth() {
		return width;
	}
}
