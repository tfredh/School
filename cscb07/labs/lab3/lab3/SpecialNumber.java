package lab3;
import java.util.List;

/**
 * An abstract class representing a special number. A special number is a number that has special properties
 * and can be added to other special numbers of the same type. The class provides methods to add a special
 * number to another special number, divide a special number by an integer, and compute the average of a list
 * of special numbers.
 * 
 * @see RationalNumber
 * @see ComplexNumber
 * @see Lab3Exception
 * @see SpecialNumber#add(SpecialNumber)
 * @see SpecialNumber#divideByInt(int)
 * @see SpecialNumber#computeAverage(java.util.List)
 */
public abstract class SpecialNumber {
    /**
     * Adds a SpecialNumber to this SpecialNumber. The two SpecialNumbers must be of the same type.
     * If the other SpecialNumber is null or not of the same type, a Lab3Exception is thrown.
     * 
     * @param specNum the SpecialNumber to add
     * @return the sum of the two SpecialNumbers
     * @throws Lab3Exception if the other SpecialNumber is null or not of the same type
     * @see RationalNumber
     * @see ComplexNumber
     * @see Lab3Exception
     */
    public abstract SpecialNumber add(SpecialNumber specNum) throws Lab3Exception;

    /**
     * Divides this SpecialNumber by an integer. If the integer is zero, a Lab3Exception is thrown.
     * 
     * @param n the integer to divide by
     * @return the quotient of the division
     * @throws Lab3Exception if the integer is zero
     */
    public abstract SpecialNumber divideByInt(int n) throws Lab3Exception;

    /**
     * Computes the average of a list of SpecialNumbers. The list cannot be null or empty.
     * 
     * @param specs the list of SpecialNumbers
     * @return the average of the list
     * @throws Lab3Exception if the list is null or empty
     */
    public static SpecialNumber computeAverage(List<SpecialNumber> specs) throws Lab3Exception {
        if (specs == null || specs.size() == 0) {
            throw new Lab3Exception("List cannot be empty");
        }

        SpecialNumber sum = specs.get(0);
        for (int i = 1; i < specs.size(); i++) {
            sum = sum.add(specs.get(i));
        }
        
        return sum.divideByInt(specs.size());
    }
}