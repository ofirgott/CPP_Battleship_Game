#include "Matrix.h"


template<typename Groups>
void print(const Groups& all_groups) {
	for (const auto& groupType : all_groups) {
		std::cout << groupType.first << ":" << std::endl;
		for (const auto& groupOfType : groupType.second) {
			for (const auto& coord : groupOfType) {
				std::cout << "{ ";
				for (auto i : coord) {   // was: for(int i : coord)
					std::cout << i << ' ';
				}
				std::cout << "} ";
			}
			std::cout << std::endl;
		}
	}
}



int main() {
	Matrix2d<char> m = { { 'a', 'A', 'a' },{ 'B', 'a', 'B' },{ 'B', 'a', 'B' } };
	//Matrix2d<bool> m = { { false, true, false },{ true, false, true },{ true, false, true} };
	auto all_groups = m.groupValues([](auto i) {return islower(i) ? "L" : "U"; });
	//auto all_groups = m.groupValues([](auto i) {return !i ? "L" : "U"; });
	print(all_groups);

	//std::cout << "________________________________________________________" << std::endl;

	Matrix3d<int> m2 = { { { 1, 2, 3 },{ 1, 2 },{ 1, 2 } },{ { 1, 2 },{ 1, 2, 3, 4 } } };
	//Matrix3d<int> m2 = { { { 1,2,3,0 },{ 1,2,0,0 },{ 1,2,0,0 } },{ { 1,2,0,0 },{ 1,2,3,4 },{ 0,0,0,0 } } };
	auto groups = m2.groupValues([](auto i) {return i % 3 ? "!x3" : "x3"; });

	print(groups);


	system("pause");
	return 0;
}

/*
 
 2D print:
L:
{ 0 0 }
{ 0 2 }
{ 1 1 } { 2 1 }
U:
{ 0 1 }
{ 1 0 } { 2 0 }
{ 1 2 } { 2 2 } 

3D print:
!x3:
{ 0 0 0 } { 0 0 1 } { 0 1 0 } { 0 1 1 } { 0 2 0 } { 0 2 1 } { 1 0 0 } { 1 0 1 } { 1 1 0 } { 1 1 1 }
{ 1 1 3 }
x3:
{ 0 0 2 } { 0 0 3 } { 0 1 2 } { 0 1 3 } { 0 2 2 } { 0 2 3 } { 1 0 2 } { 1 0 3 } { 1 1 2 } { 1 2 0 } { 1 2 1 } { 1 2 2 } { 1 2 3 }





*/

