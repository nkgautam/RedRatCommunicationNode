#ifndef IDENTITY_H
#define IDENTITY_H
#include <string>

using namespace std;

class Identity
{
    public:
        Identity();
        bool CreateID();
        string GetID();
        bool CreateID(string username, string password);
        string GetID(string username);

    protected:

    private:
};

#endif // IDENTITY_H
