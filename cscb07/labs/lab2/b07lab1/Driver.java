public class Driver {
    public static void main(String[] args) {
        // OLD
        // Polynomial p = new Polynomial();
        // System.out.println(p.evaluate(3));
        // double[] c1 = { 6, 0, 0, 5 };
        // Polynomial p1 = new Polynomial(c1);
        // double[] c2 = { 0, -2, 0, 0, -9 };
        // Polynomial p2 = new Polynomial(c2);
        // Polynomial s = p1.add(p2);
        // System.out.println("s(0.1) = " + s.evaluate(0.1));
        // if (s.hasRoot(1))
        // System.out.println("1 is a root of s");
        // else
        // System.out.println("1 is not a root of s");

        // NEW
        Polynomial p = new Polynomial();
        System.out.println(p.evaluate(3));

        double[] c1 = { 6, 0, 0, 5 };
        int[] e1 = { 0, 1, 2, 3 };
        Polynomial p1 = new Polynomial(c1, e1);

        double[] c2 = { 0, -2, 0, 0, -9 };
        int[] e2 = { 0, 1, 2, 3, 4 };
        Polynomial p2 = new Polynomial(c2, e2);
        Polynomial s = p1.add(p2);
        System.out.println("s(0.1) = " + s.evaluate(0.1));
        if (s.hasRoot(1))
            System.out.println("1 is a root of s");
        else
            System.out.println("1 is not a root of s");

        Polynomial pf1 = new Polynomial(new double[] { 6, -2, 5 }, new int[] { 0, 1, 3 });
        pf1.saveToFile("custom_poly.txt");
        // Polynomial pf2 = new Polynomial(new double[] { 5, -3, 7 }, new int[] { 0, 2,
        // 8 });
        // pf2.saveToFile("custom_poly.txt");
        // Polynomial pf3 = new Polynomial(new File("custom_poly.txt"));
        // for (double dou : pf3.getCoefficients()) {
        // System.out.println(dou);
        // }
        // for (int dou : pf3.getExponents()) {
        // System.out.println(dou);
        // }

        // Polynomial mp1 = new Polynomial(new double[] { 0, 4, 2, 3 }, new int[] { 0, 1, 2, 3 });
        // Polynomial mp2 = new Polynomial(new double[] { 7, 1, 2, 5 }, new int[] { 0, 1, 2, 3 });
        // Polynomial mResult1 = mp1.multiply(mp2);
        // mResult1.saveToFile("custom_poly.txt");
        // for (int i = 0; i < mResult1.getCoefficients().length; i++) {
        // System.out.println(mResult1.getCoefficients()[i]);
        // }

        Polynomial mp3 = new Polynomial(new double[] { 0, 4, 2, 3 }, new int[] { 0, 0, 0, 0 });
        Polynomial mp4 = new Polynomial(new double[] { 7, 1, 2, 5 }, new int[] { 0, 0, 0, 0 });
        Polynomial mResult2 = mp3.multiply(mp4);
        mResult2.saveToFile("custom_poly.txt");

        // Polynomial mpZero = new Polynomial(new double[] { 0 }, new int[] { 0 });
        // mp3.multiply(mpZero).saveToFile("custom_poly.txt");
    }
}