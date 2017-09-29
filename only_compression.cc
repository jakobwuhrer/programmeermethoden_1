#include <fstream>
#include <iostream>
#include <climits>
#include <ctype.h>

using namespace std;

ifstream in_file;
ofstream out_file;

void output_character(char character){
	if (character == '\\' or isdigit(character)){
		out_file << "\\";
		out_file << character;
	}
	else out_file << character;
}
int char_to_int(char character){
	return (int) character - 48;
}
void decode_file(){
	in_file.open("in_file.txt");
	out_file.open("out_file.txt");

	bool already_getted = false;	
	bool escape_char = false;
	char character = in_file.get();
	char previous_character;
	int character_amount;

	while(!in_file.eof()){
		if (escape_char){
			out_file.put(character);
			escape_char = false;
		} else {
			if (character == '\\'){
				escape_char = true;
			} else if (isdigit(character)){
				character_amount = char_to_int(character);
				do {
					character = in_file.get();
					if (isdigit(character)){
						character_amount = (character_amount * 10) + char_to_int(character);
					}
				} while (isdigit(character));

				already_getted = true;
				
				for(int i = 1; i < character_amount; i++){
					out_file << previous_character;
				}
			}
			else out_file << character;
		}
		previous_character = character;
		if (already_getted) already_getted = false;
		else character = in_file.get();
	}
}
int main(){
	decode_file();
}

void encode_file(){
	in_file.open("in_file.txt");
	out_file.open("out_file.txt");

	int same_character_count = 1;
	char next_character;
	char character = in_file.get();

	while (!in_file.eof()){
		next_character = in_file.get();
		if (character == next_character){
			same_character_count++;
			out_file.put(same_character_count);
		} else {
			if (same_character_count > 1){
				output_character(character);
				out_file << same_character_count;
				same_character_count = 1;
			} else {
				output_character(character);
			}
		}
		character = next_character;
	}

	in_file.close();
	out_file.close();
}


bool check_double_greater_int_max(int n){
	if (n > INT_MAX-n) return false;
	return true;
}
