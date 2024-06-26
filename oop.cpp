#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

const int maxitem = 10;//setting the size of arrays required for storing the menu of each user depending on their usertype
const int maxOrders = 90;


class User {
protected:
    string orderHistory[maxOrders];
    //int orderCount = 0;

private:
    int userID;
    string userName;
    int userPasscode;
    int userType;

public:
    // Default constructor
    User() : userID(0), userName("Admin"), userPasscode(2406), userType(0) {}

    User(int id, string name, int passcode, int type)
        : userID(id), userName(name), userPasscode(passcode), userType(type) {}

    int getuserID() const {
        return userID;
    }

    void setuserID(const int& ID) {
        userID = ID;
    }

    string getuserName() const {
        return userName;
    }

    void setuserName(const string& name) {
        userName = name;
    }

    int getuserPasscode() const {
        return userPasscode;
    }

    void setuserPasscode(const int& pswd) {
        userPasscode = pswd;
    }

    int getuserType() const {
        return userType;
    }

    void setuserType(const int& type) {
        userType = type;
    }

    void saveUserToFile() const {
        ofstream Userfile("UserFile.txt", ios::app);
        if (Userfile.is_open()) {
            Userfile << userID << " " << userPasscode << " " << userType << endl;
            Userfile.close();
        }
        else {
            cout << "Unable to open UserFile.txt" << endl;
        }
    }

    void Register() {
        cout << "For Registration of your account. Kindly fill the following credentials" << endl;
        cout << "Please enter your userID" << endl;
        cin >> userID;
        cout << "Please enter your username" << endl;
        cin >> userName;
        cout << "Please enter your password (Password must be 6 characters long)" << endl;
        cin >> userPasscode;
        while (true) {
            if (to_string(userPasscode).length() == 6) {
                break;
            }
            else {
                cout << "Invalid password format. Please enter a 6-digit password:" << endl;
                cin >> userPasscode;
            }
        }
        cout << "Please enter usertype (Faculty/nonfaculty/student)" << endl;
        cin >> userType;
        cout << "Your account is registered successfully" << endl;
        saveUserToFile();
    }

    void login()  const{
        int re_enteruser_id, re_enteruser_pass;
        cout << "Please re-enter your userId:";
        cin >> re_enteruser_id;
        cout << "Please re-enter your password :";
        cin >> re_enteruser_pass;
        if (userID == re_enteruser_id && userPasscode == re_enteruser_pass) {
            cout << "Login successful" << endl;
        }
        else {
            cout << "Login failed" << endl;
        }
    }

    void logout() {
        cout << "Logging out " << endl;
 //       if (userType == "faculty") {
 //           cout << "faculty user..." << endl;
 //       }
 //       else if (userType == "nonfaculty") {
 //           cout << "non-faculty user..." << endl;
 //       }
 //       else if (userType == "student") {
 //           cout << "student user..." << endl;
 //      }
        cout << "Logout successful." << endl;
    }
};


// Declaration of the Administrators class inheriting from User
class Administrators : public User {
public:
    Administrators() : User() {}

    void viewMenu() {
        ifstream menuFile("menu.txt");
        if (!menuFile.is_open()) {
            cout << "Error opening menu file!" << endl;
            return;
        }

        string menuItem;
        while (getline(menuFile, menuItem)) {
            cout << menuItem << endl;
        }

        menuFile.close();
    }

    void addMenuItem(const string& newItem) {
        ofstream menuFile("menu.txt", ios::app);
        if (!menuFile.is_open()) {
            cout << "Error opening menu file for writing!" << endl;
            return;
        }

        menuFile << newItem << endl;

        menuFile.close();
        cout << "Item added successfully!" << endl;
    }

    void viewOrderHistory() {
        ifstream orderFile("order_history.txt");
        if (!orderFile.is_open()) {
            cout << "No order history available." << endl;
            return;
        }

        string order;
        while (getline(orderFile, order)) {
            cout << order << endl;
        }

        orderFile.close();
    }

    void rateMenuItem(const string& itemName, int rating) {
        ofstream ratingFile("menu_ratings.txt", ios::app);
        if (!ratingFile.is_open()) {
            cout << "Error opening rating file for writing!" << endl;
            return;
        }

        ratingFile << itemName << ": " << rating << endl;

        ratingFile.close();
        cout << "Rating added successfully!" << endl;
    }

    void viewMenuRatings() {
        ifstream ratingFile("menu_ratings.txt");
        if (!ratingFile.is_open()) {
            cout << "No menu ratings available." << endl;
            return;
        }

        string rating;
        while (getline(ratingFile, rating)) {
            cout << rating << endl;
        }

        ratingFile.close();
    }


    void displayFileContents(const string& fileName) {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Error opening file: " << fileName << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }

    void viewUsersFromFile(const string& fileName) {
        ifstream userFile(fileName);
        if (!userFile.is_open()) {
            cout << "Error opening user file: " << fileName << endl;
            return;
        }

        string userInfo;
        while (getline(userFile, userInfo)) {
            cout << userInfo << endl;
        }

        userFile.close();
    }

    void removeMenuItem(const string& itemToRemove) {
        ifstream inputFile("menu.txt");
        if (!inputFile.is_open()) {
            cout << "Error opening menu file!" << endl;
            return;
        }

        ofstream tempFile("temp.txt");
        if (!tempFile.is_open()) {
            cout << "Error creating temporary file!" << endl;
            inputFile.close();
            return;
        }

        string menuItem;
        bool found = false;

        while (getline(inputFile, menuItem)) {
            if (menuItem != itemToRemove) {
                tempFile << menuItem << endl;
            }
            else {
                found = true;
            }
        }

        inputFile.close();
        tempFile.close();

        remove("menu.txt");
        rename("temp.txt", "menu.txt");

        if (found) {
            cout << "Item removed successfully!" << endl;
        }
        else {
            cout << "Item not found in the menu!" << endl;
        }
    }
    void updateStock(const string& itemName, int newQuantity) {
        ifstream inputFile("inventory.txt");
        if (!inputFile.is_open()) {
            cout << "Error opening inventory file!" << endl;
            return;
        }

        ofstream tempFile("temp_inventory.txt");
        if (!tempFile.is_open()) {
            cout << "Error creating temporary file!" << endl;
            inputFile.close();
            return;
        }

        string inventoryItem;
        bool found = false;

        while (getline(inputFile, inventoryItem)) {
            size_t pos = inventoryItem.find(itemName);
            if (pos != string::npos) {
                found = true;
                // Assuming the format is "ItemName: Quantity"
                tempFile << itemName << ": " << newQuantity << endl;
            }
            else {
                tempFile << inventoryItem << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        remove("inventory.txt");
        rename("temp_inventory.txt", "inventory.txt");

        if (found) {
            cout << "Stock updated successfully!" << endl;
        }
        else {
            cout << "Item not found in the inventory!" << endl;
        }
    }

    void viewOrdersFromFile(const string& fileName) {
        ifstream orderFile(fileName);
        if (!orderFile.is_open()) {
            cout << "Error opening order file: " << fileName << endl;
            return;
        }

        string orderInfo;
        while (getline(orderFile, orderInfo)) {
            cout << orderInfo << endl;
        }

        orderFile.close();
    }

    void viewRatingsFromFile(const string& fileName) {
        ifstream ratingFile(fileName);
        if (!ratingFile.is_open()) {
            cout << "Error opening rating file: " << fileName << endl;
            return;
        }

        string ratingInfo;
        while (getline(ratingFile, ratingInfo)) {
            cout << ratingInfo << endl;
        }

        ratingFile.close();
    }
};

// Declaration of the AuthenticationService class
class AuthenticationService {
private:
    static const int MAX_USERS = 200;
    User users[MAX_USERS];
    int userCount;

public:
    AuthenticationService() : userCount(0) {}

    void Register(int id, const string& name, int passcode, int type) {
        if (userCount < MAX_USERS) {
            users[userCount++] = User(id, name, passcode, type);
            cout << "User registered successfully!" << endl;
        }
        else {
            cout << "User registration failed. Maximum users reached." << endl;
        }
    }

    bool Login(int id, int passcode) {
        for (int i = 0; i < userCount; ++i) {
            if (id == 0 && passcode == 2406) {
                cout << "Login successful. Welcome, " << users[i].getuserName() << "!" << endl;
                return true;
            }
        }
        cout << "Invalid credentials. Login failed." << endl;
        return false;
    }
};



// Declaration of the Rating class
class Rating {
private:
    int rat_Id = 0;
    int menu_Itm_Id;
    int cust_Id;
    int score;
    string comment;

public:
    void giverating(int men_it_D)
    {
        string Use_Res;
        rat_Id = rat_Id++;
        menu_Itm_Id = men_it_D;
      
        // Get user input for rating and comment
        cout << "Do you want to give a rating to our services? (y/n) ";
        cin >> Use_Res;

        if (Use_Res == "yes" || Use_Res == "Yes" || Use_Res == "y" || Use_Res == "Y")
        {
            cout << "Enter Score (out of 5) ";
            cin >> score;

            // Validate score (assuming score is between 1 and 5)
            if (score < 1)
            {
                score = 1;
            }
            else if (score > 5)
            {
                score = 5;
            }

            // Display stars based on the score
            cout << "Rating ";
            for (int i = 0; i < score; ++i)
            {
                cout << "*";
            }
            cout << endl;

            // Get user input for comment
            cout << "Enter Comment ";
            //cin.ignore();                  // Clear the input buffer
            cin >> comment;
        }
        else
        {
            // Default values if the user chooses not to give a rating
            rat_Id = 0;
            score = 0;
            comment = "No rating given.";
        }
    }

    // Display rating details
    void print_R() const
    {
        cout << "\t\t\t\t\t\t\t\t_________________________________________"
            << "\n\t\t\t\t\t\t\t\t| Rating ID         " << rat_Id << "    \t\t|"
            << "\n\t\t\t\t\t\t\t\t| Menu Item ID      " << menu_Itm_Id << "    \t\t|"
            << "\n\t\t\t\t\t\t\t\t| Customer ID       " << cust_Id << "    \t\t|"
            << "\n\t\t\t\t\t\t\t\t| Score             " << score << "    \t\t|"
            << "\n\t\t\t\t\t\t\t\t| Comment           " << comment << "    \t\t|"
            << "\n\t\t\t\t\t\t\t\t_________________________________________" << endl;
    }
};

// Declaration of the Payment class
class Payment {
private:                                 //private data member

    int paymentID = 0;
    int orderID;
    string paymentStatus;
    double amount;


public:                              //public
    Payment(int oID, double amt)    // parametrized constructor
    {
        paymentID = paymentID++;
        orderID = oID;
        amount = amt;
        paymentStatus = "Pending";

    }

    void ProcessPayment()           // payment function
    {
        //cout << "\t\t\t\t\t\t\t\t\t_____________________________________" << endl;
        paymentStatus = "Processed";
        //cout << "\t\t\t\t\t\t\t\t\t_____________________________________" << endl;
        cout << "\t\t\t\t\t\t\t\t_________________________________________"          //print all information of process payment
            << "\n\t\t\t\t\t\t\t\t| Payment ID      " << paymentID << "     \t\t|"
            << "\n\t\t\t\t\t\t\t\t| Order ID        " << orderID << "     \t\t|"
            << "\n\t\t\t\t\t\t\t\t| Amount          " << amount << "     \t\t|"
            << "\n\t\t\t\t\t\t\t\t| Payment Status  " << paymentStatus << "      \t|"
            << "\n\t\t\t\t\t\t\t\t_________________________________________"
            << "\n\t\t\t\t\t\t\t\tHope You Enjoy,See You Again!" << endl;
    }
};




class Order                                                   //class order
{
private:
                                            //private data member
    int order_Id = 0;
    string ord_stats;
    int custom_Id;
    string item_Ord[22];                                      // Assuming a maximum of 10 items in an order
    int item_cout;                                        // Change totalPrice to itemCount


public:      
    static int orderCount;//public
    Order(int cut_ID)                                        //parametrizes constructor
    {
        order_Id = ++order_Id;
        custom_Id = cut_ID;
        item_cout = 0;                                       //intialize with 0
        ord_stats = "Pending";                                //status is pending  
    }


    void AddItem(const string& item)                         //function to add item / place order
    {
        if (item_cout <= 22)
        {
            item_Ord[++orderCount] = item;
            cout << "Item added to the order  " << endl;
        }
        else
        {
            cout << "Sorry Memory is full. You Cannot place more items " << endl;
        }
    }


    void RemoveItem(const string& item)                       // function to remove the item from place order
    {

        for (int i = 0; i < item_cout; ++i)
        {
            if (item_Ord[i] == item)
            {
                for (int j = i; j < item_cout - 1; ++j)
                {
                    item_Ord[j] = item_Ord[j + 1];
                }
                --item_cout;
                break;
            }
        }
    }

    double CalculateTotal() const                              // function to calculate the total
    {
        double t_l = 0.0;                                       // initialize the total with double value e.g (0.0)
        const double it_Pri = 200.0;                          // item price fixed

        for (int i = 0; i < item_cout; ++i)
        {
            t_l = t_l + it_Pri;
        }

        return t_l;
    }

    void ConfirmOrder()                                       // function to confirm order
    {
        ord_stats = "Confirmed";                              // order status is Confirmed

        if (ord_stats == "Confirmed")                         //if order is confirmed then process payment function call  
        {
            ProcessPayment();                                  // function call
        }
        else
        {
            cout << "Please confirm your Payment First " << endl;       //else This message print
        }

    }

    void ProcessPayment()  const                                 // function to call the payment process
    {
        cout << "\t\t\t\t\t\t\t\tPayment has been processed for Order ID " << order_Id
            << "\n\t\t\t\t\t\t\t\tAmount is " << CalculateTotal() << endl;    // Calculation Total function call to print amount
    }

    void CancelOrder()                                      // function to cancel the order
    {
        ord_stats = "Cancelled";                            // status is cancelled
        reason();                                           // reason function call that give options to user that why he/she cancel the order
    }

    void reason()                                            // function call when we need reson why customer cancel the order
    {
        int op;

        cout << "Why u are cancel the order? " << endl;
        cout << "\n\t\t\t\t\t\t\t\tOptions "                                          //Options(1 to 9)
            << "\n\t\t\t\t\t\t\t\t1. Change Of Mood "
            << "\n\t\t\t\t\t\t\t\t2. Long Wait Times "
            << "\n\t\t\t\t\t\t\t\t3. Unsatisfactory Service "
            << "\n\t\t\t\t\t\t\t\t4. Dietary Restruction "
            << "\n\t\t\t\t\t\t\t\t5. Financial Reasons "
            << "\n\t\t\t\t\t\t\t\t6. Miscommunication "
            << "\n\t\t\t\t\t\t\t\t7. Exernal Emergencies "
            << "\n\t\t\t\t\t\t\t\t8. Other"
            << "\n\t\t\t\t\t\t\t\t9. Exits" << endl;
        cout << "\n\t\t\t\t\t\t\t\tEnter the Reason why u cancel the order? " << endl;   //input options from user 
        cin >> op;
        // we use i else statments to check wht user enter
        if (op == 1)
        {
            cout << "\t\t\t\t\t\t\t\tChange Of Mood " << endl;

        }
        else if (op == 2)
        {
            cout << "\t\t\t\t\t\t\t\tLong Wait Times " << endl;
        }
        else if (op == 3)
        {
            cout << "\t\t\t\t\t\t\t\tUnsatisfactory Service " << endl;
        }
        else if (op == 4)
        {
            cout << "\t\t\t\t\t\t\t\tDietary Restruction " << endl;
        }
        else if (op == 5)
        {
            cout << "\t\t\t\t\t\t\t\tFinancial Reasons " << endl;
        }
        else if (op == 6)
        {
            cout << "\t\t\t\t\t\t\t\tMiscommunication " << endl;
        }
        else if (op == 7)
        {
            cout << "\t\t\t\t\t\t\t\tExernal Emergencies " << endl;
        }
        else if (op == 8)
        {
            cout << "\t\t\t\t\t\t\t\tOther" << endl;
        }
        else if (op == 9)
        {
            cout << "\t\t\t\t\t\t\t\tExits" << endl;
        }
    }

    void DisplayOrder() const                                                           // function to print the details of customer Order
    {
        cout << "\n\t\t\t\t\t\t\t\t_____________________________________" << endl;
        cout << "\n\t\t\t\t\t\t\t\tOrder ID " << order_Id
            << "\n\t\t\t\t\t\t\t\tCustomer ID " << custom_Id
            << "\n\t\t\t\t\t\t\t\tOrder Status " << ord_stats << endl;
        cout << "\t\t\t\t\t\t\t\tItems Ordered\n";
        for (int i = 0; i < item_cout; ++i)
        {
            cout << "\t\t\t\t\t\t\t\t * " << item_Ord[i] << endl;
        }
        cout << "\t\t\t\t\t\t\t\t_____________________________________" << endl;

        cout << "\t\t\t\t\t\t\t\t_____________________________________" << endl;
        cout << "\t\t\t\t\t\t\t\t              Total Price " << CalculateTotal() << endl;    // print total price
        cout << "\t\t\t\t\t\t\t\t-------------------------------------" << endl;
    }
};



// Declaration of the Customer class inheriting from User
class Customer : public User , public Order, public Rating {
public:
    Customer(int cut_ID) : Order(cut_ID) {
        
    }

    //storing the menu for faculty
    int facultyitem_id[maxitem] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    string facultymenu_name[maxitem] = { "Fajita Pizza", "spicy haleem", "Chicken chowmen", "seekh kabab", "Samosa chat", "roll paratha", "hot choolate", "Green Tea", "Fresh juice", "Mineralwater" };
    int facultymenu_prices[maxitem] = { 500, 550, 600, 650, 150, 200, 100, 80, 100, 90 };
    string facultymenu_description[maxitem] = { "grilled chicken with bell papers and onions on a golden crust", "blend of meat & lenticles ", "tender chicken noodles with savory veggies", "grilled sticks of tasty minces meat with special spices served with naan", "Crispy texture of samosa with chutney", "tender chicken and sauces wrapped in crispy paratha", "caramel coffee", "cardimum tea", "gourmet pepsi", "fresh and pure water" };
    int facultymenu_quanityinstock[maxitem] = { 21, 40, 50, 30, 25, 35, 40, 28, 32, 15 };
    //    storing the menu  for student
    int studentitem_id[maxitem] = { 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };
    string studentmenu_name[maxitem] = { "Chicken biryani", "zinger burger", "loaded fries", "manchurian", "club sandwich", "goll gappay", "chicken pasta", "fresh juices", "chocolate ", "hot brownie" };
    int studentmenu_prices[maxitem] = { 600, 500, 200, 600, 180, 230, 250, 150, 200, 100 };
    string studentmenu_description[maxitem] = { "flavory chicken mixed with delicious rice ", "chicken piece with cheese and onions nestled on a soft bun", "fries mixes with white sauce and small crispy chicken pieces", "egg fried rice with hot and spicy chicken curry", "tender chicken mixed with mayo and cheese in layers on softbread", "crispy hollow puris filled with tangy water and chickpeas", "creamy pasta enriched with parmesan cheese", "juices that give you real essence of fruits without any impurity", "velvety creamy texture of chocolate and vanilla mixed with milk", "soft-textured chocolate brownie with a burst of chocolate lava inside" };
    int studentmenu_quanityinstock[maxitem] = { 22, 42, 55, 35, 20, 30, 40, 27, 36, 25 };
    //storing the menu for non faculty
    int nonfacultyitem_id[maxitem] = { 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 };
    string nonfacultymenu_name[maxitem] = { "chicken karahi", "aloo gobi", "mixed vegetable", "chapli kebab", "chicken nihari", "chicken roast", "red lobia", "daal chawal", "chocolate", "icecream" };
    int nonfacultymenu_prices[maxitem] = { 620, 420, 380, 200, 300, 400, 250, 170, 220, 320 };
    string nonfacultymenu_description[maxitem] = { "chicken curry with flavorful spices", "potatoes with cauliflower curry", "cooked minced meat served with chutney", "tender chicken with aromatic spices dish", "oven-baked chicken with golden crispy coating", "curry of red beans mixed with flavorful spices", "boiled rice with tasty lentils curry", "soft and fluffy donuts with a coating of melted chocolate", "classic creamy indulgence with the flavor of pure vanilla" };
    int nonfacultymenu_quanityinstock[maxitem] = { 43, 16, 19, 25, 30, 35, 20, 22, 34 };

    string category;

    void viewmenu()//viewmenu()defination that allows users to vier their menu depending upon their user type
    {
        cout << "Please enter the category (faculty/nonfaculty/student)" << endl;
        cin >> category;
        if (category == "faculty")
        {
            cout << "-----------------------------\\\\\'WELCOME TO FAST FACULTY CAFE\'\\\\-------------------------------" << endl;
            cout << endl;
            cout << "-----------------------------\\\\\'Choose from the Faculty menu\'\\\\-------------------------------" << endl;
            displaymenu(facultyitem_id, facultymenu_name, facultymenu_prices, facultymenu_description, facultymenu_quanityinstock);
            cout << endl;
            cout << "-----------------------------\\\\\'Can also choose from student's menu\'\\\\------------------------" << endl;
            displaymenu(studentitem_id, studentmenu_name, studentmenu_prices, studentmenu_description, studentmenu_quanityinstock);
            cout << endl;
        }
        if (category == "student")
        {
            cout << "-----------------------------\\\\\'WELCOME TO FAST STUDENT CAFE\'\\\\-------------------------------" << endl;
            cout << endl;
            cout << "-----------------------------\\\\\'Can choose from student's menu\'\\\\-----------------------------" << endl;
            displaymenu(studentitem_id, studentmenu_name, studentmenu_prices, studentmenu_description, studentmenu_quanityinstock);
        }
        if (category == "nonfaculty" || category == "Nonfaculty")
        {
            cout << "-----------------------------\\\\\'WELCOME TO FAST NON-FACULTY CA-------------------------------" << endl;
            cout << endl;
            cout << "-----------------------------\\\\\'Can choose from non-faculty menu\'\\\\-----------------------------" << endl;
            displaymenu(nonfacultyitem_id, nonfacultymenu_name, nonfacultymenu_prices, nonfacultymenu_description, nonfacultymenu_quanityinstock);
        }
        else if (category != "nonfaculty" && category != "faculty" && category != "student")
        {
            cout << "Invalid category input" << endl;
        }
    }

    void displaymenu(int itemID[], string names[], int prices[], string descrip[], int quantity[]) //this function just prints the menu
    {
        cout << "ItemID: \t\t Itemname: \t ItemPrice: \t ItemQuantity:" << endl;
        for (int j = 0; j < maxitem; j++)
        {
            cout <<itemID[j] << "\t\t"<< names[j] << "\t\t"<< prices[j] << "\t\t"<< quantity[j];
            cout << endl;
        }
    }

    void placeOrder() {
        int itemId, quantity;
        int* itemIds = nullptr;
        string* itemNames = nullptr;
        int* itemPrices = nullptr;
        string* itemDescriptions = nullptr;
        int* itemQuantities = nullptr;

        // Assuming category is defined somewhere in the code
        if (category == "faculty") {
            itemIds = facultyitem_id;
            itemNames = facultymenu_name;
            itemPrices = facultymenu_prices;
            itemDescriptions = facultymenu_description;
            itemQuantities = facultymenu_quanityinstock;
        }
        else if (category == "student") {
            itemIds = studentitem_id;
            itemNames = studentmenu_name;
            itemPrices = studentmenu_prices;
            itemDescriptions = studentmenu_description;
            itemQuantities = studentmenu_quanityinstock;
        }
        else if (category == "nonfaculty") {
            itemIds = nonfacultyitem_id;
            itemNames = nonfacultymenu_name;
            itemPrices = nonfacultymenu_prices;
            itemDescriptions = nonfacultymenu_description;
            itemQuantities = nonfacultymenu_quanityinstock;
        }
        else {
            cout << "Invalid category input" << endl;
            return;
        }

        cout << "To place the order, enter the item Id: ";
        cin >> itemId;

        if (itemId < 1 || itemId > 30) {
            cout << "Invalid item ID. Please enter a valid ID." << endl;
            return;
        }

        if (itemQuantities[itemId - 1] <= 0) {
            cout << "Sorry, the item is out of stock." << endl;
            return;
        }

        cout << "Enter the quantity: ";
        cin >> quantity;

        if (quantity <= 0 || quantity > itemQuantities[itemId - 1]) {
            cout << "Invalid quantity. Please enter a valid quantity." << endl;
            return;
        }

        itemQuantities[itemId - 1] -= quantity;
        cout << "Order placed successfully!" << endl;

        stringstream ss;
        ss << "Order: " << itemId << " (Quantity: " << quantity << ")";
        orderHistory[orderCount] = ss.str();
        orderCount++;

        Payment payment(itemId, quantity);
        payment.ProcessPayment();

        
        int choice;
        cout << "Do you want to add something in order? (1 for yes/0 for no): " << endl;
        cin >> choice;
        if (choice == 1)
        {
            string add;
            cout << "What do you want to add" << endl;
            cin>>add;
            AddItem(add);
        }
        cout << "Do you want to remove something in order? (1 for yes/0 for no): " << endl;
        cin >> choice;
        if(choice==1)
        {
            string remove;
            cout << "What do you want to remove" << endl;
            cin >> remove;
            RemoveItem(remove);
        }
        double total = CalculateTotal();
        cout << "Do you want to confirm order? (1 for yes/0 for no): " << endl;
        cin >> choice;
        if(choice==1)
        ConfirmOrder();
        string cancelChoice;
        cout << "Do you want to cancel the order? (yes/no): ";
        cin >> cancelChoice;

        if (cancelChoice == "yes") {
            CancelOrder();
        }
        else {
            DisplayOrder();
        }
        cout << "Do you want to give Rating? (1 for yes/0 for no): " << endl;
        cin >> choice;
        if (choice == 1)
            giverating(itemId);
    }
    


    void vieworderhistory() const//vieworderhistory function defination that stores the itemid for every item

    {
        cout << "Order History:\n";
        for (int i = 0; i < orderCount; i++)
        {
            cout << orderHistory[i] << endl;
        }
    }
};




int Order::orderCount = 0;

int main() {
    AuthenticationService auth; // Creating an instance of AuthenticationService
    Customer customer(123); // Assuming the customer ID is 123
    

    int userType;
    int userId;
    int userPass;
    int newadmin;
   /* cout << "Do you want to add administrator?(1 for yes/0 for no)" << endl;
    cin >> newadmin;
    if (newadmin == 1)
    {
        Administrators admin();
    }
    else*/
        Administrators admin; // Creating an instance of Administrators
    cout << "====================================================" << endl;
    cout << "||                                                ||" << endl;
    cout << "||                                                ||" << endl;
    cout << "||        WELCOME TO FAST MAIN CAFE               ||" << endl;
    cout << "||               WHERE TASTE MEETS PASSION        ||" << endl;
    cout << "||                                                ||" << endl;
    cout << "||                                                ||" << endl;
    cout << "====================================================" << endl;
    // Simple login system for demonstration purposes
    cout << "Enter User Type (1 for Admin, 2 for Customer): ";
    cin >> userType;

    if (userType == 1) {
        //admin.setuserPasscode("admin");
        cout << "Enter Admin User ID: ";
        cin >> userId;
        cout << "Enter Admin Password: ";
        cin >> userPass;

        // Authenticate admin
        //bool adminLoggedIn = auth.Login(userId, userPass);
        //if (adminLoggedIn) {
            // Admin Menu
            int adminChoice;
            do {
                cout << "********Admin Menu:********" << endl;
                cout << "1. View Menu" << endl;
                cout << "2. Add Menu Item" << endl;
                cout << "3. View Order History" << endl;
                cout << "4. Rate Menu Item" << endl;
                cout << "5. View Menu Ratings" << endl;
                cout << "6. Logout" << endl;
                cout << "Enter your choice: ";
                cin >> adminChoice;

                switch (adminChoice) {
                case 1:
                    admin.viewMenu();
                    break;
                case 2: {
                    string newItem;
                    cout << "Enter new menu item: ";
                    cin.ignore();
                    getline(cin, newItem);
                    admin.addMenuItem(newItem);
                    break;
                }
                case 3:
                    admin.viewOrderHistory();
                    break;
                case 4: {
                    string itemName;
                    int rating;
                    cout << "Enter item name to rate: ";
                    cin.ignore();
                    getline(cin, itemName);
                    cout << "Enter rating for " << itemName << " (1-5): ";
                    cin >> rating;
                    admin.rateMenuItem(itemName, rating);
                    break;
                }
                case 5:
                    admin.viewMenuRatings();
                    break;
                case 6:
                    cout << "**************//Logging out as Admin.//****************" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            } while (adminChoice != 0);
     //   }
     //   else {
     //       cout << "Admin login failed. Exiting..." << endl;
     //   }
    }
    else if (userType == 2) {
        // Customer Menu
        int customerChoice;
        do {
            cout << "******************Customer Menu: *******************" << endl;
            cout << "1. View Menu" << endl;
            cout << "2. Place Order" << endl;
            cout << "3. View Order History" << endl;
            cout << "4. Logout" << endl;
            cout << "Enter your choice: ";
            cin >> customerChoice;

            switch (customerChoice) {
            case 1:
                customer.viewmenu();
                break;
            case 2:
                customer.placeOrder();
                break;
            case 3:
                customer.vieworderhistory();
                break;
            case 4:
                cout << "**********************//Logging out as Customer.//**********************" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (customerChoice != 4);
    }
    else {
        cout << "**************Invalid User Type. Exiting...*************" << endl;
    }

    return 0;
}
