SELECT e.*, ec.exp_cat_name  -- все столбцы
FROM Expense e -- осн табл для запроса
JOIN Expense_Item ei ON e.exp_it_id = ei.exp_it_id -- соед по полю
JOIN Expense_Category ec ON ei.exp_cat_id = ec.exp_cat_id
WHERE ec.exp_cat_name LIKE '%транспорт_%';



-- чтобы сравнить различные записи доходов внутри одной и той же таблицы
-- одна копия таблицы используется для поиска записей из категории 'Зарплата', а вторая копия - для поиска записей из категории 'Подарок'.
-- позволяет применять фильтры независимо к каждой копии

SELECT DISTINCT MONTH(i1.in_date) as Month – из 1 коп выбор уник мес
FROM Income i1 -- выборка данных
INNER JOIN Income_Item ii1 ON i1.in_it_id = ii1.in_it_id -- соединяем с таблицей 
INNER JOIN Income_Category ic1 ON ii1.in_cat_id = ic1.in_cat_id --
INNER JOIN Income i2 ON MONTH(i1.in_date) = MONTH(i2.in_date) – соед 2 копии табл
INNER JOIN Income_Item ii2 ON i2.in_it_id = ii2.in_it_id
INNER JOIN Income_Category ic2 ON ii2.in_cat_id = ic2.in_cat_id
WHERE ic1.in_cat_name = 'Зарплата' AND ic2.in_cat_name = 'Подарок'; -- фильтруем по категриям



-- сохраняем строки с левой, соединяем с правой
SELECT u.* 
FROM User u 
LEFT JOIN Income i ON u.user_id = i.user_id 
WHERE i.user_id IS NULL;
\\\
SELECT u.*
FROM Income i
RIGHT JOIN User u ON i.user_id = u.user_id
WHERE i.user_id IS NULL;



