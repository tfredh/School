package lab4;

public class Main {
    public static void main(String[] args) {
        Point p1 = new Point(0, 0);
        Point p2 = new Point(2, 0);
        Point p3 = new Point(1, Math.sqrt(3));
        Triangle t = new Triangle(p1, p2, p3);

        System.out.println(t.isEquilateral());
    }
}
