// Jessica Nguyen
// CSE 143
// Assignment #4: HangmanManager.java
// This program models a hangman game, but it cheats the player by delaying
// choosing the actual word until it runs out of options and is forced to
// choose a word, but still has to follow normal convention when the user 
// does actually guess a letter correctly. Using this class, the user can 
// pass a dictionary of words, choose a desired word length for their guess, 
// and declare how many wrong guesses they are allowed. Users can also: 
// get access to the current set of words being considered by the game, find
// out how many guesses they have left, find out which characters they've guessed
// already, 
 
import java.util.*;
 
public class HangmanManager {
 
    private Set<String> words; 
    private Set<Character> guesses;
    private int totalGuesses;
    private String wordDisplay; 
 
    // pre: dictionary is not empty, given target word length >= 1, given number
    //      of guesses >=0 (throws IllegalArgumentException if not)
    // post: initializes the state of the game by constructing a set of words taken from 
    //       the given dictionary where each word in that set has the given specific length,  
    //       number of wrong guesses allowed is initialized, the displayed pattern onto 
    //       the user console is initialized
    public HangmanManager(Collection<String> dictionary, int length, int max) {
        if (length < 1 || max < 0) {
            throw new IllegalArgumentException();
        }
 
        words = new TreeSet<>();
        guesses = new TreeSet<>();
        totalGuesses = max;
 
        // adds only words that match the given length into the set of words being considered
        for (String word : dictionary) {
            if (word.length() == length) {
                words.add(word);
            }
        }
 
        // creates initial displayed word with dashes representing the letters to be guessed
        wordDisplay = "-"; 
        for (int index = 1; index < length; index++) {
            wordDisplay += " -";
        }
 
    }
 
    // post: returns the current set of words that are curerntly being considered to guess from
    public Set<String> words() {
        return words;
    }
 
    // post: return how many guesses the player has left
    public int guessesLeft() {
        return totalGuesses;
    }
 
    // post: returns a list of all the characters the user has already guessed
    public Set<Character> guesses() {
        return guesses;
    }
 
    // post: returns the displayed pattern of the word currently being guessed for the user,
    //       letters that have already been guessed correctly will be displayed, and letters
    //       that haven't been guessed are displayed as dashes
    //       (throws IllegalStateException if the set of words being considered is empty)
    public String pattern() {
        if (words.isEmpty()) {
            throw new IllegalStateException();
        }
        return wordDisplay;
    }
 
    // pre: the number of guesses remaining >=1 and the set of words being considered is
    //      not empty (throws IllegalStateException if not)
    //      the given character has to be different from all the previous characters that
    //      the user had used to guess the word (throws IllegalArgumentException if not)
    // post: returns the number of occurences of the guessed letter in the word currently 
    //       being guessed
    public int record(char guess) {
        if (totalGuesses < 1 || words.isEmpty()) {
            throw new IllegalStateException();
        } 
 
        if (guesses.contains(guess)) {
            throw new IllegalArgumentException();
        }
 
        Map<String, Set<String>> setOfWords = new TreeMap<>();
        guesses.add(guess);
 
        for (String term : words) { 
            String key = makeKey(term, guess);
            if (!setOfWords.containsKey(key)) {
                setOfWords.put(key, new TreeSet<>());
            }
            setOfWords.get(key).add(term);
            // add the term to its matching pattern key in the map
        }
 
        String keyTerm = findBiggestSize(setOfWords);
        //finds the pattern key with the most words in it
 
        updateWordDisplay(keyTerm, guess);
        // updates the word display for the user once program has determined which
        // pattern to follow
 
        words = setOfWords.get(keyTerm);
        // updates the set of words being considered once the program can eliminate 
        // which sets of words to not use after user made their guess
 
        int occurence = findOccurence(keyTerm, guess);
 
        if (keyTerm.indexOf(guess) == -1) {
            // if guessed letter not found in the new pattern, meaning user guessed wrong
            totalGuesses--;
        }
 
        return occurence;
    }
 
    // post: private helper method to return the pattern for each term in the current set
    //       of words being considered
    private String makeKey(String term, char letterGuess) {
        String key = "";
 
        for (int index = 0; index < term.length(); index++) {
            if (term.charAt(index) == letterGuess) {
                key += " " + letterGuess;
            } else {
                key += " -";
            }
        }
 
        return key.substring(1); // cut off the leading extra space
    }
 
    // post: private helper method to return the pattern of the set of words with the
    //       biggest size out of all the different word pattern groups
    private String findBiggestSize(Map<String, Set<String>> setOfWords) {
        int max = 0;
        String key = "";
        for (String term : setOfWords.keySet()) {
            if (setOfWords.get(term).size() > max) {
                max = setOfWords.get(term).size();
                key = term;
            }
        }
        return key;
    }
 
    // post: private helper method to find how many occurences of the guessed letter in the 
    //       word currently being guessed
    private int findOccurence(String keyTerm, char guess) {
        int count = 0;
 
        for (int index = 0; index < keyTerm.length(); index++) {
            if (keyTerm.charAt(index) == guess) {
                count++;
            }
        }
 
        return count;
    }
 
    // post: private helper method to update the displayed word for the user
    //       depending on if they guessed a letter right or not 
    private void updateWordDisplay(String keyTerm, char guess) {
        for (int i = 0; i < keyTerm.length(); i += 2) { // +=2 to skip over the white spaces
            if (keyTerm.charAt(i) == guess) {
                wordDisplay = wordDisplay.substring(0, i) + guess + 
                        wordDisplay.substring(i + 1);
            }
        }
    }
}
