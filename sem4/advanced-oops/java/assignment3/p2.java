import java.io.*;
import java.util.*;

// descending order
class FrequencyComparator implements Comparator<Map.Entry<String, Integer>> {
    @Override
    public int compare(Map.Entry<String, Integer> e1, Map.Entry<String, Integer> e2) {
        return e2.getValue().compareTo(e1.getValue());
    }
}


public class p2 {

    public static void main(String[] args) {
        Map<String, Integer> wordCount = new TreeMap<String, Integer>();

        try (BufferedReader br = new BufferedReader(new FileReader("input.txt"))) {
            String line;

            while ((line = br.readLine()) != null) {
                line = line.toLowerCase();
                String[] words = line.split(" ");

                for (String word : words) {
                    if (word.isEmpty()) continue;
                    wordCount.put(word, wordCount.getOrDefault(word, 0) + 1);
                }
            }
        } catch (IOException e) {
            System.out.println("No file found");
            return;
        }

        List<Map.Entry<String, Integer>> sortedList = new ArrayList<>(wordCount.entrySet());

        Collections.sort(sortedList, new FrequencyComparator());

        System.out.println("\n--- Word Frequencies (Descending) ---");
        for (Map.Entry<String, Integer> entry : sortedList) {
            System.out.println(entry.getKey() + " : " + entry.getValue());
        }

        if (!sortedList.isEmpty()) {
            System.out.println("\nMost frequent word: " + sortedList.get(0));
            System.out.println("Least frequent word: " + sortedList.get(sortedList.size() - 1));
        } else {
            System.out.println("No words found in file.");
        }
    }
}
