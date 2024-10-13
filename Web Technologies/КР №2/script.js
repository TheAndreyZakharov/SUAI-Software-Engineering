
function getRandomColor() {
    var letters = '0123456789ABCDEF';
    var color = '#';
    for (var i = 0; i < 6; i++) {
        color += letters[Math.floor(Math.random() * 16)];
    }
    return color;
}

document.querySelectorAll('li').forEach(item => {
    item.addEventListener('click', function() {
        var nextItem = this.nextElementSibling;
        if (nextItem) { // Проверяем, есть ли следующий элемент
            nextItem.style.color = getRandomColor(); // Изменяем цвет текста следующего элемента на случайный цвет
        }
    });
});
