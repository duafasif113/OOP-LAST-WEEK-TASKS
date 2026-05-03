#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Transaction {
    double Amount;
    string no;
public:
    Transaction(){//deafault constructor
        Amount=0.0;
        no="0300-0000000";
    }
     void setAmount(double a){
        while(a<=0){
            cout<<"invalid Amount Negative or Zero Amount are not Allowed!"<<endl;
            cout<<"enter new Amount"<<endl;
            cin>>a;
        }
        Amount=a;
    }
    double getA(){
         return Amount; 
        }
    void setPhone(string n){ 
        while(n.length()!=12||n[0]!='0'|| n[1]!='3'||n[4]!='-')
        {
         cout<<"Enter a valid phone!"<<endl; 
         cin>>n;
         } 
         no=n; 
        }
    string getPhone() {
         return no; 
        }
    Transaction(double a, string n){//parametrired constructor
        setAmount(a);
        setPhone(n);
    }
    Transaction(double a){//convenince  constructor
        setAmount(a);
        no = "0300-0000000";
    }
    virtual double commission()=0;
    virtual string type()=0;
    virtual ~Transaction(){

    ofstream out("input.txt",ios::app);
    if(!out.is_open()){
        cout<<"file not opened";
    }
    out<<"Transaction closed: "<<no<<" | Amount: "<<Amount<<endl;
    out.close();}
};
class Mobile_load : public Transaction {
    string network;
public:
    Mobile_load(){ //default
	network = "Unknown";
	 }
    Mobile_load(double A, string n, string net):Transaction(A, n){ //parametrized constructor
	network = net;
	 }
    double commission(){
        int com=getA()*0.025;//floor to rupee
        if(com<2){
            com=2;	
				}
        return com;
    }
    string type(){ 
	return "Mobile load"; 
	}
};
class EasyPaisa:public Transaction{
    string direction;
public:
    EasyPaisa(){//default
	 direction="cash-in";
	  }
    EasyPaisa(double A,string n,string d):Transaction(A, n) {
	 direction=d;
	  }
    double commission(){
        double A=getA();
        if (A<=1000) 
		return 10;
        else if (A<=5000) 
		return 25;
        else
		 return 25+(A-5000)*0.003;
    }
    string type() { 
	return "EasyPaisa" +direction; 
	}
};
class SimReplacement:public Transaction{
public:
SimReplacement(){//deafault constructor
       setPhone("0300-0000000");
         setAmount(250.0);
         }

    double commission() {
	 return 150.0;
	  }
    string type() { 
	return "Sim Replacement";
	 }
};

class DailyLedger {
    Transaction* list[100];
    int Dcount;
public:
    DailyLedger(){ //deafult
	Dcount=0;
	 }
    void add(Transaction* t){
        if(Dcount<100){
            list[Dcount]=t;
            Dcount++;
        }
    }
    void showReport(){
        double totalBalance=0;
        double totalComm=0;
        for(int i=0;i<Dcount;i++){
            cout<<list[i]->type()<< " | "<<list[i]->getPhone()<<" | Amount: "<<list[i]->getA()<<" | Comm: "<<list[i]->commission()<<endl;
            totalBalance+=list[i]->getA();
            totalComm+=list[i]->commission();
        }
        cout<<"Total Cash Drawer: "<<totalBalance<<endl;
        cout<<"Total Commission Earned: "<<totalComm<<endl;
    }

    void closeDay() {
        ofstream r("receipt.txt");
        r<<"Day End Summary"<<endl;
        for(int i=0;i<Dcount;i++){
            r<<"Type: "<<list[i]->type()<<" Cash Drawer"<<list[i]->getA()<<"Rs "<<" Commision: "<<list[i]->commission()<<"Rs"<<endl;
            delete list[i];
        }
        r.close();
    }
};
int main() {
    DailyLedger shop;
    shop.add(new Mobile_load(500,"0308-6566919","Jazz"));
    shop.add(new EasyPaisa(6000,"0345-1234567","cash-out"));
    shop.add(new SimReplacement());
    shop.showReport();
    shop.closeDay();
    return 0;
}
