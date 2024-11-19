public class GroceryStore extends StorageManager<GroceryItem> {
	public GroceryStore() {
		super("Groceries Express", 10, 20, 30);
	}

	public GroceryStore(int small, int medium, int large) {
		super("Groceries Express", small, medium, large);
	}

	public GroceryStore(String deliveryServiceName, int small, int medium, int large) {
		super(deliveryServiceName, small, medium, large);
	}
}