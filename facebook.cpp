#include <iostream>
#include <string>
using namespace std;


class Comment {
private:
    string commenterUsername;
    string text;

public:
    Comment() {
    }
    Comment(string commenter, string txt) {
        commenterUsername = commenter;
        text = txt;
    }

    void displayComment() {
        cout << commenterUsername << " : " << text << endl;
    }
};

class Post {
private:
    string content;
    string authorUsername;
    int likeCount;
    string* comments;
    int commentCount;

public:
    friend class User;
    Post() {
        likeCount = 0;
        commentCount = 0;
        comments = nullptr;
    }
    Post(string Content, string author, int likes, int commCount, string* comms) {
        content = Content;
        authorUsername = author;
        this->likeCount = likes;
        this->commentCount = commCount;

        if (commentCount > 0 && comms) {
            comments = new string[commentCount];
            for (int i = 0; i < commentCount; i++) {
                comments[i] = comms[i];
            }
        }
        else {
            comments = nullptr;
        }
    }

    Post(const Post& other) {
        content = other.content;
        authorUsername = other.authorUsername;
        likeCount = other.likeCount;
        commentCount = other.commentCount;

        if (other.comments && commentCount > 0) {
            comments = new string[commentCount];
            for (int i = 0; i < commentCount; i++) {
                comments[i] = other.comments[i];
            }
        }
        else {
            comments = nullptr;
        }
    }

    ~Post() {
        if (comments) {
            delete[] comments;
            comments = nullptr;
        }
    }

    void addLike() {
        likeCount++;
    }

    void addComment(string commentText) {
        string* newComments = new string[commentCount + 1];

        for (int i = 0; i < commentCount; i++) {
            newComments[i] = comments[i];
        }

        // Adding new comment at the end
        newComments[commentCount] = commentText;

        // Deleting old comment arrays
        if (comments) {
            delete[] comments;
        }

        comments = newComments;
        commentCount++;
    }

    void displayPost() {
        cout << " UserName : " << authorUsername << endl;
        cout << "  Post : " << content << endl;
        cout << " Liked by Aiman and " << likeCount << " others. " << endl;
        cout << " Comments: " << commentCount << endl;
        for (int i = 0; i < commentCount; i++) {
            cout << comments[i] << endl;
        }
    }

    void addComment(string commenterUsername, string comment) {
        string formattedComment = commenterUsername + ": " + comment;
        addComment(formattedComment);
    }

};

class Friend {
private:
    string username;
    string* displayNames;
    int fCount;

public:
    Friend() {
        displayNames = nullptr;
        fCount = 0;
    }

    Friend(string uname, string* frname, int frenCount) {
        fCount = frenCount;
        username = uname;

        displayNames = new string[fCount];
        for (int i = 0; i < fCount; i++) {
            displayNames[i] = frname[i];
        }
    }

    Friend(const Friend& other) {
        fCount = other.fCount;
        username = other.username;

        displayNames = new string[fCount];
        for (int i = 0; i < fCount; i++) {
            displayNames[i] = other.displayNames[i];
        }
    }

    ~Friend() {
        if (displayNames) {
            delete[] displayNames;
            displayNames = nullptr;
        }
    }

    void setUsername(string uname) {
        username = uname;
    }

    void showFriend() {
        cout << username << " has " << fCount << " friends:  " << endl;
        for (int i = 0; i < fCount; i++) {
            cout << displayNames[i] << endl;
        }
    }
};

class FriendRequest {
private:
    string sender;
    string receiver;
    bool accepted;

public:
    FriendRequest() {
        accepted = false;
    }

    FriendRequest(string from, string to) {
        sender = from;
        receiver = to;
        accepted = false;
    }

    FriendRequest(const FriendRequest& other) {
        sender = other.sender;
        receiver = other.receiver;
        accepted = other.accepted;
    }

    string getSender() {
        return sender;
    }

    void accept() {
        accepted = true;
    }

    void reject() {
        accepted = false;
    }

    bool isAccepted() const {
        return accepted;
    }

    void display() const {
        cout << " Friend request from : " << sender << " to " << receiver << endl;
        cout << " Status : " << (isAccepted() ? "Accepted" : "Pending") << endl;
    }
};

class User {
private:
    string username;
    string password;
    string fullName;

    Friend** friends;
    int friendCount;

    Post** timeline;
    int postCount;

    FriendRequest** pendingRequests;
    int pendingRequestCount;

public:
    // Default Constructor
    User() {
        friends = nullptr;
        friendCount = 0;
        timeline = nullptr;
        postCount = 0;
        pendingRequests = nullptr;
        pendingRequestCount = 0;
    }

    // Parameterized Constructor
    User(string uname, string pwd, string name, Friend** frnds, int fCount, Post** posts, int pCount, FriendRequest** reqs, int reqCount) {
        username = uname;
        password = pwd;
        fullName = name;

        // Friends
        friendCount = fCount;
        if (fCount > 0 && frnds) {
            friends = new Friend * [friendCount];
            for (int i = 0; i < friendCount; i++) {
                friends[i] = new Friend(*frnds[i]);
            }
        }
        else {
            friends = nullptr;
        }

        // Timeline
        postCount = pCount;
        if (pCount > 0 && posts) {
            timeline = new Post * [postCount];
            for (int i = 0; i < postCount; i++) {
                timeline[i] = new Post(*posts[i]);
            }
        }
        else {
            timeline = nullptr;
        }

        // Friend Requests
        pendingRequestCount = reqCount;
        if (reqCount > 0 && reqs) {
            pendingRequests = new FriendRequest * [pendingRequestCount];
            for (int i = 0; i < pendingRequestCount; i++) {
                pendingRequests[i] = new FriendRequest(*reqs[i]);
            }
        }
        else {
            pendingRequests = nullptr;
        }
    }

    // Copy Constructor
    User(const User& other) {
        username = other.username;
        password = other.password;
        fullName = other.fullName;

        // Friends
        friendCount = other.friendCount;
        if (friendCount > 0) {
            friends = new Friend * [friendCount];
            for (int i = 0; i < friendCount; i++) {
                friends[i] = new Friend(*other.friends[i]);
            }
        }
        else {
            friends = nullptr;
        }

        // Timeline
        postCount = other.postCount;
        if (postCount > 0) {
            timeline = new Post * [postCount];
            for (int i = 0; i < postCount; i++) {
                timeline[i] = new Post(*other.timeline[i]);
            }
        }
        else {
            timeline = nullptr;
        }

        // Requests
        pendingRequestCount = other.pendingRequestCount;
        if (pendingRequestCount > 0) {
            pendingRequests = new FriendRequest * [pendingRequestCount];
            for (int i = 0; i < pendingRequestCount; i++) {
                pendingRequests[i] = new FriendRequest(*other.pendingRequests[i]);
            }
        }
        else {
            pendingRequests = nullptr;
        }
    }

    // Destructor
    ~User() {
        if (friends) {
            for (int i = 0; i < friendCount; i++) {
                delete friends[i];
            }
            delete[] friends;
        }

        if (timeline) {
            for (int i = 0; i < postCount; i++) {
                delete timeline[i];
            }
            delete[] timeline;
        }

        if (pendingRequests) {
            for (int i = 0; i < pendingRequestCount; i++) {
                delete pendingRequests[i];
            }
            delete[] pendingRequests;
        }
    }

    // Login
    bool login(string uname, string pwd) {
        return (username == uname && password == pwd);
    }

    // Posting
    void postStatus(string content) {
        Post* newPost = new Post(content, username, 0, 0, nullptr);
        Post** newTimeline = new Post * [postCount + 1];

        for (int i = 0; i < postCount; i++) {
            newTimeline[i] = timeline[i];
        }

        newTimeline[postCount] = newPost;

        if (timeline) {
            delete[] timeline;
        }

        timeline = newTimeline;
        postCount++;
    }

    // Sending and Receiving Requests
    void sendRequest(User* other) {
        FriendRequest* req = new FriendRequest(username, other->getUsername());
        other->receiveRequest(req);
    }

    void receiveRequest(FriendRequest* request) {
        FriendRequest** newRequests = new FriendRequest * [pendingRequestCount + 1];

        for (int i = 0; i < pendingRequestCount; i++) {
            newRequests[i] = pendingRequests[i];
        }

        newRequests[pendingRequestCount] = request;

        if (pendingRequests) {
            delete[] pendingRequests;
        }

        pendingRequests = newRequests;
        pendingRequestCount++;
    }

    void acceptRequest(int requestIndex) {
        if (requestIndex < 0 || requestIndex >= pendingRequestCount) {
            cout << "Invalid request index." << endl;
            return;
        }

        pendingRequests[requestIndex]->accept();

        // Extract sender username for new friend
        string senderUsername = pendingRequests[requestIndex]->getSender();

        // Create empty friend list for the new friend
        string* emptyList = nullptr;
        Friend* newFriend = new Friend(senderUsername, emptyList, 0);

        // Add to friend list
        Friend** newFriendList = new Friend * [friendCount + 1];
        for (int i = 0; i < friendCount; i++) {
            newFriendList[i] = friends[i];
        }
        newFriendList[friendCount] = newFriend;

        if (friends) {
            delete[] friends;
        }

        friends = newFriendList;
        friendCount++;
    }

    // Show Functions
    void showFriends() {
        cout << "Friends of " << username << " (" << friendCount << "):" << endl;
        for (int i = 0; i < friendCount; i++) {
            friends[i]->showFriend();
        }
    }

    void showTimeline() {
        cout << "Timeline of " << username << " (" << postCount << " posts):" << endl;
        for (int i = 0; i < postCount; i++) {
            cout << "Post #" << i << ":" << endl;
            timeline[i]->displayPost();
            cout << endl;
        }
    }

    void showPendingRequests() {
        cout << "Pending Friend Requests (" << pendingRequestCount << "):" << endl;
        for (int i = 0; i < pendingRequestCount; i++) {
            cout << "Request #" << i << ":" << endl;
            pendingRequests[i]->display();
        }
    }

    // Like & Comment
    void likePost(int postIndex) {
        if (postIndex >= 0 && postIndex < postCount) {
            timeline[postIndex]->addLike();
            cout << "Post liked!" << endl;
        }
        else {
            cout << "Invalid post index!" << endl;
        }
    }

    void commentOnPost(int postIndex, string comment) {
        if (postIndex >= 0 && postIndex < postCount) {
            timeline[postIndex]->addComment(comment);
            cout << "Comment added!" << endl;
        }
        else {
            cout << "Invalid post index!" << endl;
        }
    }

    // setter
    void setUsername(string newUsername) {
        username = newUsername;
    }

    // Getter
    string getUsername() {
        return username;
    }

    // Display
    void displayUser() {
        cout << "=== User Profile ===" << endl;
        cout << "Username: " << username << endl;
        cout << "Full Name: " << fullName << endl;
        cout << endl;
        showFriends();
        cout << endl;
        showTimeline();
    }
    Post* getPost(int index) {
        if (index >= 0 && index < postCount) {
            return timeline[index];
        }
        return nullptr;
    }

    void addFriend(string friendUsername) {
        // Create a new Friend object
        string* emptyList = nullptr;
        Friend* newFriend = new Friend(friendUsername, emptyList, 0);

        // Add to friend list
        Friend** newFriendList = new Friend * [friendCount + 1];
        for (int i = 0; i < friendCount; i++) {
            newFriendList[i] = friends[i];
        }
        newFriendList[friendCount] = newFriend;

        if (friends) {
            delete[] friends;
        }

        friends = newFriendList;
        friendCount++;
    }
};

class NewsFeed {
private:
    Post** postsFromFriends;
    int totalPosts;

public:
    NewsFeed() {
        postsFromFriends = nullptr;
        totalPosts = 0;
    }

    ~NewsFeed() {
        if (postsFromFriends) {
            for (int i = 0; i < totalPosts; i++) {
                delete postsFromFriends[i];
            }
            delete[] postsFromFriends;
        }
    }

    void generateFeed(User* currentUser) {
        // This would collect posts from friends in a real implementation
        cout << "Generating news feed for " << currentUser->getUsername() << endl;
    }

    void showFeed() {
        cout << "=== News Feed ===" << endl;
        for (int i = 0; i < totalPosts; i++) {
            postsFromFriends[i]->displayPost();
            cout << endl;
        }
    }
};

// --------- Class: Admin (inherits from User) ---------
class Admin : public User {
private:
    string adminID;
    string secretCode;

public:
    Admin() : User() {
    }

    Admin(string uname, string pwd, string name, string id, string code)
        : User(uname, pwd, name, nullptr, 0, nullptr, 0, nullptr, 0) {
        adminID = id;
        secretCode = code;
    }

    void deleteUser(User**& users, int& userCount, string username) {
        int indexToDelete = -1;

        // Find the user
        for (int i = 0; i < userCount; i++) {
            if (users[i]->getUsername() == username) {
                indexToDelete = i;
                break;
            }
        }

        if (indexToDelete == -1) {
            cout << "User not found." << endl;
            return;
        }

        // Delete the user
        User** newUsers = new User * [userCount - 1];

        int j = 0;
        for (int i = 0; i < userCount; i++) {
            if (i != indexToDelete) {
                newUsers[j++] = users[i];
            }
            else {
                delete users[i]; // Free memory of deleted user
            }
        }

        delete[] users;
        users = newUsers;
        userCount--;

        cout << "User deleted successfully." << endl;
    }

    void showAdminMenu() {
        cout << "=== Admin Menu ===" << endl;
        cout << "1. Delete User" << endl;
        cout << "2. View All Users" << endl;
        cout << "3. Logout" << endl;
    }
};

// --------- Class: Facebook (manager class) ---------
class Facebook {
private:
    User** users;
    int userCount;
    Admin* admin;

public:
    Facebook() {
        users = nullptr;
        userCount = 0;
        admin = new Admin("admin", "admin123", "System Admin", "ADMIN001", "secret123");

        // Create post content for Aiman
        string* aimanComments1 = new string[1];
        aimanComments1[0] = "Fizza: Love this post!";

        string* aimanComments2 = new string[1];
        aimanComments2[0] = "Fizza: Amazing photo!";

        Post** aimanPosts = new Post * [2];
        aimanPosts[0] = new Post("Hello everyone!", "Aiman", 3, 1, aimanComments1);
        aimanPosts[1] = new Post("Beautiful day at the beach!", "Aiman", 5, 1, aimanComments2);

        // Create post content for Fizza
        string* fizzaComments1 = new string[1];
        fizzaComments1[0] = "Aiman: Welcome to Facebook!";

        string* fizzaComments2 = new string[1];
        fizzaComments2[0] = "Aiman: Nice picture!";

        Post** fizzaPosts = new Post * [2];
        fizzaPosts[0] = new Post("Happy to be here!", "Fizza", 2, 1, fizzaComments1);
        fizzaPosts[1] = new Post("Check out my new profile picture", "Fizza", 4, 1, fizzaComments2);

        // Create friend entries
        string* aimanFriendName = new string[1];
        aimanFriendName[0] = "Fizza Khalid";
        Friend* aimanFriend = new Friend("Aiman", aimanFriendName, 1);

        string* fizzaFriendName = new string[1];
        fizzaFriendName[0] = "Aiman Khalid";
        Friend* fizzaFriend = new Friend("Fizza", fizzaFriendName, 1);

        // Create array of friends for each user
        Friend** aimanFriends = new Friend * [1];
        aimanFriends[0] = fizzaFriend;

        Friend** fizzaFriends = new Friend * [1];
        fizzaFriends[0] = aimanFriend;

        // Create users with predefined friend lists and posts
        User* aimanUser = new User(
            "Aiman", "aiman1507", "Aiman Khalid",
            aimanFriends, 1,      // Friends 
            aimanPosts, 2,        // Posts
            nullptr, 0            // No pending requests
        );

        User* fizzaUser = new User(
            "Fizza", "fizza1507", "Fizza Khalid",
            fizzaFriends, 1,      // Friends
            fizzaPosts, 2,        // Posts
            nullptr, 0            // No pending requests
        );

        // Add both users to users array
        users = new User * [2];
        users[0] = aimanUser;
        users[1] = fizzaUser;
        userCount = 2;
    }
    // Now establish their friendship and add some posts

    ~Facebook() {
        if (users) {
            for (int i = 0; i < userCount; i++) {
                delete users[i];
            }
            delete[] users;
        }
        if (admin) {
            delete admin;
        }
    }

    void registerUser() {
        string username, password, fullName;

        cout << "=== User Registration ===" << endl;
        cout << "Enter username: ";
        cin.ignore();
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);
        cout << "Enter full name: ";
        getline(cin, fullName);


        // Normal user registration
        User* newUser = new User(username, password, fullName, nullptr, 0, nullptr, 0, nullptr, 0);

        // Add to users array
        User** newUsers = new User * [userCount + 1];
        for (int i = 0; i < userCount; i++) {
            newUsers[i] = users[i];
        }
        newUsers[userCount] = newUser;

        if (users) {
            delete[] users;
        }

        users = newUsers;
        userCount++;

        cout << "User registered successfully!" << endl;
    }

    User* loginUser() {
        string username, password;

        cout << "=== User Login ===" << endl;
        cout << "Enter username: ";
        cin.ignore(); // Clear input buffer
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);

        // Check admin login
        if (admin->login(username, password)) {
            cout << "Admin login successful!" << endl;
            return admin;
        }

        // Check regular users
        for (int i = 0; i < userCount; i++) {
            if (users[i]->login(username, password)) {
                cout << "Login successful!" << endl;
                return users[i];
            }
        }

        cout << "Invalid username or password!" << endl;
        return nullptr;
    }

    void showAllUsers() {
        cout << "=== All Users ===" << endl;
        for (int i = 0; i < userCount; i++) {
            cout << i + 1 << ". " << users[i]->getUsername() << endl;
        }
    }

    void menu() {
        int choice;
        User* currentUser = nullptr;

        do {
            cout << "\n=== Facebook Clone ===" << endl;
            cout << "1. Register" << endl;
            cout << "2. Login" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                registerUser();
                break;

            case 2:
                currentUser = loginUser();
                if (currentUser) {
                    userMenu(currentUser);
                }
                break;

            case 3:
                cout << "Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
            }
        } while (choice != 3);
    }

    void userMenu(User* user) {
        int choice;

        do {
            cout << "\n=== User Menu ===" << endl;
            cout << "1. View Profile" << endl;
            cout << "2. Post Status" << endl;
            cout << "3. View Timeline" << endl;
            cout << "4. View Friends" << endl;
            cout << "5. Send Friend Request" << endl;
            cout << "6. View Pending Requests" << endl;
            cout << "7. Accept Friend Request" << endl;
            cout << "8. Like Post" << endl;
            cout << "9. Comment on Post" << endl;
            cout << "10. View News Feed" << endl;
            cout << "11. Logout" << endl;
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                user->displayUser();
                break;
            }
            case 2: {
                string content;
                cout << "Enter your status: ";
                cin.ignore();
                getline(cin, content);
                user->postStatus(content);
                cout << "Status posted!" << endl;
                break;
            }
            case 3: {
                user->showTimeline();
                break;
            }
            case 4: {
                user->showFriends();
                break;
            }
            case 5: {
                showAllUsers();
                int userIndex;
                cout << "Enter user number to send request: ";
                cin >> userIndex;

                if (userIndex > 0 && userIndex <= userCount) {
                    user->sendRequest(users[userIndex - 1]);
                    cout << "Friend request sent!" << endl;
                }
                else {
                    cout << "Invalid user number!" << endl;
                }
                break;
            }
            case 6: {
                user->showPendingRequests();
                break;
            }
            case 7: {
                user->showPendingRequests();
                int requestIndex;
                cout << "Enter request number to accept: ";
                cin >> requestIndex;
                user->acceptRequest(requestIndex);
                break;
            }
            case 8: {
                user->showTimeline();
                int postIndex;
                cout << "Enter post number to like: ";
                cin >> postIndex;
                user->likePost(postIndex);
                break;
            }
            case 9: {
                user->showTimeline();
                int postIndex;
                string comment;
                cout << "Enter post number to comment on: ";
                cin >> postIndex;
                cout << "Enter your comment: ";
                cin.ignore();
                getline(cin, comment);
                user->commentOnPost(postIndex, comment);
                break;
            }
            case 10: {
                NewsFeed feed;
                feed.generateFeed(user);
                feed.showFeed();
                break;
            }
            case 11: {
                cout << "Logged out successfully!" << endl;
                break;
            }
            default: {
                cout << "Invalid choice!" << endl;
            }
            }
        } while (choice != 11);
    }

    // Create a special user for Fizza with Aiman as a friend

};


int main() {
    Facebook fb;
    fb.menu();

    return 0;
}


