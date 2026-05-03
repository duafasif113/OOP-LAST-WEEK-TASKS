
#include <iostream>
#include <string>
#include <iomanip>//for table
using namespace std;
class Payable {
public:
    virtual double calculate_tax()=0;
    virtual double calculate_gross_pay()=0;
    virtual string get_name()=0;
    virtual string get_category()=0;
    virtual ~Payable(){}
     void generate_pay_slip(string month){//polymorphism method overloading
         cout<<"Slip for: "<<month<<endl;
     }
    void generate_pay_slip(string sDate,string eDate){
         cout<<"Slip from: "<<sDate<<" to "<<eDate<<endl;
   }
};
//2 type of tax
class Slab_tax:public Payable{
public:
    double calculate_tax(){
        double gross=calculate_gross_pay();
        if (gross<=50000)
         return 0;
        if (gross<=100000)
         return gross*0.05;
        return gross*0.125;
    }
};
class Flat_tax:public Payable{
protected:
    double rate;
public:
    Flat_tax(double r):rate(r){}
    double calculate_tax(){
         return calculate_gross_pay()*rate;
         }
};
class fixed_sal{
protected:
    double baseSalary;
public:
    fixed_sal(double s):baseSalary(s){}
};
//employees
class Consultant_doctor:public Flat_tax{
    string name;
    double opd,surgery;
public:
    Consultant_doctor(string n,double o,double s):Flat_tax(0.15),name(n),opd(o),surgery(s){}
    double calculate_gross_pay(){ 
        return(opd*3500)+(surgery*0.40);
    }
    string get_name(){return name;
    }
    string get_category(){
         return"Consultant Doctor"; 
    }
};
class Salaried_doctor:public Slab_tax,public fixed_sal{
    int nights;
    string name;
public:
    Salaried_doctor(string n,double s,int nts):fixed_sal(s),nights(nts),name(n){}
    double calculate_gross_pay(){
         return baseSalary+(nights*2000);
         }
    string get_name() 
    {
        return name;
     }
    string get_category(){ 
        return "Salaried Doctor";
    }
};

class Senior_nurse:public Slab_tax,public fixed_sal{
    int nights,years;
     string name ;
public:
    Senior_nurse(string n,double s,int nts,int yrs):fixed_sal(s),nights(nts),years(yrs),name(n) {}
    double calculate_gross_pay(){ 
        return baseSalary+(nights*800)+(years> 5? 1500:0); 
    }
    string get_name(){ 
        return name; }
    string get_category(){
         return "Senior Nurse";
         }
};

class Junior_nurse :public Flat_tax,public fixed_sal {
    string name;
public:
    Junior_nurse(string n, double s) :Flat_tax(0.025),fixed_sal( s),name(n){}
    double calculate_gross_pay(){ 
        return baseSalary; 
    }
    string get_name(){
         return name;
         }
    string get_category(){
         return "Junior Nurse";
         }
};
class Admin_staff :public Slab_tax,public fixed_sal {
    string name;
public:
    Admin_staff(string n,double s) :fixed_sal(s),name(n){}
    double calculate_gross_pay()
    { 
        return baseSalary;
     }
    string get_name(){
         return name;
         }
    string get_category(){ 
        return "Admin Staff"; 
    }
};
class Ward_Boy :public Payable{
    string name;
    double dailyWage;
    int days;
    bool isEidMonth;
public:
    Ward_Boy(string n,double w, int d,bool e):name(n), dailyWage(w), days(d), isEidMonth(e) {}
    double calculate_gross_pay(){
        double pay= dailyWage*days;
        if (isEidMonth) 
        pay +=(dailyWage*7);
        return pay;
    }
    double calculate_tax()
        { return 0;
         }
    string get_name(){
         return name; }
    string get_category(){
         return "Ward Boy"; 
        }
};
int main(){
    Payable*staff[10];//list
    int count=0;

    staff[count++]=new Consultant_doctor("Dr. Ali", 20, 100000);
    staff[count++]=new Salaried_doctor("Dr. Sara", 80000, 5);
    staff[count++]=new Senior_nurse("N. Amina", 45000, 10, 7);
    staff[count++]=new Junior_nurse("N. Zoya", 35000);
    staff[count++]=new Ward_Boy("Aslam", 1200, 26, true);
    staff[count++]=new Admin_staff("Bilal", 60000);
    staff[count++]=new Consultant_doctor("Dr. Khan", 10, 50000);
    staff[count++]=new Salaried_doctor("Dr. Usman", 120000, 2);
    staff[count++]=new Senior_nurse("N. Maryam", 50000, 4, 3);
    staff[count++]=new Junior_nurse("N. Sana", 30000);
cout<<left<<setw(20)<<"Name"<<setw(20)<<"Category"<<setw(10)<<"Gross"<<setw(10)<<"Tax"<<setw(10)<<"Net"<<endl;
cout << "---------------------------------------------------------------------" << endl;
for (int i=0;i<count;i++){
    double g=staff[i]->calculate_gross_pay();
    double t=staff[i]->calculate_tax();
    cout<<left<<setw(20)<<staff[i]->get_name()<<setw(20)<<staff[i]->get_category()<<setw(10)<<g<<setw(10)<<t<<setw(10)<<(g-t)<<endl;
}
    for (int i=0;i<count;i++){
        delete staff[i];
    }
    return 0;
}