#ifndef USER_H
#define USER_H
#include <Wt/Dbo/Dbo.h>
#include <string>

namespace dbo = Wt::Dbo;

class User {
public:

    template<class Action>
    void persist(Action& a) {
        dbo::field(a, _name,     "name");
    }

    User();

    User(const char *_name);
    User(const User *user);
    std::string name() const;
private:
    std::string _name;
};

#endif // USER_H
