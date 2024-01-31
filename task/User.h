#pragma once
class User {
	string name;
	string surname;
	string email;
public:
	User() = default;
	User(string name, string surname, string email) {
		this->name = name;
		this->surname = surname;
		this->email = email;
	}
	string getName()const { return name; }
	string getSurname()const { return name; }
	string getEmail()const { return email; }

	friend ostream& operator<<(ostream& output, const User& user);
};
ostream& operator<<(ostream& output, const User& user) {
	cout << "Name: " << user.name << endl;
	cout << "Surname: " << user.surname << endl;
	cout << "Email: " << user.email << endl;
	return output;
}