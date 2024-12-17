#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include "password.h" //created by me to check password
using namespace std;

int userID(string user , string pwd) ;
void listingQuestions() ;
long getValidinput012() ;
long getValidinput09() ;
string validAnswer(int id ); 
long getValidinput01() ;
//functions outside the main  are global variable
// we will discuss global variables later

void loadData(); //Don't bother about this code, you will learn it later.

const int qsize = 20; //Maximum number of questions
const int usize = 5;  //Maximum number of users
//variable area
bool qflag[qsize];    //use this array to check whether an element exist on an index or not.
string question[qsize];
string option1[qsize];
string option2[qsize];
string option3[qsize];
string option4[qsize];
string correctOption[qsize];

bool   uflag[usize];     //use this array to check whether an element exist on an index or not.
string username[usize];
string passwords[usize];
int    scores[usize];    //array will be used to save the score attempted.
int totalMarks[usize]  ;

int main()
{
    ofstream fout ;   
    string user;
    string pwd;
    bool userSearchFlag = false;

    long input;

    int loggedInUserType = -10; //1 for administrator, 2 for user

    //TODO-- Initializtion of all arrays
    //assign an intial values to all arrays here.

    // question  related arrays
    for(int i = 0 ; i<qsize ;i++){
        question[i] = "NV" ;
        option1[i] = "NV" ;
        option2[i] = "NV" ;
        option3[i] = "NV" ;
        option4[i] = "NV" ;
        correctOption[i] = "NV" ;
        qflag[i] = false ;
    }

    // Student related arrays 
     
     for(int i = 0 ;i<usize ; i++){
         username[i] = "NV" ;
         passwords[i] = "NV" ;
         scores[i] = -1 ;
         uflag[i] = false ;
         totalMarks[i] = 0 ;
     }
    


    

    loadData();   //Don't bother about this code, you will learn it later.

    //program header
    cout << "***************************************************************\n";
    cout << "                     Quiz System                               \n";
    cout << "***************************************************************\n";
   

    do
    {
        cout << endl;
        cout << "Choose the desired option\n";
        cout << left << setw(10) << "\t"
             << setw(25) << "1. Administrator Login"
             << setw(25) << "2. User Login"
             << setw(25) << "0. Exit";
        cout << endl;

        cout.unsetf(ios::left);
        cout.unsetf(ios::right);

        cout << "\tChoose an option: ";
        input = getValidinput012();
        cout << endl;

        switch (input)
        {

        case 1:
            // cout << "Enter the username : ";
            // cin >> user ;

            // cout << "Enter Password: ";
            // cin>> pwd ;
 
            // if (user == "Administrator" && pwd == "PF2020")
            if (loginChecker("Administrator","PF2020"))
                loggedInUserType = 1;
            else
                loggedInUserType = -1;
            break;
        case 2:
            cout << "Enter the username: ";
            cin >> user;

            cout << "Enter Password: ";
            cin >> pwd;
            // write code to search user from user list
            
            for(int i = 0;i<usize;i++){
                
                if(user == username[i] && pwd == passwords[i]){
                   userSearchFlag = true ;
                   uflag[i] = true ;
                   break ; 
                }
            }
             

            if (userSearchFlag == true)
            {
                loggedInUserType = 2;
                userSearchFlag = false ;
            }
            else
            {
                loggedInUserType = -1;
                
            }
            break;
        case 0:
            loggedInUserType = -10;
            cout << "Thank you for using system;" << endl;
            break;

        default:
            cout << "Invalid choice!!!";
            break;
        }

        if (loggedInUserType == 1) //administrator
        {
            do
            {
                cout << endl;
                cout << "Choose the desired option\n";
                cout << left << setw(20) << "\tQuestions"
                     << setw(15) << "1. Add"
                     << setw(15) << "2. Delete"
                     << setw(15) << "3. Update"
                     << setw(15) << "4. List";
                cout << endl;

                cout << setw(20) << "\tUsers"
                     << setw(15) << "5. Register"
                     << setw(15) << "6. Edit"
                     << setw(15) << "7. Delete"
                     << setw(15) << "8. List"
                     << endl;

                cout << left << setw(20) << "\t"
                     << setw(15) << "9. View Scores"
                     << setw(15) << " "
                     << setw(15) << "0. Logout";
                cout << endl;

                cout.unsetf(ios::left);
                cout.unsetf(ios::right);

                cout << "\tChoose an option: ";
                input = getValidinput09() ;

                switch (input)
                {
                case 1: { // ADDING 
                     
                    for(int i=0 ;i<qsize ; i++){
                        if(qflag[i] == false){              
                        cout<<"Enter the Question : " ;
                       // cin.ignore(100,'\n');
                        getline(cin,question[i]) ;

                        cout<<"Enter Options " ;
                        cin>>option1[i] >> option2[i] >> option3[i] >> option4[i] ;
                        cin.ignore(100,'\n') ;

                        cout<<"Enter the Correct Option : " ;
                        cin>>correctOption[i] ;
                        qflag[i] = true ;
                         break ;
                        } 
                        
 
                    }

                    

                    break; 
                    }
                case 2: {   // DELETE 
                    /* code */
                    int id ;
                    bool found = false ; 
                    // Listing All the Questions 
                    listingQuestions() ;
                    // getting user input which he/she want to delete 
                    cout<<"Select the Question ID (Q,I) to Delete a question " ;
                    cin>> id ;
                    for(int i = 0 ;i<qsize ; i++){
                        if(i == id-1 && qflag[i] == true  ){
                           question[i] = "NV" ;
                           option1[i] = "NV" ;
                           option2[i] = "NV" ;
                           option3[i] = "NV" ;
                           option4[i] = "NV" ;
                           correctOption[i] = "NV" ;
                           qflag[i] = false ;
                           found = true ;
                           break ;   
                        }
                    }
                    if(found == true)
                        cout<<"Question Deleted Successfully ! " <<endl;
                    else 
                        cout<<"Question with that ID Not Found " ; 

                    break;
                }
                case 3:{ // UPDATING
                    /* code */
                    // Displaying the list of questions  
                    int id ;
                    bool found = false ;
                    listingQuestions() ;

                    cout<<"Select the Question ID(Q,1) to update question : " ;
                    cin>> id ;

                    for(int i = 0;i<qsize ; i++ ){
                        if(i==id-1 && qflag[i] == true  ){

                            cout<<"Enter the updated Question: " ;
                            cin.ignore(100,'\n') ;
                            getline(cin,question[i]) ;

                            cout<<"Enter options :" ;
                            cin>>option1[i] >> option2[i] >> option3[i] >> option4[i] ;
                            //cin.ignore(100,'\n') ;

                            cout<<"Enter the correct answer " ;
                            cin.ignore(100,'\n') ;
                            getline(cin,correctOption[i]) ;

                            found = true ;
                            break ;
                        }
                    }
                    if(found )
                       cout<< "Question Updated Successfully !" ;
                    else 
                       cout<<"Question With that id not found " ;
                    

                    break;
                }
                case 4: { // LISTING ALL QUESTIONS 
                    /* code */
                   listingQuestions() ;
                    break;
                }
                case 5: {  // REGISTER A NEW STUDENT
                      bool available = false ;
                      for(int i=0 ;i<usize ; i++){
                        if(uflag[i] == false){              
                        cout<<"Enter Username : " ;
                        //cin.ignore(100,'\n');
                        getline(cin,username[i]) ;

                        cout<<"Enter passwords : " ;
                        getline(cin,passwords[i]) ;

                        uflag[i] = true ;
                        available = true ;
                        
                         break ;
                        } 
                    }
                    if(available)
                      cout<<"User Registered Successfully " ;
                    else 
                      cout<<"Space is Full " ;

                    break;
                }
                case 6:{ // Update STUDENT 
                    bool found = false ;
                    string name ;
                    cout<<"Enter the username to edit/update " ;
                    cin>>  name ;
                    for(int i =0 ;i<usize ; i++){
                        if(name == username[i] ){
                           cout<<"Enter the updated Username : " ;
                           cin.ignore(100,'\n') ;
                           getline(cin,username[i]) ; 

                           cout<<"Enter the Updated password : " ;
                          // cin.ignore(100,'\n') ;
                           getline(cin,passwords[i]) ;

                           found = true ;
                           break ;
                        }
                    }
                    if(found)
                       cout<<"User Updated Successfully !" ;
                    else 
                       cout<<"User with this name not found " ;
 
                    break;
                }
                case 7:{// delete student
                    /* code */
                    string name ;
                    bool found = false ;
                    cout<<"Enter the username to delete " ;
                    //cin.ignore(100,'\n') ;
                    getline(cin,name) ;

                    for(int i =0;i<usize ; i++){
                        if(name == username[i] ){
                            username[i] = "NV" ;
                            passwords[i] = "NV" ;
                            scores[i] = 0 ;
                            uflag[i] = false ; 
                            found = true ; 
                            break ;
                        } 
                    }
                    if(found)
                       cout<<"User Deleted Successfully !" ;
                    else 
                       cout<<"User Not Found " ;
                    break;
                }
                case 8: { // List of Students 
                    /* code */
                    cout<<left ;
                    cout<<setw(8)<<"U.I"<<setw(40)<<"Username"<<"Password " <<endl;
                    cout<<"******************************************************************************************"<<endl ;
                    for(int i =0 ;i<usize ; i++){
                        if(uflag[i] == true) {
                           cout<<left ;
                           cout<<setw(8)<< i+1<<setw(40)<<username[i] << passwords[i] <<endl  ;  
                        }
                    } 

                    break;
                }
                case 9:{ 
                    /* code */
                    bool found = false ;
                    cout<<"***************************************************************"<<endl ;
                    cout<<left ;
                    cout<<setw(15)<<"Username"<<setw(15)<<"Attained Marks"<<setw(15)<<" Total Marks " <<endl ;
                    cout<<"***************************************************************"<<endl ;

                    for(int i = 0 ; i<usize ; i++){
                        if(uflag[i] == true && scores[i] != -1 ){ 
                           cout<<left ; 
                           cout<<setw(15)<< username[i] << setw(15) << scores[i]  << setw(15) << totalMarks[i] <<endl ;
                           found = true ;
                        }      
                    }
                    if(found == false){
                        cout<<"None of the User have attempted Quiz"<<endl ; 
                    }

                    break;
                }
                case 0:{
                    cout << "Administrator is logged out" << endl;
                    break;
                }

                default:
                    cout << "Invalid choice!!!";
                    break;
                }
            } while (input != 0);
            input = -1; //this statment is to make sure that do not exit from outer loop
        }
        else if (loggedInUserType == 2) //user
        {   
            

         do    
            {   
                cout << endl;
                cout << "Choose the desired option\n";
                cout << left << setw(10) << "\t"
                 << setw(25) << "1. Attempt Quiz"
                 << setw(25) << "2. View Score"
                 << setw(25) << "0. Logout";
                cout << endl;

                cout.unsetf(ios::left);
                cout.unsetf(ios::right);

                cout << "\tChoose an option: ";
                input = getValidinput012();
                switch (input)
                {

                case 1:{  // Attemt Quiz
                    /* code */
                    string answer  ;
                    int score = 0 ;
                    bool proceed = true ;
                    int totMarks = 0 ;
                    

                    int id = userID(user,pwd) ;  
                    scores[id] = 0 ;

                         for(int i = 0 ;i<qsize && proceed ;i++){

                            if(qflag[i] == true){
                            cout<<left ;

                            cout<<"Q"<<i+1<<"     " <<question[i] <<endl;
                            cout<<"Options"<<endl ;
                            cout<< left ;
                            cout<<"  a."<<option1[i]<<setw(8) <<"   b."<<option2[i]<<setw(8)<<"    c."<<option3[i] << setw(8)<<"    d."<<option4[i] <<endl;
                             
                             answer = validAnswer(i) ;

                            totMarks++ ;

                            if(answer == correctOption[i]){
                               score++ ;  
                            }
                            int choice = 0 ;
                            cout<<"Do you want to proceed or submit quiz?(1/0) : " ;
                            choice = getValidinput01(); 
                            

                            if(choice == 0 ){
                                proceed = false ;
                            }
                            }
                            
                            
                        }
                        
                    scores[id] = score ;
                    totalMarks[id] = totMarks ;
                         
                          
                    
                    break;
                }
                case 2:{
                    /* code */
                    int id = userID(user , pwd) ;
                    
                    cout<<left ;
                    cout<<"************************************************************************************" <<endl ;
                    cout<< setw(15) <<"Username "<< setw(15) <<"Attained Marks " << setw(15) <<"Total Marks" <<endl ;
                    cout<<"************************************************************************************" <<endl ;
                    
                        if(uflag[id] == true){
                           cout<<setw(15)<<username[id]<<setw(15)<<scores[id]<<setw(15)<< totalMarks[id] <<endl ;   
                        }
                    


                    break;
                }

                case 0:
                    cout << "You are logged out" << endl;
                    break;

                default:
                    cout << "Invalid choice!!!";
                    break;
                }

            } while (input != 0);
            input = -1; //this statment is to make sure that do not exit from outer loop
        }
        else if (loggedInUserType == -1)
        {
            system("cls");
            cout << "You have entered invalid Credentials!!!" << endl;
        }
    } while (input != 0);

    return 0;
}

void loadData()
{
    ifstream inf1("UserList.csv");
    string line1, field1;
    vector<vector<string>> array1;
    vector<string> v1;
    string usr = "user";
    while (getline(inf1, line1))
    {
        v1.clear();
        stringstream ss(line1);
        while (getline(ss, field1, ','))
        {
            v1.push_back(field1);
        }
        array1.push_back(v1);
    }
    for (size_t i = 1; i < array1.size(); ++i)
    {
        uflag[i]=true;
        username[i] = array1[i][0];
        passwords[i] = array1[i][1];
    }
    inf1.close();

    ifstream in("QuesionsList.csv");
    string line, field;
    vector<vector<string>> array;
    vector<string> v;

    while (getline(in, line))
    {
        v.clear();
        stringstream ss(line);
        while (getline(ss, field, ','))
        {
            v.push_back(field);
        }
        array.push_back(v);
    }
    for (size_t i = 1; i < array.size(); ++i)
    {
        qflag[i] =true;
        question[i] = array[i][0];
        option1[i] = array[i][1];
        option2[i] = array[i][2];
        option3[i] = array[i][3];
        option4[i] = array[i][4];
        correctOption[i] = array[i][5];
    }
    in.close();
}


// This will return the user id 
int userID(string user , string pwd){
    int id ;
     for(int i = 0;i<usize;i++){
          if(user == username[i] && pwd == passwords[i]){
             id = i ;
             break ; 
            }   
            
     }
     return id ;
}
// This funcion will list all teh Questions 
void listingQuestions() {
    cout<<left ;
    cout<<setw(10)<<"Q1"<< setw(60)<<"Question "<< setw(10)<<"option1"<<setw(10)<<"option2"<<setw(10)<<"option3"<<setw(10)<<"option4" <<setw(10)<<"correct answer " <<endl ;
    cout<<"**************************************************************************************************************************" <<endl ;
    for(int i =0 ; i<qsize ;i++){
        if(qflag[i] == true ){
            cout<< setw(10)<<i+1<<setw(65)<<question[i]<<setw(10)<<option1[i]<<setw(10)<<option2[i]<<setw(10)<<option3[i]<<setw(10)<<option4[i]<<setw(10)<<correctOption[i] <<endl ;  
         }
    } 

}

// it will assure that input is only 0,1,2 
long getValidinput012(){
    long num ;
    char input[50] ;
    bool isNumber = false ;
    while(isNumber == false){
    cout<<"\t" ;
    cin>>input ;
    cin.ignore(100,'\n') ;
    if((input[0]=='0' || input[0] =='1'|| input[0] =='2') && input[1] ==  '\0' ){
         num = atol(input) ;
         isNumber = true  ;
         return num ;
         break ;
    }
    else {
         cout<<"\tInvalid input " <<endl ;  
    }
  }
}
// it will assure that input is only 0,1 
long getValidinput01() {
    long num;
    char input[50];
    bool isNumber = false;
    while (!isNumber) {
        
         cin >> input;
         cin.ignore(100, '\n');
     
        if ((input[0] == '0' || input[0] == '1') && input[1] == '\0') {
            num = atol(input); 
            isNumber = true;
            return num;
        } 
        else {
            cout << "\tInvalid input." << endl;
            cout<<"Do you want to proceed or submit quiz?(1/0) : " ;
        }
    }
   
}


// it will assure that input is from 0 to 9 
long getValidinput09(){
    long num ;
    char input[50] ;
    bool isNumber = false ;

    while(isNumber == false){
    cout<<"\t" ;
    cin>>input ;
    cin.ignore(100,'\n') ;

       if((input[0]>='0' && input[0] <='9') && input[1] == '\0' ){
         num = atol(input) ;
         isNumber = true ;
         return num ;
         break ;
       }
       else {
         cout<<"\tInvalid Input ." <<endl ;
       }
     
   
  }
}
// this will check the answer matches any option or not  
string validAnswer(int id ) {
      
      string answer ;
      bool isvalidAnswer = false ;
    
      while(isvalidAnswer == false){
      cout<<"Enter your Answer : " ;
      getline(cin,answer) ;  

       
     if(answer == option1[id] || answer == option2[id] || answer == option3[id] || answer == option4[id] ){
       isvalidAnswer = true ;
       return answer ;
     }    
     else {
        cout<<"Answer you write does not matches any of the options . Please write carefully " << endl ;
       
      }
     
   }
   
   
}