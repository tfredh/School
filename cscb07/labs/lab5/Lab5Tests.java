package lab5;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import lab4.Point;
import lab5.Hexagon;

class Lab5Tests {
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
	 * Tests for Hexagon class
	 */
	@Test
	void testHexagonPerimeter() {
		Point p1 = new Point(-1, 0);
		Point p2 = new Point(-0.5, Math.sqrt(3) / 2);
		Point p3 = new Point(0.5, Math.sqrt(3) / 2);
		Point p4 = new Point(1, 0);
		Point p5 = new Point(0.5, -Math.sqrt(3) / 2);
		Point p6 = new Point(-0.5, -Math.sqrt(3) / 2);
		Hexagon hex = new Hexagon(p1, p2, p3, p4, p5, p6);
		assertEquals(6.0, hex.perimeter(), 1e-7);
	}

	@Test
	void testHexagonIsEquilateralT() {
		Point p1 = new Point(-1, 0);
		Point p2 = new Point(-0.5, Math.sqrt(3) / 2);
		Point p3 = new Point(0.5, Math.sqrt(3) / 2);
		Point p4 = new Point(1, 0);
		Point p5 = new Point(0.5, -Math.sqrt(3) / 2);
		Point p6 = new Point(-0.5, -Math.sqrt(3) / 2);
		Hexagon hex = new Hexagon(p1, p2, p3, p4, p5, p6);
		assertTrue(hex.isEquilateral());
	}

	@Test
	void testHexagonIsEquilateralF() {
		Point p1 = new Point(0, 1);
		Point p2 = new Point(2, 3);
		Point p3 = new Point(4, 5);
		Point p4 = new Point(6, 7);
		Point p5 = new Point(8, 9);
		Point p6 = new Point(10, 11);
		Hexagon hex = new Hexagon(p1, p2, p3, p4, p5, p6);
		assertFalse(hex.isEquilateral());
	}
}
