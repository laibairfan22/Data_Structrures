#include <iostream>
#include <string>
#include <fstream>
using namespace std;



int main()
{
	string filename = "test";

	ofstream fout(filename + ".txt");

	fout << "hello";

	fout.close();
	return 0;
}