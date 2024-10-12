
import random

class Client:
    def __init__(self, number, name, date_of_birth, adress, work):
        self.number = number                                # Регистрационный номер (строка MM-NNNNNN)
        self.name = name                                    # ФИО(строка)
        self.date_of_birth = date_of_birth                  # дата рождения(строка)
        self.adress = adress                                # адрес(целое)
        self.work = work                                    # место работы(строка)

    def print(self):
        print("Регистрационный номер: %s\nФИО:%s\nДата рождения:%s\nАдрес:%s\nМесто работы:%s" % (self.number, self.name, self.date_of_birth, self.adress, self.work))

class HashTable:
    def __init__(self,  count_sigments=2000):
        self.count_sigments = count_sigments
        self.hash_dict = {}

    def generate_hash(self, key):
        out = 1
        for el in key:
            out += ord(el) ** 2

        return int(out % self.count_sigments)

    def add(self, client):
        hash = self.generate_hash(client.number)
        while True:
            if hash in self.hash_dict:
                self.hash_dict[hash].append(client)

            else:
                self.hash_dict[hash] = [client]
                break

    def get_by_hash(self, hash):
        return self.hash_dict[hash]

    def remove(self, hash, id):
        return self.hash_dict[hash].pop(id)

    def get_by_hash(self, hash):
        return self.hash_dict[hash]

    def clear_table(self):
        self.hash_dict = {}

    def print_table(self):
        for hash in self.hash_dict:
            # print("%d\t" % el, end="")
            for el in self.hash_dict[hash]:
                print("-" * 20)
                el.print()

################################################################################

    def find_by_name(self, name):
        for hash in self.hash_dict:
            for i, el in enumerate(self.hash_dict[hash]):
                if el.name == name:
                    return hash, i, el

        return None, None, None

    def find_by_number(self, number):
        for hash in self.hash_dict:
            for i, el in enumerate(self.hash_dict[hash]):
                if el.number == number:
                    return hash, i, el

        return None, None, None
