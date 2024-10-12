from app.search import *

def str_to_key(str):
    out = ""
    for el in str:
        if el in "1234567890":
            out += el
        else:
            out += "%d" % ord(el)
    return int(out)

class Doctor:
    def __init__(self, name, post, number_cabinet, schedule):
        self.name = name                                    # ФИО доктора(строка)
        self.post = post                                    # должность(строка)
        self.number_cabinet = number_cabinet                # номер кабинета(целое)
        self.schedule = schedule                            # График приема(строка)
        self.name_key = str_to_key(name)

    def print(self):
        print("ФИО:%s\nДолжность:%s\nНомер кабинета:%s\nГрафик приёма:%s" % (self.name, self.post, self.number_cabinet, self.schedule))

class AVLTree:
    def __init__(self):
        self.root = None
        self.client = None
        self.left = None
        self.right = None
        self.height = 1

    def clear(self):
        self.root = None
        self.client = None
        self.left = None
        self.right = None

    def insert(self, node, client):
        if node == None:
            node = AVLTree()
            node.client = None

        if node.client == None:
            node.client = client
            return node

        elif client.name_key < node.client.name_key:
            node.left = self.insert(node.left, client)

        else:
            node.right = self.insert(node.right, client)

        node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))

        balance = self.get_balance(node)

        if balance > 1 and client.name_key < node.left.client.name_key:
            return self.right_rotate(node)

        if balance < -1 and client.name_key > node.right.client.name_key:
            return self.left_rotate(node)

        if balance > 1 and client.name_key > node.left.client.name_key:
            node.left = self.left_rotate(node.left)
            return self.right_rotate(node)

        if balance < -1 and client.name_key < node.right.client.name_key:
            node.right = self.right_rotate(node.right)
            return self.left_rotate(node)

        return node

    def left_rotate(self, node):
        right = node.right
        left = right.left

        right.left = node
        node.right = left

        node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))
        right.height = 1 + max(self.get_height(right.left), self.get_height(right.right))

        return right

    def right_rotate(self, node):
        left = node.left
        right = left.right

        left.right = node
        node.left = right

        node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))
        left.height = 1 + max(self.get_height(left.left), self.get_height(left.right))

        return left

    def get_height(self, node):
        if node is None:
            return 0

        return node.height

    def get_balance(self, node):
        if node is None:
            return 0

        return self.get_height(node.left) - self.get_height(node.right)

    def search(self, node, number):
        if node is None:
            return None

        if number == node.client.number:
            return node.client

        if number < node.client.number:
            return self.search(node.left, number)

        return self.search(node.right, number)

    def post_order(self, node):
        if (node):
            self.post_order(node.left)
            self.post_order(node.right)
            print("-" * 20)
            if node.client != None:
                node.client.print()

    def post_order_return(self, node):
        out = []
        if (node):
            out += self.post_order_return(node.left)
            out += self.post_order_return(node.right)
            if node.client != None:
                out.append(node.client)

        return out


################################################################################
    def search_by_number(self, passport, current = None, first = True):
        if (current == None) and first:
            current = self

        if current == None:
            return None

        if current.client.passport == passport:
            return current.client

        a = self.search_by_number(passport,current.left,False)
        b = self.search_by_number(passport,current.right,False)
        if a != None:
            return a
        else:
            return b

    def search_by_name(self, name):
        name_key = str_to_key(name)
        current = self
        while True:
            if current == None:
                return None

            if current.client.name_key == name_key:
                return current.client

            elif name_key < current.client.name_key:
                current = current.left

            else:
                current = current.right

################################################################################
    def search_by_post(self, text, current=None):
        if current == None:
            current = self

        result = []
        if boyerMurSearch(text, current.client.post):
            result.append(current.client)

        if current.left != None:
            result += self.search_by_post(text, current.left)

        if current.right != None:
            result += self.search_by_post(text, current.right)

        return result

    def delete_by_number(self, licence):
        name_key = sum([ord(i) for i in licence])
        current = self
        go_left = False
        postv = None
        while True:
            print(current.client.passport)
            if current == None:
                return False

            if current.client.licence == licence:
                current.client = None
                if postv != None:
                    if go_left:
                        postv.left = None
                    else:
                        postv.right = None

                else:
                    postv = self

                left = current.left
                right = current.right
                if left != None:
                    self.insert(postv, left.client)

                if right != None:
                    self.insert(postv, right.client)

                return True

            else:
                postv = current
                if name_key < current.client.name_key:
                    current = current.left
                    go_left = True

                else:
                    current = current.right
                    go_left = False
