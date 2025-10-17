import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

class MyVar {
    private int val = 0;

    // use synchronized to ensure at a time, only one thread modifies the shared variable
    public synchronized void increment(int x) {
        val += x;
    }

    // use synchronized to ensure at a time, only one thread modifies the shared variable
    public synchronized void decrement() {
        val -= 1;
    }

    int getVal() {
        return val;
    }
}


class myThread extends Thread {
    private MyVar var;
    private List<Integer> increments;

    myThread(MyVar var, List<Integer> increments) {
        this.var = var;
        this.increments = increments;
    }

    @Override
    public void run() {
        for (int x : increments) {
            var.increment(x);
        }

        for (int i = 0; i < 3; i++) {
            var.decrement();
        }
    }
}


public class p5 {
    public static void main(String[] args) throws InterruptedException {
        Scanner sc = new Scanner(System.in);
        MyVar var = new MyVar();

        List<Integer> inc1 = new ArrayList<>();
        List<Integer> inc2 = new ArrayList<>();

        System.out.println("Enter 3 increment values for thread 1:");
        for (int i = 0; i < 3; i++) inc1.add(sc.nextInt());

        System.out.println("Enter 3 increment values for thread 2:");
        for (int i = 0; i < 3; i++) inc2.add(sc.nextInt());

        myThread t1 = new myThread(var, inc1);
        myThread t2 = new myThread(var, inc2);

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        System.out.println("Final value of var: " + var.getVal());
    }
}