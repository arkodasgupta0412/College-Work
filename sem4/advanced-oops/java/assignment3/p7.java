import java.util.Scanner;

class FizzBuzz {
    private int n;
    private int current = 1;

    public FizzBuzz(int n) {
        this.n = n;
    }

    public synchronized void fizz() throws InterruptedException {
        while (current <= n) {
            if (current % 5 == 0 && current % 9 != 0) {
                System.out.print("fizz ");
                current++;
                notifyAll();
            } else {
                waitIfNotOver();
            }
        }
    }

    public synchronized void buzz() throws InterruptedException {
        while (current <= n) {
            if (current % 7 == 0 && current % 3 != 0) {
                System.out.print("buzz ");
                current++;
                notifyAll();
            } else {
                waitIfNotOver();
            }
        }
    }

    public synchronized void fizzbuzz() throws InterruptedException {
        while (current <= n) {
            if (current % 5 == 0 && current % 7 == 0) {
                System.out.print("fizzbuzz ");
                current++;
                notifyAll();
            } else {
                waitIfNotOver();
            }
        }
    }

    public synchronized void number() throws InterruptedException {
        while (current <= n) {
            if (current % 7 != 0 && current % 5 != 0) {
                System.out.print(current + " ");
                current++;
                notifyAll();
            } else {
                waitIfNotOver();
            }
        }
    }

    private void waitIfNotOver() throws InterruptedException {
        if (current <= n) wait();
    }
}

public class p7{
    public static void main(String[] args) throws InterruptedException {

        int n;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter n: ");
        n = sc.nextInt();

        FizzBuzz fizzBuzz = new FizzBuzz(n);

        Thread A = new Thread(() -> {
            try {
                fizzBuzz.fizz();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        Thread B = new Thread(() -> {
            try {
                fizzBuzz.buzz();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        Thread C = new Thread(() -> {
            try {
                fizzBuzz.fizzbuzz();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        Thread D = new Thread(() -> {
            try {
                fizzBuzz.number();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });

        A.start();
        B.start();
        C.start();
        D.start();

        A.join();
        B.join();
        C.join();
        D.join();

        System.out.println("\nDone");
    }
}

