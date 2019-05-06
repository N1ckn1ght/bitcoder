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

void encode(char *input, char *output, int len) {

	int ch;
	int buffer;
	ifstream in(input, ios::in | ios::binary);
	ofstream out(output, ios::out | ios::binary);
	len = len / 8;
	for (int i = 0; i < (len * 8); i++) {
		if ((i % 8) == 0) {
			buffer = in.get();
			continue;
		}
		ch = in.get();
		ch = ch | ((buffer << (i % 8)) & (1 << 7));
		if (!in.eof()) {
			out.put((char)ch);
		}
	}
	in.close();
	out.close();
	
}

int main(int argc, char *argv[]) {
	
	int len;
	len = count(argv[1]);
	encode(argv[1],argv[2],len);
	return 0;
	
}
