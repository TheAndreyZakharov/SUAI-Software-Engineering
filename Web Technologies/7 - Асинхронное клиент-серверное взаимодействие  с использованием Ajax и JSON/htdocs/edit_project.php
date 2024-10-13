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
$sql = "SELECT * FROM Projects WHERE id = $id";
$result = $conn->query($sql);
$project = $result->fetch_assoc();

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $project_name = $_POST['project_name'];
    $project_description = $_POST['project_description'];
    $start_date = $_POST['start_date'];
    $status = $_POST['status'];
    $algorithm_id = $_POST['algorithm_id'];

    $updateSql = "UPDATE Projects SET project_name = ?, project_description = ?, start_date = ?, status = ?, algorithm_id = ? WHERE id = ?";
    $stmt = $conn->prepare($updateSql);
    $stmt->bind_param("ssssii", $project_name, $project_description, $start_date, $status, $algorithm_id, $id);

    if ($stmt->execute()) {
        header("Location: neural_networks.php");
        exit;
    } else {
        echo "Error: " . $stmt->error;
    }

    $stmt->close();
}

// Получение списка алгоритмов для выпадающего списка
$algorithm_sql = "SELECT id, name FROM Algorithms";
$algorithm_result = $conn->query($algorithm_sql);

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Edit Project</title>
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
        input[type="date"],
        select,
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
        <h1>Edit Project</h1>
        <form action="" method="post">
            Project Name: <input type="text" name="project_name" value="<?php echo htmlspecialchars($project['project_name']); ?>"><br>
            Description: <textarea name="project_description"><?php echo htmlspecialchars($project['project_description']); ?></textarea><br>
            Start Date: <input type="date" name="start_date" value="<?php echo htmlspecialchars($project['start_date']); ?>"><br>
            Status: <input type="text" name="status" value="<?php echo htmlspecialchars($project['status']); ?>"><br>
            Algorithm: 
            <select name="algorithm_id">
                <?php
                if ($algorithm_result->num_rows > 0) {
                    while($alg = $algorithm_result->fetch_assoc()) {
                        $selected = ($alg['id'] == $project['algorithm_id']) ? 'selected' : '';
                        echo "<option value='" . $alg['id'] . "' $selected>" . $alg['name'] . "</option>";
                    }
                } else {
                    echo "<option value=''>No algorithms available</option>";
                }
                ?>
            </select>
            <br>
            <input type="submit" value="Save Changes">
        </form>
    </div>
</body>
</html>
