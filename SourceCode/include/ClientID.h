#ifndef CLIENTID_H
#define CLIENTID_H

#include <string>

using namespace std;

class ClientID
{
    public:
        ClientID();
        string CreateID();
        string GetID();

    protected:

    private:
     string GetRandomDigit();
     int Random(int min, int max);
     string id = "000-000-000";
     string GetString(char x);
};

#endif // CLIENTID_H
