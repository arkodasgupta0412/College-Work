import re

class UsernameNotUniqueError(Exception): pass
class InvalidAgeError(Exception): pass
class UnderageError(Exception): pass
class InvalidEmailError(Exception): pass

def is_valid_email(email):
    return bool(re.match(r'^[\w.-]+@[\w.-]+\.\w+$', email))

def add_user(directory, username, email, age):
    try:
        if username in directory:
            raise UsernameNotUniqueError(f"Username '{username}' already exists.")
        if not isinstance(age, int) or age <= 0:
            raise InvalidAgeError("Age must be a positive integer.")
        if age < 16:
            raise UnderageError("User must be at least 16 years old.")
        if not is_valid_email(email):
            raise InvalidEmailError("Invalid email format.")
        
        directory[username] = email
        print(f"User '{username}' added successfully.")
    except Exception as e:
        print("Error:", e)

def display_users(directory):
    if not directory:
        print("No users added yet.")
    else:
        print("\nRegistered Users:")
        for username, email in directory.items():
            print(f"Username: {username}, Email: {email}")

def main():
    directory = {}
    while True:
        print("\nMenu:")
        print("1. Add User")
        print("2. Display Users")
        print("3. Exit")
        choice = input("Enter your choice: ")
        
        if choice == '1':
            username = input("Enter username: ")
            email = input("Enter email: ")
            try:
                age = int(input("Enter age: "))
                add_user(directory, username, email, age)
            except ValueError:
                print("Error: Age must be an integer.")
        elif choice == '2':
            display_users(directory)
        elif choice == '3':
            print("Exiting program.")
            break
        else:
            print("Invalid choice! Please enter 1, 2, or 3.")

if __name__ == "__main__":
    main()
