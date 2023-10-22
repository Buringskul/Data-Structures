// Invariant: 
// I used the private data members to control the linked list. The head_ptr keeps track of the first node. The tail_ptr keeps track of the last node. The cursor indicates the current node and the precursor indicates the nodes before the current node. I kept track of the total number of nodes by using the many_nodes data member. 
#include "sequence3.h"
#include <cassert>

using namespace main_savitch_5;

sequence::sequence() {
  // Initialize the object
  head_ptr = nullptr;
  tail_ptr = nullptr;
  cursor = nullptr;
  precursor = nullptr;
  many_nodes = 0;
}

sequence::sequence(const sequence &source) {
  // Copy the object onto a new object 
  many_nodes = source.many_nodes;
  precursor = source.precursor;
  cursor = source.cursor;
  *this = source;
}

sequence::~sequence() {
  // Remove everything in the list 
  list_clear(head_ptr);
  many_nodes = 0;
}

void sequence::start() {
  // If there are nodes make cursor the first node and make precursor point to null since there is nothing before the first node
  if (many_nodes != 0) {
    precursor = NULL;
    cursor = head_ptr;
  }
}

void sequence::advance() {
  // If there is a cursor, set the precursor to the cursor and make cursor point to the next node
  assert(is_item());
  precursor = cursor;
  cursor = cursor->link();
}

void sequence::insert(const value_type &entry) {
  if (is_item()) {
    // If the list has one item insert a head pointer with the value of entry and make the cursor point to the head_ptr and make precursor null
    if (precursor == NULL) {
      list_head_insert(head_ptr, entry);
      cursor = head_ptr;
      precursor = NULL;
    }
    // If the list has more than one item, insert a value right before the cursor with the value of entry and set cursor to after precursor
    else {
      list_insert(precursor, entry);
      cursor = precursor->link();
    }
  }

  else {
    // If there are no items insert a head pointer that points to entry
    list_head_insert(head_ptr, entry);
    cursor = head_ptr;
    precursor = NULL;
  }
  // Add one node to total nodes
  ++many_nodes;
}

void sequence::attach(const value_type &entry) {
  if (is_item()) {
    // If the cursor is not null, make precursor point to the current node and insert a node where cursor points to so that the node inserted becomes the precursor and the node after is the new cursor
    precursor = cursor;
    list_insert(cursor, entry);
    cursor = cursor->link();
  }

  else {
    // If the cursor is null and the head pointer is null, there are no items so attach the new entry value to the head and set cursor to the head
    if (head_ptr == NULL) {
      list_head_insert(head_ptr, entry);
      cursor = head_ptr;
      precursor = NULL;
    }
    // If the cursor is null but there is a head pointer set precursor to point to the last node and insert a node at precursor and make cursor NULL
    else {
      precursor = list_locate(head_ptr, list_length(head_ptr));
      list_insert(precursor, entry);
      cursor = precursor->link(); // NULL
    }
  }
  // Add one total node
  ++many_nodes;
}

void sequence::operator=(const sequence &source) {
  // if the lists point to the same object, end the function
  if (this == &source) {
    return;
  }

  else {
    // Copy the original object onto the new one
    list_copy(source.head_ptr, head_ptr, tail_ptr);
    
    if (source.precursor == NULL) {
      // if there is no cursor or precursor 
      if (source.cursor == NULL) {
        cursor = NULL;
        precursor = NULL;
      }

      else {
        cursor = head_ptr;
        precursor = NULL;
      }
    }

    else {
      // If there is a precursor in the new object
      node *tmp_ptr = head_ptr;
      node *source_ptr = source.head_ptr;
      //Make the precursor point to the first node in the new object
      while (source_ptr != source.precursor) {
        source_ptr = source_ptr->link();
        tmp_ptr = tmp_ptr->link();
      }

      cursor = tmp_ptr->link();
      precursor = tmp_ptr;
    }
  }
  many_nodes = source.many_nodes;
}

void sequence::remove_current() {
  assert(is_item());

  if (cursor == head_ptr) {

    // If cursor is pointed to the head pointer and is the only node remove it and set all pointers to null.
    if (many_nodes == 1) {
      list_head_remove(head_ptr);
      precursor = NULL;
      cursor = NULL;
      head_ptr = NULL;
    }

    else {
      // If cursor is pointed to the head pointer but there are multiple nodes, set the head pointer to the next link and remove the original head pointer.
      node *tmp = head_ptr;
      head_ptr = head_ptr->link();
      delete (tmp);
      cursor = head_ptr;
      precursor = NULL;
    }
  }

  else {
    // If the cursor is not the head pointer set the cursor to the next node and remove the node before it.
    cursor = cursor->link();
    list_remove(precursor);
  }
  // Subtract one from total nodes
  --many_nodes;
}

sequence::value_type sequence::current() const {
  // Return the value of the current node
  assert(is_item());
  return cursor->data();
}
// Runtime analysis is O(1) for all functions except the copy function and the remove function which is O(n)