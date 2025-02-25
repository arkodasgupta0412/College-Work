class Wrapper {
    private int value;

    // conversion from basic type (int) to Object (Wrapper)
    Wrapper(int value) {
        this.value = value;
    }

    // conversion from Object (Wrapper) to basic type (int)
    public int toInt() {
        return value;
    }

    // Conversion from basic type (int) to String
    public String intToString(int num) {
        return Integer.toString(num);
    }

    // Conversion from string to Wrapper class object
    public Wrapper fromString(String str) {
        return new Wrapper(Integer.parseInt(str));
    }

    // conversion from Wrapper class object to String object
    @Override
    public String toString() {
        return Integer.toString(value);
    }
}

public class p6 {
    public static void main(String[] args) {
        // Basic type to object
        Wrapper obj = new Wrapper(42);
        System.out.println("Object created from int: " + obj);

        // Object to basic type
        int num = obj.toInt();
        System.out.println("Converted back to int: " + num);

        // Basic type to String
        String numStr = obj.intToString(123);
        System.out.println("Integer to String: " + numStr);

        // String to numeric object
        Wrapper numFromString = obj.fromString("456");
        System.out.println("Object created from String: " + numFromString);

        // Object to String
        System.out.println(obj);
    }
}
