import java.util.Scanner;


class Circle {
    double r;
    final float PI = 3.14f;

    Circle() {r = 0.0;}

    Circle(double radius) {r = radius;}

    Circle(Circle c) {this.r = c.r;}

    double calcArea() {
	return PI * r * r;
    }
}


class p2 {
    public static void main(String[] args) {
        double r;
        Scanner in = new Scanner(System.in);


	/* call using default constructor */
	Circle c1 = new Circle();
	System.out.println("\nCall using default constructor (Circle c1)");
	System.out.printf("The radius of circle: %.2f%n", c1.r);
	System.out.printf("The area of circle: %.2f%n", c1.calcArea());



	// call using parameterized constructor */
	System.out.println("\nCall using parameterized constructor (Circle c2)");
	System.out.print("Enter radius of circle: ");
        r = in.nextDouble();
	Circle c2 = new Circle(r);
	System.out.printf("The radius of circle: %.2f%n", c2.r);
	System.out.printf("The area of circle: %.2f%n", c2.calcArea());



	// call using copy constructor (deep copy)
	System.out.println("\nCall using copy constructor (Circle c3) -> deep copy of c2");
	Circle c3 = new Circle(c2);
	System.out.printf("The radius of circle: %.2f%n", c3.r);
	System.out.printf("The area of circle: %.2f%n", c3.calcArea());



	// Assignment of two Circles (reference types) -> shallow copy
	System.out.println("\nShallow copy circle 4 from circle 2 (Circle 4) -> shallow copy of c2");
	Circle c4;
	c4 = c2;
	System.out.printf("The radius of circle: %.2f%n", c4.r);
	System.out.printf("The area of circle: %.2f%n", c4.calcArea());


	// changed radius
	System.out.print("\nEnter new radius of c2: ");
	c2.r = in.nextDouble();
	


	System.out.println("\nc3 deep-copied: ");
	System.out.printf("The radius of circle: %.2f%n", c3.r);
	System.out.printf("The area of circle: %.2f%n", c3.calcArea());



	System.out.println("\nc4 shallow-copied: ");
	System.out.printf("The radius of circle: %.2f%n", c4.r);
	System.out.printf("The area of circle: %.2f%n", c4.calcArea());

	in.close();
    }
}
