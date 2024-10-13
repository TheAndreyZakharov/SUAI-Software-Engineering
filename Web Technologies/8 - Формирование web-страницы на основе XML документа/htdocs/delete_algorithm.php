<?php
$id = $_GET['id'];
$host = 'localhost';
$user = 'root';
$pass = '';
$db = 'neural_networks_db';

$conn = new mysqli($host, $user, $pass, $db);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "DELETE FROM Algorithms WHERE id = $id";

if ($conn->query($sql) === TRUE) {
    echo "Algorithm deleted successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
header("Location: neural_networks.php");
exit;
?>
