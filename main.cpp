#include <iostream>
#include <fstream>
#include <string>
#include "uandf.h"

using namespace std;

int main() {
	string filename;
	cin>>filename;
	ifstream myfile(filename);
	string line, alphabet = "abcdefghijklmnopqrstuvwxyz";
	int value = 0;
	uandf u(71*71);
	char pic[71][71];

	while (getline(myfile, line)) {//goes through each line and value in the file to create an array of the values
		cout << line << endl;
		for (int x = 0; x < line.length(); x++) {
			if (line[x] == '+') {//if its a + create a set for it
				pic[value][x] = '+';
				u.makeSet((value*71)+x);
			}
			else {
				pic[value][x] = ' ';
			}
		}
		value++;
	}
	for (int y = 0; y < 71; y++) {
		for (int x = 0; x < 71; x++) {//goes through the array if there are adjacent +'s union them together
			if (x + 1 != 71 && pic[y][x]=='+'&& pic[y][x+1]=='+') {
					u.unionSets(((y*71)+x+1), ((y * 71) + x));
			}
			if (y + 1 != 71 && pic[y][x] == '+'&&pic[y+1][x] == '+') {
				u.unionSets((((y+1) * 71) + x), ((y * 71) + x));
			}
		}
	}
	int size=u.finalSets(); //finalize the sets
	value = 0;
	for (int y = 0; y < 71; y++) {
		for (int x = 0; x < 71; x++) {
			if (pic[y][x] == '+') {
				int s = u.topvalue((y*71)+x);//returns the sets unique number
				if (s < 27){
					cout << alphabet.at(s); // use that number to get the appropriate letter
				}
			}
			else{
				cout << ' ';
			}
		}
		cout << endl;
	}
	myfile.close();
	string exit = "i";
	while (value < (26)) {//prints each letter of the alphabet and the amount of times it appears
		cout<< alphabet.at(value)<<"  ";
		cout<<u.getTotal(value,pic)<<endl;
		value++;
	}
	for (int y = 0; y < 71; y++) {
		for (int x = 0; x < 71; x++) {
			if (pic[y][x] == '+') {//prints the value as letters again
				int s = u.topvalue((y * 71) + x);
				if (s < 27) {
					if (u.getTotal(s,pic)>2) {//this time if the value has less than 2 occurences dont show it
						cout << alphabet.at(s);
					}
					else {
						cout << ' ';
					}
				}
			}
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}
	cout << "press q to exit";
	while (exit != "q") {
		getline(cin, exit);
	}
	return 0;
}