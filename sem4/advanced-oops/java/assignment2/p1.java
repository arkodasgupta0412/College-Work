import java.util.Scanner;
import java.lang.Math;

class Solution {
    double maxArea(double[] heights, int n) {
        int left = 0, right = n-1, leftBar = left, rightBar = right;
        double maxArea = 0.0, area;

        while (left < right) {
            area = Math.min(heights[left], heights[right]) * (right - left);

            if (area > maxArea) {
                maxArea = area;
                leftBar = left;
                rightBar = right;
            }

            if (heights[left] < heights[right]) {
                left++;
            }
            else {
                right--;
            }
        }

        System.out.println("Maximum water can be contained between bars " + (leftBar + 1) + " and " + (rightBar + 1));

        return maxArea;
    }
}

public class p1 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Enter number of verticals: ");
        int n = in.nextInt();
        System.out.print("Enter the slant angle: ");
        double angle = in.nextDouble();

        double[] heights = new double[n];
        System.out.println("Enter heights: ");
        for (int i = 0; i < n; i++) {
            heights[i] = in.nextDouble() * Math.sin(Math.toRadians(angle));
        }

        Solution solution = new Solution();
        double maxArea = solution.maxArea(heights, n);

        System.out.println("Maximum water content is " + maxArea);

        in.close();
    }
}
