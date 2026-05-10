// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Item {
    T data;
    Item* next;
    explicit Item(const T& val) : data(val), next(nullptr) {}
  };

  Item* head;

 public:
  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    while (head) {
      Item* temp = head;
      head = head->next;
      delete temp;
    }
  }

  TPQueue(const TPQueue&) = delete;
  TPQueue& operator=(const TPQueue&) = delete;

  void push(const T& val) {
    Item* newItem = new Item(val);
    if (!head || val.prior > head->data.prior) {
      newItem->next = head;
      head = newItem;
      return;
    }
    Item* cur = head;
    while (cur->next && cur->next->data.prior >= val.prior) {
      cur = cur->next;
    }
    newItem->next = cur->next;
    cur->next = newItem;
  }

  T pop() {
    if (!head) {
      throw std::out_of_range("TPQueue is empty");
    }
    Item* temp = head;
    T res = head->data;
    head = head->next;
    delete temp;
    return res;
  }

  bool empty() const {
    return head == nullptr;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
