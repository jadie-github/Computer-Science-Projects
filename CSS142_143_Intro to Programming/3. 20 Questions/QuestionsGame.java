// Jessica Nguyen
// CSE 143
// Assignment #7:QuestionsGame.java
// This class QuestionsGame models a game of "20 Questions" that lets a client
// think of an object. Then the program asks the client a series of yes/no
// questions until it can make a guess about what object the client is thinking 
// about. If the program guesses right, it wins. If it guesses wrong, it 
// will ask the client to clarify more details about their object, and then 
// updates its knowledge base for future references. Clients will be able to:
// pass an input file containing a series of questions and answers for the program
// to utilize as its knowledge base; store the current questions/answers 
// knowledge base into an output file; and ask the program to play one complete
// game until it finally guesses the object.
 
import java.io.*;
import java.util.*;
 
public class QuestionsGame {
    //private internal class representing a single QuestionNode object
    private static class QuestionNode {
        public String data;
        public QuestionNode left;
        public QuestionNode right;
 
        // constructs one single QuestionNode leaf node object
        private QuestionNode(String data) {
            this(data, null, null);
        }
 
        // constructs a QuestionNode object with left and right field references
        private QuestionNode(String data, QuestionNode left, QuestionNode right) {
            this.data = data;
            this.left = left;
            this.right = right;
        }
    }
 
    //QuestionsGame class fields
    private QuestionNode overallRoot;
    private Scanner console;
 
    // post: initializes a new QuestionsGame object representing a "computer"
    //       as the default object
    public QuestionsGame() {
        console = new Scanner(System.in);
        this.overallRoot = new QuestionNode("computer");
 
    }
 
    // pre: input file is not empty or null, is legal and in standard format
    // post: the current knowledge system of questions/answers will replaced
    //       by the new sets of questions/answers provided in the input file
    public void read(Scanner input) {
        this.overallRoot = read(input, overallRoot);
    }
 
    // private helper method to help read the given input file
    private QuestionNode read(Scanner input, QuestionNode curr) {
        if (!input.hasNextLine()) { // base case when there's no more lines to be read
            return null;
        } else {
            // read input
            String type = input.nextLine();
            String data = input.nextLine();
 
            curr = new QuestionNode(data);
            // store the questions/answer responses into a new node
 
            // If type is "Q" (question), create a new node with 2 branches for yes or no
            // responses
            if (type.equals("Q:")) {
                return new QuestionNode(data, read(input, curr.left), read(input, curr.right));
            } else { // If type is "A" (answer), create a leaf node
                return new QuestionNode(data);
            }
        }
    }
 
    // post: stores the current questions/answers system to the given 
    //       output file Printstream. The output can be used to 
    //       play another game later utilizing the already existing set of 
    //       questions/answers      
    public void write(PrintStream output) {
        write(output, overallRoot);
    }
 
    // private helper method to help print the current questions/answers system
    // to the output file
    private void write(PrintStream output, QuestionNode current) {
 
        if (current != null) {
            // if current node has children nodes (left,right fields), it is a question type
            if (current.left != null && current.right != null) {
                output.println("Q:");
                output.println(current.data);
 
                write(output, current.left);
                write(output, current.right);
            } else { // if node has no children branches, it is an answer node
                output.println("A:");
                output.println(current.data); 
            }
 
        }
 
    }
 
    // post: plays one game of guessing game with the client until the program makes 
    //       a guess about what object the client is thinking about
    public void askQuestions() {
        this.overallRoot = askQuestions(overallRoot);
    }
 
    // private helper method to help store information about the current object node
    // being analyazed
    private QuestionNode askQuestions(QuestionNode curr) {
        if (curr.left != null && curr.right != null) { 
            // if the node has both children branches, it is a question
            String questionResponse = curr.data;
 
            if (yesTo(questionResponse)) {
                // if user answers yes to the question, recurse/analyze the left node
                curr.left = askQuestions(curr.left);
            } else { // if they answered "no", recurse/analyze the right node
                curr.right = askQuestions(curr.right);
            }
        } else { // if this was an answer node, no children
            String question = "Would your object happen to be " + curr.data + "?";
 
            if (yesTo(question)) {// if the computer guesses the correct object
                System.out.println("Great, I got it right!");
            } else { // if the computer fails to guess the correct answer
                System.out.print("What is the name of your object? ");
                String newObject = console.nextLine();
 
                System.out.println("Please give me a yes/no question that");
                System.out.println("distinguishes between your object");
                System.out.print("and mine--> ");
                String newQuestion = console.nextLine();
 
                String answer = "And what is the answer for your object?";
 
                if (yesTo(answer)) { // if user answers "yes" to their own question
                    curr = new QuestionNode(newQuestion, new QuestionNode(newObject), new QuestionNode(curr.data));
 
                } else { // if user answers "no" to their own question
                    curr = new QuestionNode(newQuestion, new QuestionNode(curr.data), new QuestionNode(newObject));
                }
            }
        }
        return curr;
    }
 
    // post: asks the user a question, forcing an answer of "y" or "n";
    //       returns true if the answer was yes, returns false otherwise
    public boolean yesTo(String prompt) {
        System.out.print(prompt + " (y/n)? ");
        String response = console.nextLine().trim().toLowerCase();
        while (!response.equals("y") && !response.equals("n")) {
            System.out.println("Please answer y or n.");
            System.out.print(prompt + " (y/n)? ");
            response = console.nextLine().trim().toLowerCase();
        }
        return response.equals("y");
    }
}
