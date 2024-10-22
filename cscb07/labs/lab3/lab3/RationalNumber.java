package lab3;

/**
 * A class representing a rational number. A rational number is a number that can be expressed as the
 * quotient or fraction p/q of two integers, a numerator p and a non-zero denominator q. The class
 * implements the SpecialNumber interface and provides methods to add and divide rational numbers.
 * 
 * @see SpecialNumber
 * @see SpecialNumber#add(SpecialNumber)
 * @see SpecialNumber#divideByInt(int)
 * @see SpecialNumber#computeAverage(java.util.List)
 * @see Lab3Exception
 */
public class RationalNumber extends SpecialNumber implements Comparable<RationalNumber> {
    public int numerator; 
    public int denominator; 

    /**
     * Constructs a RationalNumber object with the given numerator and denominator. If
     * the denominator is zero, a Lab3Exception is thrown.
     * 
     * @param numerator the numerator of the rational number
     * @param denominator the denominator of the rational number
     * @throws Lab3Exception if the denominator is zero
     */
    RationalNumber(int numerator, int denominator) throws Lab3Exception {
        if (denominator == 0) {
            throw new Lab3Exception("Denominator cannot be zero");
        }

        this.numerator = numerator;
        this.denominator = denominator;
    }

    /**
     * Adds a RationalNumber to this RationalNumber. If the other RationalNumber is null, a Lab3Exception
     * is thrown.
     * 
     * @param otherNum the RationalNumber to add
     * @return the sum of the two RationalNumbers
     * @throws Lab3Exception if the other RationalNumber is null
     * @see SpecialNumber#add(SpecialNumber)
     */
    @Override
    public SpecialNumber add(SpecialNumber otherNum) throws Lab3Exception {
        if (otherNum == null || !(otherNum instanceof RationalNumber)) {
            throw new Lab3Exception("Cannot add an incompatible type");
        }

        RationalNumber ratNum = (RationalNumber) otherNum;
        int newNum = this.numerator * ratNum.denominator + ratNum.numerator * this.denominator;
        int newDen = this.denominator * ratNum.denominator;

        return new RationalNumber(newNum, newDen);
    }

    /**
     * Divides this RationalNumber by an integer. If the integer is zero, a Lab3Exception is thrown.
     * 
     * @param divider the integer to divide by
     * @return the quotient of the division
     * @throws Lab3Exception if the integer is zero
     * @see Lab3Exception
     * @see SpecialNumber#divideByInt(int)
     */
    @Override
    public SpecialNumber divideByInt(int divider) throws Lab3Exception {
        if (divider == 0) {
            throw new Lab3Exception("Cannot divide by zero");
        }

        return new RationalNumber(this.numerator, this.denominator * divider);
    }

    /**
     * Compares this RationalNumber with another RationalNumber. The comparison is based on the
     * product of the numerator and denominator of the two RationalNumbers.
     * 
     * @param ratNum the RationalNumber to compare with
     * @return a negative integer, zero, or a positive integer as this RationalNumber is less than,
     *        equal to, or greater than the other RationalNumber
     * @see Comparable#compareTo(Object)
     * @see RationalNumber
     */
    @Override
    public int compareTo(RationalNumber ratNum) {
        return Integer.compare(this.numerator * ratNum.denominator, ratNum.numerator * this.denominator);
    }

    /**
     * Returns a string representation of this RationalNumber. The string representation is the
     * numerator followed by a forward slash and the denominator.
     * 
     * @return a string representation of this RationalNumber
     * @see Object#toString()
     */
    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof RationalNumber)) {
            return false;
        }

        RationalNumber ratNum = (RationalNumber) obj;
        return this.numerator * ratNum.denominator == ratNum.numerator * this.denominator;
    }

    /**
     * Returns a hash code value for this RationalNumber. The hash code is computed by dividing the
     * numerator and denominator by their greatest common divisor and then XORing the hash codes of
     * the two resulting integers.
     * 
     * @return a hash code value for this RationalNumber
     * @see Object#hashCode()
     * @see #gcd(int, int)
     * @see Integer#hashCode(int)
     */
    @Override
    public int hashCode() {
        // return Integer.hashCode(this.numerator) ^ Integer.hashCode(this.denominator);

        int gcd = gcd(this.numerator, this.denominator);

        int minNum = this.numerator / gcd;
        int minDen = this.denominator / gcd;

        return Integer.hashCode(minNum) ^ Integer.hashCode(minDen);
    }

    /**
     * Returns the greatest common divisor of two integers. The greatest common divisor is the
     * largest positive integer that divides both integers without a remainder.
     * 
     * @param a the first integer
     * @param b the second integer
     * @return the greatest common divisor of the two integers
     * @see #hashCode()
     */
    public int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
}
