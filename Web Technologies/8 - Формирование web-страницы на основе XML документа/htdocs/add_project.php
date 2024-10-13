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

    $algorithm_id = $_POST['algorithm_id'];
    $project_name = $_POST['project_name'];
    $project_description = $_POST['project_description'];
    $start_date = $_POST['start_date'];
    $status = $_POST['status'];

    $sql = "INSERT INTO Projects (algorithm_id, project_name, project_description, start_date, status) VALUES (?, ?, ?, ?, ?)";

    $stmt = $conn->prepare($sql);
    $stmt->bind_param("issss", $algorithm_id, $project_name, $project_description, $start_date, $status);

    if ($stmt->execute()) {
        echo "New project added successfully";
    } else {
        echo "Error: " . $stmt->error;
    }

    $stmt->close();
    $conn->close();

    header("Location: neural_networks.php");
    exit;
}
?>
