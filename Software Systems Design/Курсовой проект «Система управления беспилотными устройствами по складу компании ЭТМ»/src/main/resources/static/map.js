document.addEventListener('DOMContentLoaded', function () {
    initializeMap();
    createZoneLabels(document.getElementById('warehouse-map'));
});
function toggleSection(element) {
    var section = element.parentElement;
    section.classList.toggle('open');
}

function initializeMap() {
    const map = document.getElementById('warehouse-map');
    createZones(map);
    createShelves(map);
    createChargingZone(map);
    createUnloadingZone(map);
    createOfficeZone(map);
    createZoneLabels(map); // Вызываем сразу после инициализации всех зон
}

function createZones(map) {
    const zones = [
        { id: 'red-zone', className: 'red-zone', left: '8%', top: '20%', width: '28%', height: '70%' },
        { id: 'green-zone', className: 'green-zone', left: '36%', top: '20%', width: '28%', height: '70%' },
        { id: 'blue-zone', className: 'blue-zone', left: '64%', top: '20%', width: '28%', height: '70%' }
    ];

    zones.forEach(zone => {
        const zoneDiv = document.createElement('div');
        zoneDiv.id = zone.id;
        zoneDiv.className = 'zone ' + zone.className;
        Object.assign(zoneDiv.style, { left: zone.left, top: zone.top, width: zone.width, height: zone.height });
        map.appendChild(zoneDiv);
    });
}


function createShelves(map) {
    // Определяем количество стеллажей в каждой зоне
    const shelvesCount = {
        'red': 3,
        'green': 8,
        'blue': 8
    };

    // Создание стеллажей для каждой зоны
    ['red', 'green', 'blue'].forEach((zoneColor, index) => {
        const zone = map.querySelector(`.${zoneColor}-zone`);
        const zoneWidth = parseFloat(zone.style.width);
        const zoneHeight = parseFloat(zone.style.height);
        const zoneTop = parseFloat(zone.style.top);
        const zoneLeft = parseFloat(zone.style.left);
        const shelfWidth = 5; // Ширина стеллажа в процентах от ширины зоны
        const shelvesPerColumn = shelvesCount[zoneColor]; // Количество стеллажей в каждой зоне
        const shelfHeight = zoneHeight / shelvesPerColumn; // Высота одного стеллажа
        let shelfNumber = index * 100; // Начальный номер стеллажа для каждой зоны

        // Позиции стеллажей в процентах от левого края зоны
        const shelfPositions = [
            zoneLeft, // Левый край
            zoneLeft + (zoneWidth - shelfWidth) / 2, // Центр
            zoneLeft + zoneWidth - shelfWidth // Правый край
        ];

        shelfPositions.forEach(shelfLeft => {
            for (let column = 0; column < shelvesPerColumn; column++) {
                const shelf = document.createElement('div');
                shelf.className = 'shelf';
                shelf.id = `${zoneColor.charAt(0)}${String(++shelfNumber).padStart(3, '0')}`;
                shelf.innerText = shelf.id.toUpperCase();
                Object.assign(shelf.style, {
                    left: `${shelfLeft}%`,
                    top: `${zoneTop + column * shelfHeight}%`,
                    width: `${shelfWidth}%`,
                    height: `${shelfHeight}%`,
                    position: 'absolute',
                    backgroundColor: 'rgba(139, 69, 19, 0.5)', // Полупрозрачный коричневый цвет
                    color: 'white',
                    display: 'flex',
                    alignItems: 'center',
                    justifyContent: 'center'
                });
                map.appendChild(shelf);
            }
        });
    });
}







function createUnloadingZone(map) {
    const unloadingZone = document.createElement('div');
    unloadingZone.className = 'unloading-zone';
    Object.assign(unloadingZone.style, {
        left: '0',      // Слева от карты
        top: '0',       // Вверху карты
        width: '30%',   // Ширина зоны
        height: '10%'   // Высота зоны
    });
    map.appendChild(unloadingZone);
}

function createChargingZone(map) {
    const chargingZone = document.createElement('div');
    chargingZone.className = 'charging-zone';
    Object.assign(chargingZone.style, {
        left: '30%',    // После зоны разгрузки, исходя из её ширины
        top: '0',       // Та же высота, что и у зоны выгрузки
        width: '30%',   // Ширина зоны
        height: '10%'   // Высота зоны
    });
    map.appendChild(chargingZone);
}

function createOfficeZone(map) {
    const officeZone = document.createElement('div');
    officeZone.className = 'office-zone';
    Object.assign(officeZone.style, {
        left: '60%',    // Сразу за зоной зарядки
        top: '0',       // Вверху карты
        width: '40%',   // Оставшаяся ширина карты
        height: '10%'   // Та же высота, что и у зоны зарядки
    });
    map.appendChild(officeZone);
}




function createZoneLabels(map) {
    // Создаем метки для каждой зоны
    createZoneLabel(map, 'unloading-zone-label', 'Зона разгрузки', '0', '5%');
    createZoneLabel(map, 'charging-zone-label', 'Зона зарядки', '30%', '5%');
    createZoneLabel(map, 'red-zone-label', 'Зона крупногабаритных грузов', '8%', '15%');
    createZoneLabel(map, 'green-zone-label', 'Зона средних грузов', '36%', '15%');
    createZoneLabel(map, 'blue-zone-label', 'Зона электрических приборов', '64%', '15%');
    createZoneLabel(map, 'office-zone-label', '...', '65%', '5%');
}

function createZoneLabel(map, id, text, left, top) {
    const label = document.createElement('div');
    label.id = id;
    label.className = 'zone-label';
    label.innerText = text;
    Object.assign(label.style, {
        position: 'absolute',
        left: left,
        top: top,
        width: '28%', // Ширина метки соответствует ширине зоны
        textAlign: 'center',
        fontWeight: 'bold',
        color: 'rgba(0,0,0,0.5)' // Полупрозрачный чёрный цвет текста
    });
    map.appendChild(label);
}

document.addEventListener('DOMContentLoaded', function () {
    initializeMap();
    createZoneLabels(document.getElementById('warehouse-map')); // Добавляем метки зон
});












function initializeDrones() {
    const droneList = document.getElementById('drone-list');
    droneList.innerHTML = '';

    for (let i = 0; i < 9; i++) {
        const drone = createDrone(i + 1);
        document.getElementById('warehouse-map').appendChild(drone);

        const listItem = createListItem(i + 1, drone.id);
        droneList.appendChild(listItem);
    }
}

function createDrone(index) {
    const drone = document.createElement('div');
    drone.className = 'drone';
    drone.id = `drone${index}`;
    Object.assign(drone.style, {
        left: `${30 + index * 3}%`,
        top: '5%',
        position: 'absolute'
    });
    return drone;
}

function createListItem(index, droneId) {
    const listItem = document.createElement('li');
    listItem.innerText = `Беспилотный Погрузчик № ${index}`;
    listItem.setAttribute('data-drone-id', droneId);
    listItem.onclick = function() {
        // Сначала удаляем класс 'selected' у предыдущего выбранного элемента
        if (selectedDroneId) {
            const oldSelection = document.querySelector('.drones-list li.selected');
            if (oldSelection) oldSelection.classList.remove('selected');
            const oldSelectedDrone = document.getElementById(selectedDroneId);
            if (oldSelectedDrone) oldSelectedDrone.classList.remove('active');
        }

        // Установка выбранного дрона
        selectedDroneId = this.getAttribute('data-drone-id');
        this.classList.add('selected');
        const newSelectedDrone = document.getElementById(selectedDroneId);
        if (newSelectedDrone) newSelectedDrone.classList.add('active');
    };
    return listItem;
}


let selectedDroneId = null;

function selectDrone(droneId) {
    if (selectedDroneId) {
        const oldSelectedDrone = document.getElementById(selectedDroneId);
        if (oldSelectedDrone) oldSelectedDrone.classList.remove('active');
    }
    if (droneId) {
        const newSelectedDrone = document.getElementById(droneId);
        if (newSelectedDrone) newSelectedDrone.classList.add('active');
    }
    selectedDroneId = droneId;
}

function deselectAllDrones() {
    // Удаление класса 'selected' из всех элементов списка
    const selectedListItems = document.querySelectorAll('.drones-list li.selected');
    selectedListItems.forEach(item => item.classList.remove('selected'));

    // Удаление класса 'active' с активного дрона
    if (selectedDroneId) {
        const activeDrone = document.getElementById(selectedDroneId);
        if (activeDrone) activeDrone.classList.remove('active');
    }

    // Сброс выбранного ID дрона
    selectedDroneId = null;
}







const mapBounds = {
    left: 0, top: 0, right: 100, bottom: 100 // Примерные границы карты в процентах
};

// Границы стеллажей для каждой зоны
const red_shelves = [
    { left: 8, top: 19, right: 11, bottom: 90 },  // Левый стеллаж
    { left: 19, top: 19, right: 24, bottom: 90 }, // Центральный стеллаж
    { left: 30, top: 19, right: 35, bottom: 90 } // Правый стеллаж
];
const green_shelves = [
    { left: 36, top: 19, right: 39, bottom: 90 },
    { left: 47, top: 19, right: 50, bottom: 90 },
    { left: 60, top: 19, right: 69, bottom: 90 }
];
const blue_shelves = [
    { left: 64, top: 19, right: 68, bottom: 90 },
    { left: 74, top: 19, right: 80, bottom: 90 },
    { left: 86, top: 19, right: 92, bottom: 90 }
];

// Объединяем границы стеллажей с основными границами зон
const zoneBounds = {
    'red': { left: 8, top: 19, right: 36, bottom: 90, shelves: red_shelves },
    'green': { left: 36, top: 19, right: 64, bottom: 90, shelves: green_shelves },
    'blue': { left: 64, top: 19, right: 92, bottom: 90, shelves: blue_shelves },
    'charging': { left: 30, top: 0, right: 60, bottom: 10 },
    'unloading': { left: 0, top: 0, right: 30, bottom: 10 },
    'office': { left: 60, top: 0, right: 100, bottom: 10 }
};

function isWithinBounds(x, y, bounds) {
    return x >= bounds.left && x <= bounds.right && y >= bounds.top && y <= bounds.bottom;
}
// Функция для проверки столкновения с полками
function isCollisionWithShelf(droneId, x, y) {
    let zoneKey = '';
    if (droneId.includes('1') || droneId.includes('2') || droneId.includes('3')) zoneKey = 'red';
    else if (droneId.includes('4') || droneId.includes('5') || droneId.includes('6')) zoneKey = 'green';
    else if (droneId.includes('7') || droneId.includes('8') || droneId.includes('9')) zoneKey = 'blue';

    // Проверка столкновения с каждым стеллажом в зоне
    return zoneBounds[zoneKey].shelves.some(shelf =>
        x >= shelf.left && x <= shelf.right && y >= shelf.top && y <= shelf.bottom);
}
function isAllowedToMove(droneId, x, y) {
    // Определяем, к какой зоне принадлежит беспилотник
    let zoneKey = '';
    if (droneId.includes('1') || droneId.includes('2') || droneId.includes('3')) zoneKey = 'red';
    else if (droneId.includes('4') || droneId.includes('5') || droneId.includes('6')) zoneKey = 'green';
    else if (droneId.includes('7') || droneId.includes('8') || droneId.includes('9')) zoneKey = 'blue';

    // Проверка, что беспилотник находится в пределах карты
    if (!isWithinBounds(x, y, mapBounds)) return false;

    // Проверка, что беспилотник не заезжает в зону офисов
    if (isWithinBounds(x, y, zoneBounds['office'])) return false;

    // Проверка на столкновение со стеллажами
    if (isCollisionWithShelf(droneId, x, y)) return false;

    // Проверяем, находится ли беспилотник в пределах своей зоны, зон общего доступа или вне любых специфических зон
    return isWithinBounds(x, y, zoneBounds[zoneKey]) ||
        isWithinBounds(x, y, zoneBounds['charging']) ||
        isWithinBounds(x, y, zoneBounds['unloading']) ||
        (!isWithinBounds(x, y, zoneBounds['red']) &&
            !isWithinBounds(x, y, zoneBounds['green']) &&
            !isWithinBounds(x, y, zoneBounds['blue']));
}




function moveDrone(keyCode) {
    if (!selectedDroneId) return;

    const drone = document.getElementById(selectedDroneId);
    let left = parseFloat(drone.style.left);
    let top = parseFloat(drone.style.top);

    switch (keyCode) {
        case 37: if (isAllowedToMove(selectedDroneId, left - 2, top)) left -= 2; break;
        case 38: if (isAllowedToMove(selectedDroneId, left, top - 2)) top -= 2; break;
        case 39: if (isAllowedToMove(selectedDroneId, left + 2, top)) left += 2; break;
        case 40: if (isAllowedToMove(selectedDroneId, left, top + 2)) top += 2; break;
    }

    drone.style.left = `${left}%`;
    drone.style.top = `${top}%`;

}




document.addEventListener('DOMContentLoaded', function () {
    var sendButton = document.querySelector('.drone-control button');
    sendButton.addEventListener('click', sendDroneToShelf);
    initializeDrones();
});

document.addEventListener('keydown', (event) => {
    moveDrone(event.keyCode);
});

















function getShelfCoordinates(shelfNumber) {
    // Объект с координатами стеллажей
    var shelfCoordinates = {
        "R001": { x: 3, y: 6 },
        "R002": { x: 3, y: 10 },
        "R003": { x: 3, y: 15 },
        "R004": { x: 7, y: 5 },
        "R005": { x: 7, y: 10 },
        "R006": { x: 7, y: 15 },
        "R007": { x: 8, y: 5 },
        "R008": { x: 8, y: 10 },
        "R009": { x: 8, y: 15 },
        "G102": { x: 12, y: 6 },
        "G103": { x: 12, y: 8 },
        "G104": { x: 12, y: 10 },
        "G105": { x: 12, y: 12 },
        "G106": { x: 12, y: 13 },
        "G107": { x: 12, y: 15 },
        "G108": { x: 12, y: 17 },
        "G109": { x: 15, y: 4 },
        "G110": { x: 15, y: 6 },
        "G111": { x: 15, y: 8 },
        "G112": { x: 15, y: 10 },
        "G113": { x: 15, y: 12 },
        "G114": { x: 15, y: 13 },
        "G115": { x: 15, y: 15 },
        "G116": { x: 15, y: 17 },
        "G117": { x: 18, y: 4 },
        "G118": { x: 18, y: 6 },
        "G119": { x: 18, y: 8 },
        "G120": { x: 18, y: 10 },
        "G121": { x: 18, y: 12 },
        "G122": { x: 18, y: 13 },
        "G123": { x: 18, y: 15 },
        "G124": { x: 18, y: 17 },
        "B201": { x: 20, y: 4 },
        "B202": { x: 20, y: 6 },
        "B203": { x: 20, y: 8 },
        "B204": { x: 20, y: 10 },
        "B205": { x: 20, y: 12 },
        "B206": { x: 20, y: 13 },
        "B207": { x: 20, y: 15 },
        "B208": { x: 20, y: 17 },
        "B209": { x: 23, y: 4 },
        "B210": { x: 23, y: 6 },
        "B211": { x: 23, y: 8 },
        "B212": { x: 23, y: 10 },
        "B213": { x: 23, y: 12 },
        "B214": { x: 23, y: 13 },
        "B215": { x: 23, y: 15 },
        "B216": { x: 23, y: 17 },
        "B217": { x: 26, y: 4 },
        "B218": { x: 26, y: 6 },
        "B219": { x: 26, y: 8 },
        "B220": { x: 26, y: 10 },
        "B221": { x: 26, y: 12 },
        "B222": { x: 26, y: 13 },
        "B223": { x: 26, y: 15 },
        "B224": { x: 26, y: 17 },

    };

    // Возвращаем координаты стеллажа, если номер существует в объекте
    if (shelfCoordinates[shelfNumber]) {
        return shelfCoordinates[shelfNumber];
    } else {
        // Если стеллаж не найден, можно вернуть null или бросить ошибку
        return null; // или throw new Error("Стеллаж не найден.");
    }
}


function getDroneCoordinates(droneId) {
    const drone = document.getElementById(droneId);
    if (!drone) {
        console.error(`Дрон с ID '${droneId}' не найден.`);
        return null;
    }

    const mapWidth = document.getElementById('warehouse-map').clientWidth;
    const mapHeight = document.getElementById('warehouse-map').clientHeight;

    const left = parseFloat(drone.style.left) / 100 * mapWidth;
    const top = parseFloat(drone.style.top) / 100 * mapHeight;

    const x = Math.floor(left / (mapWidth / 30));
    const y = Math.floor(top / (mapHeight / 20));

    console.log(`Координаты для ${droneId}: x=${x}, y=${y}`); // Вывод координат в консоль
    return { x, y };
}




let droneStatus = {
    drone1: { busy: false, zone: 'R' },
    drone2: { busy: false, zone: 'R' },
    drone3: { busy: false, zone: 'R' },
    drone4: { busy: false, zone: 'G' },
    drone5: { busy: false, zone: 'G' },
    drone6: { busy: false, zone: 'G' },
    drone7: { busy: false, zone: 'B' },
    drone8: { busy: false, zone: 'B' },
    drone9: { busy: false, zone: 'B' }
};






function selectDroneForShelf(shelfNumber) {
    let zone = shelfNumber.charAt(0);
    let availableDrones = Object.keys(droneStatus).filter(droneId => droneStatus[droneId].zone === zone && !droneStatus[droneId].busy);

    if (availableDrones.length > 0) {
        let selectedDrone = availableDrones[0];
        droneStatus[selectedDrone].busy = true;
        return selectedDrone;
    }

    // Если все беспилотники заняты, вернем null или можно реализовать логику ожидания
    return null;
}





function calculateSimplePath(droneCoordinates, targetCoordinates) {
    let path = [];
    let currentX = droneCoordinates.x;
    let currentY = droneCoordinates.y;

    while (currentX !== targetCoordinates.x || currentY !== targetCoordinates.y) {
        if (currentX !== targetCoordinates.x) {
            currentX += (targetCoordinates.x > currentX) ? 1 : -1;
        } else if (currentY !== targetCoordinates.y) {
            currentY += (targetCoordinates.y > currentY) ? 1 : -1;
        }
        path.push([currentX, currentY]);
    }

    return path;
}

function calculatePath(droneId, targetCoordinates) {
    var droneCoordinates = getDroneCoordinates(droneId);
    if (!droneCoordinates) {
        console.error("Не удалось получить координаты для", droneId);
        return null;
    }

    return calculateSimplePath(droneCoordinates, targetCoordinates);
}







let dronesPaused = false;

function stopAllDrones() {
    dronesPaused = true;
    pauseStart = Date.now(); // Запомним время начала паузы

    const drones = document.querySelectorAll('.drone');
    drones.forEach(drone => drone.classList.add('blinking'));
}

function resumeAllDrones() {
    if (dronesPaused) {
        // Вычитаем время паузы из оставшегося времени
        remainingTime -= (Date.now() - pauseStart);
        dronesPaused = false;
    }
    const drones = document.querySelectorAll('.drone');
    drones.forEach(drone => drone.classList.remove('blinking'));
}


function moveDroneAlongPath(droneId, path, shelfName, onComplete) {
    let currentPointIndex = 0;

    function moveNext() {
        if (currentPointIndex < path.length) {
            if (!dronesPaused) {
                let point = path[currentPointIndex];
                let drone = document.getElementById(droneId);
                drone.style.left = (point[0] / 30 * 100) + '%';
                drone.style.top = (point[1] / 20 * 100) + '%';
                currentPointIndex++;
            }
            setTimeout(moveNext, 1000); // Задержка для плавного движения
        } else if (currentPointIndex >= path.length) {
            onComplete(shelfName); // Передаем shelfName в onComplete
        }
    }

    moveNext();
}





function performTaskAfterDelivery(droneId, shelfName) {
    const drone = document.getElementById(droneId);
    drone.style.border = '3px solid green';
    addToLog(droneId, `reached shelf "${shelfName}"`);


    moveToUnloadingZone(droneId, () => {
        drone.style.border = '';
        addToLog(droneId, 'reached unloading zone');
        returnToChargingZone(droneId);
    });

}





function getUnloadingCoordinates(droneId) {
    // Координата X основывается на номере беспилотника
    const x = parseInt(droneId.replace('drone', '')) - 1;
    return { x, y: 0 };
}

function getChargingCoordinates(droneId) {
    // Координата X основывается на номере беспилотника, начиная с 9
    const x = 9 + (parseInt(droneId.replace('drone', '')) - 1);
    return { x, y: 0 };
}

function moveToUnloadingZone(droneId, onComplete) {
    const unloadingCoordinates = getUnloadingCoordinates(droneId);
    const droneCoordinates = getDroneCoordinates(droneId);

    let pathToUnloadingZone = calculateSimplePath(droneCoordinates, unloadingCoordinates);
    moveDroneAlongPath(droneId, pathToUnloadingZone, 'unloading', onComplete);
}

function returnToChargingZone(droneId) {
    const chargingCoordinates = getChargingCoordinates(droneId);
    const droneCoordinates = getDroneCoordinates(droneId);

    let pathToChargingZone = calculateSimplePath(droneCoordinates, chargingCoordinates);
    moveDroneAlongPath(droneId, pathToChargingZone, 'charging', () => {
        droneStatus[droneId].busy = false;
    });
}




let sendingInProgress = false;
function sendDroneToShelf() {
    if (sendingInProgress) {
        return; // Выход, если уже отправляем дрона
    }
    sendingInProgress = true; // Установка флага отправки

    var shelfNumber = document.getElementById('shelf-number').value.toUpperCase();
    var shelfCoordinates = getShelfCoordinates(shelfNumber);

    if (shelfCoordinates) {
        var droneId = selectDroneForShelf(shelfNumber);
        if (droneId) {
            var path = calculatePath(droneId, shelfCoordinates);
            if (path && path.length > 0) {
                moveDroneAlongPath(droneId, path, shelfNumber, (shelfName) => {
                    performTaskAfterDelivery(droneId, shelfName);
                });
            } else {
                console.error("Не удалось найти маршрут к стеллажу", shelfNumber);
            }
        } else {
            console.error("Не удалось найти подходящего беспилотника для стеллажа", shelfNumber);
        }
    } else {
        console.error("Стеллаж с номером", shelfNumber, "не найден.");
    }

    // Сброс флага отправки через 1 секунду
    setTimeout(() => {
        sendingInProgress = false;
    }, 1000);
}








let shelfQueue = [];
let queueInterval;
let remainingTime = 10000; // Начальное время до следующей отправки
let pauseStart;

function handleFileSelect(event) {
    const file = event.target.files[0];
    const reader = new FileReader();

    reader.onload = function(e) {
        const contents = e.target.result;
        // Разбиваем содержимое файла по строкам
        shelfQueue = contents.split('\n').map(line => line.trim()).filter(line => line);
        startSendingDrones();
    };

    reader.readAsText(file);
}

function startSendingDrones() {
    if (queueInterval) clearInterval(queueInterval);

    queueInterval = setInterval(() => {
        if (!dronesPaused && shelfQueue.length > 0) {
            const shelfNumber = shelfQueue.shift();
            document.getElementById('shelf-number').value = shelfNumber;
            sendDroneToShelf();
            remainingTime = 10000; // Сброс таймера
        }

        if (dronesPaused) {
            clearInterval(queueInterval); // Остановка интервала
            queueInterval = setTimeout(startSendingDrones, remainingTime); // Перезапуск с оставшимся временем
        }
    }, remainingTime);
}














































function addToLog(droneId, eventDescription, eventTime = new Date()) {
    const log = document.getElementById('event-log');
    const logEntry = document.createElement('li');
    logEntry.innerText = `${eventTime.toLocaleString('ru-RU')} - UL NO.${droneId.split('drone')[1]} ${eventDescription}`;
    log.prepend(logEntry); // Используем prepend вместо appendChild
}


function createReport() {
    const logs = document.querySelectorAll('#event-log li');
    let earliestDate = null;
    let latestDate = null;
    let totalDeliveries = 0;
    let dronesUsed = new Set();

    logs.forEach(log => {
        const logParts = log.innerText.split(' - ');
        const logDateStr = logParts[0];
        // Преобразуем строку в объект Date
        const logDate = parseLogDate(logDateStr);

        if (logDate) {
            if (!earliestDate || logDate < earliestDate) earliestDate = logDate;
            if (!latestDate || logDate > latestDate) latestDate = logDate;
        }

        if (logParts[1] && logParts[1].includes('reached unloading zone')) totalDeliveries++;

        const droneMatch = logParts[1] ? logParts[1].match(/UL NO.(\d+)/) : null;
        if (droneMatch && droneMatch[1]) dronesUsed.add(droneMatch[1]);
    });

    let reportText = '';
    if (earliestDate && latestDate) {
        reportText += `The report was generated for the period: ${formatDate(earliestDate)} - ${formatDate(latestDate)}\n`;
    }
    reportText += `Delivered goods: ${totalDeliveries}\n`;
    reportText += `Unmanned loaders have been deployed: ${dronesUsed.size}\n\n`;
    reportText += 'Event Logs:\n';
    logs.forEach(log => {
        reportText += log.innerText + '\n';
    });

    const doc = new jsPDF();
    const lines = doc.splitTextToSize(reportText, 180);
    doc.text(lines, 10, 10);
    doc.save('report.pdf');
}

function parseLogDate(dateStr) {
    const dateTimeParts = dateStr.match(/(\d{2}).(\d{2}).(\d{4}), (\d{2}):(\d{2}):(\d{2})/);
    if (dateTimeParts && dateTimeParts.length === 7) {
        const [, day, month, year, hours, minutes, seconds] = dateTimeParts;
        return new Date(year, month - 1, day, hours, minutes, seconds);
    }
    return null;
}

// Функция для форматирования даты в виде строки
function formatDate(date) {
    return date.toLocaleString('ru-RU', {
        day: '2-digit',
        month: '2-digit',
        year: 'numeric',
        hour: '2-digit',
        minute: '2-digit',
        second: '2-digit',
        hour12: false
    });
}















