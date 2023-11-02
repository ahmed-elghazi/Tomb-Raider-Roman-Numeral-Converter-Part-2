#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

// NET ID : AXE210038
// NAME: AHMED ELGHAZI

struct node
{
    // node needs to hold the roman numerals, arabic digits (as an integer), and point to the next node if any
    string roman;
    int arabic;
    node *next;
};
void createNode(string roman, string arabic, node *&head)
{
    node* A = new node; // dynamically allocate new node

    // the following 2 lines clear white space from the string, making comparison easier later
    roman.erase(remove(roman.begin(), roman.end(), ' '), roman.end());
    arabic.erase(remove(arabic.begin(), arabic.end(), ' '), arabic.end());

    // these lines populate the dynamically allocated node with the data it needs to hold
    A->roman = roman;
    A->arabic = stoi(arabic);

    if(head == nullptr) // if the list is empty
    {
        head = A; // the first node is now the head
        A->next = nullptr; // the following node does not exist so next is null
    }
    else // if the list is not empty, we are adding this node to the beginning of the list
    {
        A->next = head; // make the next in our new node point to the rest of the list
        head = A; // head now points to the NEW beginning of the list
    }
}
void validity(const string &full,bool &romanValid, bool &arabicValid,string &arabic, string &roman) {
    //checks if the strings are composed of valid characters, adjusting the boolean value accordingly
    roman.clear(); // First
    arabic.clear(); // These three lines reset the values of these variables for the next iteration
    int tot = 0; // Second

    roman = full.substr(0, 17); // Roman numerals can occupy spaces 0 to 17 on a given line
    arabic = full.substr(17,4); // Arabic digits will occupy 18 to 21 meaning count from position 17

    char a = arabic.at(0);
    if (isspace(a)) {arabicValid = false; // if this char is a space, there are no arabic digits
        for (long unsigned int i = 0; i < roman.length(); i++) {
            if (roman.at(i) == 'I' || roman.at(i) == 'V' || roman.at(i) == 'X'
                || roman.at(i) == 'L' || roman.at(i) == 'C' || roman.at(i) == 'D'
                || roman.at(i) == 'M' || roman.at(i) == ' ') {}
            else {
                romanValid = false; // if the character at I is not one of these values, it is invalid
                break;
            }
        }
    }
    else {romanValid = false;
        for (long unsigned int i = 0; i < arabic.length(); i++) { // Arabic can only be digits, not punctution or alphabet
            if (isdigit(arabic[i]) || arabic[i] == ' ') {} // Check if it is a space because stirng could be "14  "
            else {arabicValid = false;} // invalid values set this to false invalidating the bool
        }

    }
    if(arabicValid){ // if arabic digits are still valid
        tot = stoi(arabic); // convert the string to an integer
        if(tot >= 5000 || tot < 1){arabicValid = false;} // Value has to be wihtin range given from instructions
        if(tot%1 != 0){arabicValid = false;} // A decimal would yield a non-zero value
    }
}
int dictionary(char c){ // this holds the values of roman numerals and returns the arabic digit value
    if (c == 'M'){return 1000;}
    else if (c == 'D'){return 500;}
    else if (c == 'C'){return 100;}
    else if (c == 'L'){return 50;}
    else if (c == 'X'){return 10;}
    else if (c == 'V'){return 5;}
    else if (c == 'I'){return 1;}
    else {return 0;}
}
void conRoman(string const arabic, string &total){ // if the value is divisible by that number, add it to the string
    // then subtract it from the arabic digit itself
    total.clear(); // resetting the value;
    int arabicM = stoi(arabic);
    while (arabicM >= 1){
        if (arabicM / 1000 >= 1){total += 'M'; arabicM = arabicM - 1000; continue;}
        if (arabicM / 900 >= 1){total += 'C'; total +='M'; arabicM = arabicM - 900; continue;}
        if(arabicM / 500 >= 1){total += 'D';arabicM = arabicM - 500;continue;}
        if (arabicM / 400 >= 1){total += 'C';total += 'D'; arabicM = arabicM - 400; continue;}
        if (arabicM / 100 >= 1){total += 'C';arabicM = arabicM - 100;continue;}
        if (arabicM / 90 >= 1){total += 'X';total += 'C'; arabicM = arabicM - 90; continue;}
        if (arabicM / 50 >= 1) {total += 'L';arabicM = arabicM - 50;continue;}
        if (arabicM / 40 >= 1){total += 'X';total += 'L'; arabicM = arabicM - 40; continue;}
        if (arabicM / 10 >= 1){total += 'X';arabicM = arabicM - 10;continue;}
        if (arabicM / 9 >= 1){total += 'I';total += 'X'; arabicM = arabicM - 9;continue;}
        if (arabicM / 5 >= 1){total += 'V';arabicM = arabicM - 5;continue;}
        if (arabicM / 4 >= 1){total += 'I';total += 'V'; arabicM = arabicM - 4; continue;}
        if(arabicM < 5){int x = arabicM/1; for (int i = 0; i < x; i++){total += 'I';} arabicM -= x;} // add multiple 1's
    }
}
void conArabic(string roman, int &totalNum){ //
    totalNum = 0; // clear the value since it is a reference
    int val1 = 0; // initialize variables
    int val2 = 0; // ^^
    for(long unsigned int i = 0; i < roman.length(); i++){
        char a  = roman.at(i); // iterate through roman
        if(i+1 < roman.length()){char b = roman.at(i+1);val2 = dictionary(b);}
        else {val2 = 0;}
        val1 = dictionary(a);
        if (val1 > val2){ totalNum += val1;} // XI equals 11 because the greater value comes first
        if (val2 > val1){totalNum += val2;totalNum -= val1;i++;} // IX equals 9 because the lower value came first
        if(val2 == val1){totalNum += val1; totalNum += val2; i++;} // If they are equal, just add two of them

    }
}
void outputfx(node *head)
{
    // this function comes after the end of program, writing the sorted list to the file
    ofstream output ("numbers.txt"); // initializing an output stream named "output" which prints to file "numbers.txt"
    while(head != nullptr) // while we are not at the end of the list
    {
        // output to the file following given format from documentation
        output << left << std::setw(17) << head->roman << setw(4) << head->arabic << '\n';

        // move head to the next node
        head = head->next;
    }
    output.close(); // close the file stream
}
bool SearchFunction(node *head, string find) {
    if (isdigit(find.at(0))) // if first character is a digit, then we need to find digits
    {
        int search = stoi(find); // convert what we are finding to an integer for easier comparison

        while(head != nullptr) // while we are not at the end of the list
        {
            if(head->arabic == search) // if the digit is found
            {
                return true; // then the bool is returned as true
            }
            head = head->next; // if this code is reached, the if statement was false and we increment head
        }
        return false; // if the loop concludes without returning true, the value was not found and is not in the list
    }
    else
    {
        while(head!= nullptr)// while we are not at the end of the list
        {
            if(head->roman == find) // if the digit is found
            {
                return true; // then the bool is returned as true
            }
            head = head->next; // if this code is reached, the if statement was false and we increment head
        }
        return false; // if the loop concludes without returning true, the value was not found and is not in the list
    }
}
void PrintFx(node *head, int ArabicOrRoman)
{
    // this function prints the value type we sorted by
    if(ArabicOrRoman == 1) // 1 is the value of roman in the menu
    {
        while(head!= nullptr) // while we are not at the end of the list
        {
          cout << head->roman << endl; // print the roman numeral
          head = head->next; // increment head
        }
    }
    else // if we are not sorting by roman, thn we are sorting by arabic
    {
        while(head!= nullptr)
        {
            cout << head->arabic << endl; // print the arabic digits
            head = head->next; // increment head
        }
    }
}
node *merge(node *left, node *right, int ArabicOrRoman) {
    node *result;
    if (ArabicOrRoman == 1) { // 1 is the value of roman in the menu
        if (left == nullptr) { // if the left sublist is empty, then everything within it was sorted
            return right; // return the rest of the right list which was previously sorted
        }
        else if (right == nullptr) { // if the right sublist is empty, then everything within it was sorted
            return left; return right; // return the rest of the left list which was previously sorted
        }
        if (left->roman <= right->roman) { // if
            result = left;
            result->next = merge(result->next, right, ArabicOrRoman);
        }
        else {
            result = right;
            result->next = merge(left, result->next, ArabicOrRoman);
        }
    }
    else // anything else is the value of arabic in the menu
    {
        if (left == nullptr) {// if the left sublist is empty, then everything within it was sorted
            return right; // return the rest of the right list which was previously sorted
        }
        if (right == nullptr) { // if the right sublist is empty, then everything within it was sorted
            return left; return right; // return the rest of the left list which was previously sorted
        }
        if (left->arabic <= right->arabic) { // the left element is the smallest in both lists
            result = left; // result points to the left element
            result->next = merge(result->next, right, ArabicOrRoman); // merge everything after left
        } else { // the right element is the smallest in both lists
            result = right; // result points to the left element
            result->next = merge(left, result->next, ArabicOrRoman); // merge everything after left
        }
    }
    return result;
}
node *mergeSort(node *&head, int ArabicOrRoman)
{
    // divide the list into left and right sublists recursively
    if(head->next == nullptr || head == nullptr) // empty list or single value list
    {
        return head;
    }
    node *slow = head;
    node *fast = head->next;
    while(fast != nullptr && fast->next != nullptr) // split the list
    {
        slow = slow->next; // slow points to the middle of the list;
        fast = fast->next->next; // fast will point out of bounds
    }

    node *right = slow->next; // everything to the right of the middle is right sublist
    slow->next = nullptr; // splitting of the sublists
    node *left = mergeSort(head, ArabicOrRoman); // divide sublist recursively
    right = mergeSort(right, ArabicOrRoman); // divide sublist recursively

    return head = merge(left, right, ArabicOrRoman); // return the head of the now merged list
}
void finalPrint(node *head)
{
    // recursive function to the print fhe node contents to console
    if(head == nullptr)
    {
        return; // base case, nothing else in the list
    }
    cout << left << setw(17) << head->roman << setw(4) << head->arabic << endl; // print to  console
    finalPrint(head->next); // call again
}

int main()
{
    string fileName, full, arabic, roman;
    cin >> fileName; // read in file name to initialize stream
    fstream file(fileName, ios::in | ios::out | ios::binary); // initializing stream
    node *head = nullptr; // head points at nothing
    if(file.good()) { // Does not work if the file stream is bad
        while (getline(file, full)) // read line from file
        {
            bool romanValid = true; // reset booleans to true
            bool arabicValid = true;
            int totalNum = 0;
            validity(full, romanValid, arabicValid, arabic, roman); // validate the lines
            if (arabicValid) {
                conRoman(arabic, roman); // convert arabic digits to roman numerals
                createNode(roman, arabic, head); // create node and add it to the list
            } else if (romanValid) {
                conArabic(roman, totalNum); // convert roman numerals to arabic digits
                arabic = to_string(totalNum); // set arabic string to the string of arabic digits
                createNode(roman, arabic, head); // create node and add it to the list
            }
        }
    }
    file.close(); // close the file
    int read = 0; // initialize read
    do
    {
        cout << "1. Search\n2. Sort\n3. Exit \n " << endl;
        cin >> read;
        if(read == 1) // search function
        {
            string find;
            cout << "what would you like to find";
            cin >> find;
            if(SearchFunction(head,find)) // returns true only if found
            {
                cout << find << " found\n";
            }
            else // was not found... returned false
            {
                cout << find << " not found\n";
            }
        }

        else if(read == 2) // sort the function
        {
            //sort function
            cout << "1. Sort by Roman numeral\n2. Sort by Arabic numeral";
            int ArabicOrRoman = 0;
            cin >> ArabicOrRoman; // 1 means sorting by roman, 2 means sorting by arabic
            mergeSort(head, ArabicOrRoman); // sort them!
            PrintFx(head, ArabicOrRoman); // print sorted list
        }
    }while(read!=3); // if read equals 3, user would like to exit
    outputfx(head); // print sorted list to the file
    finalPrint(head); // print sorted list and all contents to console
}