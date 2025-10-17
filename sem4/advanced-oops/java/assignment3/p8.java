import java.util.Scanner;

class NoticeBoard {
    private String message = "";
    private boolean isWriting = false;
    private int readersReading = 0;
    private int readersWaiting = 0;

    public synchronized void write(String msg) {
        while (isWriting || readersReading > 0) {
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        System.out.println("\nPeople are waiting to read. Writer is modifying the board.");

        isWriting = true;
        System.out.println("\nWriting message...");

        try {
            Thread.sleep(7000);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        message = msg;
        isWriting = false;
        System.out.println("Writing done.");
        notifyAll();
    }

    public synchronized void read(String name) {
        while (isWriting) {
            readersWaiting++;
            try {
                wait();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            readersWaiting--;
        }

        if (!message.isEmpty()) {
            readersReading++;
            System.out.println("\n" + name + " is reading: " + message);
        }

        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        readersReading--;
        if (readersReading == 0) {
            notifyAll();
        }
    }
}

class Writer implements Runnable {
    private NoticeBoard board;
    private String msg;

    Writer(NoticeBoard board, String msg) {
        this.board = board;
        this.msg = msg;
    }

    public void run() {
        board.write(msg);
    }
}

class Reader implements Runnable {
    private NoticeBoard board;
    private String name;

    Reader(NoticeBoard board, String name) {
        this.board = board;
        this.name = name;
    }

    public void run() {
        board.read(name);
    }
}

public class p8 {
    public static void main(String[] args) throws InterruptedException {
        Scanner sc = new Scanner(System.in);
        NoticeBoard board = new NoticeBoard();

        Thread writer1 = new Thread(new Writer(board, "Meeting at 2 PM"));
        Thread reader1 = new Thread(new Reader(board, "Samuel"));
        Thread reader2 = new Thread(new Reader(board, "Edward"));
        Thread writer2 = new Thread(new Writer(board, "Meeting postponed to 3 PM"));
        Thread reader3 = new Thread(new Reader(board, "Daniel"));

        writer1.start();

        reader1.start();

        reader2.start();
        
        writer2.start();
        
        reader3.start();
    }
}