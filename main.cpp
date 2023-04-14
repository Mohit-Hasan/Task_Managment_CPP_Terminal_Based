#include<iostream>
#include <string>
#include <sstream>
using namespace std;


//started base code
class Task{
    public:
    int sl;
    bool isComplete;
    string title;
    string description;
    string time;
    Task* next;
};

class LinkedList{
    private:
    int sl;
    public:
    Task* head;
    

    LinkedList(){
        head = nullptr;
        sl=1;
    }

    void addTask(string title, string desc, string time){
        Task* newTask = new Task();
        newTask->sl=sl; sl++;
        newTask->isComplete = false;
        newTask->title = title;
        newTask->description = desc;
        newTask->time = time;
        newTask->next = nullptr;
        
        if(head == nullptr){
            head = newTask;
            return;
        }

        Task* holdHead = head;
        while(holdHead->next != nullptr){
            holdHead = holdHead->next;
        }
        holdHead->next = newTask;
    }

    void addTasker(){
        cout<<"Add New Task\n------------------\n\n";
        string title, desc, time;
        cout << "Enter Task Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Task Description: ";
        getline(cin, desc);
        cout << "Enter Task Deadline Time: ";
        getline(cin, time);

        addTask(title,desc,time);

        system("clear");
        cout<<"Task Added Successfully"<<endl;
        mainMenu();
        
    }

    void editTask(Task* h){
        cout<<"Edit Task\n------------------\n\n";
        cout << "Enter New Task Title: ";
        cin.ignore();
        getline(cin, h->title);
        cout << "Enter New Task Description: ";
        getline(cin, h->description);
        cout << "Enter New Task Deadline Time: ";
        getline(cin, h->time);

        system("clear");
        cout<<"Task Edited Successfully\n---------------------------\n"<<endl;
        viewSingle(h->sl);
        
    }

    void deleteTask(Task *target, bool fromMark){
        int isComp = target->isComplete ? 1 : 0; //track this to determine deleted node was pending or completed to back task page

		if (target == nullptr) { return; }

        //if target node is the head
        if (target == head) {
            head = head->next;
            delete target;
            if(!fromMark){
                system("clear");
                cout<<"Task Deleted Successfully\n---------------------------\n"<<endl;
                viewTask(isComp);
            }
            return;
        }

        //find the prev of target node
        Task* prev = head;
        while (prev->next != nullptr && prev->next != target) {
            prev = prev->next;
        }

        //if anyway the target node is not found
        if (prev->next == nullptr) { 
            if(!fromMark){ 
                system("clear");
                cout<<"Task Not Found!\n---------------------------\n"<<endl;
                viewTask(isComp);
            }
            return;
        }

        //connecting target's prev with target's next
        prev->next = target->next;

        //finally delete target node :)
        delete target;

        if(!fromMark){
            system("clear");
            cout<<"Task Deleted Successfully\n---------------------------\n"<<endl;
            viewTask(isComp);
        }
        return;
	}

    void markAndDeleteTaskOpe(string *input, int maxSize){

        //converting user's inputed string to intArray to make the operation easier
        istringstream ss(*input);
        string token;
        int arr[maxSize], size = 0;
        while (getline(ss, token, ',')) {
            arr[size++] = stoi(token);
        }
        int fSize = size<maxSize? size : maxSize; // determine the final size between user can max select and how many they selected

        Task* holdHead = head;
        while(holdHead != nullptr){
            for(int j=0; j<fSize; j++){
                if(holdHead->sl == arr[j]){
                    deleteTask(holdHead, true);
                    arr[j]=-1; //there are many more efficient way by also delete the founded value from arr, but for time sortarage i did like this
                    break;
                }
            }
            holdHead = holdHead->next;
        }

        system("clear");
        cout<<"Your Marked All Task is Deleted Successfully\n-------------------------------------------\n";
        markAndDeleteTaskView();  // finally i done this project :) it's my wrriten last line code of this project!

    }

    void markAndDeleteTaskView(){

        Task* holdHead = head;
        int sl=0;
        cout<<"----------ALL TASKS-----------"<<endl;
        cout<<"SL |"<<"\tTitle\t\t"<<"| Time"<<endl;
        cout<<"------------------------------"<<endl;

        while(holdHead != nullptr){
            cout<<holdHead->sl<<". "<<holdHead->title<<"\t"<<holdHead->time<<endl;
            holdHead = holdHead->next;
            sl++;
        }
        
        string input;
        cout<<"\nSL. Mark By comma (Ex: 1,2,5,6)"<<endl;
        cout<<"0. Back Main Menu"<<endl;
        
        while (true) {
            cout<<"\nEnter: ";
            cin >> input;
            if (cin.fail()) {
                cin.clear(); // clear error flag
                cin.ignore(10000, '\n'); // ignore character
                cout << "Invalid input! Please enter a number."<<endl;
            } else {
                break;
            }
        }

        system("clear");
        if(input == "0") { mainMenu(); }
        else { markAndDeleteTaskOpe(&input, sl); } //passing user's selected sl numbers to delete and how many sl might be max to be perform del operation

	}
    
    void viewSingle(int sl){
        Task* holdHead = head, *prevHead = nullptr; //we have to track prev head to delete
        bool isFound = false, isCompleted = false;
        while(holdHead != nullptr){
            if(holdHead->sl == sl){
                cout<<holdHead->title<<endl;
                cout<<"---------------------------"<<endl;
                cout<<holdHead->description<<endl;
                isFound = true;
                if(holdHead->isComplete){ isCompleted = true; } //need this to back to the pending or completed page
                break;
            }
            holdHead = holdHead->next;
        }

        if(isFound){
            cout<<"\n1. Edit\n2. Delete\n";
            if(isCompleted){cout<<"3. Mark as Undone\n";} else {cout<<"3. Mark as Done\n";}
            cout<<"4. Back\n5. Main Menu";
        }else{
            cout<<"Not Found!!"<<endl;
            cout<<"0. Back to Mian Menu"<<endl;
        }

        int input;
        while(true) {
            cout<<"\nEnter: ";
            cin >> input;
            if (cin.fail()) {
                cin.clear(); // clear error flag
                cin.ignore(10000, '\n'); // ignore character
                cout << "Invalid input! Please enter a number."<<endl;
            } else {
                break;
            }
        }

        system("clear");
        if(input == 0){ mainMenu(); }
        else if(input == 1){ editTask(holdHead); }
        else if(input == 2){ deleteTask(holdHead, false); } //here false to make sure it's not mark and delete opeation
        else if(input == 3 && isCompleted){ holdHead->isComplete = false; cout<<"SL: "<<sl<<" is Mark as Undone Successfully\n"; viewTask(1); }
        else if(input == 3 && !isCompleted){ holdHead->isComplete = true; cout<<"SL: "<<sl<<" is Mark as Done Successfully\n"; viewTask(0); }
        else if(input == 4 && isCompleted){ viewTask(1); } // by this i know from which page user came here, pending or completed
        else if(input == 4 && !isCompleted){ viewTask(0); } // and back to them accurately
        else if(input == 5){ mainMenu(); }
        else{ cout<<"Something went wrong!\n"; mainMenu(); }
        
    }

    void viewTask(int status){ // 0=> pending, 1=> completed
        Task* holdHead = head;
        int sl = 1, input;
        cout<<"SL |"<<"\tTitle\t\t"<<"| Time"<<endl;
        cout<<"------------------------------"<<endl;
        if(status){
            while(holdHead != nullptr){
                if(holdHead->isComplete){
                    cout<<holdHead->sl<<". "<<holdHead->title<<"\t"<<holdHead->time<<endl;
                }
                holdHead = holdHead->next;
                sl++;
            }
        }else{
            while(holdHead != nullptr){
                if(!holdHead->isComplete){
                    cout<<holdHead->sl<<". "<<holdHead->title<<"\t"<<holdHead->time<<endl;
                }
                holdHead = holdHead->next;
                sl++;
            }
        }
        
        
        cout<<"\nSL. to view"<<endl;
        cout<<"0. Back Main Menu"<<endl;
        
        while (true) {
            cout<<"\nEnter: ";
            cin >> input;
            if (cin.fail()) {
                cin.clear(); // clear error flag
                cin.ignore(10000, '\n'); // ignore character
                cout << "Invalid input! Please enter a number."<<endl;
            } else {
                break;
            }
        }

        system("clear");
        if(input == 0) { mainMenu(); }
        else { viewSingle(input); }
        
    }

    int mainMenu(){
        //system("clear");
        int input;
        cout<<"Chose and enter your menu:\n"<<endl;
        cout<<"1. Add New Task"<<endl;
        cout<<"2. Pending Tasks"<<endl;
        cout<<"3. Completed Tasks"<<endl;
        cout<<"4. Mark and Delete Task"<<endl;
        cout<<"5. Exit The App"<<endl;
        
        while (true) {
             cout<<"\nEnter: ";
            cin >> input;
            if (cin.fail()) {
                cin.clear(); // clear error flag
                cin.ignore(10000, '\n'); // ignore character
                cout << "Invalid input! Please enter a number."<<endl;
            } else {
                break;
            }
        }

        system("clear");

        if(input == 1) { addTasker(); return 0; } 
        else if(input == 2) { viewTask(0); return 0; } 
        else if(input == 3) { viewTask(1); return 0; } 
        else if(input == 4) { markAndDeleteTaskView(); return 0; } 
        else if(input == 5) { cout<<"Thank you for using this Task Managment App.\nTo re open, re run the code.\n"<<endl; return 0; } 
        else {
            cout<<"Wrong Input! Please Enter Correctly."<<endl;
            return -1;
        }
        
    }
};


int main(){

    system("clear");
    LinkedList task;

    //here are some pre constructed data to test easier
    task.addTask("Do Assignment","Teacher give me some assignemnt, I have to complete it","08 May 2023");
    task.addTask("Buy a New SSD","I need a SSD for dummy files storage","10 May 2023");
    task.addTask("Make a new PC","I need a new custom PC for my new workspace","14 May 2023");
    task.addTask("Create a new Ai","I have to create a new AI modal, which I think on yesterday night","14 May 2023");

    cout<<"---------------------------------"<<endl;
    cout<<"| WELCOME TO TASK MANAGMENT APP |"<<endl;
    cout<<"---------------------------------"<<endl;
    int awake = -1;
    while(awake == -1){
        awake = task.mainMenu();
    }
    
}
