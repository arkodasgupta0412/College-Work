import java.util.Scanner;

class FizzBuzz {
    public void printFizz() {
        System.out.println("fizz");
    }

    public void printBuzz() {
        System.out.println("buzz");
    }

    public void printFizzBuzz() {
        System.out.println("fizzbuzz");
    }

    // prints the number 4
    public void printNumber() {
        System.out.println(4);
    }
}

class customThread extends Thread {
    private FizzBuzz f;

    customThread(FizzBuzz f) {
        this.f = f;
    }

    public void run() {
        System.out.println("Executing..." + Thread.currentThread().getName());
        f.printFizz();
        f.printBuzz();
        f.printFizzBuzz();
        f.printNumber();
    }
}

public class p6 {
    public static void main(String[] args) throws InterruptedException {
        FizzBuzz f = new FizzBuzz();

        Thread A = new Thread(() -> {
            f.printFizz();
        });

        Thread B = new Thread(() -> {
            f.printBuzz();
        });

        Thread C = new Thread(() -> {
            f.printFizzBuzz();
        });

        Thread D = new Thread(() -> {
            f.printNumber();
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