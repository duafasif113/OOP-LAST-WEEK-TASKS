#include "library.h"
#include<iostream>
using namespace std;
int main() {

    Library lib;

    lib.loadData();   // safe even if empty
    lib.seedData();   // demo data
    Member* test = MemberFactory::createMember("Student", "Test");
    lib.addMember(test);

    Book b("999", "Test Book", 1);
    lib.addBook(b);

    displayBook(b);

    lib.issueBook("999", test->getID());

    lib.saveData();

    return 0;
}