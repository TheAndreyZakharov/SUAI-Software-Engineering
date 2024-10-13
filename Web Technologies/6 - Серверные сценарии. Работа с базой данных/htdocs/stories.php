<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Анкета - Работа с нейронными сетями</title>
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
        h1 { 
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
        input[type="email"],
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
        .centered-image {
            text-align: center;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Истории успеха нейронных сетей</h1>
        <?php
        // Загружаем XML и XSLT
        $xml = new DOMDocument;
        $xml->load('success_stories.xml');
        
        $xsl = new DOMDocument;
        $xsl->load('transform.xslt');
        
        // Конфигурируем процессор
        $proc = new XSLTProcessor;
        $proc->importStyleSheet($xsl); // Прикрепляем XSLT
        
        // Преобразуем XML и получаем HTML
        $result = $proc->transformToXML($xml);
        
        // Выводим результат
        echo $result;
        ?>
        
    </div>
</body>
</html>
