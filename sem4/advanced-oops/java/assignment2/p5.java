import java.util.Scanner;

abstract class Customer {
    long customerID;
    String name;
    long phone;
    double loan;

    Customer(long customerID, String name, long phone) {
        this.customerID = customerID;
        this.name = name;
        this.phone = phone;
        loan = 0;
    }

    abstract void setPhone(long phone);
    abstract void setName(String name);
    abstract int getCreditLimit();

    void takeLoan(double amt) {
        Scanner in = new Scanner(System.in);
        int creditLimit = getCreditLimit();

        if (loan == creditLimit) {
            System.out.println("Credit limit reached. Please clear the debt");
        }

        else {
            if (loan + amt > creditLimit) {
                System.out.println("Potential credit limit reach");
                double left = creditLimit - loan;
                System.out.println("Amount of " + left + " left to reach limit.");
                System.out.print("Do you want to take loan of " + left + " amt? (y/n): ");
                char ch = in.next().charAt(0);
                if (ch == 'y') {
                    loan += left;
                    System.out.println("Credit limit reached. Cannot take more loans");
                } else {
                    System.out.println("Loan not taken");
                }
            } else {
                loan += amt;
                System.out.println("Loan of amount " + amt + " has been taken");
            }
        }
    }

    void payLoan(double amt) {
        int creditLimit = getCreditLimit();
        if (amt >= loan) {
            loan = 0;
            System.out.println("Loan cleared");
        }
        else {
            loan -= amt;
            System.out.println("Partial loan payed");
            System.out.println("Loan left to be payed: " + loan);
        }
    }
}

class PriviLegedCustomer extends Customer {
    private static final int creditLimit = 50000;

    PriviLegedCustomer(long customerID, String name, long phone) {
        super(customerID, name, phone);
    }

    @Override
    void setPhone(long phone) {
        this.phone = phone;
    }

    @Override
    void setName(String name) {
        this.name = name;
    }

    @Override
    int getCreditLimit() {
        return creditLimit;
    }
}

class NormalCustomer extends Customer {
    private static final int creditLimit = 25000;

    NormalCustomer(long customerID, String name, long phone) {
        super(customerID, name, phone);
    }

    @Override
    void setPhone(long phone) {
        this.phone = phone;
    }

    @Override
    void setName(String name) {
        this.name = name;
    }

    @Override
    int getCreditLimit() {
        return creditLimit;
    }
}

public class p5 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        Customer customer = null;

        System.out.println("Welcome to the Customer Management System");
        System.out.print("Enter Customer ID: ");
        long customerID = in.nextLong();
        in.nextLine(); // consume newline
        System.out.print("Enter Name: ");
        String name = in.nextLine();
        System.out.print("Enter Phone Number: ");
        long phone = in.nextLong();

        System.out.println("Select Customer Type:");
        System.out.println("1. Privileged Customer");
        System.out.println("2. Normal Customer");
        int type = in.nextInt();

        if (type == 1) {
            customer = new PriviLegedCustomer(customerID, name, phone);
        } else if (type == 2) {
            customer = new NormalCustomer(customerID, name, phone);
        } else {
            System.out.println("Invalid choice. Exiting.");
            return;
        }

        int choice;
        do {
            System.out.println("\nMenu:");
            System.out.println("1. View Details");
            System.out.println("2. Update Name");
            System.out.println("3. Update Phone Number");
            System.out.println("4. Take Loan");
            System.out.println("5. Pay Loan");
            System.out.println("6. View Loan Details");
            System.out.println("0. Exit");
            System.out.print("Enter your choice: ");
            choice = in.nextInt();
            in.nextLine(); // consume newline

            switch (choice) {
                case 1:
                    System.out.println("Customer ID: " + customer.customerID);
                    System.out.println("Name: " + customer.name);
                    System.out.println("Phone: " + customer.phone);
                    System.out.println("Loan: " + customer.loan);
                    System.out.println("Credit Limit: " + customer.getCreditLimit());
                    break;
                case 2:
                    System.out.print("Enter new name: ");
                    String newName = in.nextLine();
                    customer.setName(newName);
                    System.out.println("Name updated successfully.");
                    break;
                case 3:
                    System.out.print("Enter new phone number: ");
                    long newPhone = in.nextLong();
                    customer.setPhone(newPhone);
                    System.out.println("Phone number updated successfully.");
                    break;
                case 4:
                    System.out.print("Enter loan amount to take: ");
                    double loanAmt = in.nextDouble();
                    customer.takeLoan(loanAmt);
                    break;
                case 5:
                    System.out.print("Enter loan amount to pay: ");
                    double payAmt = in.nextDouble();
                    customer.payLoan(payAmt);
                    break;
                case 6:
                    System.out.println("Current Loan Amount: " + customer.loan);
                    break;
                case 0:
                    System.out.println("Exiting the system. Thank you!");
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        } while (choice != 0);

        in.close();
    }
}
