import sys
from sys import platform
import os

def clear_screen():
    if platform == "linux" or platform == "linux2":
        os.system("clear")
    elif platform == "darwin":
        os.system("clear")
    elif platform == "win32":
        os.system("cls")

def check_format(promt, template):
    while True:
        str = input(promt)
        if len(str) != len(template):
            print("Неправильный формат")
            continue

        for i in range(len(str)):
            if template[i] in ["N", "M"] and not str[i].isdigit():
                break
            if template[i] == "-" and not (str[i] == "-"):
                break
        else:
            break
        print("Неправильный формат")
    return str

def read_bool(promt=""):
    while True:
        read = input(promt + " (y/n): ")
        if read in ["y", "Y", "n", "N", "д", "Д", "н", "Н"]:
            return (read in ["y", "Y", "д", "Д"])

class Menu:
    def __init__(self, elements, function=None):
        self.elements = elements
        self.function = function

    def run(self):
        clear_screen()
        while True:
            print("-" * 30)
            for i in range(len(self.elements)):
                print("%2d) %s" % (i, self.elements[i][0]))

            # try:
            menu_input = int(input("\n >> "))
            clear_screen()
            self.elements[menu_input][1]()
            if self.function != None:
                self.function()
