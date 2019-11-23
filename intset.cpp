
#include "intset.h"
#include <sstream>

// ----------------------------------------------------------------------------
// robert stewart
// This class acts as a container for a set of integers and can only contain integers. The set can only contain one of each integer. Negative numbers are ignored
// A boolean array is used as the container for the set. Each index is representative an integer if the element at the index is true, false means the index integer is not contained
// It includes the methods to insert, remove, test if its empty, find if the set contains an integer.
// The program has overriden opperators for finding the union, difference, and interesection of two IntSets; including assignment operators
// The program has overriden stream operators for outputing and inputing IntSets
// The program has overriden condition operators to test if two sets are equal
// Assumptions, implementation details:
//		- Only positive integers can be inserted into the set

//-----------------------------------------------------------------------------
// IntSet() default constructor
// default constructor that initilizes an empty IntSet
// The array container is initilized to size 1 and can only contain the int 0 without being re sized
IntSet::IntSet()
{

	highestPossibleInt = 1;
	array = new bool[highestPossibleInt];
	array[0] = false;

}


//-----------------------------------------------------------------------------
// IntSet multiple argument constructor
//  IntSet constructor for one to four argument constructions. Default arguments and negative value arguemnts will be ignored in initialization
// bool container array is initialized to false for an empty IntSet
// All positive passed arguments get assigned values 
IntSet::IntSet(int a, int b, int c, int d, int e)
{

	highestPossibleInt = findMax(a, b, c, d, e) + 1;
	array = new bool[highestPossibleInt];

	for (int i = 0; i < highestPossibleInt; i++)
	{

		array[i] = false;

	}

	if (a >= 0) array[a] = true;
	if (b >= 0) array[b] = true;
	if (c >= 0) array[c] = true;
	if (d >= 0) array[d] = true;
	if (e >= 0) array[e] = true;

}


//-----------------------------------------------------------------------------
// IntSet constructor by passing IntSet 
// copy constructor that accepts an IntSet as a argument and deep copies the passed IntSets field values to the implicit fields
//const passed IntSet so modification are ensured to not be made to it
// Assumtions
//       - The passed IntSet has valid fields
IntSet::IntSet(const IntSet& set)
{

	highestPossibleInt = set.highestPossibleInt;
	array = new bool[highestPossibleInt];

	for (int i = 0; i < highestPossibleInt; i++)
	{

		array[i] = set.array[i];

	}

}


//-----------------------------------------------------------------------------
// ~deconstructor 
//precondition- object must have been created
//postconditions- IntSet dynamic bool array is deleted
// Destructor for the IntSet
// delets the dynamic memory bool array that acts as the IntSets container
IntSet::~IntSet()
{

	delete[] array;

}

//-----------------------------------------------------------------------------
// isEmpty()
//preconditions None
//postconditions Intset not affected.
// Returns true if the IntSet is empty. False otherwise
// Loops through the array container to test if any integers are stored as bools
bool IntSet::isEmpty()
{

	for (int i = 0; i < highestPossibleInt; i++)
	{

		if (array[i] == true) return false;

	}

	return true;

}


//-----------------------------------------------------------------------------
// insert
//precondition- None
//postcondition-  Inserts passed int into the IntSet
// if the container array is not large enough to store the passed int, the array will be resized to fit the passedint and the highestPossible int will be resized to passed int
// If the passed number is negative it will not be stored
// returns true if passed int is inserted into the IntSet
// returns false if the passed int is negative is not inserted into the array
bool IntSet::insert(int num)
{

	if (num < 0) return false;           // negative numbers willnot be inserted into the array
	else if (num >= highestPossibleInt)         // resize containing array to fit passed int
	{

		int newSize = num + 1;
		bool* temp = new bool[newSize];
		copySetToBiggerSet(temp, newSize);
		delete[] array;
		array = temp;
		array[num] = true;
		highestPossibleInt = newSize;

	}
	else
	{

		array[num] = true;

	}

	return true;

}


//-----------------------------------------------------------------------------
//remove
//Precondition- None
//Postcondition- removes the passed integer from the set
// returns false if passed number is negative
// returns true if the passed int was not in the set or if it was removed
bool IntSet::remove(int num)
{

	if ( num < 0) return false;
	else if (num >= highestPossibleInt)
	{

		return true;

	} else
	{

		array[num] = false;
		return true;

	}
}

//-----------------------------------------------------------------------------
//contains
//Precondition None
//Postcondition
// returns true if the IntSet contains the passed int. False otherwise
bool IntSet::contains(int num) const
{
	if (num >= highestPossibleInt) return false;
	else
	{

		return array[num];      

	}

}


//-----------------------------------------------------------------------------
// isIntSet
//Precondition- None
//Postcondition-
// returns true if IntSet contains the passed int. False otherwise
bool IntSet::isInSet(int num) const
{
	return contains(num);
}

//-----------------------------------------------------------------------------
// getHighestPossibleInt
//Precondition- None
//Postcondition- returns the highest possible int (array container size)
int IntSet::getHighestPossibleInt() const
{

	return highestPossibleInt;

}


//-----------------------------------------------------------------------------
//getSet
//Precondition-  
//Postcondition-
// returns the container array
// WARNING you can modify and delete the array after being return
// user needs to only use
bool* IntSet::getSet()
{
	return array;
}

//-----------------------------------------------------------------------------
//operator<<
//Precondition- left hand side 
//Postcondition
// returns an ostream operator that contains the toString for the IntSet
// represented as { 1 2} for an intset that contains 1 and 2. {} for an empty intset
ostream & operator<<(ostream &out, const IntSet &rhs)
{


	int lastInt = rhs.findLastInt();        // finds the last and largest int in the IntSet. value will be -1 if the intset is empty 
	if (lastInt == -1)
	{

		out << "{}";         // ostream will contain an empty array representation string if the IntSet is empty

	}
	else
	{

		out << "{ ";

		for (int i = 0; i < lastInt; i++)
		{
			if (rhs.contains(i))
			{

				out << i << " ";

			}

		}

		out << lastInt << "}";        // fence post for printing the largest int in the set with out the following whitespace

	}

	return out;

}

//-----------------------------------------------------------------------------
//operator>>
//Precondition- input 
//Postcondition
//  returns an instream that will insert ints to the IntSet from console input
// input will be terminated by inputing the int -1 into the 
istream & operator>>(istream &in, IntSet &rhs)
{

	int numToInsert = 0;
	in >> numToInsert;

	while (numToInsert != -1)        //awaits user to terminate console input by entering-1
	{

		rhs.insert(numToInsert);
		in >> numToInsert;

	}

	return in;

}

//-----------------------------------------------------------------------------
//operator+
//PreconditionRight hand side and left hand side most both be IntSets
//Postcondition
// Overloaded + operator that finds and returns the union of two sets, the set of elements that are contained in either or both sets.
IntSet operator+(const IntSet& lhs, const IntSet& rhs)
{

	if (lhs.getHighestPossibleInt() > rhs.getHighestPossibleInt())      // finds the largest of the arrays
	{

		IntSet returnSet(lhs);           //intset to return created from lhs
		returnSet.addSmallerSizedSet(rhs);        //adds the smaller intset to the return set
		return returnSet;

	}
	else
	{

		IntSet returnSet(rhs);
		returnSet.addSmallerSizedSet(lhs);
		return returnSet;

	}

}

//-----------------------------------------------------------------------------
//operator-
//Precondition- right hand side and left hand side must be IntSets
//Postcondition
// OVerloaded - operator that finds and returns the difference of two sets
IntSet operator-(const IntSet& lhs, const IntSet& rhs)
{

	if (lhs.getHighestPossibleInt() > rhs.getHighestPossibleInt())
	{

		IntSet returnSet(lhs);
		bool* returnSetArray = returnSet.getSet();

		for (int i = 0; i < rhs.getHighestPossibleInt(); i++)      //loops and finds the difference of the sets
		{

			if (rhs.contains(i) && lhs.contains(i))        //if both methods contain the same ints
			{

				returnSetArray[i] = false;

			}

		}

		return returnSet;

	}
	else
	{

		IntSet returnSet(lhs);
		bool* returnSetArray = returnSet.getSet();

		for (int i = 0; i < returnSet.getHighestPossibleInt(); i++)
		{

			if (rhs.contains(i) && lhs.contains(i))
			{

				returnSetArray[i] = false;

			}
		}

		return returnSet;

	}

}

//-----------------------------------------------------------------------------
//operator*
//Precondition- right hand side and left hand side must both be IntSets
//Postcondition 
// Overloaded * operator that finds and returns the intersection of two sets, the set of all elements that are commonto both sets
// insures that the rhs and lhs are not modified
IntSet operator*(const IntSet &lhs, const IntSet &rhs)
{

	if (lhs.getHighestPossibleInt() > rhs.getHighestPossibleInt())
	{

		IntSet returnSet(-1);
		for (int i = 0; i < lhs.getHighestPossibleInt(); i++)
		{

			if (lhs.contains(i) && rhs.contains(i))
			{

				returnSet.insert(i);

			}

		}

		return returnSet;

	}
	else
	{

		IntSet returnSet(-1);
		for (int i = 0; i < rhs.getHighestPossibleInt(); i++)
		{

			if (lhs.contains(i) && rhs.contains(i))
			{

				returnSet.insert(i);

			}

		}

		return returnSet;

	}

}

//-----------------------------------------------------------------------------
//operator==
//Precondition- right hand side and left hand side must be IntSets
//Postcondition
// returns true if the two IntSets are the same, meaning they contain the same ints 
bool operator==(const IntSet& lhs, const IntSet& rhs)
{

	if (lhs.getHighestPossibleInt() > rhs.getHighestPossibleInt())      // finds the largest array of the IntSet
	{

		for (int i = 0; i < lhs.getHighestPossibleInt(); i++)          // Goes through the larger of the arrays. 
		{

			if ((lhs.contains(i) && !rhs.contains(i)) || (!lhs.contains(i) && rhs.contains(i)))       // if one array has the element, but the other does not
			{

				return false;

			}

		}


	}
	else
	{

		for (int i = 0; i < rhs.getHighestPossibleInt(); i++)         // goes through the larger of the arrays
		{

			if ((lhs.contains(i) && !rhs.contains(i)) || (!lhs.contains(i) && rhs.contains(i)))         // if one array has the element , but the other does not
			{

				return false;

			}

		}

	}

	return true;
}

//-----------------------------------------------------------------------------
//operator!=
//Precondition
//Postcondition
// returns true if the two IntSets are not the same, meaning they do not contain the same ints. False otherwise
bool operator!=(const IntSet &lhs, const IntSet &rhs)
{

	return !operator==(lhs, rhs);

}

//-----------------------------------------------------------------------------
//findMAx
//Precondition- atleast one argument must be passed as a parameter
//Postcondition
// finds the largest int from the passed arguments and returns it
int IntSet::findMax(int a, int b, int c, int d, int e)
{

	int temp[] = { a, b, c, d, e };
	int max = 0;          // default size

	for (int i = 0; i < 5; i++)          // goes through loop of passed items and finds the max
	{

		if (temp[i] > max)
		{

			max = temp[i];

		}
	}

	return max;

}

//-----------------------------------------------------------------------------
//findLastInt
//Precondition- 
//Postcondition
// helper method that finds the largest int contained within the InSet and returns it. Returns -1 if the IntSet isempty
int IntSet::findLastInt() const
{

	for (int i = (highestPossibleInt - 1); i >= 0; i--)        //starts at the end of the array and finds the first element
	{

		if (array[i] == true)         //first element
		{

			return i;

		}

	}

	return -1;
}

//-----------------------------------------------------------------------------
//addSmallerSizedSet
//preconditions- the passed IntSet's array container must be of a smaller size that the implicit array
//Postcondition
// helper method that adds a smaller IntSet to this IntSet
void IntSet::addSmallerSizedSet(const IntSet& otherSet)
{
	for (int i = 0; i < otherSet.getHighestPossibleInt(); i++)         //goesthrough smaller array and adds elements from it to implicit array
	{

		if (otherSet.array[i] == true)
		{

			array[i] = true;

		}
	}

}

//-----------------------------------------------------------------------------
//operator=
//Precondition right hand side must be an IntSet
//Postcondition
// overloaded assignment constructor that assigns a deep copy of the IntSet fields from right hand side of the operation.
const IntSet & IntSet::operator=(const IntSet &rhs)
{

	bool* temp = new bool[rhs.getHighestPossibleInt()];       // temp bool array to replace implicite array

	for (int i = 0; i < rhs.getHighestPossibleInt(); i++)
	{

		temp[i] = rhs.array[i];

	}

	delete[] array;         //delete old array
	array = temp;
	highestPossibleInt = rhs.getHighestPossibleInt();

	return *this;

}

//-----------------------------------------------------------------------------
//operator+=
//Precondition- right hand side must be an IntSet
//Postcondition- 
// returns and assigns the lhs to the the union of two sets, the set of elements that are contained in either or both sets.
IntSet & IntSet::operator+=(const IntSet& rhs)
{

	*this = operator+(*this, rhs);
	return *this;

}

//-----------------------------------------------------------------------------
//operator*=
//Precondition right hand side must be a IntSet
//Postcondition
// returns and assigns the difference of two sets
IntSet & IntSet::operator*=(const IntSet & rhs)
{

	*this = operator*(*this, rhs);
	return *this;

}

//-----------------------------------------------------------------------------
//operator-=
//Precondition Right Hand side must be IntSet
//Postcondition
// Returns and assigns the intersection of the two sets
IntSet & IntSet::operator-=(const IntSet & rhs)
{

	*this = operator-(*this, rhs);
	return *this;

}

//-----------------------------------------------------------------------------
//copySetToBiggerSet
//Precondition- Sets must be the same size
//Postcondition
// asumes sets are the same size
// helper method copies the implecit array to the passed arrray that acts as the IntSet container 
void IntSet::copySetToBiggerSet(bool* temp, int biggerSize)
{
	int i = 0;
	for (; i < highestPossibleInt; i++)        // goes through this array container and copies values to temp 
	{

		temp[i] = array[i];

	}

	for (; i < biggerSize; i++)         //goes through the rest of the bigger array. starting at the  end of this array's size and adds values to temp
	{

		temp[i] = false;

	}


}
