import java.util.HashSet;

public class Library extends StorageManager<Book> {
	HashSet<Book> books;

	public Library() {
		super("Books Express", 5, 15, 15);
		books = new HashSet<Book>();
	}

	public Library(int small, int medium, int large) {
		super("Books Express", small, medium, large);
		books = new HashSet<Book>();
	}

	public Library(String deliveryServiceName, int small, int medium, int large) {
		super(deliveryServiceName, small, medium, large);
		books = new HashSet<Book>();
	}

	/**
	 * Alternative method names to follow exactly as the provided code.
	 * The addItem(), removeItem(), itemExists() methods are still inherited from
	 * the StorageManager class.
	 */
	public void addBook(Book book) {
		items.add(book);
		books.add(book);
	}

	public void removeBook(Book book) {
		items.remove(book);
		books.remove(book);
	}

	public boolean bookExists(Book book) {
		return items.contains(book) || books.contains(book);
	}

	@Override
	void deliver(Book book, Customer customer) {
		if (bookExists(book)) {
			books.remove(book);
			super.deliver(book, customer);
		}
	}
}