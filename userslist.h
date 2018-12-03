#ifndef USERSLIST_H
#define USERSLIST_H
#include "user.cpp"
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <vector>
#include <Wt/WCompositeWidget.h>
#include <algorithm>

using std::vector;
using std::make_unique;
using namespace Wt;

namespace Wt {
  class WStackedWidget;
  class WAnchor;
}


class UsersList : public Wt::WContainerWidget {
public:
    UsersList(const vector<User*>, const std::function<void(const User*)> onUserClicked);

    void addUser(const User* newUser);
    void setUsers(const vector<User*>);


    void removeAllUsers();
private:
    vector<User*> _users;
    vector<Wt::WText*> texts;
    std::function<void(const User*)> callback;

    void renderList();
};


#endif // USERSLIST_H
