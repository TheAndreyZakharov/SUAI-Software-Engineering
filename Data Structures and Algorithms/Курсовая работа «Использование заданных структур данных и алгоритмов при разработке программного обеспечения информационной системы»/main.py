# Номер студенческого билета:
# Предметная область: 3 Регистрация больных в поликлинике
# Метод хеширования: 0 Открытое хеширование
# Метод сортировки: 3 Шейкерная
# Вид списка: 3 Циклический двунаправленный
# Метод обхода дерева: 1 Обратный
# Алгоритм поиска слова в тексте: 0 Боуера и Мура (БМ)

import datetime

from app.structs.client import *
from app.structs.direction import *
from app.structs.doctors import *
from app.file import *
from app.sort import *
from app.menu import *
from app.search import *

################################################################################

data_file = Data_file("data")

list = None
tree = AVLTree()
hash_table = HashTable()

################################################################################

def read_file():
    global list
    global tree
    global hash_table
    for el in data_file.doctors:
        tree = tree.insert(tree, Doctor(**el))

    for key in data_file.clients:
        for el in data_file.clients[key]:
            hash_table.add(Client(**el))

    for el in data_file.direction:
        obj = Direction(**el)
        if list == None:
            list = Element_list(obj)
        else:
            list.add(obj)

def save_to_file():
    global list
    global tree
    global hash_table
    data_file.clear()
    tree_return = tree.post_order_return(tree)
    for el in tree_return:
        data = {}
        data["name"] = el.name
        data["post"] = el.post
        data["number_cabinet"] = el.number_cabinet
        data["schedule"] = el.schedule
        data_file.doctors.append(data)

    for key in hash_table.hash_dict:
        data_file.clients[key] = []
        for el in hash_table.hash_dict[key]:
            data = {}
            data["number"] = el.number
            data["name"] = el.name
            data["date_of_birth"] = el.date_of_birth
            data["adress"] = el.adress
            data["work"] = el.work
            data_file.clients[key].append(data)

    if list != None:
        out = list.get_all()
        for el in out:
            data = {}
            data["number"] = el.number
            data["name"] = el.name
            data["date"] = el.date
            data["time"] = el.time
            data_file.direction.append(data)

    data_file.save()

read_file()

################################################################################

def print_clients():
    hash_table.print_table()

def add_client():
    global hash_table
    data = {}
    data['number'] = check_format("Регистрационный номер (MM-NNNNNN):", "MM-NNNNNN")
    data['name'] = input("ФИО: ")
    data['date_of_birth'] = input("Дата рождения: ")
    data['adress'] = input("Адрес проживания: ")
    data['work'] = input("Место работы (учёбы): ")
    hash_table.add(Client(**data))

def delete_client():
    global hash_table
    name = input("ФИО: ")
    hash, id, obj = hash_table.find_by_name(name)
    if hash == None:
        print("Больного с таким именем нет.")
        return

    hash_table.remove(hash, id)

    arr = list.search_by_number(obj.number)
    for i in range(len(arr)-1, -1, -1):
        list.delete_element(arr[i])

def clear_clent():
    global hash_table
    hash_table.clear()
    print("Таблица больных очищена.")

def find_client_by_number():
    number = check_format("Регистрационный номер (MM-NNNNNN):", "MM-NNNNNN")
    hash, id, obj = hash_table.find_by_number(number)
    if hash == None:
        print("Больного с таким номером нет.")
        return

    obj.print()

def find_client_by_name():
    name = input("ФИО: ")
    hash, id, obj = hash_table.find_by_name(name)
    if hash == None:
        print("Больного с таким именем нет.")
        return

    obj.print()

################################################################################

def add_doctor():
    global tree
    data = {}
    data['name'] = input("ФИО доктора: ")
    data['post'] = input("Должность: ")
    data['number_cabinet'] = int(input("Номер кабинета: "))
    data['schedule'] = input("График приема: ")
    tree = tree.insert(tree, Doctor(**data))

def delete_doctor():
    global tree
    global list
    name = input("ФИО доктора: ")
    tree_return = tree.post_order_return(tree)
    tree.clear()
    deleted_flag = False
    for el in tree_return:
        if el.name != name:
            tree.insert(tree, el)
        else:
            deleted_flag = True

    if not deleted_flag:
        print("Доктора с таким именем не существует.")

    arr = list.search_by_name(name)
    for i in range(len(arr)-1, -1, -1):
        list.delete_element(arr[i])

def print_doctors():
    global tree
    tree.post_order(tree)

def clear_doctors():
    global tree
    tree.clear()
    print("Дерево с докторами было очищенно.")

def find_doctor_by_name():
    global tree
    name = input("ФИО доктора: ")
    obj = tree.search_by_name(name)
    if obj == None:
        print("Такого доктора нет.")
        return

    obj.print()

def find_doctor_by_post():
    global tree
    post = input("Должность: ")
    obj_list = tree.search_by_post(post)

    for el in obj_list:
        print()
        el.print()

################################################################################

def add_direction():
    global list
    data = {}
    data['number'] = check_format("Регистрационный номер (MM-NNNNNN):", "MM-NNNNNN")
    hash, id, obj = hash_table.find_by_number(data['number'])
    if hash == None:
        print("Больного с таким номером нет.")
        return

    data['name'] = input("ФИО доктора: ")
    obj = tree.search_by_name(data['name'])
    if obj == None:
        print("Такого доктора нет.")
        return

    data['date'] = input("Дата: ")
    data['time'] = input("Время: ")

    obj = Direction(**data)
    if list == None:
        list = Element_list(obj)
    else:
        list.add(obj)

def delete_direction():
    global list
    data = {}
    data['number'] = check_format("Регистрационный номер (MM-NNNNNN):", "MM-NNNNNN")
    hash, id, obj = hash_table.find_by_number(data['number'])
    if hash == None:
        print("Больного с таким номером нет.")
        return

    data['name'] = input("ФИО доктора: ")
    obj = tree.search_by_name(data['name'])
    if obj == None:
        print("Такого доктора нет.")
        return

    data['date'] = input("Дата: ")
    data['time'] = input("Время: ")

    id = list.search_by_name_number_and_datetime(**data)
    if id == None:
        print("Такого направления нет.")
        return

    list.delete_element(id)
    print("Направление было удалено.")

def print_direction():
    global list
    if list == None:
        return

    for i in range(list.get_length()):
        print()
        obj = list.get_current_item(i)
        obj.item.print()

################################################################################

menu = Menu([
    ["Выход\n", exit],
    ['[HashTable] Вывести список больных', print_clients],
    ['[HashTable] Добавить больного', add_client],
    ['[HashTable] Удалить больного', delete_client],
    ['[HashTable] Очистить список больных', clear_clent],
    ['[HashTable] Поиск больного по регистрационному номеру', find_client_by_number],
    ['[HashTable] Поиск больного по его ФИО\n', find_client_by_name],
    ['[AVLTree] Добавить врача', add_doctor],
    ['[AVLTree] Удалить врача', delete_doctor],
    ['[AVLTree] Вывести список врачей', print_doctors],
    ['[AVLTree] Очистить список врачей', clear_doctors],
    ['[AVLTree] Поиск врача по ФИО', find_doctor_by_name],
    ['[AVLTree] Поиск врача по должности\n', find_doctor_by_post],
    ['[list] Регистрация направления', add_direction],
    ['[list] Возврат направления', delete_direction],
    ['[list] Вывести списко направлений', print_direction]
], save_to_file)

menu.run()
