// Jessica Nguyen
// CSE143
// Assignment #1: LetterInventory.java
// This class LetterInventory is used to keep track of the counts of the letters
// of the alphabet in a given word, can tell clients about the size of the inventory
// or whether the inventory is empty or not, and can also be used to add or subtract 
// inventory counts with other LetterInventory objects
 
public class LetterInventory {
    private int DEFAULT_VALUE = 26;
    // 97 and 122 are the ASCII indexes of 'a' and 'z' respectively
    private int START = 97;
    private int END = 122;
    private int size;
    private int[] letters;
 
    // post: constructs a LetterInventory object of default capacity
    //       that stores a count of all alphabetic letters in the
    //       given String value, ignoring uppercase letters as well as
    //       non-alphabetic characters
    public LetterInventory(String data) {
        letters = new int[DEFAULT_VALUE];
        data = data.toLowerCase();
 
        for (int index = 0; index < data.length(); index++) {
            char letter = data.charAt(index);
            if (letter >= START && letter <= END) {
                letters[letter - START]++;
                size++;
            }
        }
    }
 
    // pre: character value is a valid letter in the alphabet
    //      (throws IllegalArgumentException if not)
    // post: returns an int count of how many of the given character is in the inventory
    public int get(char letter) {
        letter = Character.toLowerCase(letter);
        if (letter < START || letter > END) {
            throw new IllegalArgumentException();
        }
        return letters[letter - START];
    }
 
    // pre: the given character is a valid letter in the alphabet and int value >= 0
    //      (throws IllegalArgumentException if not)
    // post: the count of the given character in the inventory
    //       will be set to the given int value
    public void set(char letter, int value) {
        letter = Character.toLowerCase(letter);
        if (letter < START || letter > END || value < 0) {
            throw new IllegalArgumentException();
        } else { // character ASCII equivalent is within the range of letters array
            size += value - letters[letter - START];
            letters[letter - START] = value;
 
        }
    }
 
    // post: returns the int sum of all counts in the inventory
    public int size() {
        return size;
    }
 
    // post: returns whether the inventory is empty or not
    public boolean isEmpty() {
        return size == 0;
    }
 
    // post: returns a String representation of the letters in the inventory in
    //       alphabetical order, each letter is printed however many times
    //       its count is in the inventory, and all surrounded by square brackets
    public String toString() {
        String response = "[";
 
        for (int place = 0; place < letters.length; place++) {
            char character = (char) (START + place);
            for (int count = 0; count < letters[place]; count++) {
                response += character;
            }
 
        }
 
        return response + "]";
    }
 
    // pre: other is an already declared LetterInventory object
    // post: returns a new LetterInventory object that combines the inventory counts
    //       of this LetterInventory and the other given LetterInventory
    public LetterInventory add(LetterInventory other) {
        LetterInventory sum = new LetterInventory("");
        for (int index = 0; index < letters.length; index++) {
            sum.letters[index] = this.letters[index] + other.letters[index];
        }
        sum.size = this.size + other.size;
        return sum;
    }
 
    // pre: other is an already declared LetterInventory object
    // post: returns a new LetterInventory object as the result of subtracting
    //       the counts of the other inventory from this inventory.
    //       If the difference between the two sizes, or counts of a letter 
    //       is less than 0, method returns null
    public LetterInventory subtract(LetterInventory other) {
        LetterInventory difference = new LetterInventory("");
 
        for (int index = 0; index < letters.length; index++) {
            difference.letters[index] = this.letters[index] - other.letters[index];
 
            if (difference.letters[index] < 0) {
                return null;
            }
 
            difference.size += difference.letters[index];
        }
 
        return difference;
 
    }
 
}

