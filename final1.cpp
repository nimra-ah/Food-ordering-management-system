#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct user{
    string name;
    int sec_no;
    int item_no;
};
struct sectiondisplay{
    int item_num;
    string item_name;
    float price;
};
void makebill(user orders[], int orderCount, sectiondisplay *selectedSection,int orderno);
void writedata(user orders[], int orderCount, sectiondisplay *selectedSection, int orderno);
int readOrderNumberFromFile();
void writeOrderNumberToFile(int orderno);

void section1(sectiondisplay items[]) {
    items[0] = {1, "French Fries", 5};
    items[1] = {2, "Onion Rings", 6};
    items[2] = {3, "Garlic Bread", 5};
    items[3] = {4, "Chicken Wings", 9};
    items[4] = {5, "Spring Rolls", 7};
    items[5] = {6, "Mozzarella Sticks", 6};
    items[6] = {7, "Samosas", 6};
}

void section2(sectiondisplay items[]) {
    items[0] = {1, "Grilled Chicken Breast", 14};
    items[1] = {2, "Beef Steak (Medium)", 20};
    items[2] = {3, "Spaghetti Bolognese", 12};
    items[3] = {4, "Dal Tadka", 12};
    items[4] = {5, "Vegetable Stir Fry", 11};
    items[5] = {6, "Margherita Pizza", 13};
    items[6] = {7, "Palak Gosht", 17};
    items[7] = {8, "Chicken Tacos (3 pcs)", 10};
    items[8] = {9, "Lamb Chops", 22};
    items[9] = {10, "Biryani (Chicken or Mutton)", 16};
}

void section3(sectiondisplay items[]) {
    items[0] = {1, "Gulab Jamun", 5};
    items[1] = {2, "Ras Malai", 6};
    items[2] = {3, "Kheer", 5};
    items[3] = {4, "Cheesecake", 7};
    items[4] = {5, "Ice Cream Sundae", 6};
}

void section4(sectiondisplay items[]) {
    items[0] = {1, "Soda (Coke, Sprite, Diet Coke)", 2};
    items[1] = {2, "Iced Tea", 3};
    items[2] = {3, "Chai Tea", 3};
    items[3] = {4, "Lassi (Mango or Sweet)", 4};
    items[4] = {5, "Mint Lemonade", 3};
}
void displayFullMenu(sectiondisplay appetizers[], sectiondisplay mains[], sectiondisplay desserts[], sectiondisplay beverages[]) {
    cout << "----------- SECTION 1: Appetizers Menu -----------" << endl;
    for (int i = 0; i < 7; ++i) {
        cout << appetizers[i].item_num << ". " << appetizers[i].item_name << " - $" << appetizers[i].price << endl;
    }

    cout << "\n----------- SECTION 2: Main Courses Menu -----------" << endl;
    for (int i = 0; i < 10; ++i) {
        cout << mains[i].item_num << ". " << mains[i].item_name << " - $" << mains[i].price << endl;
    }

    cout << "\n-----------SECTION 3: Desserts Menu -----------" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << desserts[i].item_num << ". " << desserts[i].item_name << " - $" << desserts[i].price << endl;
    }

    cout << "\n-----------SECTION 4: Beverages Menu -----------" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << beverages[i].item_num << ". " << beverages[i].item_name << " - $" << beverages[i].price << endl;
    }
}

void takeOrder(user orders[],int &orderCount, sectiondisplay appetizers[], sectiondisplay mains[], sectiondisplay desserts[], sectiondisplay beverages[]){
    int totsec = 4;
    int totquantity=50;
    user u1;
    int orderno=readOrderNumberFromFile();

    cout<<"enter your name"<<endl;
    cin.ignore();
    getline(cin, u1.name);

    bool doneOrdering = true;
    sectiondisplay *selectedSection = nullptr;
    while (doneOrdering) {
    
    cout << "Enter section number (1: Appetizers, 2: Mains, 3: Desserts, 4: Beverages): ";
    cin>>u1.sec_no;

    if (u1.sec_no < 1 || u1.sec_no > totsec) {
        cout << "Invalid section number! Please enter a valid section number." << endl;
        cin>>u1.sec_no;
    }

    int sectionSize = 0;

    switch (u1.sec_no) {
        case 1:
        selectedSection = appetizers;
        sectionSize = 7;
        break;
        case 2:
        selectedSection = mains;
        sectionSize = 10;
        break;
        case 3:
        selectedSection = desserts;
        sectionSize = 5;
        break;
        case 4:
        selectedSection = beverages;
        sectionSize = 5;
        break;
    }
    
    cout << "Enter the item number you want to order: ";
    cin >> u1.item_no;
    
    if(u1.item_no > 0 && u1.item_no <= sectionSize){
        
        sectiondisplay selectedItem = selectedSection[u1.item_no - 1];

        orders[orderCount] = u1;
        orderCount++;

        cout << selectedItem.item_name << " has been added to your order!" << endl;

    } else {
            cout << "Invalid item number! Please choose a valid item." << endl;
        }

        char continueOrder;
        cout << "Would you like to order another item? (y/n): ";
        cin >> continueOrder;
        
        if(continueOrder == 'n' || continueOrder == 'N')
        doneOrdering = false;
    }
  writedata(orders, orderCount, selectedSection,orderno);
  makebill(orders, orderCount, selectedSection,orderno);
  orderno++;
  writeOrderNumberToFile(orderno);
}
    
void makebill(user orders[], int orderCount, sectiondisplay *selectedSection,int orderno) {

    cout << "\n********** Bill Summary **********" << endl;
    float totalPrice = 0;

    cout<<"ORDER # "<<orderno<<endl;
    cout << "Customer Name: " << orders[0].name << endl;
    cout << "----------------------------------" << endl;

    for (int i = 0; i < orderCount; ++i) {
        sectiondisplay selectedItem = selectedSection[orders[i].item_no - 1];
        cout << "Item " << i + 1 << ": " << selectedItem.item_name
             << " - Price: $" << selectedItem.price << endl;
        totalPrice += selectedItem.price;
    }

    cout << "----------------------------------" << endl;
    cout << "Total Amount: $" << totalPrice << endl<<endl;
    cout<<"Thanks for ordering! Your order will be ready in 20 mins"<<endl;
    cout << "**********************************" << endl;
}
void writedata(user orders[], int orderCount, sectiondisplay *selectedSection,int orderno){
    ofstream f("orderdata.txt", ios::out|ios::app);
    if (!f) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    f << "\n********** Bill Summary **********" << endl;
    float totalPrice = 0;

    f <<"ORDER # "<<orderno<<endl;
    f << "Customer Name: " << orders[0].name << endl;
    cout << "----------------------------------" << endl;

    for (int i = 0; i < orderCount; ++i) {
        sectiondisplay selectedItem = selectedSection[orders[i].item_no - 1];
        f << "Item " << i + 1 << ": " << selectedItem.item_name
             << " - Price: $" << selectedItem.price << endl;
        totalPrice += selectedItem.price;
    }

    f << "----------------------------------" << endl;
    f << "Total Amount: $" << totalPrice << endl<<endl;
    f << "**********************************" << endl;
    f.close();
}
int readOrderNumberFromFile() {
    ifstream infile("orderno.txt");
    int orderno = 1;

    if (infile) {
        infile >> orderno;
    }
    infile.close();
    return orderno;
}
void writeOrderNumberToFile(int orderno) {
    ofstream outfile("orderno.txt");
    if (outfile) {
        outfile << orderno;
    }
    outfile.close();
}
int main(){
    sectiondisplay appetizers[7], mains[10], desserts[5], beverages[5];

    section1(appetizers);
    section2(mains);
    section3(desserts);
    section4(beverages);

    int choice;
    cout << "\n**************************************************" <<endl ;
    cout << "***         Food Ordering Management System    ***"<<endl;
    cout << "**************************************************"<<endl<<endl;
    
    cout << "Please choose an option:"<<endl;
    cout << "1. On-Dining" << endl;
    cout << "2. Take-Away" <<endl;
    cout << "3. Delivery" <<endl;
    
    cout << "\nEnter your choice (1, 2, or 3): ";
    cin>>choice;

    switch(choice) {
        case 1:
            cout << "\n----- On-dining Menu -----" << endl;
            displayFullMenu(appetizers, mains, desserts, beverages);
            break;

        case 2:
            cout << "\n----- Take-away Menu -----" << endl;
            displayFullMenu(appetizers, mains, desserts, beverages);
            break;

        case 3:
            cout << "\n----- Delivery Menu -----" << endl;
            displayFullMenu(appetizers, mains, desserts, beverages);
            break;

        default:
            cout << "INVALID!!" << endl;
    }

    user orders[100];
    int orderCount = 0;
    user u1;

    takeOrder(orders, orderCount, appetizers, mains, desserts, beverages);
    return 0;
}
