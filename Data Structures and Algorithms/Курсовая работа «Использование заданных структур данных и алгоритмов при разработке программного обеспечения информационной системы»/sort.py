# Сортировка извлечени
def shaker_sort(array):
    length = len(array)
    swapped = True
    start_index = 0
    end_index = length - 1

    while (swapped == True):

        swapped = False

        # проход слева направо
        for i in range(start_index, end_index):
            arr_buf = sum([ord(i) for i in array[i].name])
            arr_buf2 = sum([ord(i) for i in array[i + 1].name])
            if (arr_buf > arr_buf2) :
                # обмен элементов
                array[i], array[i + 1] = array[i + 1], array[i]
                swapped = True

        # если не было обменов прерываем цикл
        if (not(swapped)):
            break

        swapped = False

        end_index = end_index - 1

        #проход справа налево
        for i in range(end_index - 1, start_index - 1, -1):
            arr_buf = sum([ord(i) for i in array[i].name])
            arr_buf2 = sum([ord(i) for i in array[i + 1].name])
            if (arr_buf > arr_buf2):
                # обмен элементов
                array[i], array[i + 1] = array[i + 1], array[i]
                swapped = True

        start_index = start_index + 1

    return array
