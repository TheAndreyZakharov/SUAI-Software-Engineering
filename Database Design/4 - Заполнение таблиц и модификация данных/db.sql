--Таблица User:
INSERT INTO User (user_id, name, surname) VALUES (1, 'Александр', 'Иванов');
INSERT INTO User (user_id, name, surname) VALUES (2, 'Елена', 'Иванова');
INSERT INTO User (user_id, name, surname) VALUES (3, 'Михаил', 'Иванов');
INSERT INTO User (user_id, name, surname) VALUES (4, 'Анастасия', 'Иванова');
--Таблица Income Category
INSERT INTO Income_Category (in_cat_id, in_cat_name) VALUES (1, 'Зарплата');
INSERT INTO Income_Category (in_cat_id, in_cat_name) VALUES (2, 'Подарок');
INSERT INTO Income_Category (in_cat_id, in_cat_name) VALUES (3, 'Фриланс');
--Таблица Income_Item
INSERT INTO Income_Item (in_it_id, in_it_name, in_cat_id) VALUES (1, 'Работа Александра', 1);
INSERT INTO Income_Item (in_it_id, in_it_name, in_cat_id) VALUES (2, 'День рождения Михаила', 2);
INSERT INTO Income_Item (in_it_id, in_it_name, in_cat_id) VALUES (3, 'Фриланс Елены', 3);
INSERT INTO Income_Item (in_it_id, in_it_name, in_cat_id) VALUES (4, 'Фриланс Александра', 3);
--Таблица Income
INSERT INTO Income (in_id, in_name, in_date, in_money, in_it_id, user_id) VALUES (1, 'Зарплата Александра', '2023-01-15', 60000.00, 1, 1);
INSERT INTO Income (in_id, in_name, in_date, in_money, in_it_id, user_id) VALUES (2, 'Подарок Михаилу', '2023-02-20', 5000.00, 2, 3);
INSERT INTO Income (in_id, in_name, in_date, in_money, in_it_id, user_id) VALUES (3, 'Фриланс Елены', '2023-03-05', 15000.00, 3, 2);
INSERT INTO Income (in_id, in_name, in_date, in_money, in_it_id, user_id) VALUES (4, Фриланс Александра', '2023-02-20', 10000.00, 4, 1);
INSERT INTO Income (in_id, in_name, in_date, in_money, in_it_id, user_id) VALUES (5, 'Другой подарок Михаилу', '2023-01-20', 3000.00, 2, 3);
--Таблица Expense_Category
INSERT INTO Expense_Category (exp_cat_id, exp_cat_name) VALUES (1, 'Продукты');
INSERT INTO Expense_Category (exp_cat_id, exp_cat_name) VALUES (2, 'Транспорт');
INSERT INTO Expense_Category (exp_cat_id, exp_cat_name) VALUES (3, 'Образование');
INSERT INTO Expense_Category (exp_cat_id, exp_cat_name) VALUES (4, 'Городской транспорт');
INSERT INTO Expense_Category (exp_cat_id, exp_cat_name) VALUES (5, 'Транспорт служебный');
--Таблица Expense_Item
INSERT INTO Expense_Item (exp_it_id, exp_it_name, exp_cat_id) VALUES (1, 'Покупка в супермаркете', 1);
INSERT INTO Expense_Item (exp_it_id, exp_it_name, exp_cat_id) VALUES (2, 'Абонемент на транспорт', 2);
INSERT INTO Expense_Item (exp_it_id, exp_it_name, exp_cat_id) VALUES (3, 'Школьные кружки', 3);
INSERT INTO Expense_Item (exp_it_id, exp_it_name, exp_cat_id) VALUES (4, 'Билет на городской транспорт', 4);
INSERT INTO Expense_Item (exp_it_id, exp_it_name, exp_cat_id) VALUES (5, 'Транспорт служебный', 5);
--Таблица Expense
INSERT INTO Expense (exp_id, exp_name, exp_date, exp_money, exp_it_id, user_id) VALUES (1, 'Покупки в магазине', '2023-01-16', 20000.00, 1, 2);
INSERT INTO Expense (exp_id, exp_name, exp_date, exp_money, exp_it_id, user_id) VALUES (2, 'Транспорт Елены', '2023-02-01', 1500.00, 2, 2);
INSERT INTO Expense (exp_id, exp_name, exp_date, exp_money, exp_it_id, user_id) VALUES (3, 'Кружки Михаила', '2023-03-10', 3000.00, 3, 3);
INSERT INTO Expense (exp_id, exp_name, exp_date, exp_money, exp_it_id, user_id) VALUES (4, 'Проезд на автобусе', '2023-01-17', 700.00, 4, 1);
INSERT INTO Expense (exp_id, exp_name, exp_date, exp_money, exp_it_id, user_id) VALUES (5, 'Кружки Михаила в мае', '2023-05-10', 3000.00, 3, 3);
INSERT INTO Expense (exp_id, exp_name, exp_date, exp_money, exp_it_id, user_id) VALUES (6, 'Кружки Михаила в январе', '2023-01-10', 3000.00, 3, 3);
INSERT INTO Expense (exp_id, exp_name, exp_date, exp_money, exp_it_id, user_id) VALUES (7, 'Покупки Александра в магазине', '2023-03-16', 5000.00, 1, 1);
INSERT INTO Expense (exp_id, exp_name, exp_date, exp_money, exp_it_id, user_id) VALUES (8, 'Покупки Михаила в магазине', '2023-03-17', 1500.00, 1, 3);
INSERT INTO Expense (exp_id, exp_name, exp_date, exp_money, exp_it_id, user_id) VALUES (9, 'Расходы на транспорт служебный', '2023-04-01', 2000.00, 5, 1);
INSERT INTO Expense (exp_id, exp_name, exp_date, exp_money, exp_it_id, user_id) VALUES (10, 'Покупки Анастасии в магазине', '2023-03-16', 5000.00, 1, 4);



INSERT INTO User (user_id, name, surname) VALUES (5, 'Дмитрий', 'Петров');
  
UPDATE User SET name = 'Николай' WHERE user_id = 5;
  
DELETE FROM User WHERE user_id = 5;
  
MERGE INTO Income AS target
USING Temp_Income AS source
ON target.in_id = source.in_id
WHEN MATCHED THEN
UPDATE SET in_money = source.in_money
WHEN NOT MATCHED THEN
INSERT (in_id, in_name, in_date, in_money, in_it_id, user_id)
VALUES (source.in_id, source.in_name, source.in_date, source.in_money, source.in_it_id, source.user_id)
WHEN NOT MATCHED BY SOURCE THEN
DELETE;



