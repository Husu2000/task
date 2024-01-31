#pragma once
class Admin :public User {
	string username;
	string password;
public:
	Admin() = default;
	Admin(string name, string surname, string email, string username, string password) :User(name, surname, email) {
		this->username = username;
		this->password = password;
	}

	string getUsername()const { return username; }
	string getPassword()const { return password; }

	friend ostream& operator<<(ostream& output, const Admin& admin);
};
ostream& operator<<(ostream& output, const Admin& admin) {
	cout << "Name: " << admin.getName() << endl;
	cout << "Surname: " << admin.getSurname() << endl;
	cout << "Email: " << admin.getEmail() << endl;
	cout << "Username: " << admin.username << endl;
	cout << "Password: " << admin.password << endl;
	return output;
}