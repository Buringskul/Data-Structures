#include "sequence2.h" // Provides the Sequence class with double items.
#include <cassert>
#include <cstdlib> // Provides size_t.
#include <algorithm>
using namespace std;
using namespace main_savitch_4;

sequence::sequence(size_type initial_capacity) {
  data = new value_type[initial_capacity];
  capacity = initial_capacity;
  used = 0;
  current_index = 0;
}

sequence::sequence(const sequence &source) {
  data = new value_type[source.capacity];
  capacity = source.capacity;
  used = source.used;
  current_index = source.current_index;
  copy(source.data, source.data + used, data);
}

sequence::~sequence() {
  delete [] data;
}

void sequence::resize(size_type new_capacity) {
  value_type *larger_array;
  if (new_capacity == capacity) {
    return; // The allocated memory is already the right size.
  }
    
  if (new_capacity < used) {
    new_capacity = used; // Can’t allocate less than we are using.
  }
    
  larger_array = new value_type[new_capacity];
  copy(data, data + used, larger_array);
  delete [ ] data;
  data = larger_array;
  capacity = new_capacity;
}

void sequence::start() {
  current_index = 0;
}

void sequence::advance() {
  current_index++;
}

void sequence::insert(const value_type &entry) {
  // The first action of the insert function is to ensure that there is room for a new item.
  if(capacity <= used) {
    resize(used+1);
  }

  if (!is_item()) {
    current_index = 0;
  }
  
  for (size_type i = used; i > current_index; i--) {
    data[i] = data[i - 1];
  }
  
  data[current_index] = entry;
  used++;
}

void sequence::attach(const value_type &entry) {
  if(capacity <= used) {
    resize(used+1);
  }
  
  if (!is_item()) {
    current_index = used;
  }
    
  else {
    current_index++;
    for (size_type i = used; i > current_index; i--) {
      data[i] = data[i - 1];
    }
  }
  data[current_index] = entry;
  used++;
}

void sequence::remove_current() {
  assert(is_item());
  used--;
  for (size_type i = current_index; i < used; i++) {
    data[i] = data[i + 1];
  }
}

void sequence::operator=(const sequence &source) {
  value_type *new_data;
  // Check for possible self-assignment:
  if (this == &source)
    return;
  // If necessary, allocate a dynamic array of a different size.
  if (capacity != source.capacity) {
    new_data = new value_type[source.capacity];
    delete [ ] data;
    data = new_data;
    capacity = source.capacity;
  }
  used = source.used;
  current_index = source.current_index;
  copy(source.data, source.data + used, data); // Use the copy function to copy data from the source.
}

sequence::size_type sequence::size( ) const {
  return used;
}

bool sequence::is_item( ) const {
  return (current_index < used);
}

sequence::value_type sequence::current( ) const {
  return data[current_index];
}

void sequence::operator +=(const sequence& source) {
  if(capacity < source.used+ used) {
    resize(capacity + source.used);
  }
    
  for(size_t i = used; i < used + source.used; i++) {
    data[i] = source.data[i];
  }
  used = used + source.used;
}

sequence operator +(const sequence& source1, const sequence& source2) {
  sequence result(source1.size() + source2.size());
  result += source1;
  result += source2;
  return result;
}

sequence::value_type sequence::operator[](size_type index) const {
  assert(index < used);
  return data[index];
}