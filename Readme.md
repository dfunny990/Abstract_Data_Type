Abstract Data Type Using C++

The assignment in class was to use C++ to create a templated Abstract Data Type.
The specifics of the assignment can be found below, or in a PDF in the repo.




CS253 HW6: Smaph
Description
For this assignment, you will implement a templated STL-like container. Its kind of like a set, kind of like a map, and kind of like a graph, so its a Smaph.
You will turn in a single file, Smaph.h. You may use C++11 features.
Template Parameters
A Smaph takes three template parameters:
o	The first of the two types to be stored.
o	The second of the two types to be stored.
o	Comparison functor (defaults to std::less<value_type>). It compares two instances of std::pair, and returns true if the first should be before the second in the collection. std::less with a std::pair is a two-tier comparison: it compares the first values, then break ties by comparing the second values. However, a user-supplied functor may compare in any way it wants to.


Requirements for stored type
The type stored by this templated class has the following requirements:
o	Default constructor
o	Copy constructor
o	Assignment operator
o	It is not required that ==, <, etc., be valid for the stored types. Your code must not use such operatorsit must use the comparison functor, which should default to the less<T> functor.
Required public types of Smaph
The following types have similar meanings to those of a map:
o	size_type (must be an unsigned integral type)
o	key_type (the first template argument)
o	mapped_type (the second template argument)
o	value_type (std::pair<key_type,mapped_type>)
o	iterator
Required public methods of Smaph
o	default ctor
o	copy ctor
o	ctor that takes a half-open range of two iterators
	These do not have to be iterators from a Smaph.
o	ctor that takes two arguments: key_type, mapped_type
o	ctor that takes a value_type
o	assignment operator
o	destructor
o	iterator begin() const
o	iterator end() const
o	bool empty() const
o	size_type size() const
	Number of data items currently stored
o	size_type max_size() const
	Maximum possible number of elements allowed by this design
o	iterator find(const key_type &, const mapped_type &) const 
iterator find(const value_type &) const
	Look for the instance of the given value. Return end() upon failure.
o	size_type count(const key_type &, const mapped_type &) const 
size_type count(const value_type &) const
	Return how many times the given value occurs in the container.
o	pair<iterator,bool> insert(const key_type &, const mapped_type &) 
pair<iterator,bool> insert(const value_type &)
	Insert this value, in order
	Duplicates are not permitted
	Returns an iterator pointing to the value in the container. An interator pointing to the value is always returned, whether or not anything got inserted.
	Returns a boolean that is true if the value was just inserted, as opposed to being there already.
o	void insert(iterator, iterator)
	These are not necessarily Smaph iterators.
	Insert the values in this half-open range into the collection.
	The iterators can be of any type, referring to any kind of collection.
	The iterators may point to duplicates; or values out of order.
	However, the resulting Smaph must not contain any duplicates, and must be in order.
o	bool erase(const key_type &, const mapped_type &) 
bool erase(const value_type &)
	Erase the value from the collection.
	Return true if it was there.
o	void erase(iterator)
	This is an iterator from the Smaph.
	Erase the value at that location.
o	void erase(iterator, iterator)
	These are iterators from the Smaph.
	Erase the values in that half-open range.
o	void clear()
	Make it have no values.
Required operators
o	Smaph | Smaph
o	Smaph | value_type
o	value_type | Smaph
	Returns the union of the two arguments.
o	Smaph & Smaph
o	Smaph & value_type
o	value_type & Smaph
	Returns the intersection of the two arguments.
o	Smaph |= Smaph
o	Smaph |= value_type
	Same as Smaph = Smaph | right-hand-side
o	Smaph &= Smaph
o	Smaph &= value_type
	Same as Smaph = Smaph & right-hand-side
Required operations on Smaph::iterator:
o	default constructor
o	copy constructor
o	assignment operator
o	destructor
o	==
o	!=
o	indirection
o	->
o	pre-/post-increment/decrement
The value exposed by the iterator must be read-only:
o	*iter=...; must not compile
o	iter->first=...; must not compile
o	iter->second=...; must not compile
Requirements
o	We will compile your program with: g++ -std=c++11
o	Your header file must have #include guards.
o	Your header file must not have any using declarations, not even selective ones like using std::pair.
o	You may not use any C++ containers in your implementation. No list, no vector, no set, no string, etc.
o	You may use C++ algorithms, functors, pair, etc.
o	You may not use any external programs, e.g., via system, popen, fork, exec, etc.
o	No memory leaks.
o	It must be possible for a program have several instances of Smaph active at the same time, and they must not interfere with each other.
o	It is acceptable for insert, erase, and clear to invalidate all existing iterators. It is also acceptable for them to not invalidate any iterators. Its up to you.
o	Pay attention to const-correctness. We may try to assign a const Smaph to a non-const Smaph, take the size() of a const Smaph, etc.
o	Brush your teeth after every meal.
o	You may add other methods and operators, as needed.
o	You may implement the methods inside or outside of the class declaration.

