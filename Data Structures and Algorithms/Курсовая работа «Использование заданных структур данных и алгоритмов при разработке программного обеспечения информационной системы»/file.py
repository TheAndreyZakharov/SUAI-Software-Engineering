
import os
import json

def save_dict(dict, name):
    json.dump(dict, open(str(name) + '.json','w',encoding='utf-8'), indent=2, ensure_ascii=False)

def read_dict(name):
    with open(str(name) + '.json', encoding='utf-8') as fh:
        data = json.load(fh)
    return data

class Data_file:
    def __init__(self, file_name="data"):
        self.file_name = file_name

        self.clients = {}
        self.direction = []
        self.doctors = []

        self.read()

    def clear(self):
        self.clients = {}
        self.direction = []
        self.doctors = []

    def save(self):
        data = {
            "clients": self.clients,
            "direction": self.direction,
            "doctors": self.doctors
        }
        save_dict(data, self.file_name)

    def read(self):
        if not os.path.exists(self.file_name + '.json'):
            self.save()
            self.read()
            return

        data = read_dict(self.file_name)

        self.clients = data["clients"]
        self.direction = data["direction"]
        self.doctors = data["doctors"]

    def get_all(self):
        return self.clients, self.direction, self.doctors
