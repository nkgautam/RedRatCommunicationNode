#include <iostream>
#include <future>
#include <stdio.h>
#include <sqlite3.h>
#include "Blockchain.h"
#include "Socket.h"
#include "Chat.h"

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
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

    //Chat chat;
    //chat.Run();

    sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("test.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "CREATE TABLE NODEMSG("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "SENDER           TEXT    ," \
      "JSON            INT     NOT NULL," \
      "TIMESTAMP DATETIME DEFAULT CURRENT_TIMESTAMP );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(db);

    return 0;
}
