import java.util.Scanner;

class Pizza {
	public void getVA(String size, String ... toppings) {
		System.out.println("\nPizza Order");
		System.out.println("\nSize: " + size);
		System.out.println("Toppings: ");
		for (String topping: toppings) {
			System.out.println(" - "+topping);
		}
	}

	public void getCLA(String size, String[] toppings) {
		System.out.println("\nPizza Order");
		System.out.println("\nSize: " + size);
		System.out.println("Toppings: ");
		for (int i = 0; i < toppings.length; i++) {
			System.out.println(" - "+toppings[i]);
		}
	}
}


class p6 {
	public static void main(String[] args) {
		Pizza pizza = new Pizza();

		Scanner in = new Scanner(System.in);
		System.out.print("Enter size of pizza: ");
		String size = in.nextLine();
	
		System.out.println("\nUsing variable arguments: ");
		pizza.getVA(size);
		
		System.out.println("\n\nUsing command line arguments: ");
		pizza.getCLA(size, args);
		System.out.print("\b\n");

		in.close();
	}
}
