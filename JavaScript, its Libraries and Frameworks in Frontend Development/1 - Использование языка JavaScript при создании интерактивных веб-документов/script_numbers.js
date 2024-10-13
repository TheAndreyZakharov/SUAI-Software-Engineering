// Генерируем случайное число от 1 до 10 при загрузке страницы
let secretNumber = Math.floor(Math.random() * 10) + 1;

// Функция для проверки угаданного числа
function checkNumber() {
    let userGuess = document.getElementById("guess").value;
    userGuess = parseInt(userGuess);

    if (userGuess === secretNumber) {
        document.getElementById("feedback").innerText = "Поздравляем! Вы угадали число.";
    } else if (userGuess > secretNumber) {
        document.getElementById("feedback").innerText = "Слишком большое число. Попробуйте еще раз!";
    } else {
        document.getElementById("feedback").innerText = "Слишком маленькое число. Попробуйте еще раз!";
    }
}

// Сброс игры при перезагрузке страницы
window.addEventListener('beforeunload', function (e) {
    sessionStorage.removeItem("secretNumber");
});
