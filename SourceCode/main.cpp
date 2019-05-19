#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include "Blockchain.h"

using namespace std;

#define NUM_THREADS 5

void *CommPort1(void *threadid) {
   long tid;
   tid = (long)threadid;
   cout << "Communication on port1 " << tid << endl;


   pthread_exit(NULL);
}

void *CommPort2(void *threadid) {
   long tid;
   tid = (long)threadid;
   cout << "Communication on port2 " << tid << endl;



   pthread_exit(NULL);
}

int main()
{
    cout << "RedRat Communication Node APP\n" << endl;

    /*
    BlockChain  blockChain;
    blockChain.addBlock(Block(1,"01/05/2019", "data1"));
    blockChain.addBlock(Block(2,"02/05/2019", "data2"));

    blockChain.showBlockChain();
    */

    pthread_t threads[NUM_THREADS];

    int ret;
    int i;

    for( i = 0; i < NUM_THREADS; i++ ) {
      cout << "main() : creating thread, " << i << endl;
      ret = pthread_create(&threads[i], NULL, CommPort1, (void *)i);

      if (ret) {
         cout << "Error:unable to create thread," << ret << endl;
         exit(-1);
      }
    }
    pthread_exit(NULL);


    return 0;
}
