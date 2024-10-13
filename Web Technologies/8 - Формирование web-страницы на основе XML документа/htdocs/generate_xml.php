<?php
header('Content-Type: application/xml; charset=utf-8');

$host = 'localhost';
$user = 'root';
$pass = '';
$db = 'neural_networks_db';

$conn = new mysqli($host, $user, $pass, $db);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Извлекаем данные
$algorithms_sql = "SELECT id, name, type, description FROM algorithms";
$algorithms_result = $conn->query($algorithms_sql);

$projects_sql = "SELECT id, project_name, project_description, start_date, status, algorithm_id FROM projects";
$projects_result = $conn->query($projects_sql);

// Начало XML файла
echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
echo "<NeuralNetworkData>";

// Алгоритмы
echo "<Algorithms>";
while($row = $algorithms_result->fetch_assoc()) {
    echo "<Algorithm id=\"" . $row["id"] . "\">";
    echo "<Name>" . htmlspecialchars($row["name"]) . "</Name>";
    echo "<Type>" . htmlspecialchars($row["type"]) . "</Type>";
    echo "<Description>" . htmlspecialchars($row["description"]) . "</Description>";
    echo "</Algorithm>";
}
echo "</Algorithms>";

// Проекты
echo "<Projects>";
while($row = $projects_result->fetch_assoc()) {
    echo "<Project id=\"" . $row["id"] . "\">";
    echo "<ProjectName>" . htmlspecialchars($row["project_name"]) . "</ProjectName>";
    echo "<ProjectDescription>" . htmlspecialchars($row["project_description"]) . "</ProjectDescription>";
    echo "<StartDate>" . $row["start_date"] . "</StartDate>";
    echo "<Status>" . htmlspecialchars($row["status"]) . "</Status>";
    echo "<AlgorithmId>" . $row["algorithm_id"] . "</AlgorithmId>";
    echo "</Project>";
}
echo "</Projects>";

echo "</NeuralNetworkData>";

$conn->close();
?>
