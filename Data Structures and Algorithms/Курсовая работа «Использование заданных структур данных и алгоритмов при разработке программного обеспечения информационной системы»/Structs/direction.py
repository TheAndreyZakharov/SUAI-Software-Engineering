
class Direction:
    def __init__(self, number, name, date, time):
        self.number = number
        self.name = name
        self.date = date
        self.time = time

    def print(self):
        print("Регистрационный номер: %s\nФИО: %s\nДата направления: %s\nВремя направления: %s" % (self.number, self.name, self.date, self.time))

class Element_list:
    def __init__(self, item, head=None):
        self.item = item

        self.next = None
        self.previous = None
        self.head = (self if (head == None) else head)
        self.tail = None

    def add(self, item):
        next = self.head
        while (next.next != None):
            next = next.next

        next.next = Element_list(item, self.head)
        next.next.previous = next.next

        self.head.tail = next.next
        next.next.head = self.head
        return next.next

    def get_item(self):
        return self.item

    def get_head(self):
        return self.head

    def get_all(self):
        result = []
        head = self.head
        while (head != None):
            result.append(head.item)
            head = head.next

        return result

    def get_current_item(self, id):
        head = self.head
        for _ in range(id):
            head = head.next

        return head

    def delete_element(self, id):
        if (id < 0 or id > (self.get_length() - 1)):
            return False

        if id == 0:
            self.head = self.head.next
            return True

        elem_curr = self.head
        elem_prev = None
        elem_next = None
        for i in range(id):
            elem_prev = elem_curr
            elem_curr = elem_curr.next
            elem_next = elem_curr.next

        elem_prev.next = elem_next
        # elem_next.previous = elem_prev

        return True

    def get_length(self):
        head = self.head
        count = 0
        while (head != None):
            head = head.next
            count += 1

        return count

################################################################################

    def search_by_name(self, name):
        head = self.head
        count = 0
        out = []
        while (head != None):
            if (head.item.name == name):
                out.append(count)

            head = head.next
            count += 1

        return out

    def search_by_number(self, number):
        head = self.head
        count = 0
        out = []
        while (head != None):
            if (head.item.number == number):
                out.append(count)

            head = head.next
            count += 1

        return out

    def search_by_name_number_and_datetime(self, number, name, date, time):
        head = self.head
        count = 0
        while (head != None):
            if (head.item.name == name) and (head.item.number == number) and (head.item.date == date) and (head.item.time == time):
                return count

            head = head.next
            count += 1

        return None
