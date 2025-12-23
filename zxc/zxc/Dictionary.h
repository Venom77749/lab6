#pragma once

#include <string>

/// <summary>
/// Шаблонный словарь ключ-значение на динамическом массиве.
/// </summary>
/// <typeparam name="KeyType">Тип ключа</typeparam>
/// <typeparam name="ValueType">Тип значения</typeparam>
template <typename KeyType, typename ValueType>
class Dictionary {
private:
    /// <summary>
    /// Узел словаря: пара ключ-значение.
    /// </summary>
    struct Node {
        KeyType key;
        ValueType value;
    };

    Node* data;    ///< Массив элементов
    int size;      ///< Текущее количество элементов
    int capacity;  ///< Емкость массива

public:
    /// <summary>
    /// Создает пустой словарь с начальной емкостью 10.
    /// </summary>
    Dictionary();
    /// <summary>
    /// Освобождает память, занятую словарем.
    /// </summary>
    ~Dictionary();

    /// <summary>
    /// Увеличивает емкость массива данных в два раза.
    /// </summary>
    void resize();
    /// <summary>
    /// Ищет индекс элемента по ключу.
    /// </summary>
    /// <param name="key">Искомый ключ</param>
    /// <returns>Индекс элемента или -1, если не найден</returns>
    int indexOf(const KeyType& key) const;

    /// <summary>
    /// Вставляет новую пару ключ-значение или обновляет существующую.
    /// </summary>
    /// <param name="key">Ключ</param>
    /// <param name="value">Значение</param>
    void insert(const KeyType& key, const ValueType& value);
    /// <summary>
    /// Возвращает значение по ключу либо значение по умолчанию, если ключ не найден.
    /// </summary>
    /// <param name="key">Ключ для поиска</param>
    ValueType get(const KeyType& key) const;
    /// <summary>
    /// Удаляет элемент по ключу.
    /// </summary>
    /// <param name="key">Ключ для удаления</param>
    /// <returns>true, если элемент был найден и удален</returns>
    bool remove(const KeyType& key);
    /// <summary>
    /// Проверяет наличие элемента с указанным ключом.
    /// </summary>
    /// <param name="key">Ключ для проверки</param>
    /// <returns>true, если элемент существует</returns>
    bool contains(const KeyType& key) const;
    /// <summary>
    /// Возвращает количество элементов в словаре.
    /// </summary>
    int getSize() const;
    /// <summary>
    /// Выводит все пары ключ-значение в консоль.
    /// </summary>
    void printAll() const;

    /// <summary>
    /// Сохраняет содержимое словаря в текстовый файл.
    /// </summary>
    /// <param name="filename">Имя файла для сохранения</param>
    void saveToFile(const std::string& filename) const;
};