#!/usr/bin/env python3

import cgi

print("Content-type: text/html; charset=utf-8\n")

form = cgi.FieldStorage()

# Поля для вашей анкеты
fields = ['surname', 'name', 'patronymic', 'email', 'experience', 'interests', 'role', 'comment', 'hiddenField']

# Собираем данные в строку
data = []
for field in fields:
    value = form.getvalue(field, '(не указано)')
    if isinstance(value, list):
        value = ', '.join(value)
    data.append(value)

# Записываем данные в файл
with open("/Users/andrey/Documents/SUAI/3.2/Web/8/datafile.txt", "a") as file:
    file.write(','.join(data) + '\n')

print("<html>")
print("<head>")
print("<title>Результаты анкеты</title>")
print('''
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
</style>
''')
print("</head>")
print("<body>")
print("<div class='container'>")
print("<h1>Результаты анкеты</h1>")
print("<table>")
for field, value in zip(fields, data):
    print(f"<tr><td>{field}</td><td>{value}</td></tr>")
print("</table>")
print("</div>")
print("</body>")
print("</html>")
