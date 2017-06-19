#include <iostream>


using namespace std;


template<typename Groups>
void print(const Groups& all_groups) {
	for (const auto& groupType : all_groups) {
		std::cout << groupType.first << ":" << endl;
		for (const auto& groupOfType : groupType.second) {
			for (const auto& coord : groupOfType) {
				cout << "{ ";
				for (int i : coord) {
					cout << i << ' ';
				}
				cout << "} ";
			}
			cout << endl;
		}
	}
}

int main() {
	Matrix2d<char> m = { { 'a', 'A', 'a' },{ 'B', 'a', 'B' },{ 'B', 'a', 'B' } };
	auto all_groups = m.groupValues([](auto i) {return islower(i) ? "L" : "U"; });
	print(all_groups);
}


	//	L:
	//	{ 0 0 }
	//	{ 0 2 }
	//	{ 1 1 } { 2 1 }
	//	U:
	//	{ 0 1 }
	//	{ 1 0 } { 2 0 }
	//	{ 1 2 } { 2 2 }
