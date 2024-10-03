package lab3;

/**
 * A custom exception class for Lab3. This exception is thrown when an error occurs in the lab3 package.
 * 
 * @see SpecialNumber
 * @see SpecialNumber#add(SpecialNumber)
 * @see SpecialNumber#divideByInt(int)
 * @see SpecialNumber#computeAverage(java.util.List)
 */
class Lab3Exception extends Exception {
    public String message;

    Lab3Exception(String message) {
        super(message);
        this.message = message;
    }
}