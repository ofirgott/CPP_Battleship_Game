#include <iostream>
#include <vector>
#include <map>


template<typename Groups>
void print(const Groups& all_groups) {
	for (const auto& groupType : all_groups) {
		std::cout << groupType.first << ":" << endl;
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
	auto all_groups = m.groupValues([](auto i) {return islower(i) ? "L" : "U"; });
	print(all_groups);
}

//2d print

//L:
//{ 0 0 }
//{ 0 2 }
//{ 1 1 } { 2 1 }
//U:
//{ 0 1 }
//{ 1 0 } { 2 0 }
//{ 1 2 } { 2 2 }



//3D

//int main() {
//	Matrix3d<int> m2 = { { { 1, 2, 3 },{ 1, 2 },{ 1, 2 } },{ { 1, 2 },{ 1, 2, 3, 4 } } };
//	auto groups = m2.groupValues([](auto i) {return i % 3 ? "!x3" : "x3"; });
//	print(groups);
//}

//{ {{1,2,3,0},{1,2,0,0},{1,2,0,0}}, {{1,2,0,0},{1,2,3,4},{0,0,0,0}} }

//!x3:
//{ 0 0 0 } { 0 0 1 } { 0 1 0 } { 0 1 1 } { 0 2 0 } { 0 2 1 } { 1 0 0 } { 1 0 1 } { 1 1 0 } { 1 1 1 }
//{ 1 1 3 }
//x3:
//{ 0 0 2 } { 0 0 3 } { 0 1 2 } { 0 1 3 } { 0 2 2 } { 0 2 3 } { 1 0 2 } { 1 0 3 } { 1 1 2 } { 1 2 0 } { 1 2 1 } { 1 2 2 } { 1 2 3 }



//for the bonus we neef to use:

//template<class T, size_t DIMENSIONS>
//class Matrix {
//	//...
//};
//
//template<class T>
//using Matrix2d = Matrix<T, 2>;
//
//template<class T>
//using Matrix3d = Matrix<T, 3>;
