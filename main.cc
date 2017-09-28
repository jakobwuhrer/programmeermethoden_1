#include <fstream>
#include <iostream>

// #include <climits>

using namespace std;

ifstream in_file;
ofstream out_file;

int main(){
	in_file.open("in_file.txt");
	out_file.open("out_file.txt");

	char character = in_file.get();
	while (!in_file.eof()){
		out_file.put(character);
		character = in_file.get();
	}
	// bool check_double_greater_int_max(int n){
	// 	if (n > INT_MAX-n) return false;
	// 	return true;
	// }

	in_file.close();
	out_file.close();
}
