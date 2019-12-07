#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

struct Comment
{
  string username;
  string text;
  time_t timestamp;
  Comment(string text, string username, time_t timestamp)
  {
    this->text = text;
    this->username = username;
    this->timestamp = timestamp;
  }
};

struct post
{
  string title;
  int likes;
  time_t timestamp;
  stack<Comment> comments;
  post *earlier;
  post *later;
  post(string t, int l, time_t tm)
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
/*
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
*/

class User
{
public:
  string username;
  string password;
  vector<post> posts;
  vector<*User> friends;
  post *root;
  User(string name, string password)
  {
    username = name;
    this->password = password;
  }
  
  void refreshFeed()
  {
    deleteFeed(root);
    for(int i = 0; i < friends.size(); i++)
    {
      for(int j = 0; j < friends[i]->posts.size();j++)
      {
        if(root==NULL)
        {
          root = friends[i]->posts[j];
          root->earlier=NULL;
          root->later=NULL;
        } 
        else 
        {
          post *curr = root;
          while(curr!=NULL){
            if(difftime(friends[i]->posts[j].timestamp,curr.timestamp) < 0)
            {
              curr = curr->later;
            } 
            else 
            {
              curr = curr->earlier;
            }
          }
          curr = friends[i]->posts[j];
        }
      }
    }
    printPost(root);
    //BST for you to integrate Matt, i think you should make a BST sorted off timestamps
    //loop through all of the friends and add their posts to the BST in the correct order
    //then to inorder traversal after you went through all of the friends and post the things and info
  }

  void printPost(post *node)
  {
    if(node==NULL){
      return;
    }
    printPost(node->later);
    cout<<node->title<<endl;
    cout<<"Likes: "<<node->likes<<endl;
    cout<<"Posted: "<<node->timestamp<<endl;
    //Comments need to be printed//
    printPost(node->earlier);
  }

  post* latestPost(post *node)
  {
    while(node->left != NULL){
      node = node->left;
    }
    return node;
  }

  void deleteFeed(post *node){
    if(node==NULL){
      return;
    }
    deleteFeed(node->left);
    deleteFeed(node->right);
  }

  void addFriend(User newFriend)
  {
    friends.push_back(&newFriend);
  }

  void removeFriend(string username)
  {
    for(int i = 0; i < friends.size(); i++)
    {
      if(friends[i].username == username)
      {
        friends.erase(friends.begin() + i);
      }
    }
  }

  void addPost(string text, int likes, time_t timestamp)
  {
    post p = new post(text, likes, timestamp);
    posts.push_back(p);
  }

  void addPost(string text)
  {
    time_t timestamp;
    timestamp = time(NULL);
    addPost(text, 0, timestamp);
  }

  void displayFriendList()
  {
    cout<<"Friends:"<<endl;
    for(int i = 0 ; i < friends.size(); i++)
    {
      cout<<friends[i]->username<<endl;
    }
  }

  void commentOnPost(string text, post p, time_t timestamp)
  {
    Comment newComment = Comment(text, username, timestamp);
    p.comments.push_back(newComment);
  }

  void commentOnPost(string text, post p)
  {
    time_t timestamp = time(NULL);
    commentOnPost(text, p, timestamp);
  }

  void likePost(post p)
  {
    p.likes++;
  }

};




class BuffBook
{
  vector<User> users;
  User *curruser;

public:

  BuffBook(string filename)
  {
    generateNetwork(filename);
  }

  BuffBook(){}

  void displayFeedMenu()
    {
      cout<<"Welcome to Buff Book!"<<endl;
      cout<<"1. View your feed"<<endl;
      cout<<"2. View your friends list"<<endl;
      cout<<"3. Add a friend"<<endl;
      cout<<"4. Remove a friend"<<endl;
      cout<<"5. Write a post"<<endl;
      cout<<"6. Log out"<<endl;
      int input = 0;
      while((input < 1) || (input > 6))
      {
        cin.clear();
        cin.ignore();
        cin<<input;
      }

      if(input==1)
      {
        displayFeed();
        //...//
      }

      if(input==2)
      {
        listFriends(curruser.username);
      }

      if(input==3)
      {
        cin.clear();
        cin.ignore();
        string user;
        cout<<"Enter a valid username: "<<endl;
        cin>>user;
        addFriend(user);
      }

      if(input==4)
      {
        cin.clear();
        cin.ignore();
        string user;
        cout<<"Enter a valid username: "<<endl;
        cin>>user;
        removeFriend(username)
      }

      if(input==5)
      {
        cin.clear();
        cin.ignore();
        string post;
        cout<<"Write your post here: "<<endl;
        cin>>post;
        User::addPost(post);
      }

      if(input==6)
      {
        shutdown();
      }

    }

  void addUser(string username, string password)
  {
    User newUser = User(username, password);
    users.push_back(newUser);
  }

  void printUsers()
  {
    cout<<"Users:"<<endl;
    for(int i = 0; i < users.size(); i++)
    {
      cout<<users[i].username<<" Password: "<<users[i].password<<endl;
    }
  }

  vector<User> getUsers()
  {
    return users;
  }

  void displayFeed()
  {
    curruser->refreshFeed();
  }

  void addFriend(string username2)
  {
    //Add friend for current user
    for (int i = 0; i < users.size(); i++){
      if (users[i].username == curruser.username){
        for (int j = 0; j < users.size(); j++){
          if(users[j].username == username){
            curruser->addFriend(users[j]);
          }
        }
      }
    }
  }

  void removeFriend(string username)
  {
    //Remove friend from current user's friend list
    for (int i = 0; i < users.size(); i++){
      if (users[i].username == curruser.username){
        for (int j = 0; j < users[i].friends.size(); j++){
          if(users[j].friends.username == username){
            curruser->addFriend(users[j]);
          }
        }
      }
    }
  }

  void listFriends()
  {
    //List current user's friends
    cout<<"Friends: ";
    for(int i = 0; i < curruser->friends.size();i++){
      cout<<curruser->friends[i].username<<" ";
    }
    cout<<endl;
  }

  void commentOnPost()
  {
    //Adds comment to post
    /*cin.clear();
    cin.ignore();
    string comment;
    cout<<"Write your comment here: "<<endl;
    cin>>comment;
    p.comments.push(comment);*/
  }

  void likePost()
  {
    //Increase likes on particular post
    //p.likes++;
  }

  //Utility Functions that can be used only by admin//

  void shutdown()
  {
    //Save new information to file
    /*cout<<"Shutting Down."<<endl;
    exit(1);*/
  }

  void listNetwork()
  {
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

  void generateNetwork(string filename)
  {
    //Generate network of users and posts
    //...//
    login();
  }

  void login
  {
    //Enter a valid username and password
    string user;
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
    }
    displayFeedMenu();
  }
};

int main()
{
  BuffBook b(Database.txt);
}