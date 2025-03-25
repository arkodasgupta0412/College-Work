class BankAccount:
    def __init__(self, balance=0, pin="0000"):
        self.balance = balance
        self.pin = pin
    
    def deposit(self, amount):
        if amount > 0:
            self.balance += amount
            return True
        return False
    
    def withdraw(self, amount):
        if 0 < amount <= self.balance:
            self.balance -= amount
            return True
        return False
    
    def get_balance(self):
        return self.balance
    
    def change_pin(self, new_pin):
        self.pin = new_pin
        return True

class SavingsAccount(BankAccount):
    def __init__(self, balance=0, pin="0000", interest_rate=0.01):
        super().__init__(balance, pin)
        self.interest_rate = interest_rate
    
    def apply_interest(self):
        self.balance += self.balance * self.interest_rate

class FeeSavingsAccount(SavingsAccount):
    def __init__(self, balance=0, pin="0000", interest_rate=0.01, withdrawal_fee=1.0):
        super().__init__(balance, pin, interest_rate)
        self.withdrawal_fee = withdrawal_fee
    
    def withdraw(self, amount):
        total_amount = amount + self.withdrawal_fee
        if total_amount <= self.balance:
            self.balance -= total_amount
            return True
        return False

def main():
    print("Select Account Type:")
    print("1. Bank Account")
    print("2. Savings Account")
    print("3. Fee Savings Account")
    choice = int(input("Enter choice: "))
    
    if choice == 1:
        account = BankAccount()
    elif choice == 2:
        account = SavingsAccount()
    elif choice == 3:
        fee = float(input("Enter withdrawal fee: "))
        account = FeeSavingsAccount(withdrawal_fee=fee)
    else:
        print("Invalid choice")
        return
    
    while True:
        print("\nMenu:")
        print("1. Deposit")
        print("2. Withdraw")
        print("3. Check Balance")
        print("4. Change PIN")
        print("5. Apply Interest (Savings & Fee Savings Only)")
        print("6. Exit")
        option = int(input("Enter option: "))
        
        if option == 1:
            amount = float(input("Enter deposit amount: "))
            if account.deposit(amount):
                print("Deposit successful.")
            else:
                print("Invalid deposit amount.")
        elif option == 2:
            amount = float(input("Enter withdrawal amount: "))
            if account.withdraw(amount):
                print("Withdrawal successful.")
            else:
                print("Insufficient balance or invalid amount.")
        elif option == 3:
            print("Current Balance:", account.get_balance())
        elif option == 4:
            new_pin = input("Enter new PIN: ")
            account.change_pin(new_pin)
            print("PIN changed successfully.")
        elif option == 5 and isinstance(account, SavingsAccount):
            account.apply_interest()
            print("Interest applied.")
        elif option == 6:
            print("Exiting program.")
            break
        else:
            print("Invalid option.")

if __name__ == "__main__":
    main()
