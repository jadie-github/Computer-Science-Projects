// Jessica Nguyen
// CSE143
// Homework #2 part 1: GuitarString.java
// This class GuitarString is used to model a ring buffer of a guitar
// where it holds frequencies of a guitar string as the string is
// being plucked. Clients can choose to construct a guitar string with
// a chosen frequency, or fill in the ring buffer with a chosen array.
// Clients can also choose to pluck the string, perform a Karplus-Strong update
// or obtain the current sample of the ring buffer.
 
import java.util.*;
 
public class GuitarString {
 
    private final double SAMPLING_RATE = StdAudio.SAMPLE_RATE;
    public final double ENERGY_DECAY_FACTOR = 0.996;
    private Queue<Double> ringBuffer;
    private int capacity;   
 
    // pre: frequency > 0 and be less than or equal to half of the sampling rate's value
    //      (throws IllegalArgumentException if not)
    // post: constructs a guitar string with given frequency
    public GuitarString(double frequency) {
 
        ringBuffer = new LinkedList<Double>();
 
        capacity = (int) Math.round(SAMPLING_RATE / frequency);
 
        if (frequency <= 0 || capacity < 2) {
            throw new IllegalArgumentException();
        }
 
        for (int item = 0; item < capacity; item++) {
            ringBuffer.add(0.0);
        }
 
    }
 
    // pre: init.length >= 2 (throws IllegalArgumentException if not)
    // post: constructs a guitar string and initialize the elements of 
    //       the ring buffer to values from the given array
    public GuitarString(double[] init) {
        capacity = init.length;
 
        if (capacity < 2) {
            throw new IllegalArgumentException();
        }
 
        ringBuffer = new LinkedList<Double>();
 
        for (int item = 0; item < capacity; item++) {
            ringBuffer.add(init[item]);
        }
 
    }
 
    // post: replaces all elements of the ring buffer to random double values
    public void pluck() {
        Random rand = new Random();
        for (int item = 0; item < capacity; item++) {
            double random = -0.5 + rand.nextDouble();
            ringBuffer.add(random); // adds to back of queue
            ringBuffer.remove(); // remove value at the front of queue
        }
 
    }
 
    // post: performs the Karplus-Strong algorithm once
    public void tic() {
        double num1 = ringBuffer.remove();
        double num2 = ringBuffer.peek(); 
        ringBuffer.add((num1 + num2) / 2.0 * ENERGY_DECAY_FACTOR);
    }
 
    // post: returns the current value in front of the ring buffer
    public double sample() {
        return ringBuffer.peek();
 
    }
}
