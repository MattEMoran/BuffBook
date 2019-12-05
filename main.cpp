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
  stack<string> comments;
  post(string t, int l, string tm)
  {
    title = t;
    l = likes;
    timestamp = tm;
  }
};

struct Friend
{
  user *u;
}

class User
{
 string username;
 string password;
 stack <post> stream;
 vector <Friend> friends;
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
    /*for (int i = 0; i < users.size(); i++){
      if (users[i].username == curruser.username){
        for (int j = 0; j < users.size(); j++){
          if(users[j].username == username){
            Friend temp;
            temp.u = &users[j];
            users[i].friends.push_back(temp);
          }
        }
      }
    }*/
  }

  void removeFriend(string username){
    //Remove friend from current user's friend list
    /*for (int i = 0; i < users.size(); i++){
      if (users[i].username == curruser.username){
        for (int j = 0; j < users[i].friends.size(); j++){
          if(users[i].friends.username == username){
            Friend temp;
            temp = users[i].
          }
        }
      }
    }*/
  }

  void writePost(){
    //Create post for current user
    /*cin.clear();
    cin.ignore();
    string postText;
    cout<<"Write your post here: ";
    cin>>postText;
    string tm = "";
    post p(postText,0,tm);
    curruser.stream.push(p);*/
  }

  void listFriends(){
    //List current user's friends
    /*cout<<"Friends: ";
    for(int i = 0; i < curruser.friends.size();i++){
      cout<<curruser.friends[i].username<<" ";
    }
    cout<<endl;*/
  }

  void commentOnPost(post *p){
    //Adds comment to post
    /*cin.clear();
    cin.ignore();
    string comment;
    cout<<"Write your comment here: "<<endl;
    cin>>comment;
    p.comments.push(comment);*/
  }

  void likePost(post *p){
    //Increase likes on particular post
    //p.likes++;
  }

  //Utility Functions that can be used only by admin//

  void shutDown(){
    //Save new information to file
    /*cout<<"Shutting Down."<<endl;
    exit(1);*/
  }

  void listNetwork(){
    //List all users and their friends
    /*for(int i = 0; i < users.size(); i++){
      cout<<"User: "<<users[i].username<<endl;
      cout<<"   Friends: ";
      for(int j = 0; j < users[i].friends.size; j++){
        cout<<users[i].friends[j].username<<" ";
      }
      cout<<endl;
    }*/
  }

  void generateNetwork(string filename){
    //Generate network of users and posts
  }

  void login{
    //Enter a valid username and password
    /*string user;
    string pass;
    cin.clear();
    cin.ignore();
    bool check = false;
    int ind = -1;
    while(check == false){
      cout<<"Enter a valid username: "<<endl;
      cin>>user;
      for(int i = 0;i < users.size();i++){
        if(users[i].username == user){
          check = true;
          ind = i;
        }
      }
      cin.clear();
    }
    check = false;
    while(check==false){
      cout<<"Enter a valid username: "<<endl;
      cin>>user;
      if(users[ind].password == pass){
        check = true;
      }
      cin.clear();
      cout<<"Welcome to Buff Book!"<<endl;
    }*/
    
  }
}

int main() {
  BuffBook b(Database.txt);
}