#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>

#include "mysesion.cpp"
#include "userslist.cpp"

//auto fakeData(){
//    std::vector <User*> users;


//    User user("name");
//    users.push_back(new User("first user"));
//    users.push_back(new User("second user"));
//    return users;
//}

class HelloApplication : public Wt::WApplication {
public:
    HelloApplication(const Wt::WEnvironment& env);
    void initDb();

private:
    Wt::WLineEdit *nameEdit_;
    Wt::WText *greeting_;
    UsersList *list;
    DBSession session_;
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("Hello world");

    root()->addWidget(std::make_unique<Wt::WText>("Your name, please? "));
    nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    Wt::WPushButton *button = root()->addWidget(std::make_unique<Wt::WPushButton>("Add me."));
    root()->addWidget(std::make_unique<Wt::WBreak>());
    greeting_ = root()->addWidget(std::make_unique<Wt::WText>("List of all users: "));
    root()->addWidget(std::make_unique<Wt::WBreak>());

    auto fake = session_.allUsers();

    list = root()->addWidget(
                std::make_unique<UsersList>(fake,
                                            [this](const User* clickedUser)
    {
        session_.removeUser(clickedUser);
        list->removeAllUsers();
        for (const User *user : session_.allUsers()){
            list->addUser(user);
            std::cerr << " user " << user->name();
        }
   }));

    auto greetCallback = [this]{
        const User *newUser = new User(nameEdit_->text().toUTF8().c_str());
        list->addUser(newUser);
        session_.addUser(newUser);
    };

    button->clicked().connect(greetCallback);
}

int main(int argc, char **argv){
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
      return std::make_unique<HelloApplication>(env);
    });
}
