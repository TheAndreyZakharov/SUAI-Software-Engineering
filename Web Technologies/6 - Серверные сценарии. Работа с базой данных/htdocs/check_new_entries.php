<?php
header('Access-Control-Allow-Origin: *'); // Разрешает доступ для всех доменов

$host = 'localhost';
$user = 'root';
$pass = '';
$db = 'neural_networks_db';

// Создаем подключение
$conn = new mysqli($host, $user, $pass, $db);

// Проверяем подключение
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Запрос для получения последних записей алгоритмов и проектов
$sql = "(SELECT 'algorithm' as type, name, description, id FROM algorithms ORDER BY id DESC LIMIT 5)
        UNION
        (SELECT 'project' as type, project_name as name, project_description as description, id FROM projects ORDER BY id DESC LIMIT 5)
        ORDER BY id DESC LIMIT 5";

$result = $conn->query($sql);

$new_entries = array();

if ($result->num_rows > 0) {
    // Добавляем каждую новую запись в массив
    while($row = $result->fetch_assoc()) {
        array_push($new_entries, $row);
    }
} 

// Возвращаем результат в формате JSON
$response = array(
    "status" => "success",
    "timestamp" => date("Y-m-d H:i:s"),
    "data" => $new_entries
);

echo json_encode($response);


// Закрываем подключение
$conn->close();
?>
