#include <iostream>
#include <stdexcept>
using namespace std;

// Student class
class Student
{
    int roll, score;

public:
    // Overload operator> for Student comparison
    // Student() {}
    bool operator>(const Student &s) const
    {
        return this->score > s.score;
    }

    // Accessor for score (if needed elsewhere)
    int getScore() const
    {
        return score;
    }

    // Friend functions for input and output
    friend istream &operator>>(istream &, Student &);
    friend ostream &operator<<(ostream &, const Student &);
};

// Input operator for Student
istream &operator>>(istream &cin, Student &s)
{
    cout << "Enter roll and score: ";
    cin >> s.roll >> s.score;
    return cin;
}

// Output operator for Student
ostream &operator<<(ostream &cout, const Student &s)
{
    cout << "Roll: " << s.roll << ", Score: " << s.score;
    return cout;
}

// Template for the Array class
template <typename T>
class Array
{
    T *p;     // Pointer to hold the array
    int size; // Size of the array

public:
    // Constructor
    Array(int k = 0) : size(k)
    {
        if (size == 0)
        {
            p = nullptr;
        }
        else
        {
            p = new T[size];
            for (int i = 0; i < size; i++)
            {
                T t;
                cin >> t;
                p[i] = t;
            }
        }
    }

    // Destructor to free allocated memory
    ~Array()
    {
        delete[] p;
    }

    // Get the maximum element in the array
    T getMax()
    {
        if (size == 0)
        {
            cout << "Array is empty!";
        }

        T mx = p[0];
        for (int i = 1; i < size; i++)
        {
            if (p[i] > mx)
            {
                mx = p[i];
            }
        }
        return mx;
    }

    // Friend function for output
    template <typename U>
    friend ostream &operator<<(ostream &out, Array<U> &a);
};

// Definition of the output operator for Array
template <typename T>
ostream &operator<<(ostream &out, Array<T> &a)
{
    if (a.size == 0)
    {
        out << "Array is empty.";
    }
    else
    {
        for (int i = 0; i < a.size; i++)
        {
            out << a.p[i] << endl;
        }
    }
    return out;
}

// Main function to test the program
int main()
{
    // Array of integers
    cout << "Creating an Array of integers (size 5):" << endl;
    Array<int> intArray(5);
    cout << "Integer Array:" << endl
         << intArray;
    cout << "Maximum value in the Integer Array: " << intArray.getMax() << endl;

    // Array of Students
    cout << "\nCreating an Array of Students (size 3):" << endl;
    Array<Student> studentArray(3);
    cout << "Student Array:" << endl
         << studentArray;

    cout << "Student with maximum score:" << endl
         << studentArray.getMax() << endl;

    return 0;
}
