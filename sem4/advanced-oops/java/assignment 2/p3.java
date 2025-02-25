import java.util.Scanner;
import java.util.Vector;

class Tree {
    private TreeNode root;

    static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int val) {
            this.val = val;
            left = null;
            right = null;
        }
    }

    void addNode() {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter tree node data: ");
        int data = in.nextInt();
        TreeNode newNode = new TreeNode(data);

        if (root == null) {
            root = newNode;
        }
        else {
            TreeNode curr = root;
            while (true) {
                System.out.print("Where to insert? Left(L)/Right(R) of "+curr.val+": ");
                char ch = in.next().charAt(0);
                if (ch == 'L') {
                    if (curr.left != null) {
                        curr = curr.left;
                    }
                    else {
                        curr.left = newNode;
                        break;
                    }
                }
                else {
                    if (curr.right != null) {
                        curr = curr.right;
                    }
                    else {
                        curr.right = newNode;
                        break;
                    }
                }
            }
        }
    }

/*void preOrder(TreeNode root) {
if (root == null) return;
System.out.print(root.val+" ");
preOrder(root.left);
preOrder(root.right);
}*/

    void dfs(TreeNode root, Vector<Integer> ds, Vector<String> paths) {
        if (root == null) return;

        ds.add(root.val);

        if (root.left == null && root.right == null) {
            StringBuilder path = new StringBuilder();
            int i;
            for (i = 0; i < ds.size()-1; i++) {
                path.append(ds.get(i)).append("->");
            }
            path.append(ds.get(i));
            paths.add(path.toString());
        }
        else {
            dfs(root.left, ds, paths);
            dfs(root.right, ds, paths);
        }
        ds.remove(ds.size()-1);
    }

    TreeNode getRoot() {
        return root;
    }

}


public class p3{
    public static void main(String[] args) {
        Tree t = new Tree();
        Vector<Integer> ds = new Vector<>();
        Vector<String> paths = new Vector<>();

        Scanner in = new Scanner(System.in);

        boolean run = true;

        while (run) {
            System.out.println("\nMenu:\n1. Build Tree\n2. Root to leaf paths\n3. Exit");
            int ch = in.nextInt();

            switch(ch) {
                case 1:
                    while (true) {
                        System.out.print("Add another node? Yes(Y) / No(N): ");
                        int c = in.next().charAt(0);
                        if (c == 'Y') {
                            t.addNode();
                        }
                        else {
                            break;
                        }
                    }
                    break;

                case 2:
                    t.dfs(t.getRoot(), ds, paths);
                    for (String s: paths) {
                        System.out.println(s);
                    }
                    break;

                case 3:
                    run = false;
                    System.out.println("Exiting...");
                    break;

                case 4:
                    System.out.println("Invalid choice");
                    break;
            }

        }
// t.preOrder(t.getRoot());

        in.close();
    }
}
