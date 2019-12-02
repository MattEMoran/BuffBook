#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct post{
  string title;
  int likes;
  string timestamp;
  vector<string> comments;
  post(string t, int l, string tm)
  {
    title = t;
    l = likes;
    timestamp = tm;
  }
};

class User
{
 string username;
 string password;
 stack <post> stream;
 vector <User> friends;
 User(string name, string password){
   username = name;
   password = password;
 }
 
};

class BuffBook{
  vector<User> users;
  User *curruser;
  private:
  BuffBook(string filename){
    generateNetwork(filename);
  }

  void refreshFeed(){
    //Display 10 most recent posts from all friends
  }

  void addFriend(string username){
    //Add friend for current user
  }

  void removeFriend(string username){
    //Remove friend from current user's friend list
  }

  void writePost(){
    //Create post for current user
    cin.clear();
    cin.ignore();
    string postText;
    cout<<"Write your post here: ";
    cin>>postText;
    string tm = "";
    post p(postText,0,tm);
    curruser.stream.push(p);
  }

  void listFriends(){
    //List current user's friends
    cout<<"Friends: ";
    for(int i = 0; i < curruser.friends.size();i++){
      cout<<curruser.friends[i].username<<" ";
    }
    cout<<endl;
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
    for(int i = 0; i < users.size(); i++){
      cout<<"User: "<<users[i].username<<endl;
      cout<<"   Friends: ";
      for(int j = 0; j < users[i].friends.size; j++){
        cout<<users[i].friends[j].username<<" ";
      }
      cout<<endl;
    }
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