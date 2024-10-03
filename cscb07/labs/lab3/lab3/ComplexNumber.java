package lab3;

public class ComplexNumber extends SpecialNumber implements Comparable<ComplexNumber> {
    double real;
    double imaginary;

    ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

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

    @Override
    public SpecialNumber divideByInt(int divider) throws Lab3Exception {
        if (divider == 0) {
            throw new Lab3Exception("Cannot divide by zero");
        }

        return new ComplexNumber(this.real / divider, this.imaginary / divider);
    }

    @Override
    public int compareTo(ComplexNumber compNum) {
        double thisSize = Math.sqrt(Math.pow(this.real, 2) + Math.pow(this.imaginary, 2));
        double compNumSize = Math.sqrt(Math.pow(compNum.real, 2) + Math.pow(compNum.imaginary, 2));

        return Double.compare(thisSize, compNumSize);
    }

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

    @Override
    public int hashCode() {
        return Double.hashCode(this.real) ^ Double.hashCode(this.imaginary);
    }
}
