// Jessica Nguyen
// CSE143, Winter 2019
// Project name: HuffmanCode.java
// This program, HuffmanCode.java, represents a huffman code for a particular message.
// It is used to compress/decompress text files using Huffman Coding.
// The users will be able to: pass a text file (.txt) to make a compressed 
// huffman code file (.code), compress that file into (.short), decompress 
// that file into a (.new) file, initialize a huffman code by using an array of 
// different frequencies representing counts of characters in a text, and 
// construct a huffman code by reading a given input (.code) file
 
import java.io.*;
import java.util.*;
 
public class HuffmanCode {
    private static class HuffmanNode implements Comparable<HuffmanNode> {
    //private internal class representing a single HuffmanCode object
        public int character;
        public int frequency;
        public HuffmanNode left;
        public HuffmanNode right;
 
        // constructs one single HuffmanNode leaf node object with a character and its frequency
        public HuffmanNode(int character, int frequency) {
            this(character, frequency, null, null);
        }
 
        // post: constructs a HuffmanNode object with character, frequencies, 
        //       left and right field references
        private HuffmanNode(int character, int frequency, HuffmanNode left, HuffmanNode right) {
            this.character = character;
            this.frequency = frequency;
            this.left = left;
            this.right = right;
        }
 
        // returns negative number if this HuffmanNode comes before other
        // returns positive number if this HuffmanNode comes after other
        // if two frequencies of the HuffmanNodes are equal, they are the same.
        // HuffmanNodes are ordered by frequencies from least to most
        public int compareTo(HuffmanNode other) {
            return this.frequency - other.frequency;
 
        }
 
    }
 
    // HuffmanCode class field
    private HuffmanNode rootNode;
 
    // pre: frequencies array is not emppty/null, contain frequencies for 256 different
    //      ascii characters
    // post: initializes a new huffman code object based on the array of frequencies
    //       passed as the parameter, the index of the array represents the ascii
    //       value of a character, the value is the frequency
    public HuffmanCode(int[] frequencies) {
        Queue<HuffmanNode> priority = new PriorityQueue<>();
 
        for (int index = 0; index < frequencies.length; index++) {
            if (frequencies[index] != 0) {
                priority.add(new HuffmanNode(index, frequencies[index]));
            }
        }
        while (priority.size() > 1) {
            HuffmanNode first = priority.remove();
            HuffmanNode second = priority.remove();
            priority.add(new HuffmanNode(256, first.frequency + second.frequency, first, second));
            // performs the Huffman algorithm, adding two nodes' frequencies together,
            // forming a third one with its frequency being the sum of the 2 frequencies,
            // then add it back to the queue in its appropriate place
        }
 
        // stores reference to the binary tree in the priority queue;
        rootNode = priority.peek();
 
    }
 
    // pre: Scanner input is not empty/null and has to be in standard format, 
    //      containing line pairs: first line is the ascii value of character,
    //      second line is the binary code for that character
    // post: constructs a huffman code object in preorder traversal order from reading 
    //       an input file passed as a parameter. The huffman code object will get updated
    //       with information from the input file
    public HuffmanCode(Scanner input) {
        while (input.hasNextLine()) {
            // every time this loop runs, current node will have been updated with new
            // character nodes
            int asciiValue = Integer.parseInt(input.nextLine());
            String pathway = input.nextLine();
            rootNode = read(rootNode, asciiValue, pathway);
        }
    }
 
    // Private helper method to help read the input file to construct a huffman code.
    // A HuffmanNode that is null will be assigned a character value of 256 and frequency of 0
    // A HuffmanNode with a specific character value will be assigned a frequency of 0
    // Parameters: current HuffmanNode is used to keep track of which node the program
    // is looking at. The int ascii value is the character data that will be stored into the node,
    // the String pathway is used to keep track of the encoding value of a specific character
    private HuffmanNode read(HuffmanNode current, int asciiValue, String pathway) {
        if (pathway.isEmpty()) {
            // base case: if there's no path left to take, create a leaf node storing the
            // specified character value
            return new HuffmanNode(asciiValue, 0); // setting frequency to just a standard value of 0
        } else {// if there are still things to be read from the "pathway"
            if (current == null) {
                // if the rootnode is null, construct the initial empty node
                // (the highest level HuffmanNode actually branches off to other leaf nodes
                // that store actual values)
                current = new HuffmanNode(256, 0);
            }
 
            if (pathway.charAt(0) == '0') { // if pathway is '0', construct new node on the left
                current.left = read(current.left, asciiValue, pathway.substring(1));
            } else { // if pathway is '1', construct new node on the right
                current.right = read(current.right, asciiValue, pathway.substring(1));
 
            }
        }
 
        return current;
    }
 
    // pre: the given PrintStream output is a valid .code file so that the data
    //      can be saved there. 
    // post: print the current huffman code into a PrintStream output,
    //       the output of the huffman code appear in preorder traversal order.
    //       the huffman code structure still remains in original state
    public void save(PrintStream output) {
        save(output, rootNode, "");
    }
 
    // private helper method to help write the current huffman codes into
    // an output in preorder traversal order
    // Parameters: PrintStream output is a valid .code file, HuffmanNode current is 
    // the current node that is being considered, String pathway represents the 
    // encoding code to get to the node containing a character value. String pathway 
    // will be updated as the method traverses the huffman code
    private void save(PrintStream output, HuffmanNode current, String pathway) {
        if (current != null) {
            if (current.left == null && current.right == null) {
                // if node is a leaf node (contains an actual character value)
                output.println(current.character);
                output.println(pathway);
            } else {
                save(output, current.left, pathway + "0");
                save(output, current.right, pathway + "1");
            }
 
        }
 
    }
 
    // pre: the input stream contains legal encoding of characters for this huffman code
    // post: the method will read individual bits from the input stream and write the
    //       corresponding characters to the output in preorder. 
    //       The output will be stored in a .new file as a result of decompressing 
    //       the compressed file
    public void translate(BitInputStream input, PrintStream output) {
        HuffmanNode current = rootNode;
        // using loops instead of recursion to avoid exceeding the stack depth
        while (input.hasNextBit() || (current.left == null && current.right == null)) {
            // the "or" case is because even if we hit a leaf node, we still want to print
            // out the character
            // for that leaf node even if the input runs out of bits to read
            if (current.left == null && current.right == null) {
                // if the node is a leaf node and stores an actual character value
                // print it out to the output
                output.write(current.character);
                current = rootNode; // go back to the top of the tree, do it all over again
            } else { // other case: input has a next bit to read from
                int nextBit = input.nextBit();
                if (nextBit == 0) {
                    current = current.left;
                } else {
                    current = current.right;
                }
            }
        }
    }
 
}
