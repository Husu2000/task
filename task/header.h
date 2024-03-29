#pragma once

class Exception : public exception
{
	string _message;
	string _file;
	string _date;
	string _time;
	int _line;
public:
	Exception() : _message(), _file(), _date(), _time(), _line() {}

	Exception(string message, string file, string date, int line) : exception(message.c_str())
	{
		_file = file;
		_date = date;
		_line = line;

		time_t currentTime = time(nullptr);
		_time = ctime(&currentTime);

		_message = "Message: " + string(exception::what())
			+ "\nFile: " + _file
			+ "\nDate: " + _date
			+ "\nTime: " + _time
			+ "Line: " + to_string(_line)
			+ "\n\n";
	}

	char const* what() const override
	{
		return _message.c_str();
	}
};

class Quiz;
Quiz loadQuizFromFile(const string& filename);

void setText(string& text, int minTextLength) // userden stringlere min. simvol sayi ile input almaq ucun
{
	while (true)
	{
		try
		{
			getline(cin, text);
			if (text.size() >= minTextLength) break;
			else 
			{
				string msg = "Sual minimum " + to_string(minTextLength) + " simvol olmalidir";
				throw Exception(msg, __FILE__, __DATE__, __LINE__);
			}
		}
		catch (Exception& ex) { cout << ex.what() << "\n\n\n"; }
	}
}

void setText(string& text, int minTextLength, string prompt) // userden stringlere min. simvol sayi ile input almaq ucun
{
	while (true)
	{
		try
		{
			getline(cin, text);
			if (text.size() >= minTextLength) break;
			else
			{
				string msg = "Sual minimum " + to_string(minTextLength) + " simvol olmalidir";
				throw Exception(msg, __FILE__, __DATE__, __LINE__);
			}
		}
		catch (Exception& ex) { cout << ex.what() << "\n\n\n" << prompt << ": "; }
	}
}

class Question;
void setCorrect(int option, Question*& question);

class Question
{
private:
	string _text;
	pair<string, bool> _ans1; // bool cavabin duz olub olmadigini gosterir
	pair<string, bool> _ans2;
	pair<string, bool> _ans3;
	pair<string, bool> _ans4;

public:
	const string getText() { return _text; }
	const pair<string, bool> getAns1() { return _ans1; }
	const pair<string, bool> getAns2() { return _ans2; }
	const pair<string, bool> getAns3() { return _ans3; }
	const pair<string, bool> getAns4() { return _ans4; }

	int getCorrect()
	{
		if (_ans1.second) return 0;
		else if (_ans2.second) return 1;
		else if (_ans3.second) return 2;
		else return 3;
	}

	void setAns(pair<string, bool>& destination, pair<string, bool> source) 
	{
		destination.first = source.first;
		destination.second = source.second;
	}
	void setText(string text) { _text = text; }

	Question() : _ans1{ "", false }, _ans2{ "", false }, _ans3{ "", false }, _ans4{ "", false } {}
	Question(string text) : Question() { setText(text); }
	Question(string text, pair<string, bool> ans1, pair<string, bool> ans2, pair<string, bool> ans3, pair<string, bool> ans4)
	{
		setText(text);
		setAns(_ans1, ans1);
		setAns(_ans2, ans2);
		setAns(_ans3, ans3);
		setAns(_ans4, ans4);
	}

	friend void setCorrect(int option, Question*& question);
	friend void editQuestion(Question*& question);
	friend Quiz loadQuizFromFile(const string& filename);
	friend Question* createQuestion();
	friend ostream& operator<<(ostream& out, Question* q);
};

ostream& operator<<(ostream& out, Question* q)
{
	cout << q->_text << endl;
	cout << "1: " << q->_ans1.first << endl;
	cout << "2: " << q->_ans2.first << endl;
	cout << "3: " << q->_ans3.first << endl;
	cout << "4: " << q->_ans4.first << endl;
	return out;
}

void setCorrect(int option, Question*& question) // cavabin duzgun olub olmadigini teyin edir
{
	question->_ans1.second = false;
	question->_ans2.second = false;
	question->_ans3.second = false;
	question->_ans4.second = false;

	if (!option) question->_ans1.second = true;
	else if (option == 1) question->_ans2.second = true;
	else if (option == 2) question->_ans3.second = true;
	else if (option == 3) question->_ans4.second = true;
}

class Quiz
{
private:
	string _name;

public:
	vector<Question*> _questions;

	const string getName() { return _name; }
	vector<Question*> getQuestions() { return _questions; }
	void setName(string name) { _name = name; }
	void setQuestions(vector<Question*> questions) { _questions = questions; }

	Quiz() = default;
	Quiz(string name) : Quiz() { setName(name); }
	Quiz(string name, vector<Question*> questions) : Quiz() { setName(name); setQuestions(questions); }

	void save()
	{
		ofstream file(_name + ".txt", ios::out);
		ofstream names("quiznames.txt", ios::out | ios::app);
		
		names << _name << endl;
		names.close();

		try
		{
			if (!file) throw Exception("File could not be opened", __FILE__, __DATE__, __LINE__);
		}
		catch (Exception& ex) { cout << ex.what() << endl; return; }

		for (Question* question : _questions)
		{
			file << "Question: " << question->getText() << endl;

			file << "Answer: " << question->getAns1().first << " - " << (question->getAns1().second ? "1" : "0") << endl;
			file << "Answer: " << question->getAns2().first << " - " << (question->getAns2().second ? "1" : "0") << endl;
			file << "Answer: " << question->getAns3().first << " - " << (question->getAns3().second ? "1" : "0") << endl;
			file << "Answer: " << question->getAns4().first << " - " << (question->getAns4().second ? "1" : "0") << endl;

			file << endl;
		}

		file.close();
		cout << "Quiz saved" << endl;
	}

	void show()
	{
		cout << "Quiz Name: " << _name << endl;

		int questionNumber = 1;
		for (Question* question : _questions)
		{
			cout << "\nQuestion " << questionNumber << ": " << question->getText() << endl;

			cout << "Answers:" << endl;
			cout << "1. " << question->getAns1().first << endl;
			cout << "2. " << question->getAns2().first << endl;
			cout << "3. " << question->getAns3().first << endl;
			cout << "4. " << question->getAns4().first << endl;

			questionNumber++;
		}
	}
	friend void createQuiz();
};

Quiz loadQuizFromFile(const string& filename)
{
	ifstream file(filename);
	try
	{
		if (!file)
		{
			throw Exception("File could not be opened for loading", __FILE__, __DATE__, __LINE__);
		}
	}
	catch (Exception& ex) { cout << ex.what() << endl; return Quiz(); }

	vector<Question*> questions;
	Quiz quiz(filename.substr(0, filename.size() - 4), questions);
	string line;

	while (getline(file, line))
	{
		if (line.substr(0, 8) == "Question")
		{
			Question* currQuestion = new Question();

			currQuestion->setText(line.substr(10));
			getline(file, line);
			currQuestion->_ans1.first = line.substr(0, line.size()-3);
			currQuestion->_ans1.second = (line.substr(line.size() - 1) == "1");

			getline(file, line);
			currQuestion->_ans2.first = line.substr(0, line.size() - 3);
			currQuestion->_ans2.second = (line.substr(line.size() - 1) == "1");

			getline(file, line);
			currQuestion->_ans3.first = line.substr(0, line.size() - 3);
			currQuestion->_ans3.second = (line.substr(line.size() - 1) == "1");

			getline(file, line);
			currQuestion->_ans4.first = line.substr(0, line.size() - 3);
			currQuestion->_ans4.second = (line.substr(line.size() - 1) == "1");

			questions.push_back(currQuestion);
		}
	}

	quiz.setQuestions(questions);
	return quiz;
}

Question* createQuestion()
{
	Question* question = new Question();
	string text, ans1, ans2, ans3, ans4;

	system("CLS");
	cout << "Question: ";
	setText(text, 3, "Question: ");
	question->setText(text);

	cout << "Answer 1: ";
	setText(ans1, 2, "Answer 1: ");
	question->_ans1.first = ans1;

	cout << "Answer 2: ";
	setText(ans2, 2, "Answer 2: ");
	question->_ans2.first = ans2;

	cout << "Answer 3: ";
	setText(ans3, 2, "Answer 3: ");
	question->_ans3.first = ans3;

	cout << "Answer 4: ";
	setText(ans4, 2, "Answer 4: ");
	question->_ans4.first = ans4;

	system("CLS");
	cout << "Select correct answer" << endl;
	cout << question;

	Menu<string> menu(vector<string>{ans1, ans2, ans3, ans4});
	int option = menu.start();
	setCorrect(option, question);

	return question;
}

void editQuestion(Question*& question)
{
	Menu<string> menu(vector<string>
	{
		"Edit Question Text",
			"Edit Answer 1",
			"Edit Answer 2",
			"Edit Answer 3",
			"Edit Answer 4",
			"Reset Correct Answer",
			"Exit"
	});

	while (true)
	{
		int option = menu.start("Choose field to edit:\n");
		if (option == 0)
		{
			system("CLS");
			string text;
			cout << "Question: ";
			setText(text, 3, "Question: ");
			question->setText(text);
		}
		else if (option >= 1 && option <= 4)
		{
			system("CLS");
			string ans;
			cout << "Answer " << option << ": ";
			setText(ans, 3, "Answer: ");
			if (option == 1) question->_ans1.first = ans;
			else if (option == 2) question->_ans2.first = ans;
			else if (option == 3) question->_ans3.first = ans;
			else if (option == 4) question->_ans4.first = ans;
		}
		else if (option == 5)
		{
			Menu<string> ansMenu(vector<string>
			{
				question->getAns1().first,
					question->getAns2().first,
					question->getAns3().first,
					question->getAns4().first,
					"Exit"
			});

			int ansOption = ansMenu.start("Choose the new correct answer:\n");
			if (ansOption >= 0 && ansOption < 4)
			{
				setCorrect(ansOption, question);
			}
		}
		else if (option == 6) break;
	}
}

void createQuiz()
{
	int tracker = 0;
	Quiz* quiz = new Quiz();
	string quizName;
	vector<string> options =
	{
		"New",
		"Back",
		"Save"
	};
	Menu<string>* menu = new Menu<string>(options);
	
	system("CLS");
	cout << "Quiz name: ";
	setText(quizName, 2, "Quiz name: ");
	quiz->_name = quizName;

	while (true)
	{
		int option = menu->start();
		if (option == 0)
		{
			quiz->_questions.push_back(createQuestion());
			tracker++;
		}

		else if (option == 1)
		{
			editQuestion(quiz->_questions[tracker - 1 ]);
			tracker++;
		}

		else if (option == 2) 
		{
			quiz->save();
			break;
		}
	}
}

bool checkFromFile(string filename, string word)
{
	vector<string> words;
	ifstream file(filename);

	string line;
	while (getline(file, line)) 
	{
		stringstream ss(line);
		string word;
		while (ss >> word) words.push_back(word);
	}

	for (auto i : words) if (i == word) return true;

	file.close();
	return false;
}

void startQuiz()
{
	int correct = 0, pass = 0;
	vector<string> quiz_names;
	quiz_names.push_back("Exit");
	ifstream file("quiznames.txt", ios::out);
	try
	{
		if (!file) throw Exception("File acilmadi", __FILE__, __DATE__, __LINE__);
	}
	catch (Exception& ex) { cout << ex.what() << endl; return; }

	string line;
	while (getline(file, line))
	{
		quiz_names.push_back(line);
	}
	file.close();

	Menu<string> quiz_names_menu(quiz_names);
	int opt = quiz_names_menu.start();
	if (opt == 0) return;

	system("CLS");
	Quiz quiz = loadQuizFromFile((quiz_names[opt] + ".txt"));

	string name;
	cout << "Enter your name: " << endl;
	setText(name, 3, "Name-> ");

	ofstream names("names.txt", ios::out | ios::app);
	names << name << endl;
	names.close();

	for (size_t i = 0; i < quiz._questions.size();)
	{
		Question* currentQuestion = quiz._questions[i];

		Menu<string> question_menu;
		if (i == quiz._questions.size() - 1) 
		{
			question_menu = Menu<string>(vector<string>{
				currentQuestion->getAns1().first,
					currentQuestion->getAns2().first,
					currentQuestion->getAns3().first,
					currentQuestion->getAns4().first,
					"Back",
					"Submit"
			});

			opt = question_menu.start(currentQuestion->getText());

			if (currentQuestion->getCorrect() == opt)
				correct++;
			else if (opt == 4)
			{
				pass++;
				i--;
			}

			else if (opt == 5)
			{
				ofstream file(quiz.getName() + "Leaderboard.txt", ios::out | ios::app);
				file << quiz.getName() << endl;
				file << name << ' ' << correct << ' ' << quiz._questions.size() << ' ' << pass;
				file.close();
				return;
			}
		}

		else
		{
			question_menu = Menu<string>(vector<string>{
				currentQuestion->getAns1().first,
					currentQuestion->getAns2().first,
					currentQuestion->getAns3().first,
					currentQuestion->getAns4().first,
					"Next",
					"Back",
					"Submit"
			});

			opt = question_menu.start(currentQuestion->getText());

			if (currentQuestion->getCorrect() == opt)
				correct++;

			if (opt == 4)
			{
				pass++;
				i++;
			}

			else if (opt == 5)
			{
				ofstream file(quiz.getName() + "Leaderboard.txt", ios::out | ios::app);
				file << name << ' ' << correct << ' ' << quiz._questions.size() << ' ' << pass;
				file.close();
				return;
			}
		}
	}
}


void leaderboard()
{
	system("CLS");
	ifstream file("quiznames.txt", ios::in);
	string line;
	vector<string> quizzes;
	quizzes.push_back("Exit");

	while (getline(file, line))
		quizzes.push_back(line);

	file.close();

	Menu<string> leaderboard_menu(quizzes);

	while (true)
	{
		int opt = leaderboard_menu.start("Select quiz you wish to see the leaderboard of:\n");
		if (opt == 0) return;
		ifstream leaderboardFile((quizzes[opt] + "Leaderboard.txt"), ios::in);

		try
		{
			if (!leaderboardFile) throw Exception("File could not be opened", __FILE__, __DATE__, __LINE__);
		}
		catch (Exception& ex) { cout << ex.what() << endl; }

		unordered_map<string, int> scores;

		string name;
		int correct, total, incorrect;
		while (leaderboardFile >> name >> correct >> total >> incorrect)
		{
			scores[name] = correct;
			
		}

		leaderboardFile.close();

		vector<pair<string, int>> sortedScores(scores.begin(), scores.end());
		sort(sortedScores.begin(), sortedScores.end(), [](const auto& a, const auto& b) 
			{
				return a.second > b.second;
			});

		cout << "\nTop 5 Scores:\n";
		int count = 0;
		for (const auto& score : sortedScores)
		{
			cout << "Name: " << score.first << ", Correct Answers: " << score.second << endl;
			count++;
			if (count >= 5)
				break;
		}

		cout << "Press any button to continue\n";
		_getch();
	}
}

void start()
{
	Menu<string> main(vector<string>
	{
		"Create Quiz",
			"Start Quiz",
			"Leaderboard",
			"Quit"
	});

	while (true)
	{
		int opt = main.start();
		if (opt == 0) createQuiz();
		else if (opt == 1) startQuiz();
		else if (opt == 2) leaderboard();
		else if (opt == 3) return;
	}
}