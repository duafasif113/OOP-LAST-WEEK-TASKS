#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Logger {
private:
    static Logger* instance;
    int count;
    Logger() { count = 0; }
public:
    static Logger* getInstance() {
        if (!instance) instance = new Logger();
        return instance;
    }
    void log(string msg) {
        ofstream f("audit_log.txt", ios::app);
        f << ++count << ": " << msg << endl;
        f.close();
    }
};
Logger* Logger::instance = nullptr;

class Member {
protected:
    string name;
    int id;
public:
    static int idCount;
    Member(string n) : name(n) { id = ++idCount; }
    virtual int getLimit() = 0;
    virtual double getFine(int d) = 0;
    int getID() { return id; }
    string getName() { return name; }
    virtual ~Member() {}
};
int Member::idCount = 100;

class Student : public Member {
public:
    Student(string n) : Member(n) {}
    int getLimit() { return 3; }
    double getFine(int d) { return d * 5.0; }
};

class Faculty : public Member {
public:
    Faculty(string n) : Member(n) {}
    int getLimit() { return 8; }
    double getFine(int d) { 
        if (d > 0) cout << "HoD Alert: " << name << " is late." << endl;
        return 0.0; 
    }
};

class MemberFactory {
public:
    static Member* create(string type, string name) {
        if (type == "Student") return new Student(name);
        if (type == "Faculty") return new Faculty(name);
        return nullptr;
    }
};

class Book {
private:
    string isbn, title;
    int stock;
public:
    Book() : isbn(""), title(""), stock(0) {}
    Book(string i, string t, int s) : isbn(i), title(t), stock(s) {}
    
    bool operator==(const Book& other) {
        return this->isbn == other.isbn;
    }

    void addStock() {
        stock++;
        if (stock == 1) cout << "Observer: " << title << " is now available!" << endl;
    }

    string getISBN() { return isbn; }
    string getTitle() { return title; }
    int getStock() { return stock; }
    void removeStock() { if (stock > 0) stock--; }
};

class Library {
private:
    Book books[50];
    Member* users[50];
    int bCount, uCount;
public:
    Library() : bCount(0), uCount(0) {}

    void addBook(Book b) {
        if (bCount < 50) books[bCount++] = b;
    }

    void addUser(Member* m) {
        if (uCount < 50) {
            users[uCount++] = m;
            Logger::getInstance()->log("Registered: " + m->getName());
        }
    }

    void issue(int mID, string code) {
        for (int i = 0; i < bCount; i++) {
            if (books[i].getISBN() == code && books[i].getStock() > 0) {
                books[i].removeStock();
                Logger::getInstance()->log("ID " + to_string(mID) + " took " + code);
                return;
            }
        }
    }

    void save() {
        ofstream f("data.txt");
        for (int i = 0; i < bCount; i++) {
            f << books[i].getISBN() << "," << books[i].getTitle() << "," << books[i].getStock() << endl;
        }
        f.close();
    }

    ~Library() {
        for (int i = 0; i < uCount; i++) delete users[i];
    }
};

int main() {
    Library myLib;
    myLib.addBook(Book("B1", "C++ Basics", 0));
    myLib.addBook(Book("B2", "OOP Guide", 10));

    Member* m = MemberFactory::create("Student", "Aisha");
    myLib.addUser(m);

    myLib.issue(m->getID(), "B2");
    
    Book temp("B1", "C++ Basics", 0);
    temp.addStock();

    myLib.save();
    return 0;
}