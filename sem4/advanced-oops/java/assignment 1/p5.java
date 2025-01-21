import java.util.Scanner;

class p5 {
	void show(int i) {
		System.out.println("Inside void show(int)");
	}

	void show(double d) {
		System.out.println("Inside void show(double)");
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		System.out.print("Enter a short integer: ");
		short s = in.nextShort();

		System.out.print("Enter a double: ");
		double d = in.nextDouble();

		p5 obj = new p5();
		obj.show(s);
		obj.show(d);
	}
}
