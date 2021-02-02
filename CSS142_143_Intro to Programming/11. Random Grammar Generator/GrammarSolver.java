// Jessica Nguyen
// CSE 143
// Homework #5: GrammarSolver.java
// This class models a "grammar elements generator" that reads a grammar in BNF format
// as an input file, and allows the user to randomly generate elements of the grammar.
// Clients can: pass a list containing BNF grammar rules, specify what elements of the
// grammar they want to generate, how many of them they want to generate,
// find out if a symbol is a nonterminal of the grammar, and obtain the list
// of all available nonterminal symbols. 
 
import java.util.*;
 
public class GrammarSolver {
    private SortedMap<String, String[]> symbolsRules;
 
    // pre: the given grammar is not empty, and there are no more than one
    //      entry in the grammar for the same nonterminal symbol
    //      (throws IllegalArgumentException if not)
    // post: nonterminals and terminals of the given grammar are sorted out 
    //       so they can be generated randomly
    public GrammarSolver(List<String> grammar) {
 
        if (grammar.isEmpty()) {
            throw new IllegalArgumentException();
        }
        symbolsRules = new TreeMap<>();
 
        for (String structure : grammar) {
            separateParts(structure);
        }
 
    }
 
    // private helper method to separate out nonterminal and terminal symbols
    //      throws IllegalArgumentException if there are more than one
    //      entry in the grammar for the same nonterminal symbol
    private void separateParts(String structure) {
        String[] parts = structure.split("::=");
 
        for (int index = 0; index < parts.length; index++) {
            parts[index] = parts[index].trim();
 
        }
 
        String nonTerminal = parts[0];
 
        String[] terminals = parts[1].split("\\|");
 
        for (int index = 0; index < terminals.length; index++) {
            terminals[index] = terminals[index].trim();
        }
 
        if (symbolsRules.containsKey(nonTerminal)) {
            throw new IllegalArgumentException();
            // because the requirement for the grammar is that there should be
            // "no two or more entries in the grammar for the same nonterminal"
        } else {
            symbolsRules.put(nonTerminal, terminals);
        }
 
    }
 
    // post: returns true if the given symbol is a nonterminal of the grammar,
    //       returns false otherwise.
    public boolean grammarContains(String symbol) {
        return symbolsRules.containsKey(symbol);
    }
 
    // pre: the grammar has to contain the given nonterminal symbol, the given number of times
    //      for the generated nonterminals has to be >=0
    //      (throws IllegalArgumentException if not)
    // post: method randomly generates the given number of occurrences of the given 
    //       nonterminal symbol
    public String[] generate(String symbol, int times) {
        if (!symbolsRules.containsKey(symbol) || times < 0) {
            throw new IllegalArgumentException();
        }
 
        String[] sentences = new String[times];
 
        for (int index = 0; index < times; index++) {
            sentences[index] = generate(symbol).trim();
        }
 
        return sentences;
    }
 
    // private helper method that returns one random instantiation of a nonterminal symbol
    private String generate(String symbol) {
        if (!symbolsRules.containsKey(symbol)) {
            // base case: when the symbol is an actual word and not a nonterminal, then
            // return it
            return " " + symbol;
        }
 
        String[] terminals = symbolsRules.get(symbol); //array of available terminals
 
        int num = (int) (Math.random() * terminals.length); 
        String key = terminals[num];
        // picks a random terminal from the array of terminals
 
        String[] differentTerminals = key.split("\\s+");
        // splits individual symbols from that chosen terminal in the case that there are 
        // more than one symbol in that terminal
 
        String answer = "";
        for (String terminal : differentTerminals) {
            answer += generate(terminal);
        }
        // keeps generating elements of the grammar recursively as long as there are still symbols 
        // to be generated from the list of nonterminals
 
        return answer;
 
    }
 
    // post: returns all the available nonterminal symbols from the grammar
    public String getSymbols() {
        String answer = "";
        for (String key : symbolsRules.keySet()) {
            answer += ", " + key;
        }
        return "[" + (answer + "]").substring(2);
    }
 
}
