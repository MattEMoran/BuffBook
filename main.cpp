#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct user
{
 string username;
 string password;
 vector<post> stream;
 vector<user> friends;
 user(string name, string password){
   username = name;
   password = password;
 }
}

struct post{
  string title;
  int likes;
  string timestamp;
  vector<string> comments;
  post(string t, int l, string tm){
    title = t;
    l = likes;
    timestamp = tm;
  }
}

class BuffBook{
  //Hash of usernames and passwords?
  private:
  BuffBook(string filename){
    generateNetwork(filename);
  }

  void refreshFeed(){
    //Display 10 most recent posts from all friends
  }

  void addFriend(){
    //Add friend for current user
  }

  void removeFriend(){
    //Remove friend from current user's friend list
  }

  void writePost(){
    //Create post for current user
  }

  void listFriends(){
    //List current user's friends
  }

  void commentOnPost(){
    //Adds comment to post
  }

  void likePost(){
    //Increase likes on particular post
  }

  //Utility Functions that can be used only by admin//

  void shutDown(){
    //Save new information to file
  }

  void listNetwork(){
    //List all users and their friends
  }

  void generateNetwork(string filename){
    //Generate network of users and posts
  }

  void login{
    //Enter a valid username and password
  }
}

int main() {
  BuffBook b(Database.txt);
}