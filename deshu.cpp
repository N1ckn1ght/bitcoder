#include <iostream>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

int count(char *input) {

	ifstream in(input, ios::in | ios::binary);
	int count = 0;
	char check;
	while ((check = in.get()) != EOF) {
		count++;
	}
	in.close();
	return count;

}

void decode(char *input, char *output, int len) {
	
	int ch;
	int encoded;
	int buf[7];
	ifstream in(input, ios::in | ios::binary);
	ofstream out(output, ios::out | ios::binary);
	len = len / 7;
	encoded = 0;
	for (int i = 0; i < (len * 7); i++) {
		ch = in.get();
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
	in.close();
	out.close();
	
}

int main(int argc, char *argv[]) {
	
	int len;
	len = count(argv[1]);
	decode(argv[1], argv[2], len);
	return 0;
	
}
