#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>


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
		MatrixPrinter<T,DIMENSIONS - 1>::print(values, size0, dimensions + 1, out);
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

	Matrix() {}
	
	// DIMENSIONS == 1
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
	
	
	Matrix(Matrix&& m)noexcept {													/* move constructor */
		*this = std::move(m);
	}

	auto& operator=(Matrix&& m) noexcept {											/* move assignment*/
		std::swap(_array, m._array);
		std::swap(const_cast<size_t&>(_size), const_cast<size_t&>(m._size));
		std::swap(_dimensions, m._dimensions);
		return *this;
	}


	friend std::ostream& operator<<(std::ostream& out, const Matrix& m) {			/* for matrix printing */
		MatrixPrinter<T, DIMENSIONS>::print(m._array.get(), m._size, m._dimensions, out);
		return out;
	}

	
	template<class GroupingFunc, class G = typename std::result_of<GroupingFunc(T)>::type>
	auto groupValues(GroupingFunc groupingFunc)
	{
		std::map<G, std::vector<CoordinatesGroup>> groups;		/* mapping the matrix to groups according to the groupingfunc output */	
		
																/* isMappedCoord -we cannot use vector of bool because of https://stackoverflow.com/a/8399470. we cannot also use bitset, 
																 * because in bitset we need to know the size in compilation time.
																 * isMappedCoord[i] can be == '0' for false, or == '1' for true
																 */
		std::vector<char> isMappedCoord(_size, '0');				
		int currCoordIndex = 0;
		
		while(currCoordIndex < _size)
		{
			if (isMappedCoord[currCoordIndex] != '0')
				currCoordIndex++;

			else {
			
				auto currCoord = flatIndex2Coordinate(currCoordIndex);
				G coordKey = groupingFunc(_array[currCoordIndex]);

				if (groups.find(coordKey) == groups.end())						/* coordKey is not in the map - insert it with empty group in value */
					groups[coordKey] = std::vector<CoordinatesGroup>();

				CoordinatesGroup currGroup;
				getAllAdjacentCoordsSameGroup<GroupingFunc>(groupingFunc, currCoord, coordKey, currGroup, isMappedCoord);
				
				bool groupInserted = false;

				for (auto& group : groups[coordKey]) {
					
					if (isGroupsAdjacent(currGroup, group))
					{
						groupInserted = true;
						for (auto coord : currGroup)
							group.emplace_back(coord);
						break;												/* we can exit from the for loop once we find some adjacent group*/
					}
				}
				if (!groupInserted)											/* if we didn't find group to be inserted - create new group under this key */
					groups[coordKey].emplace_back(currGroup);
			
				for (auto& coord : currGroup)
					isMappedCoord[Coordinate2flatIndex(coord)] = '1';		/* marked all coordinates in the group we found as mapped */
			}
		}
		
		/* sorting all coordinate groups */
		for (auto& type : groups)
			for (auto& group : type.second)
				std::sort(group.begin(), group.end(), coordinatesComparisonFunc);

		return groups;
	}


private:

	std::unique_ptr<T[]> _array = nullptr;
	size_t _dimensions[DIMENSIONS] = {};
	const size_t _size = 0;
	friend class Matrix<T, DIMENSIONS + 1>;

	template<class GroupingFunc, class G = typename std::result_of<GroupingFunc(T)>::type>
	void getAllAdjacentCoordsSameGroup(GroupingFunc groupingFunc, const Coordinate& currCoord, G coordKey, CoordinatesGroup& currGroup, std::vector<char>& isMappedCoord)const
	{
		 auto currFlatIndex = Coordinate2flatIndex(currCoord);
		
		if(groupingFunc(_array[currFlatIndex]) == coordKey)
		{
			isMappedCoord[currFlatIndex] = '1';						/* mark this coordinate as mapped */
			currGroup.emplace_back(currCoord);

			for(auto dim = 0; dim < DIMENSIONS; dim++)
			{
				Coordinate tmpCoord = currCoord;
				tmpCoord[dim]++;
				if(isValidCoordinate(tmpCoord) && isMappedCoord[Coordinate2flatIndex(tmpCoord)] == '0')
					getAllAdjacentCoordsSameGroup<GroupingFunc>(groupingFunc, tmpCoord, coordKey, currGroup, isMappedCoord);
	
				if(tmpCoord[dim] >= 2)								/* -1 in coordinate will be problematic because Coordinate is from type size_t */
				{
					tmpCoord[dim] -= 2;
					if (isValidCoordinate(tmpCoord) &&	isMappedCoord[Coordinate2flatIndex(tmpCoord)] == '0')
						getAllAdjacentCoordsSameGroup<GroupingFunc>(groupingFunc, tmpCoord, coordKey, currGroup, isMappedCoord);
				}		
			}
		}
	}

	static bool isGroupsAdjacent(const CoordinatesGroup& groupA, const CoordinatesGroup& groupB)
	{
		for (auto& coordB : groupB)
			for (auto& coordA : groupA)
				if (isAdjacent(coordA, coordB))
					return true;
	
		return false;
	}

	static bool isAdjacent(const Coordinate& coordA, const Coordinate& coordB)
	{
		if (coordA == coordB) return true;				/* same Coordinate - operator == of std::vector is good for us in this case */
		
		CoordinatesGroup adjacentCoordsOfA;

		for (auto i = 0; i < DIMENSIONS; i++)
		{
			Coordinate tmpCoord = coordA;				/* creates all adjacent coords of coordA */
			tmpCoord[i]++;
			adjacentCoordsOfA.emplace_back(tmpCoord);
			if(tmpCoord[i] >= 2)
			{
				tmpCoord[i] -= 2;
				adjacentCoordsOfA.emplace_back(tmpCoord);
			}
		}
	
			for (auto adjCoordOfA : adjacentCoordsOfA)
				if (adjCoordOfA == coordB)
					return true;

		return false;
	}

	size_t Coordinate2flatIndex(const Coordinate& coord)const
	{
		size_t flatIndex = 0;

		for (auto dim = 0; dim < DIMENSIONS; dim++)
		{
			auto dimMul = coord[dim];
			for (auto i = dim + 1 ; i < DIMENSIONS; i++)
				dimMul *= _dimensions[i];
		
			flatIndex += dimMul;
		}
		
		return flatIndex;
	}

	bool isValidCoordinate(const Coordinate& coord)const
	{
		for (auto i = 0; i < DIMENSIONS; i++)
		{
			if (coord[i] >= _dimensions[i] || coord[i] < 0) 
				return false;
		}
		return true;
	}

	Coordinate flatIndex2Coordinate(size_t index)const
	{
		Coordinate outCoord(DIMENSIONS, 0);

		if (index < 0 || index >= _size)
			throw std::exception("Index out of range");

		size_t mul = _size;

		for (auto i = 0; i < DIMENSIONS; i++) {
			mul /= _dimensions[i];
			outCoord[i] = index / mul;
			index -= outCoord[i] * mul;
		}

		return outCoord;
	}

	static bool coordinatesComparisonFunc(const Coordinate& coordA, const Coordinate& coordB) {
		for (auto i = 0; i < DIMENSIONS; i++)
		{
			if (coordA[i] < coordB[i]) return true;
			if (coordA[i] > coordB[i]) return false;
			//else - check next dimension
		}
		return true;
	}

};

template<class T>
using Matrix2d = Matrix<T, 2>;

template<class T>
using Matrix3d = Matrix<T, 3>;

