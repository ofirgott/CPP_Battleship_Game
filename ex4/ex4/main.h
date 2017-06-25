#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <list>

template<class T, size_t DIMENSIONS>
class Matrix;



//template <size_t DIMENSIONS>
//using Coordinate = std::array<int, DIMENSIONS> ;
//
//template <size_t DIMENSIONS>
//using CoordinatesGroup = std::vector<Coordinate<DIMENSIONS>>;

//template <size_t DIMENSIONS>
//using Coordinate = std::array<size_t, DIMENSIONS>;

template<class T, size_t DIMENSIONS>
struct MatrixCopier {
	static void copy(T* dest, size_t dest_size, const size_t* dest_dimensions, const T* source, size_t source_size, const size_t* source_dimensions) {
		size_t dest_size0 = dest_dimensions[0] ? dest_size / dest_dimensions[0] : 0;
		size_t source_size0 = source_dimensions[0] ? source_size / source_dimensions[0] : 0;
		for (size_t i = 0; i < source_dimensions[0]; ++i) {
			MatrixCopier<T, DIMENSIONS - 1>::copy(dest + (i * dest_size0), dest_size0, dest_dimensions + 1, source + (i * source_size0), source_size0, source_dimensions + 1);
		}
	}
};

template<class T>
struct MatrixCopier<T, 1> {
	static void copy(T* dest, size_t dest_size, const size_t* dest_dimensions, const T* source, size_t source_size, const size_t* source_dimensions) {
		for (size_t i = 0; i < source_size; ++i) {
			dest[i] = source[i];
		}
	}
};

template<class T, size_t DIMENSIONS>
struct MatrixPrinter {
	static void print(const T* values, size_t size, const size_t* dimensions, std::ostream& out = std::cout) {
		out << '{';
		size_t size0 = size / dimensions[0];
		MatrixPrinter<T, DIMENSIONS - 1>::print(values, size0, dimensions + 1, out);
		for (size_t i = 1; i < dimensions[0]; ++i) {
			out << ',';
			MatrixPrinter<T, DIMENSIONS - 1>::print(values + (i*size0), size0, dimensions + 1, out);
		}
		out << '}';
	}
};

template<class T>
struct MatrixPrinter<T, 1> {
	static void print(const T* values, size_t size, const size_t* dimensions, std::ostream& out = std::cout) {
		out << '{';
		out << values[0];
		for (size_t i = 1; i < size; ++i) {
			out << ',' << values[i];
		}
		out << '}';
	}
};


template<typename T, size_t DIMENSIONS>
class Matrix
{
public:

	
	using Coordinate = std::vector<size_t>;
	using CoordinatesGroup = std::vector<Coordinate>;
	//using CoordinatesGroup = std::vector<Coordinate<DIMENSIONS>>;

	//Template Coordinate data structure
	//using Coordinate = std::array<size_t, DIMENSIONS>;
	
	
	//using Coordinate = CRD<DIMENSIONS> ;
	//using CoordinatesGroup = std::vector<Coordinate> ;
	//using CoordinatesGroup = std::vector<Coordinate>;
	Matrix() {}
	
	// DIMENSIONS == 1
	// We want here a ctor with this signature:
	//    Matrix(const std::initializer_list<T>& values) {
	// but SFINAE is needed to block this ctor from being used by Matrix with DIMENSIONS > 1
	// The SFINAE results with the exact signature we want, but only for cases DIMENSIONS == 1
	template<typename G = T>
	Matrix(const std::initializer_list<typename std::enable_if_t<DIMENSIONS == 1, G>>& values) {
		
		const_cast<size_t&>(_size) = values.size();
		_dimensions[0] = _size;
		_array = std::make_unique<T[]>(_size);
		size_t i = 0;
		for (auto& val : values) {
			_array[i++] = val;
		}
	}
	
	
	// DIMENSIONS > 1
	// We want here a ctor with this signature:
	//    Matrix(const std::initializer_list<Matrix<T, DIMENSIONS-1>>& values) {
	// although this ctor is not useful and won't be used by Matrix<T, 1> it will still be in class
	// and thus would compile as part of Matrix<T, 1> resulting with a parameter of type:
	//          const std::initializer_list< Matrix<T, 0> >& values
	// having Matrix<T, 0> as a parameter - even for a function that is not in use, inside a class that is used
	// would require the compiler to instantiate Matrix<T, 0> class which results with a warning
	// the SFINAE below solves this warning.
	// The SFINAE results with the exact signature we want, but only for cases DIMENSIONS > 1
	template<typename G = T>
	Matrix(const std::initializer_list<Matrix<typename std::enable_if_t<(DIMENSIONS > 1), G>, DIMENSIONS - 1>>& values) {
		_dimensions[0] = values.size();
		for (auto& m : values) {
			for (size_t dim = 0; dim < DIMENSIONS - 1; ++dim) {
				if (m._dimensions[dim] > _dimensions[dim + 1]) {
					_dimensions[dim + 1] = m._dimensions[dim];
				}
			}
		}
		size_t size = 1;
		for (size_t dim = 0; dim < DIMENSIONS; ++dim) {
			size *= _dimensions[dim];
		}

		const_cast<size_t&>(_size) = size;
		_array = std::make_unique<T[]>(_size); // "zero initialized" - T()
		size_t i = 0;
		size_t dest_size = _size / _dimensions[0];
		for (auto& m : values) {
			MatrixCopier<T, DIMENSIONS - 1>::copy(&(_array[i * dest_size]), dest_size, _dimensions + 1, m._array.get(), m._size, m._dimensions);
			++i;
		}
	}
	
	Matrix(Matrix&& m)noexcept {
		*this = std::move(m);
	}

	auto& operator=(Matrix&& m) noexcept {
		std::swap(_array, m._array);
		std::swap(const_cast<size_t&>(_size), const_cast<size_t&>(m._size));
		std::swap(_dimensions, m._dimensions);
		return *this;
	}

	/* Getters */
	//size_t getDimension(size_t i) const {
	//	return _dimensions[i];
	//}

	size_t size() const { return _size; }

	friend std::ostream& operator<<(std::ostream& out, const Matrix& m) {
		MatrixPrinter<T, DIMENSIONS>::print(m._array.get(), m._size, m._dimensions, out);
		return out;
	}

	/* Now our funcions! */

	
	template<class GroupingFunc, class G = typename std::result_of<GroupingFunc(T)>::type>
	auto groupValues(GroupingFunc groupingFunc)
	{
		//using GroupingType = std::result_of_t<GroupingFunc(T)>;
		//std::map<GroupingType, std::vector<CoordinatesGroup>> groups;
		std::map<G, std::vector<CoordinatesGroup>> groups;
		for (auto i = 0; i < DIMENSIONS; ++i)
		{
			std::cout << "Dim " << i << ": " <<  _dimensions[i] << std::endl;
		}
		for (auto i = 0; i < _size; i++)
		{
			
			G coordKey = groupingFunc(_array[i]);
			Coordinate currCoord = flatIndex2Coordinate(i);
			
			std::cout << "now with coord: ( ";
			for (auto ax : currCoord) {
				std::cout << ax << ", ";
			}
			std::cout << ")" << std::endl;
			//auto currCoord;
			//std::copy(currCoord, currCoord + DIMENSIONS, flatIndex2Coordinate(i));

			if (groups.find(coordKey) != groups.end())
			{
				bool currCoordAdded = false;
				for (auto& currGroupOfCurrKey : groups[coordKey])
				{
					
					for (auto& coord : currGroupOfCurrKey) {
						if(coordsEq(currCoord, coord))
						{
							currCoordAdded = true;
							break;
						}
						if (!currCoordAdded &&isAdjacent(currCoord, coord))
						{
							currGroupOfCurrKey.emplace_back(currCoord);
							currCoordAdded = true;
							if (currCoord[0] == 1 && currCoord[1] == 2 && currCoord[2] == 3) std::cout << "fuci" << std::endl;
							break;
						}
					}
				}
				if (!currCoordAdded) {
					CoordinatesGroup tmpCoordGroup;
					tmpCoordGroup.emplace_back(currCoord);
					groups[coordKey].push_back(tmpCoordGroup);
				}
			}
			else
			{
				
				CoordinatesGroup tmpCoordGroup(0);
				tmpCoordGroup.push_back(currCoord);
				std::vector<CoordinatesGroup> tmpVec(0);
				tmpVec.emplace_back(tmpCoordGroup);
				//groups.insert(coordKey);
			
				groups[coordKey] = tmpVec;
			}
		}
		return groups;
	}

	auto flatIndex2Coordinate(size_t index)const
	{
		Coordinate outCoord(DIMENSIONS, 0);
		//return outCoord;
		if (index < 0 || index >= _size)
			throw std::exception("Index out of range");

		size_t mul = _size;


		for (auto i = 0; i < DIMENSIONS; i++) {
			mul /= _dimensions[i];
			outCoord[i] = index / mul;
			index -= outCoord[i] * mul;
		}


		//for (auto i = DIMENSIONS; i != 0; --i) {
		//	mul /= _dimensions[i - 1];
		//	outCoord[i-1] = index / mul;
		//	index -= outCoord[i-1] * mul;
		//}

		return outCoord;
	}

	void testFlatIndextoCoord()const
	{
		for (auto i = 0; i < _size; i++)
		{
			
		}
	}


private:
	//constexpr static size_t NUM_DIMENSIONS = DIMENSIONS;
	std::unique_ptr<T[]> _array = nullptr;
	size_t _dimensions[DIMENSIONS] = {};
	const size_t _size = 0;
	friend class Matrix<T, DIMENSIONS + 1>;

	



	static bool isAdjacent(Coordinate coordA, Coordinate coordB)
	{
		if (coordA == coordB) return false;

		CoordinatesGroup adjacentCoordsOfA;

		for (auto i = 0; i < DIMENSIONS; i++)
		{
			Coordinate tmpCoord = coordA;
			tmpCoord[i]++;
			adjacentCoordsOfA.push_back(tmpCoord);
			if(tmpCoord[i] >= 2)
			{
				tmpCoord[i] -= 2;
				adjacentCoordsOfA.push_back(tmpCoord);
			}
		}
	
			for (auto& adjCoordOfA : adjacentCoordsOfA)
			{
				//if (adjCoordOfA == coordB)
				if(coordsEq(adjCoordOfA ,coordB))
					return true;
			}
		return false;
	}

	static bool coordsEq(Coordinate a, Coordinate b)
	{
		/*if (a.size() != b.size())
			return false;*/

		for (auto i = 0; i < a.size(); i++)
		{
			if (a[i] != b[i])
				return false;
		}
		return true;
	}


	//static bool isCoordianesEquals(Coordinate a, CoordinatesGroup b)
	//{
	//	for (auto i = 0; i < DIMENSIONS; i++)
	//	{
	//		if (a[i] != b[i])
	//			return false;
	//	}
	//	return true;
	//}


	
	using Matrix2d = Matrix<T, 2>;

	
	using Matrix3d = Matrix<T, 3>;


	//std::vector<size_t> computeIndexes(size_t index) const
	//{
	//	assert(index < values.size());
	//
	//	std::vector<size_t> res(dimensions.size());
	//
	//	size_t mul = values.size();
	//	for (size_t i = dimensions.size(); i != 0; --i) {
	//		mul /= dimensions[i - 1];
	//		res[i - 1] = index / mul;
	//		assert(res[i - 1] < dimensions[i - 1]);
	//		index -= res[i - 1] * mul;
	//	}
	//	return res;
	//}

	int Coordinate2flatIndex(Coordinate coord)const
	{
		if (!isValidCoordinate(coord))
			return -1;

		int flatIndex = 0;

		for (auto lyr = 0; lyr < DIMENSIONS; lyr++)
		{
			int lyrMul = coord[lyr];

			for (auto i = 0; i < DIMENSIONS; i++)
				lyrMul *= _dimensions[i];
		
			flatIndex += lyrMul;
		}

		return flatIndex;
	}

	bool isValidCoordinate(Coordinate coord)const
	{
		for (auto i = 0; i < coord.size(); i++)
		{
			if (coord[i] >= _dimensions[i] || coord[i] < 0) 
				return false;
		}
		return true;
	}

};

	
	//1D return (z * xMax * yMax) + (y * xMax) + x;



//		array[N, M, K]->flat_memory[N * M * K]
//
//		flat_index(i, j, k) = (M*N) * i + M * j + k
//
//		array[N, M, K, L]->flat_memory[N * M * K * L]
//
//		flat_index(i, j, k, l) = (M*N*K) * i + (M*N) * j + M* k + l


//	array[N, M, K, L, P]->flat_memory[N * M * K * L * P]
//	flat_index(i, j, k, l, p) = (M*N*K*L) * i + (M*N*K) * j + (M*N) * k + M * l + p; 



template<class T>
using Matrix2d = Matrix<T, 2>;

template<class T>
using Matrix3d = Matrix<T, 3>;


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
	/*Matrix2d<char> m = { { 'a', 'A', 'a' },{ 'B', 'a', 'B' },{ 'B', 'a', 'B'} };
	auto all_groups = m.groupValues([](auto i) {return islower(i) ? "L" : "U"; });
	print(all_groups);
	
	std::cout << "________________________________________________________" << std::endl;*/

	Matrix3d<int> m2 = { { { 1, 2, 3 },{ 1, 2 },{ 1, 2 } },{ { 1, 2 },{ 1, 2, 3, 4 } } };
	//Matrix3d<int> m2 = { { { 1,2,3,0 },{ 1,2,0,0 },{ 1,2,0,0 } },{ { 1,2,0,0 },{ 1,2,3,4 },{ 0,0,0,0 } } };
	auto groups = m2.groupValues([](auto i) {return i % 3 ? "!x3" : "x3"; });
	print(groups);
	
	
	system("pause");
	return 0;
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
