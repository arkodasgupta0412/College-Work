import java.util.Scanner;
import java.util.Vector;

abstract class Account {
    long _account;
    double _balance;
    double _rate;

    Account(long account, double balance, double rate) {
        this._account = account;
        this._balance = balance;
        this._rate = rate;
    }

    abstract void setRate(double newRate);
    abstract double calculateInterest(double time);
    abstract void withdraw(double amount);
    abstract void deposit(double amount);
}

class SavingsAccount extends Account {
    SavingsAccount(long account, double balance, double rate) {
        super(account, balance, rate);
    }

    @Override
    void setRate(double newRate) {
        _rate = newRate;
    }

    @Override
    double calculateInterest(double time) {
        return _balance * _rate * time / 100;
    }

    @Override
    void withdraw(double amount) {
        if (amount > _balance) {
            System.out.println("Insufficient balance");
        }
        else {
            _balance -= amount;
            System.out.println("Successfully withdrawn");
        }
        System.out.println("Balance is " + _balance);
    }

    @Override
    void deposit(double amount) {
        _balance += amount;
        System.out.println("Amount deposited");
        System.out.println("Balance is " + _balance);
    }
}

class CurrentAccount extends Account {
    private double _overdraft;
    private static final double _overdraftLimit = 2000.00;
    private boolean hasReachedLimit;

    CurrentAccount(long account, double balance, double rate) {
        super(account, balance, rate);
        _overdraft = 0;
    }

    @Override
    void setRate(double newRate) {
        _rate = newRate;
    }

    @Override
    double calculateInterest(double time) {
        if (_overdraft > 0)
            return _overdraft * _rate * time / 100;
        return 0;
    }

    @Override
    void withdraw(double amt) {
        Scanner in = new Scanner(System.in);
        if (amt > _balance) {
            _overdraft += (amt - _balance);
            _balance = 0;
            double _overdraftLimit = 2000;
            if (_overdraft > _overdraftLimit) {
                System.out.println("Potential overdraft limit reach.");
                _overdraft -= amt;
                double maxWithdraw = _overdraftLimit - _overdraft;
                if (maxWithdraw != 0) {
                    System.out.println("Maximum withdrawal allowed: " +maxWithdraw);
                    System.out.print("Do you want to withdraw " + maxWithdraw + "? (y/n): ");
                    char ch = in.next().charAt(0);
                    if (ch == 'y') {
                        System.out.println("Amount withdrawn: " + maxWithdraw);
                        _overdraft = _overdraftLimit;
                        System.out.println("Overdraft limit reached.");
                    }
                    else {
                        System.out.println("Withdrawal not granted");
                    }
                }
                else {
                    System.out.println("Overdraft limit reached. Please clear overdraft.");
                }

            }
            else {
                System.out.println("Amount withdrawn");
                System.out.println("Balance remaining: " + _balance);
                System.out.println("Overdraft: " + _overdraft);
            }
        }
        else {
            _balance -= amt;
            System.out.println("Amount withdrawn");
            System.out.println("Balance remaining: " + _balance);
            System.out.println("Overdraft: " + _overdraft);
        }
    }

    @Override
    void deposit(double amt) {
        if (_overdraft > 0) {
            if (amt > _overdraft) {
                _overdraft = 0;
                _balance += (amt - _overdraft);
                System.out.println("Amount deposited. Overdraft cleared.");
            }
            else {
                _overdraft += amt;
                _balance = 0;
                System.out.println("Amount deposited. " + (_overdraft - amt) + " amount required to clear overdraft");
            }
        }
        else {
            _balance += amt;
            System.out.println("Amount deposited");
        }

    }

    double get_overdraft() {
        return _overdraft;
    }

    void displayOverdraftAmount() {
        System.out.println("The overdraft amount is: Rs " + _overdraft);
    }
}

class Bank {
    private Vector<Account> accounts;

    Bank() {
        accounts = new Vector<>();
    }

    void addAccount(Account account) {
        if (verifyAccount(account._account)) {
            System.out.println("Account already exists with this account number.");
        }
        else {
            accounts.add(account);
            System.out.println("New account created.");
        }
    }

    boolean verifyAccount(long account) {
        for (Account ac : accounts) {
            if (ac._account == account) {
                return true;
            }
        }
        return false;
    }

    void displayAllAccounts() {
        if (accounts.isEmpty()) {
            System.out.println("No accounts to display.");
            return;
        }

        System.out.println("\nList of Accounts:");
        for (Account acc : accounts) {
            System.out.println("Account Number: " + acc._account);
            System.out.println("Balance: " + acc._balance);
            System.out.println("Interest Rate: " + acc._rate);
            System.out.println("Account Type: " + (acc instanceof SavingsAccount ? "Savings" : "Current"));
            System.out.println("------------------------------");
        }
    }

    Account getAccount(long account) {
        for (Account acc : accounts) {
            if (acc._account == account) {
                return acc;
            }
        }
        return null;
    }
}

public class p4 {
    public static void main(String[] args) {
        Bank bank = new Bank();
        Scanner in = new Scanner(System.in);
        boolean run = true;

        System.out.println("Welcome to Banking System");

        while (run) {
            System.out.println("\n1. Add Account\n2. Withdraw amount\n3. Deposit Amount\n4. Calculate Interest\n5. Set interest rate\n6. Check Account\n7. Display All Accounts\n8. Exit");
            System.out.print("Choose an option: ");
            int choice = in.nextInt();

            switch (choice) {
                case 1:
                    System.out.print("Account Type:\n1. Savings\n2. Current\n");
                    System.out.print("Enter: ");
                    int type = in.nextInt();
                    System.out.print("Enter Account Number: ");
                    long accNo = in.nextLong();
                    System.out.print("Enter Initial Balance: ");
                    double balance = in.nextDouble();
                    System.out.print("Enter Interest Rate: ");
                    double rate = in.nextDouble();

                    if (type == 1) {
                        bank.addAccount(new SavingsAccount(accNo, balance, rate));
                    } else if (type == 2) {
                        bank.addAccount(new CurrentAccount(accNo, balance, rate));
                    } else {
                        System.out.println("Invalid account type.");
                    }
                    break;

                case 2:
                    System.out.print("Enter Account Number: ");
                    accNo = in.nextLong();
                    if (bank.verifyAccount(accNo)) {
                        System.out.print("Enter amount to withdraw: ");
                        long amt = in.nextLong();
                        Account acc = bank.getAccount(accNo);
                        acc.withdraw(amt);
                    }
                    else {
                        System.out.println("Invalid account number.");
                    }
                    break;

                case 3:
                    System.out.print("Enter Account Number: ");
                    accNo = in.nextLong();
                    if (bank.verifyAccount(accNo)) {
                        System.out.print("Enter amount to deposit: ");
                        long amt = in.nextLong();
                        Account acc = bank.getAccount(accNo);
                        acc.deposit(amt);
                    }
                    else {
                        System.out.println("Invalid account number.");
                    }
                    break;

                case 4:
                    System.out.print("Enter Account Number: ");
                    accNo = in.nextLong();
                    if (bank.verifyAccount(accNo)) {
                        Account acc = bank.getAccount(accNo);
                        if (acc instanceof CurrentAccount && ((CurrentAccount) acc).get_overdraft() == 0.0) {
                            System.out.println("No overdraft pending.");
                        }
                        else {
                            System.out.print("Enter time period (in years) for interest calculation: ");
                            double time = in.nextDouble();
                            double interest = acc.calculateInterest(time);
                            System.out.println("Interest calculated: " + interest);
                        }
                    }
                    else {
                        System.out.println("Invalid account number.");
                    }
                    break;

                case 5:
                    System.out.print("Enter Account Number: ");
                    accNo = in.nextLong();
                    if (bank.verifyAccount(accNo)) {
                        Account acc = bank.getAccount(accNo);
                        System.out.print("Enter new rate of interest: ");
                        double newRate = in.nextDouble();
                        acc.setRate(newRate);
                        System.out.println("New rate has been set on this account.");
                    }
                    else {
                        System.out.println("Invalid account number.");
                    }
                    break;

                case 6:
                    System.out.print("Enter Account Number: ");
                    accNo = in.nextLong();
                    if (bank.verifyAccount(accNo)) {
                        Account acc = bank.getAccount(accNo);
                        System.out.println("Account Number: " + acc._account);
                        System.out.println("Balance: " + acc._balance);
                        System.out.println("Interest Rate: " + acc._rate);
                        System.out.println("Account Type: " + (acc instanceof SavingsAccount ? "Savings" : "Current"));
                    }
                    else {
                        System.out.println("Invalid account number.");
                    }
                    break;

                case 7:
                    bank.displayAllAccounts();
                    break;

                case 8:
                    System.out.println("Exiting...");
                    in.close();
                    run = false;
                    break;

                default:
                    System.out.println("Invalid choice. Try again.");
                    break;
            }
        }
    }
}
