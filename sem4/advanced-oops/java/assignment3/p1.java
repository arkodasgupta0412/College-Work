import java.util.*;

class SweetSelector {

    public static int sweetNumber(int n, int k) {
        return Math.min(k, n / 2);
    }

    public static void generateCombinations(int k, int r, List<List<Integer>> result) {
        List<Integer> current = new ArrayList<>();
        backtrack(1, k, r, current, result);
    }

    private static void backtrack(int start, int k, int r, List<Integer> current, List<List<Integer>> result) {
        if (current.size() == r) {
            result.add(new ArrayList<>(current));
            return;
        }
        for (int i = start; i <= k; i++) {
            current.add(i);
            backtrack(i + 1, k, r, current, result);
            current.remove(current.size() - 1);
        }
    }
}

public class p1 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        SweetSelector s = new SweetSelector();

        System.out.print("Enter total number of sweets: ");
        int n = sc.nextInt();

        System.out.print("Enter number of different types of sweets: ");
        int k = sc.nextInt();

        int maxTypes = s.sweetNumber(n, k);
        System.out.println("\nMaximum different types Soham can taste: " + maxTypes);

        List<List<Integer>> combinations = new ArrayList<>();
        s.generateCombinations(k, maxTypes, combinations);

        System.out.println("\nSome combinations of sweet types Soham can choose:");
        int limit = Math.min(5, combinations.size());
        for (int i = 0; i < limit; i++) {
            System.out.println(combinations.get(i));
        }

        System.out.println("\nTotal number of combinations possible: " + combinations.size());
    }
}
