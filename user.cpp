#include "user.h"
User::User()
{    }

User::User(const char *name){
    _name.assign(name);
}

User::User(const User *user){
    this->_name.assign(user->name());
}

std::string User::name() const {
    return _name;
}
