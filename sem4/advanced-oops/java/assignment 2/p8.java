class ReverseCharSequence implements CharSequence {
    private final String reversed;

    public ReverseCharSequence(String str) {
        this.reversed = new StringBuilder(str).reverse().toString();
    }

    @Override
    public char charAt(int index) {
        if (index < 0 || index >= reversed.length()) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return reversed.charAt(index);
    }

    @Override
    public int length() {
        return reversed.length();
    }

    @Override
    public CharSequence subSequence(int start, int end) {
        if (start < 0 || end > reversed.length() || start > end) {
            throw new IndexOutOfBoundsException("Invalid subsequence range");
        }
        return reversed.substring(start, end);
    }

    @Override
    public String toString() {
        return reversed;
    }
}

public class p8 {
    public static void main(String[] args) {
        ReverseCharSequence rev = new ReverseCharSequence("hello");

        System.out.println("charAt(1): " + rev.charAt(1));

        System.out.println("Length: " + rev.length());

        System.out.println("subSequence(1, 4): " + rev.subSequence(1, 4));

        System.out.println("Reversed String: " + rev);
    }
}

