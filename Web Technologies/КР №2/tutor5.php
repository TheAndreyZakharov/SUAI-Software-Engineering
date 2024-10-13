<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>Результаты анкеты</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            color: #333;
            padding: 20px;
        }
        .container {
            max-width: 800px;
            margin: 0 auto;
            background: #fff;
            padding: 20px;
            box-shadow: 0 4px 8px rgba(0,0,0,0.1);
            border-radius: 8px;
        }
        h1 {
            color: #4CAF50;
            text-align: center;
        }
        ul {
            list-style-type: none;
            padding: 0;
        }
        li {
            padding: 8px;
            border-bottom: 1px solid #ccc;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Результаты анкеты</h1>
        <ul>
        <?php
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $fields = ['surname', 'name', 'patronymic', 'email', 'experience', 'interests', 'role', 'comment'];
            foreach ($fields as $field) {
                if ($field == 'interests' && !empty($_POST[$field])) {
                    $value = htmlspecialchars(implode(', ', $_POST[$field]));
                } else {
                    $value = !empty($_POST[$field]) ? htmlspecialchars($_POST[$field]) : '(не указано)';
                }
                echo "<li><strong>$field:</strong> $value</li>";
            }
        }
        ?>
        </ul>
    </div>
</body>
</html>
