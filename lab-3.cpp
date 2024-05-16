#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <sstream>
#include <map>
#include <math.h>

using namespace std ;

class PhoneRecord {
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string& n, const string& org, const vector<string>& numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const {
        return name;
    }

    string getOrganisation() const {
        return organisation;
    }

    vector<string> getPhoneNumbers() const {
        return phoneNumbers;
    }
};

class HashTableRecord {
private:
    int key;
    PhoneRecord* element; // Pointer to PhoneRecord
    HashTableRecord* next;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord* rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const {
        return key;
    }

    PhoneRecord* getRecord() const {
        return element;
    }

    HashTableRecord* getNext() const {
        return next;
    }

    void setNext(HashTableRecord* nxt) {
        next = nxt;
    }
};

class PhoneBook {
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord* hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    // Add your own implementation for hashing
    int computeHash(string str){
    long long int hash_val=0,p=1000000007,xi=1;
    int i=0,j,m=263,x=263;
    int num;
   
    for(i=0;i<str.length();i++){
        num=str.at(i);

       
        xi=pow(x,i);
     //    cout<<"xi = "<<"at i= "<<i<<" "<<xi<<endl;
        // cout<<num*(xi%p)<<endl;


        // hash_val=hash_val+(num*(xi%p));
        hash_val=hash_val+(num*xi%p);
        // cout<<hash_val<<endl;   
        
        


    }

    
    hash_val=hash_val%m;
    hash_val = (int)hash_val;

    // cout<<hash_val<<endl;



    return hash_val;
    
}


    // Add your own implementation for adding a contact
    void addContact( PhoneRecord* record){
        int hash_val;
        // string str;
        // str=(record->getName());
         string inputString = record->getName();

        // Create an input string stream
        istringstream iss(inputString);

        vector<string> words;
        string word;

        // Read words one by one from the stringstream
        while (iss >> word) {
            words.push_back(word);
        }


        for(int i=0 ; i<words.size();i++){
            hash_val=computeHash(words[i]); // computing hash value
            HashTableRecord *htr= new HashTableRecord(hash_val,record);  //initalised key and phonerecord pointer // creating new htr for each name piece


            //directly adding if first element is empty
            if(hashTable[hash_val]==nullptr){
                hashTable[hash_val]=htr;
                htr->setNext(nullptr);

            }

            //if not empty then creating a linked list
            else{
                HashTableRecord* temp= hashTable[hash_val];
                while(temp->getNext()!=nullptr){

                    temp=temp->getNext();

                }
                // now temp is basically my last node from current linked list
                    
                    temp->setNext(htr);
                    htr->setNext(nullptr);
            }



                

        }


        // HashTableRecord* ptr=hashTable[hash_val];
  
        // while(ptr!=nullptr){
        //     cout<<"hash_value= "<<hash_val<<endl;
        //     cout<<ptr->getRecord()->getName()<<endl;
        //     ptr=ptr->getNext();
        //     // cout<<ptr<<endl;
        // }

        
    };

    // Add your own implementation for deleting a contact
    bool deleteContact(const string* searchName){
        // string str = *searchName;
        bool check=true;
        int i=0;
       vector<PhoneRecord*> list = fetchContacts(searchName);
    //    printlist(list);
        if(list.empty()){
            check=false;
            return check;
        }
        
        PhoneRecord* selectedpr=nullptr;

        for(i=0;i<list.size();i++){
                if(list[i]->getName()==*searchName){
                    selectedpr=list[i];
                    break;
                }
                // lets say search name isnt complete name
                    string inputString = list[i]->getName();

                    // Create an input string stream
                    istringstream iss(inputString);

            vector<string> words;
            string word;

            // Read words one by one from the stringstream
            while (iss >> word) {
                words.push_back(word);
            }

            for(int j=0;j<words.size();j++){

             if(words[j]==*searchName){
                    selectedpr=list[i];
                    break;
                }
            }

            words.clear();

        }
            // cout<<selectedpr->getName()<<endl;

        string inputString = selectedpr->getName();

        // Create an input string stream
        istringstream iss(inputString);

        vector<string> words;
        string word;

        // Read words one by one from the stringstream
        while (iss >> word) {
            words.push_back(word);
        }

        for( i=0 ; i<words.size();i++){
            int key = computeHash(words[i]);
            // cout<<words[i]<<endl;
            HashTableRecord *htr = hashTable[key];
            // cout<<selectedpr<<endl;
            if(htr->getRecord()->getName()==selectedpr->getName()){
                //  cout<<htr->getRecord()->getName()<<endl;
                //  cout<<"hello bhai-1"<<endl;

                 hashTable[key]=htr->getNext();
            }
            else{
                while(htr->getNext()->getRecord()->getName()!=selectedpr->getName()){
                //  cout<<htr->getRecord()->getName()<<endl;
                    // cout<<"hello bhai-2"<<endl;
                    htr= htr->getNext();
                }
                    //here htr->next contains record to be deleted
                    htr->setNext(htr->getNext()->getNext());
            }

            

        }


         


        return check;
    };

    // Add your own implementation for fetching contacts
    vector<PhoneRecord*> fetchContacts(const string* query){

        int key;

       vector < vector<PhoneRecord*> > list;
        vector<PhoneRecord*>lol;
        vector<PhoneRecord*>final_list;
        string inputString = *query;

        // Create an input string stream
        istringstream iss(inputString);

        vector<string> words;
        string word;

        // Read words one by one from the stringstream
        while (iss >> word) {
            words.push_back(word);
        }

        vector<int> count(words.size(),0);

       

        //got words array
        for(int i=0;i<words.size();i++){
            count[i]=0;
        

           key= computeHash(words[i]);
        //    cout<<"given key= "<<key<<endl;

            for(int j=0;j<HASH_TABLE_SIZE;j++){
                HashTableRecord* ptr = hashTable[j];
                if(ptr!=nullptr){

                //  cout<<"ptr key= "<<ptr->getKey()<<endl;
                if(ptr->getKey()==key){
                    while(ptr!=nullptr){
                        count[i]++;

                        lol.push_back(ptr->getRecord());
                        ptr=ptr->getNext();

                    }
                }
                }

            }
            list.push_back(lol);
            lol.clear();
            // cout<<"count= "<<count[i]<<endl;

        }

       // list is a 2-d vector conatining record pointers 
       // now i will find max in count array
       while(!count.empty()){
        int max=0;
        for(int i=0;i<count.size();i++){
                if(count[max]<=count[i]){
                    max=i;
                }
        }

            for(int j=0;j<list[max].size();j++){
                final_list.push_back(list[max][j]);

            }
        count.erase(count.begin()+max);
                

       }
           //printing final list
    //    for(int i=0;i<final_list.size();i++){
    //         cout<<final_list[i]->getName()<<endl;
    //    }


        return final_list;

    }

    // Add your own implementation for counting records pointing to a contact
    // int countRecordsPointingTo(const PhoneRecord* record) const;

    // Add your own implementation for reading records from a file
    void readRecordsFromFile(const string& csv_file_path){ 
         // Initialize a vector of vectors to store the words arrays
       vector<vector<string>> words_arrays;
       int hash_val;

    // Open the CSV file for reading
       ifstream csv_file(csv_file_path);
       string line;

      // Read each line from the CSV file
    while (  getline(csv_file, line) ) {
           vector<   string> words;
           istringstream iss(line);
           string word;

        // Split the line into individual words using commas as the separator
        while (   getline(iss, word, ',')) {
            words.push_back(word);
        }

        // Append the words array to the list of word arrays
        words_arrays.push_back(words);
    }

    // Close the CSV file
     csv_file.close();


     for(int i=0;i<words_arrays.size();i++){
        string name,org;
        name = words_arrays[i][0] ;//extracting name
        org = words_arrays[i][words_arrays[i].size()-1]; // extracting org. in string
        vector<string> numbers;
        
        for(int j=1 ; j<words_arrays[i].size()-1;j++){
            numbers.push_back(words_arrays[i][j]);
        }

        // extracted , name , org and (phone number in vector`)
    
        PhoneRecord *pr = new PhoneRecord(name,org,numbers); 
        //made a phone record object with all enitites initialised

        addContact(pr);
        //adding record in hashtable array

        
     }
          

    }


    void printHashTable(){
        int count=0;
        for(int i=0;i<HASH_TABLE_SIZE;i++){
            HashTableRecord* ptr=hashTable[i];
            // cout<<"i = "<<i<<" ptr= "<<ptr<<endl;
            while(ptr!=nullptr){
                cout<<"hash_value= "<<ptr->getKey()<<endl;
                cout<<ptr->getRecord()->getName()<<endl;
                ptr=ptr->getNext();
                count++;
                // cout<<ptr<<endl;
            }

            cout<<endl;

        }
        // cout<<count;
    }


    void printlist(vector<PhoneRecord*>final_list){
            for(int i=0;i<final_list.size();i++){
            cout<<final_list[i]->getName()<<endl;
       }
    }
    // Destructor
    // ~PhoneBook();
};

    
// int main() {
//     PhoneBook *ph2 = new PhoneBook();
//     ph2->readRecordsFromFile("Details.txt");
//     // ph2->printHashTable();
//     string str="Bansal";
//     vector<PhoneRecord*>list_1=ph2->fetchContacts(&str);
//     // ph2->printlist(list_1);
//     cout<<endl;
//     ph2->deleteContact(&str);
//     cout<<endl;
//     vector<PhoneRecord*>list_2=ph2->fetchContacts(&str);
//     // ph2->printlist(list_2);

//     cout<<ph2->computeHash("Doe")<<endl;
//     cout<<ph2->computeHash("Brown")<<endl;
//     // ph2->printHashTable();
//     //    cout<< ph2->computeHash("Mishra")<<endl;
//     //    cout<< ph2->computeHash("Das")<<endl;
//     return 0;
// }
    



