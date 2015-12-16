# CPP-Testat3 - Indexable Set Class Template

Create a class template indexableSet<T,COMPARE=std::less<T>> that inherits from std::set<T,COMPARE> and allows indexing its content like you could do with a std::vector<T>. Negative indices should index from the "end" of the set. Provide also member functions front() and back() that correspond to those of vector.

Write Test cases and implementation code for indexableSet for the following aspects:

  - all constructors available for std::set should work identically for indexableSet
  - Index access should reveal the stored values in sorted order
  - negative indices should index the set from the end, so that s[-1] is the last available (the greatest) element in the set and s[-s.size()] == s[0]
  - provide member functions front() and back()
  - all of your operations that might result in undefined behavior, because an index is out of range, or no elements exist should throw a corresponding standard exception.
  - allow instantiating indexableSet with a different compare functor. Demonstrate that with a test case with your own caselessCompare functor for std::string. (indexableSet<std::string,caselessCompare>) 

Note: Implement the template class indexableSet as header-only (indexableSet.h) within your CUTE test project.

Note: remember the rules for class templates inheriting from a class that also depends on a template parameter! Otherwise interesting effects for name lookup might happen. Omitting that will cause you to fail! 
