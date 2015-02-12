/*
 * transposition-decr.cpp
 *
 *  Created on: Feb 11, 2015
 *      Author: Greg
 */
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
string k1;
string k2;
string textfile;
string ciphertext;

bool removeChar(char c) {//
	if (isalpha(c)) {
		return false;
	}
	return true;
}
string parseKey(string key) {
	string tempkey = "";
	size_t found;
	int keyLength = key.length();

	for (int i = 0; i < keyLength; i++) {
		found = tempkey.find(key[i]);
		if (found == string::npos && isalpha(key[i])) {
			tempkey += key[i];
		}
	}
	transform(tempkey.begin(), tempkey.end(),tempkey.begin(), ::toupper);
	cout << tempkey.substr(0,10);
	return tempkey.substr(0,10);
}
bool readCiphertext(string textfile) {
	string line;
	ifstream myfile(textfile.c_str());
	if (myfile.is_open()) {
		while (getline(myfile,line)) {
			ciphertext += line;
	    }
		myfile.close();
	}else {
		return false;
	}
	return true;
}
string decrypt(string k1, string k2, string ciphertext) {
	string tempkey;//used to store sorted k1 or k2
	size_t index;//used to sort k1 or k2 alphabetically
	string ciphertext2;//string to store ciphertext generated by k2
	string plaintext;//string to store plaintext generated by k1
	int length;//used to indicate length of plaintext or ciphertext
	int count;

	ciphertext2 = ciphertext;
	plaintext = ciphertext;

	count = 0;
	length = ciphertext.length();
	tempkey = k2;
	sort(tempkey.begin(), tempkey.end());
	for (int i = 0; i < 10; i++) {
		index = k2.find(tempkey[i]);
		for (int j = index; j < length; j+=10) {
			ciphertext2[j] = ciphertext[count];
			count++;
		}
	}

	count = 0;
	tempkey = k1;
	sort(tempkey.begin(), tempkey.end());
	for (int i = 0; i < 10; i++) {
		index = k1.find(tempkey[i]);
		for (int j = index; j < length; j+=10) {
			plaintext[j] = ciphertext2[count];
			count++;
		}
	}

	cout << plaintext << '\n';
	return plaintext;
}


int main() {
	string parseTemp;

	//Ask user for first key and sanitize that key
	cout << "Please enter a 10 character key. The key must contain only letters from the "
		  "English alphabet and must not contain duplicate characters.\n";
	cin >> k1;
	parseTemp = parseKey(k1);
	while (parseTemp.length() < 10) {
		cout << "The key must be at least 10 characters long. The key must contain only letters from the "
		  "English alphabet and must not contain duplicate characters. Please enter a valid key.\n";
		cin >> k1;
		parseTemp = parseKey(k1);
	}
	k1 = parseTemp;

	//Ask user for second key and sanitize that key
	cout << "First key accepted.\n" << "Now please enter a second key, satisfying the same criteria.\n";
	cin >> k2;
	parseTemp = parseKey(k2);
	while (parseTemp.length() < 10) {
		cout << "The key must be at least 10 characters long. The key must contain only letters from the "
		  "English alphabet and must not contain duplicate characters. Please enter a valid key.\n";
		cin >> k2;
		parseTemp = parseKey(k2);
	}
	k2 = parseTemp;

	//ask user for filename containing ciphertext
	cout << "Second key accepted\n" << "Now please enter the name of a text file to be decrypted.\n";
	cin >> textfile;
	if (readCiphertext(textfile)) {
		cout << ciphertext <<'\n';
	}

	//generate plaintext using the 2 keys and the ciphertext, and store it in file called Greg-Boyarko-decrypted-str.txt
	ofstream outputFile ("Greg-Boyarko-decrypted-str.txt");
	if (outputFile.is_open()) {
		outputFile << decrypt(k1, k2, ciphertext) << '\n';
		outputFile.close();
	}else {
		cout << "Unable to open file" << '\n';
	}
}
