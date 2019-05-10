#include <iostream>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

int count(char *input) {

	ifstream in(input, ios::in | ios::binary);

	if (!in) {
                cout << "Sorry, pal.\nSomething went wrong...\n\nCan't load <input> file." << endl;
                exit(1);
        }

	int count = 0;
	char check;
	while ((check = in.get()) != EOF) {
		count++;
	}
	in.close();
	//cout << "(DEBUG) len = " << count << endl;
	return count;

}

void encode(char *input, char *output, char *key, int len) {

	ifstream in(input, ios::in | ios::binary);
	ofstream out(output, ios::out | ios::binary);

        if (!out) {
                cout << "Sorry pal.\nMaybe I need more permissions to make output file.\n\nOutput failed." << endl;
                exit(1);
        }

	int ch;
	int buffer;
	int x = 0;
	int cycle = len / 8;

	for (int i = 0; i < (cycle * 8); i++) {
		if ((i % 8) == 0) {
			buffer = in.get();
			continue;
		}
		ch = in.get();
		ch = ch | ((buffer << (i % 8)) & (1 << 7));
		if (!in.eof()) {
			ch = ch ^ key[x%5];
			out.put((char)ch);
			x++;
		}
	}

	for (int i = (cycle * 8); i < len; i++) {
                //cout << "(DEBUG) i = " << i << "; len = " << len << endl;
                ch = in.get();
                if (!in.eof()) {
                        out.put((char)ch);
                }
	}

	in.close();
	out.close();

}

void decode(char *input, char *output, char *key, int len) {

	ifstream in(input, ios::in | ios::binary);
	ofstream out(output, ios::out | ios::binary);

	if (!out) {
		cout << "Sorry pal.\nMaybe I need more permissions to make output file.\n\nOutput failed." << endl;
		exit(1);
	}

	int ch;
	int encoded = 0;
	int buf[7];
	int x = 0;
	int cycle = len / 7;

	for (int i = 0; i < (cycle * 7); i++) {
		ch = in.get();
		ch = ch ^ key[x%5];
		x++;
		encoded = encoded | ((ch >> 7) << (6 - (i % 7)));
		ch = ch & 0x7F;
		if (!in.eof()) {
			buf[i % 7] = ch;
		}
		if ((i + 1) % 7 == 0) {
			out.put((char)encoded);
			for (int j = 0; j < 7; j++) {
				out.put((char)buf[j]);
			}
			encoded = 0;
		}
	}

	for (int i = 0; i < 7; i++) {
		//cout << "(DEBUG) i = " << i << "; len = " << len << endl;
		ch = in.get();
		if (!in.eof()) {
			out.put((char)ch);
		}
	}

	in.close();
	out.close();

}

int main(int argc, char *argv[]) {

	if (argc != 5) {
		cout << "Usage: <input> <output> <encode/decode> <key>\nkey must be 5 characters long" << endl;
		exit(1);
	}

	int len;
	len = count(argv[1]);

	if (toupper(*argv[3]) == 'E') {
		encode(argv[1],argv[2],argv[4],len);
	}
	else if (toupper(*argv[3]) == 'D') {
		decode(argv[1],argv[2],argv[4],len);
	}
	else {
		cout << "Sorry, pal.\nWrong arguments.\n\nUsage: <input> <output> <encode/decode> <key>\nkey must be 5 characters long" << endl;
		exit(1);
	}

	return 0;

}
