import java.util.*;

public class p4 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        List<Integer> scores = new ArrayList<>();
        System.out.println("\nEnter number of goals scored by teams: ");
        for (String s : sc.nextLine().split(" ")) {
            scores.add(Integer.parseInt(s));
        }

        int n = scores.size();
        int[] left = new int[n];
        int[] right = new int[n];
        int[] result = new int[n];

        left[0] = 1;
        for (int i = 1; i < n; i++) {
            left[i] = left[i - 1] * scores.get(i - 1);
        }

        right[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            right[i] = right[i + 1] * scores.get(i + 1);
        }

        for (int i = 0; i < n; i++) {
            result[i] = left[i] * right[i];
        }

        System.out.println("\n");
        for (int i = 0; i < n; i++) {
            System.out.println("Score: " + scores.get(i) + ", Product (excluding this): " + result[i]);
        }
    }
}
