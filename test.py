#!/usr/bin/env python3

import module_name as sign_database

# Создание базы данных знаков
db = sign_database.SignDatabase()

# Создание знаков
sign1 = sign_database.Sign("X", 1, 30.0, 50.0)
sign2 = sign_database.Sign("Y", 2, 30.1, 50.1)
sign3 = sign_database.Sign("Z", 3, 30.2, 50.2)

print(sign1.get_name())
print(sign1.get_id())
print(sign1.get_coordinates().longitude, sign1.get_coordinates().latitude)

# Добавление знаков
db.add_sign(sign1)
db.add_sign(sign2)
db.add_sign(sign3)

# Добавления существующего знака
try:
    db.add_sign(sign1)
except RuntimeError as e:
    print(e)  # Вывод ошибки о том, что нельзя добавлять один и тот-же знак

print('\n', "========================================================================================================================================================", '\n')

# Поиск знака
found_sign = db.find_sign(1)
print(f"Found sign: {found_sign.name}, ID: {found_sign.id}, Coordinates: ({found_sign.coordinates.longitude}, {found_sign.coordinates.latitude})")

try:
    db.find_sign(5)
except RuntimeError as e:
    print(e)  # Вывод ошибки о том, что такого знака нет

print('\n', "========================================================================================================================================================", '\n')

# Удаление знака
db.remove_sign(1)

# Попытка найти удаленный знак
try:
    db.find_sign(1)
except RuntimeError as e:
    print(e)  # Вывод ошибки о том, что знак не найден

print('\n', "========================================================================================================================================================", '\n')

# Добавления нескольких знаков

sign4 = sign_database.Sign("A", 4, 30.4, 50.4)
sign5 = sign_database.Sign("B", 5, 30.5, 50.5)
sign6 = sign_database.Sign("C", 6, 30.6, 50.6)
sign7 = sign_database.Sign("D", 7, 30.7, 50.7)
sign8 = sign_database.Sign("E", 8, 30.8, 50.8)
sign9 = sign_database.Sign("F", 9, 30.9, 50.9)
sign10 = sign_database.Sign("G", 10, 31.0, 51.0)
signA = sign_database.Sign("GG", 3, 5.0, 6.0)

try:
    db.add_signs([signA, sign4, sign5, sign6, sign7, sign8, sign9, sign10])
except RuntimeError as e:
    print(e)  # Вывод ошибки о том, что нельзя добавлять один и тот-же знак

db.print_all_signs()
