// Jessica Nguyen
// CSE143
// Assignment #6: AnagramSolver.java
// This class AnagramSolver allows clients to print out all the possible anagram 
// words of their given word or phrase, using words from a given dictionary file.
// The clients will also be able to select how many different words maximum that
// they want to be generated based on their given word/phrase.
 
import java.util.*;
 
public class AnagramSolver {
    private Map<String, LetterInventory> inventories;
    private List<String> dictionary;
    private List<String> prunedDictionary;
 
    // pre: dictionary is not empty or null
    // post: initializes the state of the anagram solver
    //       that will be using the client's given dictionary
    public AnagramSolver(List<String> dictionary) {
        this.dictionary = dictionary;
        makeAnagramMap();
    }
 
    // private helper method that pre-processes the dictionary to compute
    // different inventories for each word in the dictionary in advance
    private void makeAnagramMap() {
        inventories = new HashMap<>();
 
        for (String word : dictionary) {
 
            LetterInventory inventory = new LetterInventory(word);
 
            inventories.put(word, inventory);
 
        }
 
    }
 
    // pre: given string is not empty, max value >= 0
    //      (throws IllegalArgumentException if max < 0)
    // post: different combination of words (only words from the given dictionary)
    //       that are the anagrams of the given word/phrase are printed
    public void print(String text, int max) {
        if (max < 0) {
            throw new IllegalArgumentException();
        }
 
        LetterInventory originalText = new LetterInventory(text);
 
        List<String> wordChoices = pruneDictionary(originalText);
        // create list of all possible choices, "pruning" the dictionary
 
        print(originalText, max, new Stack<String>(), wordChoices);
 
    }
 
    // private helper method: optimizizes the anagram-solving process by reducing
    //      the original dictionary to only a smaller list of words that are relevant
    // post: returns a list containing only relevant words to be considered by the anagram solver
    private List<String> pruneDictionary(LetterInventory originalText) {
        prunedDictionary = new ArrayList<>();
 
        for (String word : dictionary) {
            LetterInventory current = inventories.get(word);
            LetterInventory newWord = originalText.subtract(current);
 
            if (newWord != null) {
                prunedDictionary.add(word);
            }
        }
        return prunedDictionary;
    }
 
    // private helper method: helps the print method to print out different
    //    combination of words that are the anagram of the given word/phrase
    private void print(LetterInventory text, int max, Stack<String> chosen, List<String> wordChoices) {
        if (text.isEmpty() && (chosen.size() <= max || max == 0)) { // base case
 
            System.out.println(chosen);
 
        } else {
 
            for (String word : wordChoices) {
 
                // choose
                LetterInventory currentWord = inventories.get(word);
                LetterInventory newWord = text.subtract(currentWord);
 
                if (newWord != null) {
                    chosen.push(word);
 
                    // explore
                    print(newWord, max, chosen, wordChoices);
 
                    // unchoose
                    chosen.pop();
                    newWord = newWord.add(currentWord);
 
                }
 
            }
 
        }
    }
 
}
