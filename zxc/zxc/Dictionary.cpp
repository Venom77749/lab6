#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <string>


template class Dictionary<std::string, int>;

template <typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::Dictionary() : size(0), capacity(10) {
    data = new Node[capacity];
}

template <typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::~Dictionary() {
    delete[] data;
}


template <typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::resize() {
    capacity *= 2;
    Node* newData = new Node[capacity];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

template <typename KeyType, typename ValueType>
int Dictionary<KeyType, ValueType>::indexOf(const KeyType& key) const {
    for (int i = 0; i < size; i++) {
        if (data[i].key == key) {
            return i;
        }
    }
    return -1;
}

template <typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    int index = indexOf(key);
    if (index != -1) {
        data[index].value = value;
    }
    else {
        if (size >= capacity) {
            resize();
        }
        data[size].key = key;
        data[size].value = value;
        size++;
    }
}

template <typename KeyType, typename ValueType>
ValueType Dictionary<KeyType, ValueType>::get(const KeyType& key) const {
    int index = indexOf(key);
    if (index != -1) {
        return data[index].value;
    }
    return ValueType();
}

template <typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::remove(const KeyType& key) {
    int index = indexOf(key);
    if (index == -1) {
        return false;
    }
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
    return true;
}

template <typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::contains(const KeyType& key) const {
    return indexOf(key) != -1;
}

template <typename KeyType, typename ValueType>
int Dictionary<KeyType, ValueType>::getSize() const {
    return size;
}

template <typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::printAll() const {
    if (size == 0) {
        std::cout << "Словарь пуст!" << std::endl;
        return;
    }
    std::cout << "\nЛОГИНЫ" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << "Ключ: " << data[i].key << " | Значение: " << data[i].value << std::endl;
    }
    std::cout << std::endl;
}

template <typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::saveToFile(const std::string& filename) const {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Не удалось создать файл " << filename << std::endl;
        return;
    }
    outputFile << size << std::endl;
    for (int i = 0; i < size; i++) {
        outputFile << data[i].key << " " << data[i].value << std::endl;
    }
    outputFile.close();
}
