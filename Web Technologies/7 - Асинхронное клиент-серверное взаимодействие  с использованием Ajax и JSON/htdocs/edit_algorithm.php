<?php
$host = 'localhost';
$user = 'root';
$pass = '';
$db = 'neural_networks_db';

$conn = new mysqli($host, $user, $pass, $db);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$id = $_GET['id'];
$sql = "SELECT * FROM Algorithms WHERE id = $id";
$result = $conn->query($sql);
$algorithm = $result->fetch_assoc();

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $name = $_POST['name'];
    $type = $_POST['type'];
    $description = $_POST['description'];

    $updateSql = "UPDATE Algorithms SET name = ?, type = ?, description = ? WHERE id = ?";
    $stmt = $conn->prepare($updateSql);
    $stmt->bind_param("sssi", $name, $type, $description, $id);

    if ($stmt->execute()) {
        header("Location: neural_networks.php");
        exit;
    } else {
        echo "Error: " . $stmt->error;
    }

    $stmt->close();
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Edit Algorithm</title>
    <style>
        body { 
            font-family: Arial, sans-serif; 
            background-color: #f4f4f4;
            color: #333;
        }
        .container { 
            width: 60%; 
            margin: 20px auto; 
            padding: 20px; 
            background: white; 
            box-shadow: 0 0 10px rgba(0,0,0,0.1);
        }
        h1 { 
            color: #4CAF50;
            text-align: center;
        }
        input[type="text"],
        textarea {
            width: 100%;
            padding: 10px;
            margin: 6px 0;
            display: inline-block;
            border: 1px solid #ccc;
            border-radius: 4px;
            box-sizing: border-box;
        }
        input[type="submit"] {
            width: 100%;
            background-color: #4CAF50;
            color: white;
            padding: 14px 20px;
            margin: 8px 0;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        input[type="submit"]:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Edit Algorithm</h1>
        <form action="" method="post">
            Name: <input type="text" name="name" value="<?php echo htmlspecialchars($algorithm['name']); ?>"><br>
            Type: <input type="text" name="type" value="<?php echo htmlspecialchars($algorithm['type']); ?>"><br>
            Description: <textarea name="description"><?php echo htmlspecialchars($algorithm['description']); ?></textarea><br>
            <input type="submit" value="Save Changes">
        </form>
    </div>
</body>
</html>
