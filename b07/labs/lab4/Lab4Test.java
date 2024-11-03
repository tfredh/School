package lab4;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class Lab4Test {
	/**
	 * Tests for Point class
	 */
	@Test
	void testPoint() {
		Point p1 = new Point(0, 0);
		Point p2 = new Point(1, 0);
		assertEquals(1.0, p1.distance(p2), 1e-7);
	}

	@Test
	void testPointSameInstance() {
		Point p = new Point(1, 1);
		assertTrue(p.equals(p));
	}

	@Test
	void testPointNullCheck() {
		Point p = new Point(1, 1);
		assertFalse(p.equals(null));
	}

	@Test
	void testPointDifferentClass() {
		Point p = new Point(1, 1);
		String s = "different object (string class)";
		assertFalse(p.equals(s));
	}

	@Test
	void testPointEqualsT() {
		Point p1 = new Point(1, 1);
		Point p2 = new Point(1, 1);
		assertTrue(p1.equals(p2));
	}

	@Test
	void testPointXEqualsF() {
		Point p1 = new Point(1, 1);
		Point p2 = new Point(2, 2);
		assertFalse(p1.equals(p2));
	}

	@Test
	void testPointYEqualsF() {
		Point p1 = new Point(1, 1);
		Point p2 = new Point(1, 2);
		assertFalse(p1.equals(p2));
	}

	@Test
	void testPointHashCode() {
		Point p = new Point(1, 1);
		assertEquals(p.hashCode(), p.hashCode());
	}

	/**
	 * Tests for Triangle class
	 */
	@Test
	void testTrianglePerimeter() {
		Point p1 = new Point(0, 0);
		Point p2 = new Point(0, 3);
		Point p3 = new Point(4, 0);
		Triangle t = new Triangle(p1, p2, p3);
		assertEquals(12.0, t.perimeter(), 1e-7);
	}

	@Test
	void testTriangleEquilateralT() {
		Point p1 = new Point(0, 0);
		Point p2 = new Point(0, 3);
		Point p3 = new Point(Math.sqrt(Math.pow(3, 2) - Math.pow(1.5, 2)), 1.5);
		Triangle t = new Triangle(p1, p2, p3);
		assertTrue(t.isEquilateral());
	}

	@Test
	void testTriangleEquilateralF() {
		Point p1 = new Point(0, 0);
		Point p2 = new Point(0, 3);
		Point p3 = new Point(4, 0);
		Triangle t = new Triangle(p1, p2, p3);
		assertFalse(t.isEquilateral());
	}
}
