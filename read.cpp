#include<stdio.h>
#include<sstream>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<chrono> // NOLINT （build/c++11）

using namespace std;

class Timer{
    public:
        chrono::high_resolution_clock::time_point sttime;
        chrono::high_resolution_clock::time_point edtime;
        double elap;
        void Reset();
        void Currenttime();
        void prtime();
};

void Timer::Reset(){
    sttime = chrono::high_resolution_clock::now();
}

void Timer::Currenttime(){
    edtime = chrono::high_resolution_clock::now();
    elap = chrono::duration<double,std::micro>(edtime-sttime).count();
}

void Timer::prtime(){
    cout<<"CPU time:"<<elap<<" microseconds"<<endl;
}


int value(const string& a){
	if(a=="new"){
		return 1;
	}
	else if(a =="used"){
		return 2;
	}
	else{
		return 3;
	}
}

struct book{
    int isbn;
    string langu;
    string version;

    book() : isbn(0), langu(""), version(""){}

    friend std::ostream& operator<<(std::ostream& os, const book& a){
            os<< a.isbn <<endl;
            os<< a.langu <<endl;
            os<< a.version <<endl;
    return os;
    }
}; 
    
    bool operator<(const book& a, const book& b){
	int k,j;
	
	if(a.isbn!=b.isbn){
		return a.isbn<b.isbn;
	}
	else{
		k=value(a.version);
		j=value(b.version);
		
		if(k!=j){
			return k<j;
		}
		else{
			return a.langu<b.langu;
		}
	}
    }

    bool operator==(const book& a, const book& b){
    return (a.isbn==b.isbn)&&(a.version==b.version)&&(a.langu==b.langu);
    } 
    
       
int lns(vector<book>& a, vector<book>& b){
	int len= a.size(), fish = b.size();
    int i,j;
    int count=0;
    for(j=0;j<fish;j++){
        for(i=0;i<len;i++){
            if(a.at(i)==b.at(j)){
                count ++;
                break;
            }
        }
    }
    return count;
}

int binarys(vector<book>& a, vector<book>& b){
    int count=0;
    vector<book> cp = a;
    sort(cp.begin(),cp.end());
    int bite,bs=b.size();
    int i=0;
    int j=a.size()-1;
    int m = (i+j)/2;
    for(bite=0;bite<bs;bite++){
        while(i<j){
            if(a.at(m)<b.at(bite)){
                i=m+1;
                m=(i+j)/2;
            }
            else{
                j=m;
                m=(i+j)/2;
            }
        }
	if(a.at(i)==b.at(bite)){
		count+=1;
	}
    }
    return count;
}

int recru(vector<book>& a, book& b, int i, int j){
    int m=(i+j)/2;
    if(i<j){
        if(a.at(m)==b){
	   return 1;  
        }
        else if(a.at(m)<b){
           return recru(a,b,m+1,j);
        }
        else{
           return recru(a,b,i,m);
        }
    } 
    else{
        return 0;
    }   
}

int recrusivebs(vector<book>& a,vector<book>& b){
    int count=0;
    vector<book> cp = a;
    sort(cp.begin(),cp.end());
    int bite,bs=b.size();
    int i=0;
    int j=a.size()-1;
    for(bite=0;bite<bs;bite++){
        count +=recru(cp,b.at(bite),i,j);
    }
    return count;
}


void readtovector(string& flname, vector<book>& new1){

    ifstream nb(flname);
    book wb;

    if(!nb){
        cerr<<"Error: cannot open file "<<flname<<endl;
   	exit(-1); 
    }
    string kn;
    string lan;
    string ver;
    string a;
    int b;
    
    while(getline(nb,kn)&&!kn.empty()){
        
        stringstream ss(kn);
        
        getline(ss,a,',');
        getline(ss,lan,',');
        getline(ss,ver);

    //cout<<endl;
  
    //cout<<a<<'x'<<lan<<'x'<<ver<<'x'<<endl;

    b = stoi(a);

    wb.isbn=b;
    wb.langu=lan;
    wb.version=ver;

    new1.push_back(wb);

    wb=book();
    
    }
    nb.close();
}
    
int start(vector<book>& a,vector<book>& b){
    char choice;
    int fcount=0;
    Timer ct;
    int i=1;

while(i==1){
    cout<<"Choice of search method ([l]inear, [b]inary, [r]ecrusiveBinary)?"<<endl;
    cin>>choice;
    switch(choice){
        case 'l':
	    ct.Reset();
            fcount += lns(a,b);
                i=0;
            break;
        
        case 'b':
	    ct.Reset();
            fcount += binarys(a,b);
                i=0;
            break;
            
        case 'r':
	    ct.Reset();
            fcount += recrusivebs(a,b);
                i=0;
            break;
            
        default:
            cout<< "Incorrect choice"<<endl;
            i=1;
            break;
    }
}
    ct.Currenttime();
    ct.prtime();
    return fcount;
}



int main(int argc, char* argv[]){
    vector<book> new1,rq1;
    string nwbook,rqbook,ansbook;
    if(argc==3){
        nwbook = argv[1];
        rqbook = argv[2];
	ansbook = "found.dat";
    }
    else if(argc == 4){
        nwbook = argv[1];
        rqbook = argv[2];
        ansbook = argv[3];
    }
    else{
        cerr<<"Usage:.SearchNew";
	return 0;
    }

    readtovector(nwbook,new1);
    readtovector(rqbook,rq1);

   //  sort(new1.begin(),new1.end());
   //  for(auto i : new1) cout<< i <<endl;
   //  for(auto i : rq1) cout<< i <<endl;

    
    
    int fcount;
    
    fcount = start(new1,rq1);
    
        ofstream ans(ansbook);
        ans<<fcount;
        cout<<"write complete"<<endl;
        ans.close();

    
    return 0;
}
































