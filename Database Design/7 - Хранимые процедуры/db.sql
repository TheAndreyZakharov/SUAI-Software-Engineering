DELIMITER $$

CREATE PROCEDURE InsertIncomeWithReference(
    IN _user_name VARCHAR(255),
    IN _surname VARCHAR(255),
    IN _in_cat_name VARCHAR(255),
    IN _in_it_name VARCHAR(255),
    IN _in_name VARCHAR(255),
    IN _in_date DATE,
    IN _in_money DECIMAL(10,2)
)
BEGIN
    DECLARE _user_id INT;
    DECLARE _in_cat_id INT;
    DECLARE _in_it_id INT;

    -- Проверяем существует ли пользователь, если нет - вставляем и получаем ID
    SELECT user_id INTO _user_id FROM User WHERE name = _user_name AND surname = _surname;
    IF _user_id IS NULL THEN
        INSERT INTO User(name, surname) VALUES (_user_name, _surname);
        SET _user_id = LAST_INSERT_ID();
    END IF;

    -- Проверяем существует ли категория дохода, если нет - вставляем и получаем ID
    SELECT in_cat_id INTO _in_cat_id FROM Income_Category WHERE in_cat_name = _in_cat_name;
    IF _in_cat_id IS NULL THEN
        INSERT INTO Income_Category(in_cat_name) VALUES (_in_cat_name);
        SET _in_cat_id = LAST_INSERT_ID();
    END IF;

    -- Проверяем существует ли статья дохода, если нет - вставляем и получаем ID
    SELECT in_it_id INTO _in_it_id FROM Income_Item WHERE in_it_name = _in_it_name AND in_cat_id = _in_cat_id;
    IF _in_it_id IS NULL THEN
        INSERT INTO Income_Item(in_it_name, in_cat_id) VALUES (_in_it_name, _in_cat_id);
        SET _in_it_id = LAST_INSERT_ID();
    END IF;

    -- Теперь вставляем запись в таблицу Income
    INSERT INTO Income(in_name, in_date, in_money, in_it_id, user_id) VALUES (_in_name, _in_date, _in_money, _in_it_id, _user_id);
END$$

DELIMITER ;
CALL InsertIncomeWithReference('Имя', 'Фамилия', 'КатегорияДохода', 'СтатьяДохода', 'Название дохода', '2023-01-01', 10000.00);







CALL InsertIncomeWithReference('Имя', 'Фамилия', 'КатегорияДохода', 'СтатьяДохода', 'Название дохода', '2023-01-01', 10000.00);
CALL InsertIncomeWithReference('Алексей', 'Смирнов', 'Инвестиции', 'Дивиденды', 'Дивиденды от акций', '2023-06-01', 15000.00);
CALL InsertIncomeWithReference('Иван', 'Петров', 'Инвестиции', 'Дивиденды', 'Дивиденды от акций', '2023-06-30', 80000.00);





DELIMITER $$

CREATE PROCEDURE DeleteIncomeItemWithCategoryCleanup(
    IN _in_it_id INT
)
BEGIN
    DECLARE _in_cat_id INT;

    -- Получаем in_cat_id для удаляемого income_item
    SELECT in_cat_id INTO _in_cat_id FROM Income_Item WHERE in_it_id = _in_it_id;

    -- Удаляем запись из income_item
    DELETE FROM Income_Item WHERE in_it_id = _in_it_id;

    -- Проверяем, остались ли связанные записи в income_category
    IF NOT EXISTS (SELECT 1 FROM Income_Item WHERE in_cat_id = _in_cat_id) THEN        -- Если связанные записи отсутствуют, удаляем категорию
        DELETE FROM Income_Category WHERE in_cat_id = _in_cat_id;
    END IF;
END$$

DELIMITER ;

CALL DeleteIncomeItemWithCategoryCleanup(5);







DELIMITER $$

CREATE PROCEDURE CascadeDeleteIncomeItem(
    IN _in_it_id INT
)
BEGIN
    -- Удаляем связанные данные из дочерней таблицы income
    DELETE FROM Income WHERE in_it_id = _in_it_id;

    -- Удаляем запись из родительской таблицы income_item
    DELETE FROM Income_Item WHERE in_it_id = _in_it_id;
END$$

DELIMITER ;

CALL CascadeDeleteIncomeItem(5);








DELIMITER $$

CREATE PROCEDURE CalculateTotalIncome(
    OUT total_income DECIMAL(10,2)
)
BEGIN
    SELECT SUM(in_money) INTO total_income FROM Income;
END$$

DELIMITER ;

CALL CalculateTotalIncome(@total);
SELECT @total AS TotalIncome;








DROP PROCEDURE IF EXISTS GenerateDetailedIncomeStatistics;


DELIMITER $$

CREATE PROCEDURE GenerateDetailedIncomeStatistics()
BEGIN
    -- Создание временной таблицы для статистики
    CREATE TEMPORARY TABLE IF NOT EXISTS TempDetailedIncomeStatistics (
        CategoryName VARCHAR(255),
        TotalRecords INT,
        TotalAmount DECIMAL(10,2),
        AverageAmount DECIMAL(10,2)
    );

    -- Заполнение временной таблицы данными
    INSERT INTO TempDetailedIncomeStatistics (CategoryName, TotalRecords, TotalAmount, AverageAmount)
    SELECT IC.in_cat_name, 
           COUNT(I.in_id), 
           SUM(I.in_money), 
           AVG(I.in_money)
    FROM Income I
    JOIN Income_Item II ON I.in_it_id = II.in_it_id
    JOIN Income_Category IC ON II.in_cat_id = IC.in_cat_id
    GROUP BY IC.in_cat_name;

    -- Вывод данных из временной таблицы
    SELECT * FROM TempDetailedIncomeStatistics;

    -- Удаляем временную таблицу
    DROP TEMPORARY TABLE IF EXISTS TempDetailedIncomeStatistics;
END$$

DELIMITER ;







CALL GenerateDetailedIncomeStatistics();
