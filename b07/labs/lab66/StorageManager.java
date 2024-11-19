import java.util.HashSet;

public abstract class StorageManager<T extends PhysicalItem> {
    String deliveryServiceName;
    int small;
    int medium;
    int large;
    HashSet<T> items;

    public StorageManager(String deliveryServiceName, int small, int medium, int large) {
        this.deliveryServiceName = deliveryServiceName;
        this.small = small;
        this.medium = medium;
        this.large = large;

        items = new HashSet<T>();
    }

    public void addItem(T item) {
        items.add(item);
    }

    public void removeItem(T item) {
        items.remove(item);
    }

    public boolean itemExists(T item) {
        return items.contains(item);
    }

    String determineBoxSize(T item) {
        double length = item.getLength();
        double width = item.getWidth();
        double height = item.getHeight();
        double max = length;
        if (max < width)
            max = width;
        if (max < height)
            max = height;
        if (max < this.small)
            return "small";
        else if (max < this.medium)
            return "medium";
        else if (max < this.large)
            return "large";
        else
            return "x-large";
    }

    void deliver(T item, Customer customer) {
        if (itemExists(item)) {
            System.out.println("Delivering " + item);
            System.out.println("Delivery service: " + this.deliveryServiceName);
            System.out.println("Box size: " + determineBoxSize(item));
            System.out.println("Address: " + customer.getPostalCode());
            removeItem(item);
        }
    }
}
