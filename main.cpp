// Подключения всех нужных библиотек
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <iostream>

namespace py = pybind11;  // Упрощение обращения к пространству имен pybind11

// Структура для хранения координат
struct Coordinates {
    double longitude;  // Долгота
    double latitude;   // Широта
};

// Класс, представляющий дорожный знак
class Sign {
public:
    std::string name;           // Имя знака
    unsigned int id;            // Уникальный идентификатор знака
    Coordinates coordinates;     // Координаты знака

    Sign() : name(""), id(0), coordinates{0.0, 0.0} {}

    Sign(const std::string& name, unsigned int id, double longitude, double latitude) 
        : name(name), id(id), coordinates{longitude, latitude} {}

    std::string get_name() const {
        return name;
    }

    unsigned int get_id() const {
        return id;
    }

    Coordinates get_coordinates() const {
        return coordinates;
    }

};

// Класс для управления базой данных знаков
class SignDatabase {
private:
    std::unordered_map<unsigned int, Sign> signs;  // Хранилище знаков, где ключ - идентификатор знака

public:
    // Метод для добавления нового знака в базу данных
    void add_sign(const Sign& sign) {
        if (signs.find(sign.id) != signs.end()) {
            throw std::runtime_error("Sign with this ID: " + std::to_string(sign.id) + " already exists.");
        }
        signs[sign.id] = sign;
    }

    // Метод для удаления знака по его идентификатору
    void remove_sign(unsigned int id) {
        auto it = signs.find(id);
        if (it != signs.end()) { 
            signs.erase(it);
            std::cerr << "Sign with ID: " << id << " is removed." << std::endl;
        } else {
            std::cerr << "Warning: Sign with ID: " << id << " does not exist." << std::endl;
        }
    }

    // Метод для поиска знака по его идентификатору и возврата его данных
    Sign find_sign(unsigned int id) {
        auto it = signs.find(id);
        if (it != signs.end()) {
            return it->second;
        }
        throw std::runtime_error("Sign with this ID: " + std::to_string(id) + " not found.");
    }

    // Метод для добавления нескольких знаков в базу данных
    void add_signs(const std::vector<Sign>& new_signs) {
        for (const auto& sign : new_signs) {
            try {
                add_sign(sign);  // Пытаемся добавить знак
            } catch (const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;  // Выводим сообщение об ошибке, но продолжаем
            }
        }
    }

    // Метод для вывода всех знаков в базе данных
    void print_all_signs() const {
        if (signs.empty()) {
            std::cout << "No signs in the database." << std::endl;
            return;
        }

        std::cout << "Signs in the database:" << std::endl;
        for (const auto& pair : signs) {
            const Sign& sign = pair.second;
            std::cout << "ID: " << sign.id 
                      << ", Name: " << sign.name 
                      << ", Coordinates: (" << sign.coordinates.longitude 
                      << ", " << sign.coordinates.latitude << ")" 
                      << std::endl;
        }
    }
};

// Определение модуля Python с использованием pybind11
PYBIND11_MODULE(module_name, m) {
    py::class_<Coordinates>(m, "Coordinates")  // Объявление класса Coordinates в Python
        .def(py::init<double, double>())       // Конструктор с параметрами долготы и широты
        .def_readwrite("longitude", &Coordinates::longitude)  // Доступ к полю долготы из Python
        .def_readwrite("latitude", &Coordinates::latitude);   // Доступ к полю широты из Python

    py::class_<Sign>(m, "Sign")                // Объявление класса Sign в Python
        .def(py::init<const std::string&, unsigned int, double, double>())  // Конструктор с параметрами
        .def_readwrite("name", &Sign::name)                    // Доступ к полю имени из Python
        .def_readwrite("id", &Sign::id)                        // Доступ к полю ID из Python
        .def_readwrite("coordinates", &Sign::coordinates)     // Доступ к полю координат из Python
        .def("get_name", &Sign::get_name)                    // Геттер для имени знака
        .def("get_id", &Sign::get_id)                        // Геттер для ID знака
        .def("get_coordinates", &Sign::get_coordinates);      // Геттер для координат знака


    py::class_<SignDatabase>(m, "SignDatabase")  // Объявление класса SignDatabase в Python
        .def(py::init<>())                          // Конструктор по умолчанию для базы данных знаков
        .def("add_sign", &SignDatabase::add_sign)   // Метод добавления знака в базу данных
        .def("remove_sign", &SignDatabase::remove_sign)  // Метод удаления знака из базы данных
        .def("find_sign", &SignDatabase::find_sign)      // Метод поиска знака по ID в базе данных
        .def("add_signs", &SignDatabase::add_signs)     // Метод добавления нескольких знаков в базу данных
        .def("print_all_signs", &SignDatabase::print_all_signs);  // Метод вывода всех знаков в базе данных
}
