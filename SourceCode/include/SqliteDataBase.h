#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H
#include <stdio.h>
#include <sqlite3.h>

class SqliteDataBase
{
    public:
        SqliteDataBase();
        ~SqliteDataBase();
        bool InsertRecord(char* sql);
        bool SelectRecord(char* sql);

        bool DeleteRecord(char* sql);
    protected:

    private:
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        char *sql;
        bool CreateTable(char* tblSchema);
        bool OpenDataBase();

};

#endif // SQLITEDATABASE_H
