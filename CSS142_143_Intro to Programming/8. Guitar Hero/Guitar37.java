// Jessica Nguyen
// CSE143
// Homework #2 part 2: Guitar37.java
// This Guitar37 class models a guitar keyboard with 37 different notes where each note
// represents a different musical note. Clients will be able to
// play a note by passing a pitch to the program, specify a character that indicates which note
// to play using the keys on the user keyboard, get the current sound sample, advance the time 
// forward one "tic", and determine the current time. 
 
public class Guitar37 implements Guitar {
    public static final String KEYBOARD = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' "; // keyboard layout
    private final int STRINGS_COUNT = KEYBOARD.length(); // denotes 37 notes
    private GuitarString[] strings;
    private int displacement; // for converting from pitch to index
    private int ticTimes;
 
    // post: constructs a Guitar37 object with 37 notes, each
    //       note has a different frequency
    public Guitar37() {
        displacement=24;
        ticTimes=0;
        strings = new GuitarString[STRINGS_COUNT];
        for (int index = 0; index < STRINGS_COUNT; index++) {
            double frequency = 440.0 * (Math.pow(2, ((index - 24.0) / 12.0)));
            strings[index] = new GuitarString(frequency);
        }
    }
 
    // pre: pitch >=-24 and pitch <= 12 where 0 represents concert A
    //      and the pitch goes up/down chromatically
    // post: if the pitch is playable, the guitar string will be plucked.
    //       If not, the program will ignore it. No exceptions are thrown.
    public void playNote(int pitch) {
        pitch += displacement;
        if (pitch >= 0 && pitch < STRINGS_COUNT) { // from indexes 0 to 36
            strings[pitch].pluck();
        }
    }
 
    // pre: the given character belongs to the list of keys playable by the guitar
    // post: return whether the given key has a corresponding string on the guitar
    public boolean hasString(char key) {
        // if the given character doesn't belong to the list of playable keys,
        // the program will return -1, so by checking if the result
        // is -1, we can tell whether a key is a valid key or not
        return KEYBOARD.indexOf(key) != -1;
    }
 
    // pre: the given character belongs to the list of keys playable by the guitar
    //      (throws IllegalArgumentException if not)
    // post: the guitar string that corresponds to the given key will be plucked
    public void pluck(char key) {
 
        int keyPosition = KEYBOARD.indexOf(key);
 
        if (keyPosition == -1) {
            throw new IllegalArgumentException();
        }
 
        strings[keyPosition].pluck();
 
    }
 
    // post: returns the current sound sample of all guitar strings
    public double sample() {
        double sum = 0;
        for (GuitarString s : strings) {
            sum += s.sample();
        }
        return sum;
    }
 
    // post: the time is advanced forward to one more "tic"
    public void tic() {
        for (GuitarString s : strings) {
            s.tic();
 
        }
        ticTimes++;
 
    }
 
    // post: returns the current time (the number of "tics" that has been called)
    //       if tic() was never implemented, this method returns -1
    public int time() {
 
        return ticTimes;
    }
 
}
