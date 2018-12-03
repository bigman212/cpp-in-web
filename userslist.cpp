#include "userslist.h"

UsersList::UsersList(
        const vector<User*> users,
        const std::function<void(const User *)> onUserClicked)
    : Wt::WContainerWidget(), _users(std::move(users))
{
    renderList();
    this->callback = onUserClicked;
}

void UsersList::addUser(const User *newUser){
    this->addWidget(make_unique<Wt::WText>(newUser->name()));
    this->addWidget(make_unique<Wt::WBreak>());
    _users.push_back(new User(newUser));
}

void UsersList::removeAllUsers(){
    _users.clear();
    clear();
}

void UsersList::setUsers(const vector<User *> newUsers){
    _users.clear();
    _users = std::move(newUsers);
    renderList();
}

void UsersList::renderList(){
    clear();
    std::for_each(_users.begin(), _users.end(), [=](User *user){
        Wt::WText *t = this->addWidget(make_unique<Wt::WText>(user->name()));
        this->addWidget(make_unique<Wt::WBreak>());

        t->clicked().connect([=]{
            callback(user);
        });

        this->texts.push_back(t);
    });
}
