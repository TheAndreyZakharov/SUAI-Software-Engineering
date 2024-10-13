<?php
ini_set('display_errors', 1);
error_reporting(E_ALL);

if (isset($_POST['submit'])) {
    $host = 'localhost';
    $user = 'root';
    $pass = '';
    $db = 'neural_networks_db';

    $conn = new mysqli($host, $user, $pass, $db);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $name = $_POST['name'];
    $type = $_POST['type'];
    $description = $_POST['description'];

    $sql = "INSERT INTO Algorithms (name, type, description, created_at) VALUES (?, ?, ?, NOW())";

    // Использование подготовленных запросов для предотвращения SQL-инъекций
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("sss", $name, $type, $description);

    if ($stmt->execute()) {
        echo "New algorithm added successfully";
    } else {
        echo "Error: " . $stmt->error;
    }

    $stmt->close();
    $conn->close();

    // Перенаправление должно происходить после выполнения запроса
    header("Location: neural_networks.php");
    exit;
}
?>
