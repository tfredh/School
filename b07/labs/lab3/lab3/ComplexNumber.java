package lab3;

/**
 * A class representing a complex number. A complex number is a number that can
 * be expressed as a + bi,
 * where a is the real part and bi is the imaginary part. The class implements
 * the SpecialNumber interface
 * and provides methods to add and divide complex numbers.
 * 
 * @see SpecialNumber
 * @see SpecialNumber#add(SpecialNumber)
 * @see SpecialNumber#divideByInt(int)
 * @see SpecialNumber#computeAverage(java.util.List)
 * @see Lab3Exception
 */
public class ComplexNumber extends SpecialNumber implements Comparable<ComplexNumber> {
    public double real;
    public double imaginary;

    /**
     * Constructs a ComplexNumber object with the given real and imaginary parts.
     * 
     * @param real      the real part of the complex number
     * @param imaginary the imaginary part of the complex number
     * @see SpecialNumber
     */
    ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    /**
     * Adds a ComplexNumber to this ComplexNumber. If the other ComplexNumber is
     * null, a Lab3Exception
     * is thrown. The sum of two complex numbers is the sum of their real parts and
     * the sum of their
     * imaginary parts. The sum is returned as a new ComplexNumber object.
     * 
     * @param otherNum the ComplexNumber to add
     * @return the sum of the two ComplexNumbers
     * @throws Lab3Exception if the other ComplexNumber is null
     * @see SpecialNumber#add(SpecialNumber)
     */
    @Override
    public SpecialNumber add(SpecialNumber otherNum) throws Lab3Exception {
        if (otherNum == null || !(otherNum instanceof ComplexNumber)) {
            throw new Lab3Exception("Cannot add an incompatible type");
        }

        ComplexNumber compNum = (ComplexNumber) otherNum;
        double newReal = this.real + compNum.real;
        double newImaginary = this.imaginary + compNum.imaginary;

        return new ComplexNumber(newReal, newImaginary);
    }

    /**
     * Divides this ComplexNumber by an integer. If the integer is zero, a
     * Lab3Exception is thrown.
     * The division of a complex number by an integer is the division of the real
     * and imaginary parts
     * by the integer. The quotient is returned as a new ComplexNumber object. If
     * the integer is zero,
     * a Lab3Exception is thrown.
     * 
     * @param divider the integer to divide by
     * @return the quotient of the division
     * @throws Lab3Exception if the integer is zero
     * @see SpecialNumber#divideByInt(int)
     */
    @Override
    public SpecialNumber divideByInt(int divider) throws Lab3Exception {
        if (divider == 0) {
            throw new Lab3Exception("Cannot divide by zero");
        }

        return new ComplexNumber(this.real / divider, this.imaginary / divider);
    }

    /**
     * Compares this ComplexNumber with another ComplexNumber based on their sizes.
     * The size of a complex
     * number is the square root of the sum of the squares of the real and imaginary
     * parts. The comparison
     * is based on the sizes of the two complex numbers.
     * 
     * @param compNum the ComplexNumber to compare with
     * @return a negative integer, zero, or a positive integer if this ComplexNumber
     *         is less than, equal to,
     *         or greater than the other ComplexNumber
     * @see Comparable#compareTo(Object)
     */
    @Override
    public int compareTo(ComplexNumber compNum) {
        double thisSize = Math.sqrt(Math.pow(this.real, 2) + Math.pow(this.imaginary, 2));
        double compNumSize = Math.sqrt(Math.pow(compNum.real, 2) + Math.pow(compNum.imaginary, 2));

        return Double.compare(thisSize, compNumSize);
    }

    /**
     * Checks if this ComplexNumber is equal to another object. Two ComplexNumbers
     * are equal if their real
     * and imaginary parts are equal. To avoid floating point precision errors, the
     * real and imaginary parts
     * are compared using Double.compare.
     * 
     * @param obj the object to compare with
     * @return true if the ComplexNumbers are equal, false otherwise
     * @see Object#equals(Object)
     * @see Double#compare(double, double)
     */
    @Override
    public boolean equals(Object obj) {
        if (obj == null || !(obj instanceof ComplexNumber)) {
            return false;
        }

        ComplexNumber compNum = (ComplexNumber) obj;
        // return this.real == compNum.real && this.imaginary == compNum.imaginary;
        // To avoid floating point precision errors
        return Double.compare(this.real, compNum.real) == 0 && Double.compare(this.imaginary, compNum.imaginary) == 0;
    }

    /**
     * Returns a hash code value for this ComplexNumber. The hash code is computed
     * by XORing the hash codes
     * of the real and imaginary parts.
     * 
     * @return a hash code value for this ComplexNumber
     * @see Object#hashCode()
     * @see Double#hashCode(double)
     */
    @Override
    public int hashCode() {
        return Double.hashCode(this.real) ^ Double.hashCode(this.imaginary);
    }
}
