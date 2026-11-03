
import java.util.*;

class Node {
    char ch;
    int freq;
    Node left, right;

    Node(char ch, int freq) {
        this.ch = ch;
        this.freq = freq;
        left = right = null;
    }
}

public class exp2 {

    static void generateCodes(Node root, String code,
            Map<Character, String> huffmanCode) {

        if (root == null)
            return;

        if (root.left == null && root.right == null) {
            huffmanCode.put(root.ch, code);
            return;
        }

        generateCodes(root.left, code + "0", huffmanCode);
        generateCodes(root.right, code + "1", huffmanCode);
    }

    static String encode(String text,
            Map<Character, String> huffmanCode) {

        StringBuilder encoded = new StringBuilder();

        for (char ch : text.toCharArray()) {
            encoded.append(huffmanCode.get(ch));
        }

        return encoded.toString();
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the string: ");
        String text = sc.nextLine();

        if (text.isEmpty()) {
            System.out.println("String cannot be empty.");
            return;
        }

        Map<Character, Integer> frequency = new HashMap<>();

        for (char ch : text.toCharArray()) {
            frequency.put(ch, frequency.getOrDefault(ch, 0) + 1);
        }

        System.out.println("\nCharacter Frequencies:");

        for (Map.Entry<Character, Integer> entry : frequency.entrySet()) {
            System.out.println(entry.getKey() + " : " + entry.getValue());
        }

        PriorityQueue<Node> pq = new PriorityQueue<>(
                (a, b) -> Integer.compare(a.freq, b.freq));

        for (Map.Entry<Character, Integer> entry : frequency.entrySet()) {
            pq.add(new Node(entry.getKey(), entry.getValue()));
        }

        while (pq.size() > 1) {

            Node left = pq.poll();
            Node right = pq.poll();

            Node parent = new Node('\0', left.freq + right.freq);

            parent.left = left;
            parent.right = right;

            pq.add(parent);
        }

        Node root = pq.poll();

        Map<Character, String> huffmanCode = new HashMap<>();

        generateCodes(root, "", huffmanCode);

        System.out.println("\nHuffman Codes:");

        for (Map.Entry<Character, String> entry : huffmanCode.entrySet()) {
            System.out.println(entry.getKey() + " : " + entry.getValue());
        }

        String encodedText = encode(text, huffmanCode);

        System.out.println("\nOriginal String: " + text);
        System.out.println("Encoded String: " + encodedText);

        System.out.println("\nOriginal Size: " + text.length() * 8 + " bits");
        System.out.println("Encoded Size: " + encodedText.length() + " bits");

        sc.close();
    }
}
