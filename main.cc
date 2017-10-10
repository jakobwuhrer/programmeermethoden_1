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
	in_file.open("test_files/moeilijk2017uit.txt");
	out_file.open("out_file.txt");

	bool escape_mode = false;
	bool int_mode = false;

	char character = in_file.get();
	char previous_character;
	char previous_noncounter;

	int character_amount;

	while(!in_file.eof()){
		if (escape_mode or character == '\n' or character == '\r'){
			previous_noncounter = character;
		 	out_file.put(character);
			escape_mode = false;
		} else if (character == '\\'){
			escape_mode = true;
		} else if (isdigit(character)){
			if (not int_mode) previous_noncounter = previous_character;
			int_mode = true;
			character_amount = (character_amount * 10) + char_to_int(character);
		} else if (int_mode){
			int_mode = false;
			for(int i = 1; i < character_amount; i++){
				out_file << previous_noncounter;
			}
			character_amount = 0;
			previous_noncounter = character;
		} else {
			out_file << character;
			previous_noncounter = character;
		}

		previous_character = character;
		character = in_file.get();
	}
}
void encode_file(){
	//in_file.open("in_file.txt");
	//out_file.open("out_file.txt");
	in_file.open("test_files/moeilijk2017.txt");
	out_file.open("out_file.txt");

	int same_character_count = 1;
	char next_character;
	char character = in_file.get();
	int current_number = 0;
	bool number_mode = false;

	while (!in_file.eof()){
		next_character = in_file.get();
			
		if (isdigit(character)){
			number_mode = true;
			current_number = current_number*10 + char_to_int(character);
		} else if (number_mode){
			lychrel(current_number);
			number_mode = false;
			current_number = 0;
		}

		if (character == next_character){
			same_character_count++;
			out_file.put(same_character_count);
		} else {
			output_character(character);
			if (same_character_count > 1){
				out_file << same_character_count;
				same_character_count = 1;
			}
		}
		character = next_character;
	}

	in_file.close();
	out_file.close();
}
int reverse_int(int n){
	long to_return;
	while (n>9){
		to_return = to_return*10 + n %10;
		n = n/10;
	}
	if (to_return > INT_MAX) return to_return;
	else return -1;
}
bool next_step_possible(int n, int m){
	return (INT_MAX - n > m);
}
void lychrel(int start){
	int current_step = start;
	int inversion = reverse_int(start);
	int step_count = 0;
	while (true){
		if (not next_step_possible(current_step, inversion)){
			cout << "De inversie bij de huidige stap opte tellen zou in een integer overflow resulteren." << endl;
			cout << start << "Zou dus een lychrel-getal kunnen zijn." << endl;
			break;
		} else if (inversion == current_step){
			cout << "Na " << step_count << " omkeringen, zijn we bij het palindroomgetal " << current_step << " aangekomen.";
			cout << start << " is dus geen lychrel-getal.";
			break;
		}
		step_count ++;
		current_step = current_step + inversion;
		inversion = reverse_int(current_step);
	}
}

int main(){
	encode_file();
}
