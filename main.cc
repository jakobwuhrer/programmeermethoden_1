#include <fstream>
#include <iostream>
#include <climits>
//#include <ctype.h>

using namespace std;

ifstream in_file;
ofstream out_file;

void output_character(char character){
	if (character == '\\' || isdigit(character)){
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
		if (escape_mode || character == '\n' || character == '\r'){
			previous_noncounter = character;
		 	out_file.put(character);
			escape_mode = false;
		} else if (character == '\\'){
			escape_mode = true;
		} else if (isdigit(character)){
			if (!int_mode) previous_noncounter = previous_character;
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

bool next_step_possible(int reverse_number, int current_number) {
	if (reverse_number < 0 || current_number < 0)
		return false;
	//return (INT_MAX - n > m);
	return true; 
}
////convert char to int/////
int chartoint(char character) {
	return (int)(character - 48);
}
////isdigit function/////
bool isdigit(char character) {
	if (chartoint(character)>0 && chartoint(character) < 10) { return true; }
	else { return false; }
}
////reverse int/////
int reverseint(int current_number) {
	int rev = 0;
	while (current_number != 0) {
		rev = rev * 10;
		rev = rev + current_number % 10;
		current_number = current_number / 10;
	}
	return rev;
}
////lychrel////
int lychrel(int current_number) {
	int cout_number = current_number;
	int iteration_counter = 0;

	int reverse_number = reverseint(current_number);
	if (current_number == reverse_number) { cout << cout_number << "is al een palindroom" << endl; return 0; }
	do {
		current_number = reverse_number + current_number;
		reverse_number = reverseint(current_number);
		iteration_counter++;
	}while (next_step_possible(reverse_number, current_number) && (reverse_number != current_number));
	
	if (reverseint(current_number) == current_number){
		cout << current_number << " is een palindroom van " << cout_number << " na " << iteration_counter << " iteraties"<< endl;
	}

	if (next_step_possible(reverse_number, current_number) == false) { 
		cout << cout_number << "lychrel number found after " << iteration_counter << " iteraties" <<endl; 
	}
}
void encode_file(){
	in_file.open("in_file.txt");
	out_file.open("out_file.txt");
	//in_file.open("test_files/moeilijk2017.txt");
	//out_file.open("out_file.txt");

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
		} else if (number_mode){//werkt niet als laatste char in file getal is
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
int main(){
	char testchar;
	encode_file();
	cin >> testchar;
}
