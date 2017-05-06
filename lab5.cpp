#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class Printable {
public:
	virtual void print(std::ostream& stream) = 0;
};

enum Access { Low, Medium, High, Full };

const string accessName[]{
	"Low", "Medium", "High", "Full"
};

string accessNames(Access acc) {
	return accessName[(int)acc];
}

class Accesible {
public:
	virtual void setAccess(Access access) = 0;
	virtual int getAccess() = 0;
	virtual bool checkAccessible(Access access) = 0;
};


class User : public Printable, public Accesible {
private:
	Access access = Access::Low;

public:
	string name;
	int id;

	User(int i, string n, Access access = Access::Low) 
		: id(i), name(n), access(access) {
	}

	void print(std::ostream& stream) override {
		stream << "#" << id << " " << name;
		stream << " " << accessNames(access);
	}

	void setAccess(Access access) override {
		this->access = access;
	}
	int getAccess() override {
		return access;
	}
	bool checkAccessible(Access level) override {
		return (level < access) == true;
	}


};

class Admin : public User {
public:
	Admin(int i, string n)
		: User(i, n, Access::Full) {
	}

	void setAccess(Access access) override {
		throw exception("Nie mozna zmienic");
	}
};
int main()
{
	User u(1, "Imie");
	u.print(cout);
	cout << endl;
	u.setAccess(Access::High);

	cout << u.getAccess() << endl;
	cout << u.checkAccessible(Access::Medium) << endl;

	cout << u.checkAccessible(Access::Full) << endl;

	Admin a(3, "Imie");
	a.print(cout);
	try {
		a.setAccess(Access::Full);
	}
	catch (exception e) {
		cerr << e.what();
	}
	system("pause");
}

