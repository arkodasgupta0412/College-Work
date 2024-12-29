#include <iostream>
using namespace std;

class Array
{
    int *arr;
    int size;

public:
    Array(int s = 0, int e = 0)
    {
        size = s;
        if (s == 0)
            arr = NULL;

        arr = new int[s];
        for (int i = 0; i < size; i++)
        {
            arr[i] = e;
        }
    }

    Array(const Array &a)
    {
        size = a.size;
        if (size != 0)
        {
            arr = new int[a.size];
            for (int i = 0; i < a.size; i++)
            {
                arr[i] = a.arr[i];
            }
        }
        else
        {
            arr = NULL;
        }
    }

    Array(int a[], int s)
    {
        size = s;
        if (s == 0)
            arr = NULL;
        arr = new int[s];
        for (int i = 0; i < size; i++)
        {
            arr[i] = a[i];
        }
    }

    Array operator+(const Array a)
    {
        Array res(max(size, a.size));
        int i = 0;
        while (i < min(size, a.size))
        {
            res.arr[i] = arr[i] + a.arr[i];
            i++;
        }

        while (i < size)
        {
            res.arr[i] = arr[i];
            i++;
        }

        while (i < a.size)
        {
            res.arr[i] = a.arr[i];
            i++;
        }

        return res;
    }

    Array operator=(const Array a)
    {
        size = a.size;
        if (size != 0)
        {
            for (int i = 0; i < size; i++)
            {
                arr[i] = a.arr[i];
            }
        }
        else
        {
            arr = NULL;
        }

        return *this;
    }

    int &operator[](int i)
    {
        return arr[i];
    }

    Array operator*(int k)
    {
        for (int i = 0; i < size; i++)
        {
            arr[i] *= k;
        }
        return *this;
    }

    ~Array()
    {
        if (arr != NULL)
        {
            delete[] arr;
        }
    }

    friend Array operator*(int, const Array);
    friend ostream &operator<<(ostream &, const Array &);
};

Array operator*(int k, const Array a)
{
    for (int i = 0; i < a.size; i++)
    {
        a.arr[i] *= k;
    }

    return a;
}

ostream &operator<<(ostream &cout, const Array &a)
{
    for (int i = 0; i < a.size; i++)
    {
        cout << a.arr[i] << " ";
    }
    cout << endl;
    return cout;
}

int main()
{
    Array a1(5);
    Array a2(6, 9);
    Array a3(a1);
    int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Array a4(arr, 8);

    cout << a1 << a2 << a3 << a4;

    cout << a2 + a4;
    Array a5;
    a5 = a2;
    cout << a5;

    cout << a4 * 3;

    cout << 2 * a2;
}