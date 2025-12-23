#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Dictionary.h"
#include "Pistol.h"

int main() {
    setlocale(LC_ALL, "rus");

    int mainChoice;
    std::cout << "1. Оружие" << std::endl;
    std::cout << "2. Словарь логинов (из файла students.txt)" << std::endl;
    std::cout << "Выбор: ";
    std::cin >> mainChoice;
    std::cin.ignore();

    if (mainChoice == 1) {
        int choice;
        std::cout << "\nВЫБЕРИТЕ ОРУЖИЕ" << std::endl;
        std::cout << "1. Пистолет" << std::endl;
        std::cout << "2. Автомат" << std::endl;
        std::cout << "Выбор: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            int pistolAmmo;
            std::cout << "Количество патронов в пистолете: ";
            std::cin >> pistolAmmo;
            Pistol pistol(pistolAmmo);

            std::cout << "\nПИСТОЛЕТ (" << pistol.getAmmo() << " патронов) ===" << std::endl;
            int shots;
            std::cout << "Сколько раз стрелять? ";
            std::cin >> shots;
            std::cin.ignore();

            for (int i = 0; i < shots; i++) {
                pistol.shoot();
            }
        }
        else if (choice == 2) {
            int autoType;
            std::cout << "\nТип автомата:" << std::endl;
            std::cout << "1. По умолчанию (30/30)" << std::endl;
            std::cout << "2. Укажите вместимость" << std::endl;
            std::cout << "3. Укажите вместимость и скорострельность" << std::endl;
            std::cout << "Выбор: ";
            std::cin >> autoType;
            std::cin.ignore();

            Automatic autoGun;
            if (autoType == 2) {
                int capacity;
                std::cout << "Вместимость обоймы: ";
                std::cin >> capacity;
                autoGun = Automatic(capacity);
            }
            else if (autoType == 3) {
                int capacity, fireRate;
                std::cout << "Вместимость обоймы: ";
                std::cin >> capacity;
                std::cout << "Скорострельность: ";
                std::cin >> fireRate;
                autoGun = Automatic(capacity, fireRate);
            }

            std::cout << "\nАВТОМАТ (" << autoGun.getAmmo() << " патронов, "
                << autoGun.getRateOfFire() << " выстр/сек) ===" << std::endl;

            int action;
            std::cout << "Что делать?" << std::endl;
            std::cout << "1. Одна серия выстрелов" << std::endl;
            std::cout << "2. Стрельба N секунд" << std::endl;
            std::cout << "Выбор: ";
            std::cin >> action;
            std::cin.ignore();

            if (action == 1) {
                autoGun.shoot();
            }
            else {
                int seconds;
                std::cout << "Сколько секунд стрелять? ";
                std::cin >> seconds;
                autoGun.shootForSeconds(seconds);
            }
        }
    }
    else if (mainChoice == 2) {
        std::ifstream input("students.txt");
        if (!input.is_open()) {
            std::cerr << "Не удалось открыть файл students.txt" << std::endl;
            return 1;
        }

        int n;
        input >> n;
        if (n < 0 || n > 100) {
            std::cerr << "Ошибка: число учеников должно быть от 0 до 100" << std::endl;
            return 1;
        }

        Dictionary<std::string, int> surnameCount;

        std::cout << "ФИО и логины:" << std::endl;
        for (int i = 0; i < n; ++i) {
            std::string surname, name;
            input >> surname >> name;

            if (surname.size() > 20) {
                std::cerr << "Ошибка: фамилия \"" << surname
                    << "\" длиннее 20 символов" << std::endl;
                return 1;
            }
            if (name.size() > 15) {
                std::cerr << "Ошибка: имя \"" << name
                    << "\" длиннее 15 символов" << std::endl;
                return 1;
            }

            int count = surnameCount.get(surname);
            std::string login = (count == 0)
                ? surname
                : surname + std::to_string(count + 1);

            surnameCount.insert(surname, count + 1);

            // тут видны и ФИО, и логин
            std::cout << surname << " " << name << " -> " << login << std::endl;
        }

        input.close();

        int choice = 0;
        while (true) {
            std::cout << "\n1. Добавить новый логин" << std::endl;
            std::cout << "2. Удалить логин" << std::endl;
            std::cout << "3. Показать все логины (фамилия + счётчик)" << std::endl;
            std::cout << "4. Сохранить словарь и выйти" << std::endl;
            std::cout << "Выберите действие (1-4): ";
            std::cin >> choice;
            std::cin.ignore();

            if (choice == 1) {
                std::cout << "\nДОБАВЛЕНИЕ ЛОГИНА" << std::endl;
                std::cout << "Введите фамилию (ключ): ";
                std::string surname;
                std::getline(std::cin, surname);

                std::cout << "Введите счетчик (значение): ";
                int counter;
                std::cin >> counter;
                std::cin.ignore();

                surnameCount.insert(surname, counter);
                std::cout << "Логин добавлен!" << std::endl;
            }
            else if (choice == 2) {
                std::cout << "\nУДАЛЕНИЕ ЛОГИНА" << std::endl;
                std::cout << "Введите фамилию для удаления: ";
                std::string surname;
                std::getline(std::cin, surname);

                if (surnameCount.remove(surname)) {
                    std::cout << "Логин удален!" << std::endl;
                }
                else {
                    std::cout << "Логин не найден!" << std::endl;
                }
            }
            else if (choice == 3) {
                surnameCount.printAll();
            }
            else if (choice == 4) {
                surnameCount.saveToFile("students_out.txt");
                std::cout << "Словарь сохранен в students_out.txt. До свидания!" << std::endl;
                break;
            }
            else {
                std::cout << "Неверный выбор!" << std::endl;
            }
        }
    }

    return EXIT_SUCCESS;
}
