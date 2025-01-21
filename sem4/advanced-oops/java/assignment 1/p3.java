import java.util.Scanner;

class p3 {
	public static void main(String[] args) {
		int n;
		Scanner in = new Scanner(System.in);
		System.out.print("Enter n: ");
		n = in.nextInt();

		int[] arr = new int[n];
		for (int i = 0; i < n; i++) {
			arr[i] = i+1;
		}

		// printing original array
		System.out.print("{ ");
		for (int i = 0; i < n; i++) {
			System.out.print(arr[i] + " ");
		}
		System.out.print("}");

		int skip = 2, currSize = n;
		while (skip <= currSize) {
			int i = 0;
			for (int j = 0; j < currSize; j += skip) {
				arr[i++] = arr[j];
			}
			currSize = i;

			System.out.print(" -> { ");
			for (int j = 0; j < currSize; j++) {
				System.out.print(arr[j] + " ");
			}
			System.out.print("}");
			skip++;
		}
		System.out.print("\n");
		in.close();
	}
}
