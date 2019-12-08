#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

//struct Friend;

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
  string text;
  int likes;
  time_t timestamp;
  stack<Comment> comments;
  post *earlier;
  post *later;
  post(string t, int l, time_t tm)
  {
    text = t;
    l = likes;
    timestamp = tm;
  }
};

class User
{
public:
  string username;
  string password;
  vector<post> posts;
  vector<User*> friends;
  vector<post*> feed;
  post *root;
  User(string name, string password)
  {
    username = name;
    this->password = password;
  }
  
  void refreshFeed()
  {
    for(int i = 0; i < friends.size(); i++)
    {
      for(int j = 0; j < friends[i]->posts.size();j++)
      {
        if(root==NULL)
        {
          root = &friends[i]->posts[j];
          root->earlier=NULL;
          root->later=NULL;
        } 
        else 
        {
          post *curr = root;
          while(curr!=NULL){
            if(friends[i]->posts[j].timestamp > curr->timestamp)
            {
              curr = curr->later;
            } 
            else if (friends[i]->posts[j].timestamp < curr->timestamp)
            {
              curr = curr->earlier;
            }
            else
            {
              curr = curr->later;
            }
          }
          curr = &friends[i]->posts[j];
        }
      }
    }  
    traverse(root);
  }

  void traverse(post *node){
    if(node==NULL){
      return;
    }
    traverse(node->earlier);
    feed.push_back(node);
    traverse(node->later);
  }
  
  void addToFeed(post p){
    if(root==NULL)
        {
          root = &p;
          root->earlier=NULL;
          root->later=NULL;
        } 
        else 
        {
          post *curr = root;
          while(curr!=NULL){
            if(p.timestamp > curr->timestamp)
            {
              curr = curr->later;
            } 
            else if (p.timestamp < curr->timestamp)
            {
              curr = curr->earlier;
            }
            else
            {
              curr = curr->later;
            }
          }
          curr = &p;
        }
  }

  void deleteFeed(post *node){
    if(node==NULL){
      return;
    }
    deleteFeed(node->earlier);
    deleteFeed(node->later);
  }
  
  void addFriend(User u)
  {
    friends.push_back(&u);
  }

  void removeFriend(string username)
  {
    for(int i = 0; i < friends.size(); i++)
    {
      if(friends[i]->username == username)
      {
        friends.erase(friends.begin() + i);
      }
    }
  }

  void addPost(string text, int likes, time_t timestamp)
  {
    post p = post(text, likes, timestamp);
    posts.push_back(p);
    addToFeed(p);
  }

  void addPost(string text)
  {
    time_t timestamp;
    timestamp = time(NULL);
    addPost(text, 0, timestamp);
  }

  void commentOnPost(string text, post p, time_t timestamp)
  {
    Comment newComment(text, username, timestamp);
    p.comments.push(newComment);
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

  void displayFriendList()
  {
    cout<<"Friends:"<<endl;
    for(int i = 0 ; i < friends.size(); i++)
    {
      cout<<friends[i]->username<<endl; 
    }
  }

  void printAllPosts()
  {
    cout<<"All Post From "<<username<<endl;
    for(int i = 0; i < posts.size(); i++)
    {
      cout<<posts[i].text<<endl<<"timestamp: ";
      printTimeIntoWords(posts[i].timestamp);
      cout<<endl<<endl;
    }
  }

  void printTimeIntoWords(time_t rawTime)
  {
    char *timeString = ctime(&rawTime);
    cout<<timeString<<endl;
  }
};




class BuffBook
{
public:

  vector<User> users;
  User *curruser;

  BuffBook(string filename)
  {
    generateNetwork(filename);
  }

  BuffBook(){}

  void displayFeedMenu()
    {
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
        cin>>input;
      }
      if(input == 1)
      {
        displayFeed();
        for(int i = 0; i < 10; i++){
          printPost(curruser->feed.at(i));
        }
      }

      if(input == 2)
      {
        addFriend("Mattie");
        listFriends();
      } 

      if(input == 3)
      {
        cin.clear();
        cin.ignore();
        string user;
        cout<<"Enter a valid username: ";
        cin>>user;
        addFriend(user);
      }

      if(input == 4)
      {
        cin.clear();
        cin.ignore();
        string username;
        cout<<"Enter a valid username: ";
        cin>>username;
        removeFriend(username);
      }

      if(input == 5)
      {
        cin.clear();
        cin.ignore();
        string post;
        cout<<"Write your post here: ";
        cin>>post;
        curruser->addPost(post);
      }

      if(input == 6)
      {
        shutdown();
      }
    };

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
      cout<<users[i].username<<endl;
    }
  }

  void printPost(post *p)
  {
    cout<<p->text<<endl;
    cout<<"Likes: "<<p->likes<<endl;
    cout<<p->timestamp<<endl;
    for(int i = 0; i < p->comments.size();i++)
    {
      //cout<<"@"<<p->comments.at(i).username<<p->comments.at(i).text<<endl;
    }
  }

  int getUserIndexByUsername(string username)
  {
    for(int i = 0; i < users.size(); i++)
    {
      if(users[i].username == username)
      {
        return i;
      }
    }
    return -1;
  }

  void displayFeed()
  {
    curruser->refreshFeed();
  }
  
  void addFriend(string username2)
  {
    //Add friend for current user
    for (int i = 0; i < users.size(); i++){
      if (users[i].username == curruser->username){
        for (int j = 0; j < users.size(); j++){
          if(users[j].username == username2){     
            curruser->addFriend(users[j]);
            for(int k = 0; k < users[j].posts.size();k++){
              curruser->addToFeed(users[j].posts[k]);
            }
          }
        }
      }
    }
  }

  void removeFriend(string username)
  {
    //Remove friend from current user's friend list
    for (int i = 0; i < users.size(); i++){
      if (users[i].username == curruser->username){
        for (int j = 0; j < users[i].friends.size(); j++){
          if(users[j].username == username){
            curruser->removeFriend(users[j].username);
          }
        }
      }
    }
  }

  void listFriends()
  {
     curruser->displayFriendList();
  }

  

  void shutdown()
  {
    //Close program
    cout<<"Shutting Down."<<endl;
    exit(1);
  }

  //Utility Functions that can be used only by admin//

  void listNetwork()
  {
    //List all users and their friends
    for(int i = 0; i < users.size(); i++){
      cout<<"User: "<<users[i].username<<endl;
      cout<<"   Friends: ";
      for(int j = 0; j < users[i].friends.size(); j++){
        cout<<users[i].friends[j]->username<<" ";
      }
      cout<<endl;
    }
  }

  void generateNetwork(string filename)
  {
    //Generate network of users and posts
    //...//
  }

  void vectorize(post *node)
  {
    
  }
  
  void login()
  {
    //Enter a valid username and password
    string user;
    string pass;
    bool check = false;
    int ind = -1;
    while(check == false)
    {
      cout<<"Enter a valid username: ";
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
      cout<<"Enter a valid password: ";
      cin>>pass;
      if(users[ind].password == pass){
        check = true;
      }
      cin.clear();
    }
    curruser = &users[ind];
    cout<<"Welcome to Buff Book!"<<endl;
    while(true)
    {
      displayFeedMenu();
    }
  }

  void printTimeIntoWords(time_t rawTime)
  {
    char *timeString = ctime(&rawTime);
    cout<<timeString<<endl;
  }
};

/*struct Friend
{
  User *u;
};*/

int main()
{ 
  BuffBook b("Database.txt");
  b.addUser("Mattie", "BigMoney");
  b.addUser("Mikey", "SmallMoney9");
  b.addUser("PhatBoi", "SmallPeen");
  b.users[1].addFriend(b.users[0]);
  b.users[0].addFriend(b.users[1]);
  b.users[2].addFriend(b.users[1]);
  b.users[2].addFriend(b.users[0]);
  b.users[2].removeFriend("Mikey");
  b.users[1].addPost("Howdy yall!", 2, 1000000000);
  b.users[1].addPost("Whats Up Pimps And Players");
  b.users[1].printAllPosts();
  b.printUsers();
  b.login();
};