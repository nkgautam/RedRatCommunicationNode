#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include "Blockchain.h"
#include "Socket.h"

using namespace std;

#define NUM_THREADS 1
#define PORTSERVER     9000
#define PORTCLIENT     9001

void *CommPort1(void *threadid) {
   long tid;
   tid = (long)threadid;

   UDPSocket sock1(PORTSERVER);
   Block block(1,"27/05/2019", "data1");
   std::string str = block.showBlock();
   sock1.SendDataGram(str.c_str(),str.length(),"localhost",PORTCLIENT);

   char str1[256] ={0};

   std::string sender = "localhost";
   unsigned short sport = PORTCLIENT;
   int ret = sock1.RecvDataGram(str1,256 ,sender,sport);
   if(ret > 0)
   {
        cout << "Ret : " << ret << endl;
        str1[ret] = '\0';
        cout << "RecvDataGram recev from client : " << str1 << endl;
            pthread_exit(NULL);
   }
   pthread_exit(NULL);

}

void *CommPort2(void *threadid) {
   long tid;
   tid = (long)threadid;

    UDPSocket sock1(PORTCLIENT);
    char str0[256] = {0};

    std::string sender = "localhost";
    unsigned short sport = PORTSERVER;

    int ret = sock1.RecvDataGram(str0,256 ,sender,sport);
    if (ret >  0)
    {
        cout << "Ret : " << ret << endl;
        str0[ret] = '\0';
        cout << "RecvDataGram recev from server : " << str0 << endl;
        string str3= "Thanks from clinet.";
        sock1.SendDataGram(str3.c_str(),str3.length(),"localhost",PORTSERVER);
        pthread_exit(NULL);
    }


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
      ret = pthread_create(&threads[i], NULL, CommPort2, (void *)i);


      if (ret) {
         cout << "Error:unable to create thread," << ret << endl;
         exit(-1);
      }
    }
    pthread_exit(NULL);

    return 0;
}
