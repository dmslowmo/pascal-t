/**
This program can generate Pascal Triangle for as many rows as specified by user.
In addition, it is also possible to limit the number size generated by using modulus operand (%).
The usage:
    ./pascalTriangle arg1 arg2
    where arg1 = no. of rows -- (required),
          arg2 = the modulus value -- if '0' or no input, the default is no modulus, maximum number is UINT_MAX
*/

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <string>

using namespace std;

using Row = vector<int>;
using Rows = vector<Row>;

constexpr unsigned DarkBackground = 1;
constexpr unsigned argno = 2;

string rowAsMultiColorString(string leadingSpaces, Row row, unsigned modulo)
{
	string str = leadingSpaces;
	for (auto element : row) {
		str += "\033[1;" + to_string(30 + (element % modulo) % 7 + DarkBackground) + "m"; //the color code prefix
		str += to_string(element % modulo); //the element to print
		str += "\033[0m"; //the suffix to reset the color
		str += " ";
	}
	str.pop_back();
	return str;
}

Rows pascalTriangle(int level)
{
	if (level == 0) {
		cout << "invalid argument: " << level << endl;
		throw;
	} else if (level == 1) {
		Row row = Row{1};
		return Rows{row};
	} else if (level == 2) {
		Rows triangle = pascalTriangle(1);
		triangle.push_back(Row{1, 1});
		return triangle;
	} else {
		Rows triangleAbove = pascalTriangle(level - 1);
		Row rowAbove = triangleAbove[level - 2];
		Row row = Row{1};
		for (int i = 1; i < (level - 1); ++i) {
			unsigned int element = rowAbove[i - 1] + rowAbove[i];
			row.push_back(element);
		}
		row.push_back(1);
		Rows triangle = triangleAbove;
		triangle.push_back(row);
		return triangle;
	}
}

string serializeTriangle(Rows triangle, unsigned modulo = UINT_MAX)
{
	ostringstream os;
	string leadingSpaces = string(triangle.size(), ' ');
	for (Row row : triangle) {
		os << rowAsMultiColorString(leadingSpaces, row, modulo) << endl;
		leadingSpaces.pop_back();
	}
	return os.str();
}

int main(int argc, char* argv[])
{
	if (argc < 2 || atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0) {
		cout << "Usage: " << argv[0] << " [levels]" << " [optional: modulo]" << endl;
		cout << "where levels > 0 and modulo > 0" << endl;
		exit(1);
	}

	int level = atoi(argv[1]);
	unsigned modulo = UINT_MAX;
	if (argc >= 3) modulo = atoi(argv[2]);

	Rows triangle = pascalTriangle(level);
	cout << serializeTriangle(triangle, modulo) << endl;
	return 0;
}
