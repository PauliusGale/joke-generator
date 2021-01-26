#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>


using namespace std;

class Jokes{
    private:
    string *Q, *A; //questions and answers
    int n, r;      //n - size of arrays, r - additional number
    public:
    Jokes():n(0){}
    ~Jokes(){     
       delete[] Q;
       delete[] A;
    }
    Jokes(int n){
    this->n=n;
    Q=new string[3*n]; 
    A=new string[3*n]; 
    }
    void get_jokes(){
        ifstream fd("jokes.txt");
        fd.ignore(10, '\n');
        for(int i=0; i<n; i++){
            getline(fd, Q[i]);
            getline(fd, A[i]);
        }
        fd.close();
    }
    void print_all(){
        for(int i=0;i<n;i++){
            cout<<i+1<<". "<<Q[i]<<" "<<A[i]<<endl;
        }
    }
    void print_random(){
        r=rand() % (n-1) ;
        cout<<Q[r]<<" "<<A[r]<<endl;
    }

    void print_chosen(){
        cout<<"Enter the number from 1 to "<<n<<endl;
        cin>>r;
        cout<<Q[r-1]<<" "<<A[r-1]<<endl;
    }
    void print_in_database(){
        string name;
        cout<<"Enter full name of file you want to print all jokes to (e.g. file.txt)."<<endl;
        cin>>name;
        if(name=="jokes.txt") { //the file where jokes are stored
            cout<<"Wrong file name. Try another one"<<endl;
            return;
        }
        ofstream fr(name);
        for(int i=0;i<n;i++){
            fr<<i+1<<". "<<Q[i]<<" "<<A[i]<<endl;
        }
        fr.close();
        cout<<"Your jokes were printed :)"<<endl;
    }
    void print_mix(){
        r=rand() % (n-1);
        cout<<Q[r]<<" ";
        r=rand() % (n-1); 
        cout<<A[r]<<endl;

    }
    void write_new(){
        size_t bad;
        cout<<"Enter the question. Don't forget the question mark - ?."<<endl;
        cin.ignore(2, '\n');
        getline(cin, Q[n]);
        bad = Q[n].find("shit");
        if (bad != string::npos){
            cout << "No inappropriate words allowed!" << endl;
            return;
        }
        cout<<"Enter the answer. "<<endl;
        getline(cin, A[n]);
        bad = A[n].find("shit");
        if (bad != string::npos){
            cout << "No inappropriate words allowed!" << endl;
            return;
        }
        n++;
        cout<<"Your joke was saved :)"<<endl;
    }

    void exit(){
        ofstream fd("jokes.txt");
        fd<<n<<endl;
        for(int i=0; i<n; i++){
            fd<<Q[i]<<endl;
            fd<<A[i]<<endl;
        }
        fd.close();
    }
};

int main(){

int n=0;
char key='7';
ifstream fd("jokes.txt");
fd>>n;
if(n==0) {
    cout<<"No file of jokes found!";
    cin.get();
    return 0;
}
fd.close();
Jokes A(n);
 A.get_jokes();
cout<<"Welcome!";
while(key!='0'){
    cout<<'\n';
    cout<<"Enter 1 to print all full jokes, 2 - random full jokes, 3 - chosen jokes, \n";
    cout<<"4 - the mix, 5 - print all jokes to database, 6 - write a new one or 0 - to exit"<<endl;
    cin>>key;
    switch(key){
        case '6':
            A.write_new();
            break;
        case '5':
            A.print_in_database();
            break;
        case '4':
            A.print_mix();
            break;
        case '3':
            A.print_chosen();
            break;
        case '2':
            A.print_random();
            break;
        case '1':
            A.print_all();
            break;
        case '0':
            cout<<"Do you want to save changes? If yes - enter Y, if no - N."<<endl;
            char yn;
            cin>>yn;
            if(yn=='Y'||yn=='y') {
                A.exit();
            }
            return 0;
            break;
        default:
            cout<<"Error. Wrong number."<<endl;
        }
}

return 0;
}
