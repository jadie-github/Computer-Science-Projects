/*Jessica Nguyen
CSS430, Program3C
philosopher.cpp
This program presents different implemementation solutions for the dining philosophers problem.

Table 0 Allows each philosopher to pick up and put down her left/right chopsticks without checking their availability. 
The logic is wrong but runs fastest. 

Table 1 uses “hogging” method to ensure mutual exclusion between philosophers. 
It ensures that only 1 philosopher can eat at a time, while others wait. 
This can cause starvation if one philosopher keeps executing indefinitely.

Table 2 uses a monitor to manipulate semaphores. All philosophers start off with THINKING. 
If they are HUNGRY, they have to test whether their chopsticks are being used by anyone else or not. 
If available, they can begin EATING and locking the monitor. 
Or else, they would wait until the adjacent chopsticks aare available and it becomes their turn to eat.

*/

#include <pthread.h> // pthread
#include <stdio.h>
#include <stdlib.h>   // atoi( )
#include <unistd.h>   // sleep( )
#include <sys/time.h> // gettimeofday
#include <iostream>   // cout

#define PHILOSOPHERS 5
#define MEALS 3

using namespace std;

//This uses a monitor to manipulate semaphores 
class Table2 {
public:
  Table2( ) {
    // initialize every philophers at the beginning, equivalent to thinking
    pthread_mutex_init(&lock, nullptr);

    for(int i = 0; i < PHILOSOPHERS; i++){
      state[i] = THINKING;
      pthread_cond_init(&self[i], nullptr); 
    }
  }

  /* pickup() -- If a philosopher i wishes to pickup(), they are set to HUNGRY, 
  and have to test whether their chopsticks are being used by anyone else or not. 
  Postconditions: If available, they can begin EATING and locking the monitor. 
                  Else, they would wait until the chopsticks are available to them
  */
  void pickup( int i ) {
    pthread_mutex_lock(&lock); //locks monitor
    
    state[i] = HUNGRY;
    //see if adjacent philosophers are eating or not
    test(i);

    //if adjacent philosophers are still eating, it needs to wait
    if(state[i] != EATING){
      
      pthread_cond_wait(&self[i], &lock);
    } 
  
    cout << "philosopher[" << i << "] picked up chopsticks" << endl;  
      
    pthread_mutex_unlock(&lock); //unlocks monitor
      
  }

  /*putdown() -- releases the use of current chopsticks and reset own state back to THINKING
  */
  void putdown( int i ) {
    // implement by yourself by referring to the textbook.
    //reset my state to thinking, releasing chopsticks
    pthread_mutex_lock(&lock); //locks monitor
    
    cout << "philosopher[" << i << "] put down chopsticks" << endl;

    state[i] = THINKING;

    //check on adjacent philosophers to allow them to start eating because I have finished
    test((i + PHILOSOPHERS - 1) % PHILOSOPHERS);
    test((i + 1) % PHILOSOPHERS);
    pthread_mutex_unlock(&lock);
  }

private:
  enum { THINKING, HUNGRY, EATING } state[PHILOSOPHERS];
  pthread_mutex_t lock;
  pthread_cond_t self[PHILOSOPHERS];

  void test( int i ) {
    //check my 2 adjacent neighbors: if I am hungry and neither of them are eating, I can take the chopsticks and eat
    if(state[(i + PHILOSOPHERS - 1) % PHILOSOPHERS] != EATING &&
       state[i] == HUNGRY &&
       state[(i + 1) % PHILOSOPHERS] != EATING){
          state[i] = EATING;
          pthread_cond_signal(&self[i]);
         
       }
  }
};

// executes wait on every other philosopher until the current philosopher is finished eating -- can cause starvation
class Table1 {
public:
  Table1( ) {
    // initialize the mutex lock
    pthread_mutex_init(&lock, nullptr); //NOT SURE
  }
  void pickup( int i ) {
    pthread_mutex_lock(&lock);
    cout << "philosopher[" << i << "] picked up chopsticks" << endl;
    
  }

  void putdown( int i ) {
    
    cout << "philosopher[" << i << "] put down chopsticks" << endl;
    pthread_mutex_unlock(&lock);
    
  }

private:
  // define a mutex lock
  pthread_mutex_t lock;
};

class Table0 {
public:
  void pickup( int i ) {
    cout << "philosopher[" << i << "] picked up chopsticks" << endl;
  }

  void putdown( int i ) {
    cout << "philosopher[" << i << "] put down chopsticks" << endl;
  }
};

static Table2 table2;
static Table1 table1;
static Table0 table0;

static int table_id = 0;

void *philosopher( void *arg ) {
  int id = *(int *)arg;
  
  for ( int i = 0; i < MEALS; i++ ) {
    switch( table_id ) {
    case 0:
      table0.pickup( id );
      sleep( 1 );
      table0.putdown( id );
      break;
    case 1:
      table1.pickup( id );
      sleep( 1 );
      table1.putdown( id );
      break;
    case 2:
      table2.pickup( id );
      sleep( 1 );
      table2.putdown( id );
    break;
    }
  }
  return NULL;
}

int main( int argc, char** argv ) {
  pthread_t threads[PHILOSOPHERS];
  pthread_attr_t attr;
  int id[PHILOSOPHERS];
  table_id = atoi( argv[1] );

  pthread_attr_init(&attr);
  
  struct timeval start_time, end_time;
  gettimeofday( &start_time, NULL );
  for ( int i = 0; i < PHILOSOPHERS; i++ ) {
    id[i] = i;
    pthread_create( &threads[i], &attr, philosopher, (void *)&id[i] );
  }

  for ( int i = 0; i < PHILOSOPHERS; i++ )
    pthread_join( threads[i], NULL );
  gettimeofday( &end_time, NULL );

  sleep( 1 );
  cout << "time = " << ( end_time.tv_sec - start_time.tv_sec ) * 1000000 + ( end_time.tv_usec - start_time.tv_usec ) << endl;

  return 0;
}
