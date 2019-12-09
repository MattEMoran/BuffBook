#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

//The comment struct contains the username of the author of the comment, the content of the comment, and a timestamp.
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

//The post struct contains the text of the post, the number of likes it has, and an appropriate timestamp. It also has a vector containing comments on the post as well as pointers used for the BST of posts.
struct post
{
  string username;
  string text;
  int likes;
  time_t timestamp;
  vector<Comment> comments;
  post *earlier;
  post *later;
  post(string t, int l, time_t tm, string uname)
  {
    text = t;
    likes = l;
    timestamp = tm;
    username = uname;
  }
};

//The User class contains a username and password of each user on the network, as well as vectors containing their posts, pointers to their friends, pointers to the posts of their friends, and a pointer to the root post of the BST.
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
    root=NULL;
  }
  
  //The refreshFeed function is responsible for generating the BST when the user first logs in.
  //Insertion of each post from each friend of the user is handeled by using earlier and later pointers that are filled by comparing the timestamps of the to-be-inserted post and the current post.
  //After building the BST in O(nlogn) time and with O(n) space complexity, the traverse function is called.
  void refreshFeed()
  {
    deleteFeed(root);
    for(int i = 0; i < friends.size(); i++)
    {
      for(int j = 0; j < friends[i]->posts.size(); j++)
      {
        post *newP = new post(friends[i]->posts[j].text, 
        friends[i]->posts[j].likes, 
        friends[i]->posts[j].timestamp,
        friends[i]->posts[j].username);
        for(int i = 0; i < friends[i]->posts[j].comments.size();i++){
          newP->comments.at(i) = friends[i]->posts[j].comments.at(i);
        }
          
        if(root==NULL)
        {
          root = newP;
          root->earlier=NULL;
          root->later=NULL;
        } 
        else 
        {
        post *curr = root;
        post *parr = NULL;
        while(curr!=NULL){
          parr = curr;
          if(friends[i]->posts[j].timestamp < curr->timestamp)
          {
            curr = curr->later;
          } 
          else if (friends[i]->posts[j].timestamp > curr->timestamp)
          {
            curr = curr->earlier;
          }
          else
          {
            curr = curr->earlier;
          }
        }
          if(parr->timestamp > friends[i]->posts[j].timestamp){
            parr->later = newP;
            parr->earlier = NULL;
          } else {
            parr->earlier = newP;
            parr->later = NULL;
          }
        }
      }
    } 
    traverse(root);
  }

  //The traverse function takes in a pointer to a post as input.
  //The function recursively traverses through the BST of posts and adds them to the current user's feed, contained in a vector. 
  void traverse(post *node){ 
    if(node==NULL){
      return;
    }
      traverse(node->earlier);
      feed.push_back(node);
      traverse(node->later);     
  }
  
  //The addToFeed function takes in a post as input.
  //The function performs the same insertion algorithm as the refreshFeed function where earlier and later pointers are used to traverse the already built tree. The function compares the timestamps of the to-be-inserted post and the current post.
  void addToFeed(post p){
    post *newP = new post(p.text, p.likes, p.timestamp,p.username);
      for(int i = 0; i < p.comments.size();i++){
        newP->comments.at(i) = p.comments.at(i);
      }
        
      if(root==NULL)
      {
        root = newP;
        root->earlier=NULL;
        root->later=NULL;
      } 
      else 
      {
      post *curr = root;
      post *parr = NULL;
      while(curr!=NULL){
        parr = curr;
        if(newP->timestamp < curr->timestamp)
        {
          curr = curr->later;
        } 
        else if (newP->timestamp > curr->timestamp)
        {
          curr = curr->earlier;
        }
        else
        {
          curr = curr->earlier;
        }
      }
        if(parr->timestamp > newP->timestamp){
          parr->later = newP;
          parr->earlier = NULL;
        } else {
          parr->earlier = newP;
          parr->later = NULL;
        }
      }
    }

  //The deletedFeed function takes in a pointer to a post as input.
  //The function recursively traverses the tree and deletes each node.
  void deleteFeed(post *node){
    if(node==NULL){
      return;
    }
    deleteFeed(node->earlier);
    delete node;
    deleteFeed(node->later);
  }
  
  //The addFriend function takes in a user as input.
  //The function then pushes the address of the friend in memory to the friends vector of the current user
  void addFriend(User * u)
  {
    friends.push_back(u);
  }

  //The removeFriend function takes in a username as input.
  //The function then traverses the friends vector of the current user and removes that friend.
  void removeFriend(string username)
  {
    bool x = false;
    for(int i = 0; i < friends.size(); i++)
    {
      if(friends[i]->username == username)
      {
        friends.erase(friends.begin() + i);
        x = true;
      }
    }
    if (x == false)
      cout<<"User could not be found."<<endl;
  }

  //The addPost function takes in a string "text", an integer "likes", and a timestamp as input.
  //The function creates a new object of type post using the inputs provided and pushes it into the posts vector of the current user.
  void addPost(string text, int likes, time_t timestamp)
  {
    post p = post(text, likes, timestamp, this->username);
    posts.push_back(p);
  }

  //The addPost function takes in a string "text" as input.
  //The function creates a timestamp and then calls the alternative addPost function with the input provided. This function is used when no likes or timestamp are provided.
  void addPost(string text)
  {
    time_t timestamp;
    timestamp = time(NULL) - 25200;
    addPost(text, 0, timestamp);
  }

  //The commentOnPost fucntion takes in a string "text", a post "*p", and a timestamp as input.
  //The function creates a newComment of type Comment using the inputs provided. That comment is then pushed into the comments vector of the appropriate post.
  void commentOnPost(string text, post *p, time_t timestamp)
  {
    Comment newComment(text, username, timestamp);
    p->comments.push_back(newComment);
  }

  //The commentOnPost function takes in a string "text" and a post "*p" as input.
  //The function creates a timestamp and then calls the alternative commentOnPost function with the input provided. This function is used when no timestamp is provided.
  void commentOnPost(string text, post *p)
  {
    time_t timestamp = time(NULL) - 25200;
    commentOnPost(text, p, timestamp);
  }

  //The likePost function takes in a post p as input and increases the likes of that post by one.
  void likePost(post * p)
  {
    p->likes++;
  }

  //The displayFriendList function prints out the username of every user in the current user's friends vector.
  void displayFriendList()
  {
    cout<<"Friends:"<<endl;
    for(int i = 0 ; i < friends.size(); i++)
    {
      cout<<friends[i]->username<<endl; 
    }
  }

  //The printAllPosts function prints out the information of every post in the current user's posts vector.
  void printAllPosts()
  {
    cout<<"All Posts From: "<<username<<endl;
    for(int i = 0; i < posts.size(); i++)
    {
      cout<<posts[i].text<<endl<<"Posted: ";
      printTimeIntoWords(posts[i].timestamp);
      cout<<endl;
    }
  }

  //The printTimeIntoWords method takes in a timestamp "rawTime" and converts it into a usable string.
  void printTimeIntoWords(time_t rawTime)
  {
    char *timeString = ctime(&rawTime);
    cout<<timeString<<endl;
  }
};



//The BuffBook class contains a vector of all users within the network as well as a pointer to the currently logged in user.
class BuffBook
{
public:

  vector<User> users;
  User *curruser;

  BuffBook(string filename)
  {
    generateNetwork(filename); //call to the generateNetwork using a passed filename string
  }

  BuffBook(){} //Used for when no filename is passed

  //The displayFeedMenu function displays a list of options for the user to choose from. Each input redirects to appropriate functions in both the BuffBook and User classes.
  void displayFeedMenu()
  {
    cout<<"1. View your feed"<<endl;
    cout<<"2. View your friends list"<<endl;
    cout<<"3. Add a friend"<<endl;
    cout<<"4. Remove a friend"<<endl;
    cout<<"5. Write a post"<<endl;
    cout<<"6. View your posts"<<endl;
    cout<<"7. Log out"<<endl;
    int input = 0;
    while((input < 1) || (input > 7))
    {
      cin.clear();
      cin.ignore();
      cin>>input;
    }
    if(input == 1)
    {
      system("clear");
      for(int i = 0; i < curruser->feed.size(); i++){
        cout<<"Post "<<(i+1)<<endl;
        cout<<endl;
        printPost(*curruser->feed[i]); //Calls the printPost function for the ten most recent posts.
        cout<<endl;
      }
      postMenu(); 
    }

    if(input == 2)
    {
      system("clear");
      listFriends();
      cout<<endl;
    } 

    if(input == 3)
    {
      system("clear");
      cin.clear();
      cin.ignore();
      string user;
      cout<<"Enter a valid username: ";
      cin>>user;
      addFriend(user);
    }

    if(input == 4)
    {
      system("clear");
      cin.clear();
      cin.ignore();
      string username;
      cout<<"Enter a valid username: ";
      cin>>username;
      removeFriend(username);
    }

    if(input == 5)
    {
      system("clear");
      cin.clear();
      cin.ignore();
      string post;
      cout<<"Write your post here: ";
      getline(cin,post);
      curruser->addPost(post);
    }

    if(input == 6)
    {
      system("clear");
      curruser->printAllPosts();
      cout<<endl;
    }
    if(input == 7)
    {
      system("clear");
      shutdown();
    }
  };

  //The postMenu function is called when the user selects the "View feed" option from the feedMenu function.
  //The function displays a short list of functions used while navigating the user's feed.
  void postMenu(){
    cout<<"1. Go Back"<<endl;
    cout<<"2. Like a post"<<endl;
    cout<<"3. Shutdown"<<endl;
    int input = 0;
    while((input < 1) || (input > 3))
    {
      cin.clear();
      cin.ignore();
      cin>>input;
    }
    if(input==1){
      system("clear");
      displayFeedMenu();
    }
    if(input==2){
      int post = 0;    
      while((post - 1 < 0) || (post - 1 > curruser->feed.size())){
        cout<<"Which post are you liking?"<<endl;
        cin>>post;
      }
      curruser->likePost(curruser->feed.at(post - 1));
      system("clear");
      for(int i = 0; i < curruser->feed.size(); i++){
        cout<<"Post "<<(i+1)<<": "<<endl;
        printPost(*curruser->feed[i]); //Calls the printPost function for the ten most recent posts.
        cout<<endl;
      }
      postMenu();
    }
    if(input==3){
      system("clear");
      shutdown();
    }
  }

  //The addUser function takes in two strings - a username and a password - as input.
  //This utility function creates a newUser of type User using the inputs provided and then pushes the user into the vector of users for the BuffBook class.
  void addUser(string username, string password)
  {
    User newUser = User(username, password);
    users.push_back(newUser);
  }

  //The printUsers function iterates through the users vector and prints out each user's username.
  void printUsers()
  {
    cout<<"Users:"<<endl;
    for(int i = 0; i < users.size(); i++)
    {
      cout<<users[i].username<<endl;
    }
  }

  //The printPost function prints out the information associated with a post passed in as a pointer.
  //The function also iterates through the comments vector of the post and prints the information associated with each comment.
  void printPost(post p)
  {
    cout<<"@"<<p.username<<endl;
    cout<<p.text<<endl;
    cout<<p.likes<<" likes"<<endl;
    cout<<"Posted ";
    printTimeIntoWords(p.timestamp);
    for(int i = 0; i < p.comments.size();i++)
    {
      printTimeIntoWords(p.comments.at(i).timestamp);
      cout<<"     @"<<p.comments.at(i).username<<"   "<<p.comments.at(i).text<<endl;
    }
  }

  //The getUserIndexByUsername function takes in a string "username" as input.
  //The function iterates through the users vector until it finds the desired user.
  //The function returns the index of the found user. If the user isn't found, -1 is returned.
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
  
  //The addFriend function takes in a string "username" as input.
  //The function traverses the users vector until it finds the to-be-added friend. It then calls the addFriend function of the current user as well as the addToFeed function of the current user to add the user and their posts, respectively.
  void addFriend(string username2)
  {
    bool x = false;
    for (int j = 0; j < users.size(); j++)
    {
      if(users[j].username == username2)
      {     
        curruser->addFriend(&users[j]);
        x = true;
        if(users[j].posts.size()!=0){
            curruser->refreshFeed();
        }
        
      }
    }
    if(x==false)
      cout<<"User could not be found"<<endl;
  }

  //The removeFriend takes in a string "username" as input.
  //The function iterates once through the vector of users to find the current user and then the current user's friends vector to find the to-be-removed user. The removeFriend function of the current user is then called.
  void removeFriend(string username)
  {
    curruser->removeFriend(username);
  }
  
  //The listFriends function calls the displayFriendList method of the current user.
  void listFriends()
  {
     curruser->displayFriendList();
  }

  //The shutdown function declares that the program is shutting down, calls the deleteFeed method of the current user using the root of that user's BST of posts, and then quits.
  void shutdown()
  {
    //Close program
    cout<<"Shutting Down."<<endl;
    curruser->deleteFeed(curruser->root);
    exit(1);
  }

  //The listNetwork function lists all users and their friends within the network.
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
  
  //The login function prompts the user to input a valid username and password. If the username and password are validated, the current user pointer is set, the BST of posts for the user is created and the displayFeedMenu function is called.
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
    curruser->refreshFeed();
    while(true)
    {
      displayFeedMenu();
    }
  }

  //The printTimeIntoWords method takes in a timestamp "rawTime" and converts it into a usable string.
  void printTimeIntoWords(time_t rawTime)
  {
    char *timeString = ctime(&rawTime);
    cout<<timeString<<endl;
  }

  //FileFormat
  //Username|Password|Friend1,Friend2|P1Text~Likes~Timestamp~C1~Timestamp~Username~C2...|P2...
  void readfile(string filename)
  {
    ifstream filestream;
    filestream.open(filename);
    string line;
    while(filestream.good())
    {
      getline(filestream, line);

      if (line == "")
      {
        continue;
      }
      stringstream ss(line);

      string username;
      string password;

      getline(ss, username, '|');
      getline(ss, password, '|');

      User newUser(username, password);

      string temp;
      getline(ss, temp, '|'); //skips past the friends so they can be added on the second time through the loop

      while(getline(ss, temp, '|')) //iterates through all of the posts
      {
        stringstream ss2(temp);

        string postText;
        string postLikesString;
        string postTimestampString;

        getline(ss2, postText, '~');
        getline(ss2, postLikesString, '~');
        getline(ss2, postTimestampString, '~');

        post newPost = post(postText, stoi(postLikesString), stoi(postTimestampString), username);

        string commentText;
        string commentTimestampString;
        string commentUsername;
        int comments = 0;
        while(getline(ss2, commentText, '~'))
        {
          getline(ss2, commentTimestampString, '~');
          getline(ss2, commentUsername, '~');

          Comment newComment = Comment(commentText, commentUsername, stoi(commentTimestampString));
          newPost.comments.push_back(newComment);
        }
        newUser.posts.push_back(newPost);
      }
      users.push_back(newUser);
    }
    filestream.close();

    //Now read file again to add friend connections
    fstream filestream2;
    filestream2.open(filename);
    string line_;
    int lineCounter = 0;
    while(filestream2.good())
    {
      getline(filestream2, line_);
      //if(line == "") break;
      stringstream ss(line_);
      string temp; //Used to iterate through file;
      getline(ss, temp, '|');//sets temp to the username
      getline(ss, temp, '|');//sets temp to the password
      getline(ss, temp, '|');//sets temp to the list of friends usernames
      string usernameOfFriend;
      stringstream ss3(temp);
      while(getline(ss3, usernameOfFriend, ','))
      {
        int indexOfFriend = getUserIndexByUsername(usernameOfFriend);
        users.at(lineCounter).addFriend(&users.at(indexOfFriend));
      }
      lineCounter++;
    }
    filestream2.close();
  }

  void writeToFile(string filename)
  {
    ofstream outputfile;
    outputfile.open(filename);
    for(int i = 0; i < users.size(); i++)
    {
      outputfile<<users[i].username<<"|"<<users[i].password<<"|";

      for(int j = 0; j < users.at(i).friends.size(); j++)
      {
        if(j != 0)
        {
          outputfile<<",";
        }
        outputfile<<users[i].friends[j]->username;
      }
      cout<<users.at(i).posts.size()<<endl;
      for(int j = 0; j < users.at(i).posts.size(); j++)
      {
        outputfile<<"|"<<users[i].posts[j].text;
        outputfile<<"~"<<users[i].posts[j].likes;
        outputfile<<"~"<<users[i].posts[j].timestamp;

        for(int k = 0; k < users[i].posts[j].comments.size(); k++)
        {
          outputfile<<"~"<<users[i].posts[j].comments[k].text;
          outputfile<<"~"<<users[i].posts[j].comments[k].timestamp;
          outputfile<<"~"<<users[i].posts[j].comments[k].username;
        }
      }
      outputfile<<endl;
    }
  }
};

int main()
{ 
  BuffBook b = BuffBook();
  /*
  b.addUser("admin","1234");
  b.addUser("Mattie", "BigMoney");
  b.addUser("Mikey", "SmallMoney9");
  b.addUser("A", "A");
  b.users.at(1).addPost("Test post 2", 1, 1000000000);
  b.users.at(2).addPost("Test post 3", 1, 1000000000);
  b.users.at(2).addPost("Test post 4", 2, 10000000);
  */
  b.readfile("Database.txt");
  b.users[0].displayFriendList();
  //b.users.at(3).addFriend(&b.users.at(2));
  //b.users[2].addFriend(b.users[0]);
  //b.users[2].printAllPosts();
  //b.printPost(b.users[2].posts[0]);
  //b.printUsers();
  b.login();
};