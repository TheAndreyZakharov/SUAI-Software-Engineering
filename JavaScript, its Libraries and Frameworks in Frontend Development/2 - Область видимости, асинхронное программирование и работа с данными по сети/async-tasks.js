// Задание 1: Функция filterArray
function filterArray(array, callback) {
    const result = [];
    for (let i = 0; i < array.length; i++) {
        if (callback(array[i])) {
            result.push(array[i]);
        }
    }
    return result;
}

function isEven(number) {
    return number % 2 === 0;
}

function isOdd(number) {
    return number % 2 !== 0;
}

// Использование filterArray
const numbers = [1, 2, 3, 4, 5, 6];
const evenNumbers = filterArray(numbers, isEven);
console.log('Четные числа:', evenNumbers);

const oddNumbers = filterArray(numbers, isOdd);
console.log('Нечетные числа:', oddNumbers);

// Задание 2: Асинхронная функция fetchData
function fetchData(url) {
    return new Promise((resolve, reject) => {
        fetch(url)
            .then(response => {
                if (response.ok) {
                    return response.text();
                } else {
                    throw new Error('Ошибка запроса: ' + response.status);
                }
            })
            .then(data => resolve(data))
            .catch(error => reject(error));
    });
}

// Использование открытого тестового API для получения данных
fetchData('https://jsonplaceholder.typicode.com/posts/1')
    .then(data => console.log('Данные:', data))
    .catch(error => console.error('Ошибка:', error));
