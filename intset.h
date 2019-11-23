#ifndef INTSET_H
#define INTSET_H

// robert stewart
// ----------------------------------------------------------------------------
// This class acts as a container for a set of integers and can only contain integers. The set can only contain one of each integer. Negative numbers are ignored
// A boolean array is used as the container for the set. Each index is representative an integer if the element at the index is true, false means the index integer is not contained
// It includes the methods to insert, remove, test if its empty, find if the set contains an integer.
// The program has overriden opperators for finding the union, difference, and interesection of two IntSets; including assignment operators
// The program has overriden stream operators for outputing and inputing IntSets
// The program has overriden condition operators to test if two sets are equal
// Assumptions, implementation details:
//		- Only positive integers can be inserted into the set

#include <iostream>
#include <string>

using namespace std;

class IntSet
{
public:

	IntSet();        // default constructor that constructs an empty set with no integers contained
	IntSet(int a, int b = -1, int c = -1, int d = -1, int e = -1);        // IntSet constructor for one to four argument constructions. Default arguments and negative value arguemnts will be ignored
	IntSet(const IntSet&);          // InSet constructor that accepts a IntSet argument. Creates a deep copy of the passed IntSet argument

	~IntSet();         // Deconstructor that deallocates memory to the bool array field of an IntSet 

	bool isEmpty();         // Returns true if the IntSet is empty. False if it not empty.
	bool insert(int);          // Inserts the int argument into the Set. Returns true if the passed int is sucessful. If the passed int is negative 
	bool remove(int);          // Removes the int argument from the set. Returns false if the argument is not in the set 
	bool contains(int) const;        // Returns true if the int argument is in the IntSet, false otherwise
	bool isInSet(int) const;         // Returns true if the int argument is in the IntSet, false otherwise

	int getHighestPossibleInt() const;          // Returns the size of the bool array that is used to implement the IntSet
	bool* getSet();         // returns the bool array that implements the IntSet. Can be used to modify the bool aray

	void addSmallerSizedSet(const IntSet&);          // adds a set that has a smaller highestPossibleInt to the implicit IntSet  


	const IntSet& operator=(const IntSet&);        // This is “gets”, or the assignment operator, used to assign(deep copy) one set to another

	friend ostream& operator<<(ostream&, const IntSet&);         // Returns an outstream that contains the toString of the IntSet that looks like 
	friend istream& operator >> (istream&, IntSet&);         // Returns the istream inserts integers into the set from console input


	IntSet& operator+=(const IntSet&);          // returns and assigns the lhs to the the union of two sets, the set of elements that are contained in either or both sets.
	IntSet& operator*=(const IntSet&);          // returns and assigns the difference of two sets
	IntSet& operator-=(const IntSet&);          // Returns and assigns the intersection of the two sets

	int findLastInt() const;       // Finds the largest int contained in a set


private:

	int highestPossibleInt;          // Highest POSSIBLE int in the set (array size)
	bool* array;      // array that implements the IntSet

	int findMax(int, int, int, int, int);        // Returns the max value of the passed int arguments

	void copySetToBiggerSet(bool* temp, int);        // Copies the implicit set (bool array) that is smaller to a set that has a larger highestPossibleInt (larger array): Precondition- Passed bool array must be larger



};

IntSet operator+(const IntSet&, const IntSet&);        // Overloaded + operator that finds and returns the union of two sets, the set of elements that are contained in either or both sets.
IntSet operator-(const IntSet&, const IntSet&);        // OVerloaded - operator that finds and returns the difference of two sets
IntSet operator*(const IntSet&, const IntSet&);        // Overloaded * operator that finds and returns the intersection of two sets, the set of all elements that are commonto both sets

bool operator==(const IntSet&, const IntSet&);         // Overloaded == operator that returns true if the IntSets consistsof the same integers. False otherwise
bool operator!=(const IntSet&, const IntSet&);         // Overloaded != operator that returns truye if the IntSet does not consist of the same integers. False otherwise

#endif

