import java.util.*;

class TreeNode {
    String val;
    TreeNode left, right;

    TreeNode(String val) {
        this.val = val;
    }
}

class FamilyTree {
    private int preorderIndex = 0;
    private Map<String, Integer> inorderIndexMap = new HashMap<>();

    public TreeNode buildTree(String[] preorder, String[] inorder) {
        for (int i = 0; i < inorder.length; i++) {
            inorderIndexMap.put(inorder[i], i);
        }
        return build(preorder, 0, inorder.length - 1);
    }

    private TreeNode build(String[] preorder, int inStart, int inEnd) {
        if (inStart > inEnd) return null;

        String val = preorder[preorderIndex++];
        TreeNode node = new TreeNode(val);

        int index = inorderIndexMap.get(val);
        node.left = build(preorder, inStart, index - 1);
        node.right = build(preorder, index + 1, inEnd);

        return node;
    }

    // Print the binary tree structure visually
    public void printTree(TreeNode root) {
        System.out.println("\nBinary Tree Structure:");
        printTreeHelper(root, 0);
    }

    private void printTreeHelper(TreeNode node, int level) {
        if (node == null) return;

        printTreeHelper(node.right, level + 1);
        System.out.println("    ".repeat(level) + "|-- " + node.val);
        printTreeHelper(node.left, level + 1);
    }

    public void printCousins(TreeNode root) {
        Map<Integer, List<TreeNode>> levels = new HashMap<>();
        Map<TreeNode, TreeNode> parent = new HashMap<>();

        Queue<TreeNode> q = new LinkedList<>();
        q.offer(root);
        parent.put(root, null);
        int level = 0;

        while (!q.isEmpty()) {
            int size = q.size();
            List<TreeNode> current = new ArrayList<>();

            for (int i = 0; i < size; i++) {
                TreeNode node = q.poll();
                current.add(node);

                if (node.left != null) {
                    q.offer(node.left);
                    parent.put(node.left, node);
                }
                if (node.right != null) {
                    q.offer(node.right);
                    parent.put(node.right, node);
                }
            }

            levels.put(level++, current);
        }

        for (List<TreeNode> group : levels.values()) {
            for (int i = 0; i < group.size(); i++) {
                for (int j = i + 1; j < group.size(); j++) {
                    TreeNode a = group.get(i);
                    TreeNode b = group.get(j);
                    if (parent.get(a) != parent.get(b)) {
                        System.out.println("Cousins: " + a.val + " & " + b.val);
                    }
                }
            }
        }
    }
}

public class p3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter preorder traversal: ");
        String[] preorder = sc.nextLine().split(" ");

        System.out.println("Enter inorder traversal: ");
        String[] inorder = sc.nextLine().split(" ");

        FamilyTree ft = new FamilyTree();
        TreeNode root = ft.buildTree(preorder, inorder);

        ft.printTree(root);

        System.out.println("\n");
        ft.printCousins(root);
    }
}