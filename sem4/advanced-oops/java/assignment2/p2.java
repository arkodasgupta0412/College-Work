import java.util.Scanner;

class CircularLinkedList {
    Node head;

    static class Node {
        int data;
        Node next;

        Node(int d) {
            data = d;
        }
    }

    void insert() {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter node data: ");
        int data = in.nextInt();
        Node newNode = new Node(data);

        if (head == null) {
            head = newNode;
        }
        else {
            Node tmp = head;
            do {
                tmp = tmp.next;
            }while(tmp.next != head);
            tmp.next = newNode;
        }
        newNode.next = head;
    }

    void display() {
        if (head == null) {
            System.out.println("Circular Linked List is empty.");
            return;
        }
        System.out.println("\nCircular Linked List: ");
        Node tmp = head;
        do {
            System.out.print(tmp.data + "->");
            tmp = tmp.next;
        }while(tmp != head);
        System.out.print("HEAD");
    }

    int getEvenNodeSum() {
        int sum = 0;
        Node tmp = head;
        do {
            if (tmp.data % 2 == 0) {
                sum += tmp.data;
            }
            tmp = tmp.next;
        }while(tmp != head);
        return sum;
    }
}

public class p2 {
    public static void main(String[] args) {
        CircularLinkedList list = new CircularLinkedList();
        Scanner in = new Scanner(System.in);
        System.out.print("Enter the size of the list: ");
        int n = in.nextInt();

        for (int i = 0; i < n; i++) {
            list.insert();
        }

        list.display();

        int sum = list.getEvenNodeSum();
        System.out.println("\n\nSum of even nodes is: " + sum);

        in.close();
    }
}
