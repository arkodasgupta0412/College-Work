/* */

import java.util.Scanner;

class p1 {
    public static void main(String[] args) {
        short a, b;
        Scanner in = new Scanner(System.in);
        System.out.print("Enter first number: ");
        a = in.nextShort();
        System.out.print("Enter second number: ");
        b = in.nextShort();
        in.close();

        short sum = (short)(a + b);
        System.out.print("Sum = " + sum + "\n");
    }
}
