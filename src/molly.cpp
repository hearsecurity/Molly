#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std; 

struct response_status {

    string response; 
    int code; 
}; 

struct file_status {
    
    int code; 
    string line; 
};

string splitString(string input, char separator) {

    size_t pos;
    vector<string> text;

    while (!input.empty()) {

        pos = input.find(separator); 

        if (pos == string::npos) {
            text.push_back(input);
            break;
        }
        text.push_back(input.substr(0, pos));

        input = input.substr(pos + 1);
    }
    return text[1]; 
}

struct file_status check_existence(char* filename, string search)
{
    int offset; 
    string line;
    ifstream Myfile;

    struct file_status status; 

    Myfile.open (filename);

    if (Myfile.is_open())
    {
        while (!Myfile.eof())
        {
            getline(Myfile,line);
            if ((offset = line.find(search, 0)) != string::npos) 
            {
                status.code = 0; 
                status.line = line;
                Myfile.close();
                return status;
            }
        }
        Myfile.close();
    }
    
    status.code = 1;
    status.line = ""; 

    return status;
}

void set_response(string question, string learn) {

    std::ofstream outfile;
    outfile.open("adb.txt", ios_base::app);
    outfile <<  question + ":" + learn << endl;
}

struct response_status get_response(string question) {
     
    struct response_status value; 
    struct file_status status; 

    status = check_existence("adb.txt", question);
    value.code = status.code;
    
    if(value.code == 0) {
        value.response = splitString(status.line, ':');
    }      
    return value;
}


int main() {

    string question; 
    string response; 
    string learn; 

    struct response_status value; 

    while(1) {
        
        cout << "\nQuestion: "; 
        getline(cin, question);  
        value = get_response(question);
        
        if(value.code == 1) {

            cout << "Learn: ";
            getline(cin, learn);
            set_response(question, learn); 

        }else if(value.code == 0){

            cout << "\nResponse: ";   
            cout << value.response << endl;
        }


    }
return 0; 
}