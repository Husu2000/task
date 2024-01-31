#pragma once

void addQuestion() {
	string question, answer_A, answer_B, answer_C, answer_D, correctOpt;
	char input;
	while (true) {
		cin.ignore();
		cout << "Enter the question: ";
		getline(cin, question);
		cout << "A: ";
		getline(cin, answer_A);

		cout << "B: ";
		getline(cin, answer_B);

		cout << "C: ";
		getline(cin, answer_C);

		cout << "D: ";
		getline(cin, answer_D);
		cin.ignore();

		cout << "Correct option is ";
		cin >> correctOpt;
		ofstream questionFile;
		ofstream answerFile;
		answerFile.open("answers.txt");
		questionFile.open("questions.txt");

		if (!answerFile)
			throw exception("Answer file can not found !!!");
		if (!questionFile)
			throw exception("Question file can not found !!!");
		if (!answerFile.is_open())
			throw exception("Answer file can not opened !!!");
		if (!questionFile.is_open())
			throw exception("Question file can not opened !!!");
		questionFile << ++questioNumber << endl;
		questionFile << question << endl;
		questionFile << "A:" << answer_A << '\t';
		questionFile << "B:" << answer_B << endl;
		questionFile << "C:" << answer_C << '\t';
		questionFile << "D:" << answer_D << endl;
		answerFile << correctOpt << endl;
		answerFile.close();
		questionFile.close();
		cout << "\t\t\t\t\tQuestion successfully added!!!" << endl;
		cout << "\t\t\t\t\tWould you want go to main menu? : ";
		input = _getch();
		if (input == 13) {
			system("cls");
			break;
		}
	}
}

void LeaderBoard() {
	string line;
	ifstream leaderBoard("scoreboard.txt");
	if (!leaderBoard.is_open())
		throw exception("Leader board can not open !!!");
	else {
		while (getline(leaderBoard, line)) {
			cout << line << '\n';
		}
		leaderBoard.close();
	}

}

void Questions() {
	ofstream file;
	ofstream fileA;
	file.open("questions.txt", fstream::app);
	fileA.open("answers.txt", fstream::app);
	file << "1\n When computer was first invented?\n";
	file << " a.1820 \t b.1823\n";
	file << " c.1834 \t d.1922\n";
	fileA << 'a' << endl;
	file << "2\n Which day is celebrated as 'World Computer Literacy day'?\n";
	file << " a.October 6 \t b.December 2\n";
	file << " c.October 4 \t d.May 15\n";
	fileA << 'b' << endl;
	file << "3\n Who is known as human computer of India?\n";
	file << " a. Sundar Pichai \t b.Sathya Nathella\n";
	file << " c. Shakunthala Devi\t c.Derek o brein\n";
	fileA << 'c' << endl;
	file << "4\n 'Do no evil' is the tag line of\n";
	file << " a. Adobe \t b. Microsoft\n";
	file << " c. Linux \t d. Google\n";
	fileA << 'd' << endl;
	file << "5\n Extension of PDF\n";
	file << " a. Portable Document Format \t b. Personal Document Format\n";
	file << " c. Portable Digital format \t d. Presentation Document Format\n";
	fileA << 'a' << endl;
	file << "6\n Which company invented floppy disk?\n";
	file << " a. Microsoft \t b. Apple\n";
	file << " c. Intel \t d.IBM\n";
	fileA << 'a' << endl;
	file << "7\n IC chips are usually made of\n";
	file << " a. Lead \t b. Silicon\n";
	file << " c. Chromium \t d. Gold\n";
	fileA << 'b' << endl;
	file << "8\n Technology no longer protected by copyrights and available to all is\n";
	file << " a. Proprietary \t b. Open\n";
	file << " c. Experimental \t d. Free\n";
	fileA << 'a' << endl;
	file << "9\n In binary language each alphabet is made up of unique combinationof \n";
	file << " a. 8 bytes \t b.8 kbytes\n";
	file << " c. 8 character \t d. 8 bits\n";
	fileA << 'd' << endl;
	file << "10\n The term bit is short for\n";
	file << " a. Byte \t b. Binary language\n";
	file << " c. Binary digit \t d.Binary number\n";
	fileA << 'c' << endl;
	file << "11\n Who invented graphical use interface(GUI)?\n";
	file << " a.Microsoft \t b.Apple\n";
	file << " c.Xerox \t d. IBM\n";
	fileA << 'c' << endl;
	file << "12\n What is the transfer rate of a satandard USB2.0?\n";
	file << " a.100Mbit/s \t b.480 Mbit/s\n";
	file << " c.1 Gbit/s \t c. 250 Mbit/c\n";
	fileA << 'b' << endl;
	file << "13\n Who invented USB?\n";
	file << " a. HP \t b.Samsung\n";
	file << " c. Intel \t d. AMD\n";
	fileA << 'c' << endl;
	file.close();

}


void StartQuiz(bool& isGuest) {
	int score = 0;
	cout << "\t\t\t\t\t\tWelcome " << username << " !!!!" << endl;
	Sleep(1500);
	system("cls");
	ifstream file;
	ofstream fileMyA;
	ifstream fileA;
	string myline;
	string answer;
	string Fanswer;
	int pos = 0;
	fileMyA.open("myAnswers.txt");
	fileA.open("answers.txt");
	file.open("questions.txt");
	if (!file)
		throw exception("File can not found !!!");
	if (!file.is_open())
		throw exception("File can not opened !!!");
	while (file) {
		getline(file, myline);
		cout << myline << '\n';
		if (pos == 3) {
			getline(fileA, Fanswer);
		reanswer:
			cin >> answer;
			if (answer == "a" || answer == "b" || answer == "c" || answer == "d" || answer == "s") {
				fileMyA << answer << endl;
				pos = 0;
				if (answer == Fanswer)
					score += 5;
			}
			else {
				cout << "You can choose only abcds !!!" << endl;
				goto reanswer;
			}
		}
		else
			pos++;
	}

	if (isGuest == 1) {
		ofstream leaderBoard;
		leaderBoard.open("scoreboard.txt", fstream::app);
		leaderBoard << username << ' ' << score << endl;
	}
	else
		cout << username << ' ' << score << " point" << endl;
}

