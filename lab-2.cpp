#include <bits/stdc++.h>
#include<iostream>
#include <sstream>
using namespace std;


class StudentRecord{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName() {
        return studentName;
    }
    void set_studentName(string Name) {
        studentName = Name;
    }
    string get_rollNumber() {
        return rollNumber;
    }
    void set_rollNumber(string rollnum) {
        rollNumber = rollnum;
    }
};



class Node{
	private:
		Node* next=nullptr;
		StudentRecord* element=nullptr;
	public:
	    Node* get_next() {
	        return next; 
	    }
	    StudentRecord* get_element() {
	        return element; 
	    }

	    void set_next(Node* value){
	    	next = value;
            
	    }
	    void set_element(StudentRecord* student){
	    	element = student;
            
	    }

};

class Entity {
private:
    string name;
    Node* iterator=nullptr;

public:
    string get_name() const{
        return name;
    }
    void set_name(string Name) {
        name = Name;
    }
    Node* get_iterator() const{
        return iterator;
    }
    void set_iterator(Node* iter) {
        iterator = iter;
    }
};


class LinkedList : public Entity {
    // Implement LinkedList members here
    public:
        void add_student(const StudentRecord& student){
            
                // cout<<student.get_studentName()<<endl;
                StudentRecord* stud=new StudentRecord(student);
                Node *node=new Node(); 
                node->set_element(stud);
                // cout<<node->get_element()->get_studentName()<<endl; //for checking is element actually getting added to node
                // cout<<"address of iterator= "<<get_iterator()<<endl;
                // cout<<"address of current node= "<<node<<endl;
                // cout<<"address of next node= "<<node->get_next()<<endl;
                // cout<<endl;
                node->set_next(get_iterator());
                set_iterator(node);
                
               

        }
             


        void delete_student(string studentName){


             Node *prev = get_iterator();
            
            //if first element is to be deleted
             if(prev->get_element()->get_studentName()==studentName){
                set_iterator(prev->get_next());
                
             }

            while(prev->get_next()->get_element()->get_studentName()!=studentName){
                prev=prev->get_next();

            }

            //    cout<<"address of node to be deleted "<<prev->get_next();

            prev->set_next(prev->get_next()->get_next());
            
        }
};  
    vector<StudentRecord> students;
    vector<LinkedList> EntityArray;

bool check_duplicate(string str){

    bool check = false;
    for(int i=0 ; i<EntityArray.size();i++){
         if(str==EntityArray[i].get_name()){
            check=true;
            break;
         }
         else{
            check=false;
         }
    }

    return check;


}

bool check_student(string name , string roll){ //checks for duplicate students in students vector using name and roll number 
    int i=0;
    bool check=true;
    for(i=0;i<students.size();i++){
        if(name==students[i].get_studentName() ){
            check=false;
            
            break;
        }
        
    }

    return check;
}


void get_entites(string file_path){
    
    ifstream file(file_path);

    string ent_str,line,name;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, ent_str, ',');
        
        while(!ss.eof()){
            getline(ss,ent_str,','); //entity strings
            if(ent_str[0]=='['){
                ent_str=ent_str.substr(1);
            }
            if(ent_str[ent_str.size()-1]==']'){
                ent_str=ent_str.substr(0,ent_str.size()-1);
            }
            // got filtered entity string from above if statements
                // cout<<ent_str<<endl;
                // c++;

            if(!check_duplicate(ent_str)){

                LinkedList entity_obj;
                entity_obj.set_name(ent_str);
                entity_obj.set_iterator(NULL);



                EntityArray.push_back(entity_obj);


             }
           
            
        }
            
        
    }

    file.close();

    

}



   


void read_input_file(string file_path){
    ifstream inputFile(file_path); 
   int i,j,check=1,counter=-1;

     string line;
    while ( getline(inputFile, line)) {
         istringstream iss(line);
         string token;

        // Vector to store individual words
         vector< string> values;

        while ( getline(iss, token, ',')) {
             istringstream iss2(token);
             string word;

            while ( getline(iss2, word, '[')) {
                if (!word.empty()) {
                     istringstream iss3(word);
                     string bracketWord;

                    while ( getline(iss3, bracketWord, ']')) {
                        if (!bracketWord.empty()) {
                            values.push_back(bracketWord);
                        }
                    }
                }
            }
        }


        StudentRecord s;
        s.set_studentName(values[0]);
        s.set_rollNumber(values[1]);

        if(check_student(s.get_rollNumber(),s.get_rollNumber())){

            counter++;
            students.push_back(s);

        }

        //this gives entity array
        get_entites(file_path);
        
        for(j=0;j<EntityArray.size();j++){
            for(i=2;i<values.size();i++){
            if(values[i]==EntityArray[j].get_name()){
                    EntityArray[j].add_student(students[counter]);
            }

            }
        }
        
        
    }

    inputFile.close();

    
        
        

  
        
    



}




    





