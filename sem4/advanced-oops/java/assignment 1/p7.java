import java.util.Scanner;

class BankAcct {
	private long _accno;
	private double _balance;
	private static double _rate = 0.1;

	BankAcct(long account, double balance) {
		_accno = account;
		_balance = balance;
	}

	void set_rate(double r) {
		_rate = r;
	}

	double show_balance() {
		return _balance;
	}

	double calc_interest() {
		return _rate * _balance;
	}

	double show_rate() {
		return _rate;
	}
}

class p7 {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		System.out.print("Enter account number: ");
		long account = in.nextLong();

		System.out.print("Enter balance: ");
		double balance = in.nextDouble();

		BankAcct a = new BankAcct(account, balance);

		boolean running = true;

		while (running) {
			System.out.println("Menu\n1. set rate\n2. show balance\n3. calculate interest\n4. show rate\n5. Exit");
		int ch = in.nextInt();
		
		switch (ch) {
			case 1:
				System.out.print("Enter new interest rate: ");
				double r = in.nextDouble();
				a.set_rate(r);
				System.out.println("interest rate changed");
				break;

			case 2:
				System.out.print("Balance remaining: " + a.show_balance() + "/-\n");
				break;

			case 3:
				System.out.print("Interest: " + a.calc_interest() + "/-\n");
				break;

			case 4:
				System.out.print("Interest rate: " + a.show_rate() + "\n");
				break;

			case 5:
				System.out.print("Thank you\n");
				running = false;
				break;

			default:
				System.out.print("Invalid input\n");
				break;
			}
		}

		in.close();
	}
}
