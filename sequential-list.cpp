
#include <iostream>
#include "sequential-list.h"

using namespace std;

// Create a new SequentialList with the given number of elements.
// creates a constructor and sets the size to zero, capacity to cap, and creates a new list
SequentialList::SequentialList(unsigned int cap) {
    size_ = 0;
    capacity_ = cap;
    data_ = new SequentialList::DataType[cap];
}

//Destroy this SequentialList, freeing all dynamically allocated memory.
// destructor for previous constructor, deleting the variable with the new operator since it's memory was dynamically allocated
SequentialList::~SequentialList() {
    delete data_;
    data_ = NULL;

}

// Returns the number of elements in the list.
// returns size_ which is the int that indicates how many elements are being used in the list
unsigned int SequentialList::size() const {
    return size_;
}

// Returns the maximum number of elements the list can hold.
// returns capacity_ which is the capacity of the list, i.e. how many items can be stored in data_
unsigned int SequentialList::capacity() const {
    return capacity_;
}

// Returns true if the list is empty, false otherwise.
// checks if the size of the list is equal to zero, which means there are no items in it, and it's empty
// if this is the case, the function will return true
// in all other cases, it will return false
bool SequentialList::empty() const {
    if (size_ == 0) {

        return true;
    }

    return false;
}

// Returns true if the list is at capacity, false otherwise.
// checks if the number of items in the list is the same as the maximum number of items allowed in the list
// if these 2 numbers are equivalent, the list is full, and the function returns true
// otherwise the bool function will return false
bool SequentialList::full() const {
    if (size_ == capacity_) {
        return true;
    }
    return false;
}

// Returns the value at the given index in the list. If index is invalid,
// return the value of the last element.
// checks for invalid index first, which would be if it's outside the size of the list, or equal to it which is why the >= symbol is used
// in this case, it returns the value at an index that's one less than the size of the list
// since the index starts at 0 but the list size starts counting from 1 - meaning the last value will be returned
// otherwise, if index is valid, this if statement will not be relevant and the given index will be called with the list to give that specific value
SequentialList::DataType SequentialList::select(unsigned int index) const {
    if (index >= size_) {
        return data_[size_ - 1];
    }
    return data_[index];
}

// Searches for the given value, and returns the index of this value if found.
// Returns the size of the list otherwise
// creating integer i to check through each value in the list
// this integer will increase by 1 each time the for loop is iterated through, which will be until i is equal to size
// the for loop checks if the data value at each index matches the value that's being searched for, if so i will be returned which is the index of the given value
// if there is no match, the function breaks out of the for loop and instead will return the size of the list
unsigned int SequentialList::search(DataType val) const {
    for (int i = 0; i < size_; i++) {
        if (data_[i] == val) {
            return i;
        }
    }
    return size_;
}

// Prints all elements in the list to the standard output.
// creating integer i to go through each value in the list
// this integer will increase by 1 each time the for loop is iterated through, which will be until i is equal to size
// the for loop prints the value at each index in the list with an output statement, it will do this for every index in the list and stop when it reaches the end
void SequentialList::print() const {
    for (int i = 0; i < size_; i++) {
        std::cout << data_[i] << std::endl;
    }
}

// Inserts a value into the list at a given index.
// this function first checks if the index is outside of the size of the list, OR if the list is already full - calling the full function
// if either of these conditions are true then the function will return false
bool SequentialList::insert(DataType val, unsigned int index) {

    if (index > size_ || full()) {
        return false;
    }

// creating an integer i that starts at the highest index value which is one less than the size since index starts at 0
// the for loop brings i from the end of the list to the given index by decreasing the value of i by one each iteration
// with each iteration, the for loop moves the elements to the right of the given index over, to make room for the value being inserted at the index
// it stops when i has arrived at the index or has gone past it - index is being forced to convert to a signed int to cover the case of inserting into an empty list
// if it's not a signed int, i will start at -1 and decrease with each iteration,
// once i is at the correct index, the for loop ends, all elements have been shifted, and the value that's given is put into the list at the given index
// the size of the list is then increased by 1 because there is now a new element
    for (int i = size_ - 1; i >= (signed int) index; i--) {
        data_[i + 1] = data_[i];
    }

    data_[index] = val;
    size_++;
    return true;

}

// Inserts a value at the beginning of the list.
// since the function above inserts a given value into a given index, I can just call that function within this function, with an index of 0
// this ensures the value is inserted at the front of the list
bool SequentialList::insert_front(DataType val) {
    return insert(val, 0);
}
// Inserts a value at the end of the list.
// can use the previously created function once more, but this time the index will be at size_ since it should be inserted at an index that's one more than the list's index
// ensures the value inserted is at the back of the list
bool SequentialList::insert_back(DataType val) {
    return insert(val, size_);
}
// Deletes a value from the list at the given index.
// the function first checks if the given index is greater than or equal to the size of the list
// if this is the case there will be no value to delete
// if either this is true or if the list is empty, the function will return false
bool SequentialList::remove(unsigned int index) {
    if (index >= size_ || empty()) {
        return false;
    }
// for loop that creates an integer i which will be equal to the index above the given index, and increases it by one for each iteration
// with each iteration the loop sets the value at the index of the value of one less than i, to the value at the index of i
// this will assign the given index, the value at the index beside it, deleting the value at the given index, shifting over all the values
// iterations continue until i is no longer less than the size, meaning it's reached the last index and continuing would go to a non-existent value
// the size of the list is then decreased by one since a value was deleted, and the function returns true since it's a bool function
    for (int i = index + 1; i < size_; i++) {
        data_[i - 1] = data_[i];
    }

    size_--;
    return true;
}
// Deletes a value from the beginning of the list.
// since a remove function was already created for a given index, it can be called with the index of 0, which will delete the first value in the list
bool SequentialList::remove_front() {
    return remove(0);
}
// Deletes a value at the end of the list.
// can use the remove function again and delete at the index that's one less than size since the index starts at 0 and size starts at 1,
// one less than the size will be equivalent to the index of the last element
bool SequentialList::remove_back() {
    return remove(size_ - 1);
}
// Replaces the value at the given index with the given value.
// first checks to make sure the given index is not equal to the size of the list
// if this is the case then there is nothing to replace since it's beyond the index of the list
bool SequentialList::replace(unsigned int index, DataType val) {
    if (index >= size_) {
        return false;
    }
// takes the value at the given index and sets it equal to the given value, replacing what was there before
    data_[index] = val;
    return true;
}



