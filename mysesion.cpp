#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>
#include <Wt/Dbo/backend/Sqlite3.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/WApplication.h>
#include <Wt/WLogger.h>
#include "user.h"
#include <vector>

using namespace Wt;
namespace dbo = Wt::Dbo;
typedef dbo::ptr<User> User_ptr;
typedef dbo::collection<User_ptr> Users;

class DBSession {
public:
    DBSession(){
      auto sqlite3 = std::make_unique<Dbo::backend::Sqlite3>
              (WApplication::instance()->appRoot() + "hangman.db");
      sqlite3->setProperty("show-queries", "true");
      session_.setConnection(std::move(sqlite3));

      session_.mapClass<User>("user");

      dbo::Transaction transaction(session_);
      try {
        session_.createTables();
        log("info") << "Database created";
      } catch (...) {
        log("info") << "Using existing database";
      }

      transaction.commit();
    }

    ~DBSession()
    {}

    std::vector<User*> allUsers() const {
        std::vector <User*> result;
        dbo::Transaction transaction{session_};
        Users users = session_.find<User>();
        for (const dbo::ptr<User> &user : users){
            result.push_back(new User(user.get()));
        }
        return result;
    }

    void removeUser(const User* user){
       dbo::Transaction transaction{session_};
       User_ptr userToDelete =
               session_.find<User>().where("name = ?").bind(user->name());
       userToDelete.remove();
    }

    void addUser(const User* newUser){
        dbo::Transaction transaction{session_};

        std::unique_ptr<User> user{new User(newUser)};
        session_.add(std::move(user));
        transaction.commit();
    }

private:
    mutable dbo::Session session_;
};
