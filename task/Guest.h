#pragma once
class Guest {
	string _name;
	string _surname;
public:
	Guest() = default;
	Guest(string name, string surname) {
		this->_name = name;
		this->_surname = surname;
	}
	string getName() { return _name; }
	string getSurname() { return _surname; }


	friend ostream& operator<<(ostream output, const Guest& guest);
};
ostream& operator<<(ostream output, const Guest& guest) {
	cout << "Name: " << guest._name << endl;
	cout << "Surname: " << guest._surname << endl;
	return output;
}