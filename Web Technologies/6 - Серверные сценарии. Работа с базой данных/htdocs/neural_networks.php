<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Neural Networks Projects</title>
    <style>
        .error-message {
            color: red;
            margin: 10px 0;
        }
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
        h1, h2 { 
            color: #4CAF50;
            text-align: center;
        }
        table { 
            width: 100%; 
            border-collapse: collapse;
            margin-bottom: 20px;
        }
        th, td { 
            text-align: left; 
            padding: 12px; 
            border-bottom: 1px solid #ddd;
        }
        tr:hover { 
            background-color: #f5f5f5;
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
        label {
            margin-right: 10px;
        }
    </style>
</head>
<body>
<div class="container">
		<h1>Neural Networks Algorithms and Projects</h1>

		<!-- Форма добавления нового алгоритма -->
		<h2>Add New Algorithm</h2>
		<form method="post" action="add_algorithm.php">
			Name: <input type="text" name="name"><br>
			Type: <input type="text" name="type"><br>
			Description: <textarea name="description"></textarea><br>
			<input type="submit" name="submit" value="Add Algorithm">
		</form>

		<?php
		// Подключение к базе данных
		$host = 'localhost';
		$user = 'root';
		$pass = '';
		$db = 'neural_networks_db';

		$conn = new mysqli($host, $user, $pass, $db);
		if ($conn->connect_error) {
			die("Connection failed: " . $conn->connect_error);
		}

		// Запрос для получения алгоритмов
		$algorithm_sql = "SELECT id, name FROM Algorithms";
		$algorithm_result = $conn->query($algorithm_sql);
		?>

		<!-- Форма добавления нового проекта -->
		<h2>Add New Project</h2>
		<form method="post" action="add_project.php">
			Project Name: <input type="text" name="project_name"><br>
			Description: <textarea name="project_description"></textarea><br>
			Start Date: <input type="date" name="start_date"><br>
			Status: <input type="text" name="status"><br>

			<!-- Выпадающий список алгоритмов -->
			Algorithm: 
			<select name="algorithm_id">
				<?php
				if ($algorithm_result->num_rows > 0) {
					while($row = $algorithm_result->fetch_assoc()) {
						echo "<option value='" . $row["id"] . "'>" . $row["name"] . "</option>";
					}
				} else {
					echo "<option value=''>No algorithms available</option>";
				}
				?>
			</select>
			<br>
			
			<input type="submit" name="submit" value="Add Project">
		</form>


		<?php
		// Вывод таблицы Algorithms
		$sql = "SELECT * FROM Algorithms";
		$result = $conn->query($sql);
		echo "<h2>Algorithms</h2>";
		if ($result->num_rows > 0) {
			echo "<table border='1'><tr><th>Name</th><th>Type</th><th>Description</th><th>Actions</th></tr>";
			while($row = $result->fetch_assoc()) {
				echo "<tr><td>" . $row["name"] . "</td><td>" . $row["type"] . "</td><td>" . $row["description"] . "</td>";
				echo "<td><a href='edit_algorithm.php?id=" . $row["id"] . "'>Edit</a> | <a href='delete_algorithm.php?id=" . $row["id"] . "'>Delete</a></td></tr>";
			}
			echo "</table>";
		} else {
			echo "No algorithms found.<br>";
		}


		// Вывод таблицы Projects с добавленной колонкой алгоритма
		$sql = "SELECT Projects.*, Algorithms.name AS algorithm_name FROM Projects LEFT JOIN Algorithms ON Projects.algorithm_id = Algorithms.id";
		$result = $conn->query($sql);
		echo "<h2>Projects</h2>";
		if ($result->num_rows > 0) {
			echo "<table border='1'><tr><th>Project Name</th><th>Description</th><th>Start Date</th><th>Status</th><th>Algorithm</th><th>Actions</th></tr>";
			while($row = $result->fetch_assoc()) {
				echo "<tr><td>" . $row["project_name"] . "</td><td>" . $row["project_description"] . "</td><td>" . $row["start_date"] . "</td><td>" . $row["status"] . "</td><td>" . $row["algorithm_name"] . "</td>";
				echo "<td><a href='edit_project.php?id=" . $row["id"] . "'>Edit</a> | <a href='delete_project.php?id=" . $row["id"] . "'>Delete</a></td></tr>";
			}
			echo "</table>";
		} else {
			echo "No projects found.<br>";
		}
		?>





		<!-- Форма для ввода размеров матрицы -->
		<h2>Create Matrix</h2>
		<form method="post" action="">
			Rows: <input type="number" name="rows" min="1" required><br>
			Columns: <input type="number" name="columns" min="1" required><br>
			<input type="submit" value="Create Matrix">
		</form>

		<?php
		if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['rows']) && isset($_POST['columns'])) {
			$rows = (int)$_POST['rows'];
			$columns = (int)$_POST['columns'];
			echo "<h3>Matrix ($rows x $columns)</h3>";
			echo "<table border='1'>";
			for ($i = 1; $i <= $rows; $i++) {
				echo "<tr>";
				for ($j = 1; $j <= $columns; $j++) {
					echo "<td>" . $i * $j . "</td>";
				}
				echo "</tr>";
			}
			echo "</table>";
		}
		?>
	</div>
</body>
</html>