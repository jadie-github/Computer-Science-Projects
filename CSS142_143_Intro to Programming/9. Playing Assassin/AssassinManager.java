// Jessica Nguyen
// CSE143
// Homework #3: AssassinManager.java
// This class models a game of "Assassin" where the user can input a file full of names
// and a kill ring will be generated based on that file. The user can execute tasks such as: 
// print names of people still in the game, print names of people who are already killed 
// (placed in the graveyard), kill off a player, check if a person is frontAlive or frontDead, check if 
// the game is over or not, and find out who the winner is if the game is over.
 
import java.util.*;
 
public class AssassinManager {
 
    private AssassinNode frontAlive;
    private AssassinNode frontDead;
 
    // pre: list containing names is not empty or null, contains only non-empty strings,
    //      no duplicates in names
    //      (throws IllegalArgumentException if list is empty or null)
    // post: an assassin kill ring containing all the names is generated
    public AssassinManager(List<String> names) {
 
        if (names == null || names.isEmpty()) {
            throw new IllegalArgumentException();
        }
 
        for (int item = names.size() - 1; item >= 0; item--) {
            frontAlive = new AssassinNode(names.get(item), frontAlive);
        }
 
    }
 
    // post: prints out name of all players currently in the kill ring and who they're stalking
    //       if only one player is left, the result prints that they are stalking themselves
    public void printKillRing() {
 
        AssassinNode curr = frontAlive;
 
        while (curr.next != null) {
            printStalking(curr.name, curr.next.name);
            curr = curr.next;
        }
 
        // if only one person is in the list, or if the loops reaches the last person,
        // the killer name is the first person node's name.
        printStalking(curr.name, frontAlive.name);
 
    }
 
    // post: private helper method prints out names of who is stalking who
    private void printStalking(String killer, String victim) {
        System.out.println("    " + killer + " is stalking " + victim);
    }
 
    // post: prints out name of players that are frontDead, and who killed them
    //       in the order of most recently killed first.
    //       produces no output if graveyard is empty (no one is frontDead)
    public void printGraveyard() {
        if (frontDead != null) { // check: if graveyard is empty
 
            AssassinNode curr = frontDead;
 
            while (curr != null) {
                System.out.println("    " + curr.name + " was killed by " + curr.killer);
                curr = curr.next;
            }
        }
    }
 
    // post: returns whether the given name is in the current kill ring or not
    public boolean killRingContains(String name) {
        return contains(frontAlive, name);
    }
 
    // post: returns whether the given name is in the current graveyard or not
    public boolean graveyardContains(String name) {
        return contains(frontDead, name);
    }
 
    // post: private helper returns whether the given list contains the given name
    //       or not
    private boolean contains(AssassinNode list, String name) {
        AssassinNode curr = list;
        while (curr != null) {
            if (curr.name.equalsIgnoreCase(name)) {
                return true;
            }
            curr = curr.next;
        }
 
        return false;
    }
 
    // post: returns whether the game is over or not
    public boolean gameOver() {
        return frontAlive.next == null;
 
    }
 
    // post: returns name of the winner of the game
    //       returns null if game is not over yet
    public String winner() {
        if (gameOver()) {
            return frontAlive.name;
        }
        return null;
 
    }
 
    // pre: given name is part of the current kill ring 
    //      (throws IllegalArgumentException if not)
    //      and game is still going on 
    //      (throws IllegalStateException if not)
    // post: the person with the given name will be killed,
    //       that person is transferred to the graveyard, the kill ring updates
    //       in terms of who's stalking who
    public void kill(String name) {
        if (!killRingContains(name)) { // if the name isn't in the kill ring
            throw new IllegalArgumentException();
        }
        if (gameOver()) { // if game is over
            throw new IllegalStateException();
        }
 
        AssassinNode killer = getKiller(name); // get the killer node
        AssassinNode victim;
 
        // case: if victim is the first person in the kill ring
        if (frontAlive.name.equalsIgnoreCase(name)) {
            victim = frontAlive; // get the victim node
 
            frontAlive = frontAlive.next;// node containing killer points to next person after victim
 
            transfer(victim, killer);
 
        } else { // case: if victim is not the first person in the kill ring
            victim = killer.next;// get victim node
 
            // node containing killer points to next person after victim
            killer.next = killer.next.next;
 
            transfer(victim, killer);
        }
    }
 
    // post: private helper method to find out who the killer is for the given
    //       victim
    private AssassinNode getKiller(String name) {
        AssassinNode temp = frontAlive;
 
        while (temp != null && temp.next != null && !temp.next.name.equalsIgnoreCase(name)) {
            temp = temp.next;
        }
 
        // if the victim is the first person, then the loop will run to the very end,
        // and the last person is the killer for the first person because this list
        // models a loop
 
        return temp;
    }
 
    // post: private helper method to transfer victim to frontDead list and updates the
    //       frontAlive list
    private void transfer(AssassinNode victim, AssassinNode killer) {
        victim.killer = killer.name;// sets killer name for victim
 
        victim.next = frontDead; // points victim to frontDead list
        frontDead = victim; // updates the frontDead list
    }
 
}
