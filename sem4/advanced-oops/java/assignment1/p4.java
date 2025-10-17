import java.util.Scanner;

class p4 {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		System.out.print("Enter string 1: ");
		String s1 =  in.nextLine();

		String s2;
		s2 = s1;
		
		boolean output1 = (s1 == s2);
		boolean output2 = (s1.equals(s2));

		System.out.print("String 1 = " + s1 + "\n");
		System.out.print("String 2 (assigned from string 1) = " + s2 + "\n");
		System.out.print("\nOutput 1 (using == ): " + output1 + "\n");
		System.out.print("Output 2 (using equals() method): " + output2 + "\n");

		System.out.print("\nEnter string 3 (with same content as string 1): ");
		String s3 = in.nextLine();

		output1 = (s1 == s3);
		output2 = (s1.equals(s3));

		System.out.print("\nString 1 = " + s1 + "\n");
		System.out.print("String 3 (separate input) = " + s3 + "\n");
		System.out.print("\nOutput 1 (using == ): " + output1 + "\n");
		System.out.print("Output 2 (using equals() method): " + output2 + "\n");
		
		in.close();
	}
}
