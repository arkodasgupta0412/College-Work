import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

class StringAnalyzer {
    private String inputString;

    public StringAnalyzer(String input) {
        this.inputString = input;
    }

    public void setNewString(String newInput) {
        this.inputString = newInput;
    }

    public int countLetterA() {
        int count = 0;
        for (int i = 0; i < inputString.length(); i++) {
            char ch = Character.toLowerCase(inputString.charAt(i));
            if (ch == 'a') {
                count++;
            }
        }
        return count;
    }

    public int countAnd() {
        int count = 0;
        String lowerCase = toLowerCase(inputString);
        for (int i = 0; i <= lowerCase.length() - 3; i++) {
            if (lowerCase.charAt(i) == 'a' && lowerCase.charAt(i + 1) == 'n' && lowerCase.charAt(i + 2) == 'd' &&
                    (i == 0 || lowerCase.charAt(i - 1) == ' ') && (i + 3 == lowerCase.length() || lowerCase.charAt(i + 3) == ' ')) {
                count++;
            }
        }
        return count;
    }

    public boolean startsWithThe() {
        if (inputString.length() < 3) {
            return false;
        }
        return Character.toLowerCase(inputString.charAt(0)) == 't' &&
                Character.toLowerCase(inputString.charAt(1)) == 'h' &&
                Character.toLowerCase(inputString.charAt(2)) == 'e';
    }

    public char[] toCharArray() {
        char[] charArray = new char[inputString.length()];
        for (int i = 0; i < inputString.length(); i++) {
            charArray[i] = inputString.charAt(i);
        }
        return charArray;
    }

    public List<String> getTokens() {
        List<String> tokens = new ArrayList<>();
        StringBuilder currentToken = new StringBuilder();
        for (int i = 0; i < inputString.length(); i++) {
            char c = inputString.charAt(i);
            if (c == ' ' || c == '@' || c == '.') {
                if (currentToken.length() > 0) {
                    tokens.add(currentToken.toString());
                    currentToken.setLength(0);
                }
            } else {
                currentToken.append(c);
            }
        }
        if (currentToken.length() > 0) {
            tokens.add(currentToken.toString());
        }
        return tokens;
    }

    public String findLargestPalindrome() {
        StringBuilder cleanString = new StringBuilder();
        for (int i = 0; i < inputString.length(); i++) {
            char c = inputString.charAt(i);
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == ' ') {
                cleanString.append(Character.toLowerCase(c));
            }
        }
        String[] words = splitBySpace(cleanString.toString());
        String largestPalindrome = "";
        for (String word : words) {
            if (isPalindrome(word) && word.length() > largestPalindrome.length()) {
                largestPalindrome = word;
            }
        }
        return largestPalindrome.isEmpty() ? "No palindrome found" : largestPalindrome;
    }

    private boolean isPalindrome(String str) {
        int left = 0, right = str.length() - 1;
        while (left < right) {
            if (str.charAt(left++) != str.charAt(right--)) {
                return false;
            }
        }
        return true;
    }

    private String toLowerCase(String str) {
        StringBuilder lower = new StringBuilder();
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (c >= 'A' && c <= 'Z') {
                lower.append((char) (c + ('a' - 'A')));
            } else {
                lower.append(c);
            }
        }
        return lower.toString();
    }

    private String[] splitBySpace(String str) {
        List<String> words = new ArrayList<>();
        StringBuilder word = new StringBuilder();
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            if (c == ' ') {
                if (word.length() > 0) {
                    words.add(word.toString());
                    word.setLength(0);
                }
            } else {
                word.append(c);
            }
        }
        if (word.length() > 0) {
            words.add(word.toString());
        }
        return words.toArray(new String[0]);
    }

    public void displayAnalysis() {
        System.out.println("Analysis for: \"" + inputString + "\"");
        System.out.println("Number of 'a's: " + countLetterA());
        System.out.println("Number of \"and\"s: " + countAnd());
        System.out.println("Starts with \"The\": " + startsWithThe());
        System.out.println("Character array: " + Arrays.toString(toCharArray()));
        System.out.println("Tokens: " + getTokens());
        System.out.println("Largest palindrome: " + findLargestPalindrome());
    }
}

public class p7 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        StringAnalyzer analyzer = new StringAnalyzer("");

        while (true) {
            System.out.println("\nEnter a string to analyze (or type 'exit' to quit):");
            String input = scanner.nextLine();

            if (input.equalsIgnoreCase("exit")) {
                break;
            }

            analyzer.setNewString(input);
            analyzer.displayAnalysis();
        }

        scanner.close();
        System.out.println("Program terminated.");
    }
}
