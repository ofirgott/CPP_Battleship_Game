#include <iostream>


using namespace std;

template<typename Groups>
void print(const Groups& all_groups) {
	for (const auto& groupType : all_groups) {
		cout << groupType.first << ":" << endl;
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
	Matrix3d<int> m2 = { { { 1, 2, 3 },{ 1, 2 },{ 1, 2 } },{ { 1, 2 },{ 1, 2, 3, 4 } } };
	auto groups = m2.groupValues([](auto i) {return i % 3 ? "!x3" : "x3"; });
	print(groups);
}


//	!x3:
//	{ 0 0 0 } { 0 0 1 } { 0 1 0 } { 0 1 1 } { 0 2 0 } { 0 2 1 } { 1 0 0 } { 1 0 1 } { 1 1 0 } { 1 1 1 }
//	{ 1 1 3 }
//	x3:
//	{ 0 0 2 } { 0 0 3 } { 0 1 2 } { 0 1 3 } { 0 2 2 } { 0 2 3 } { 1 0 2 } { 1 0 3 } { 1 1 2 } { 1 2 0 } { 1 2 1 } { 1 2 2 } { 1 2 3 }
