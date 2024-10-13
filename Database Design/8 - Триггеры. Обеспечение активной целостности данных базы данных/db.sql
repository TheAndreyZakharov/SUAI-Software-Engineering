DELIMITER //
CREATE TRIGGER before_insert_income
BEFORE INSERT ON Income
FOR EACH ROW
BEGIN
    -- Объявляем переменные для проверки существования пользователя и категории
    DECLARE user_exists INT DEFAULT 0;
    DECLARE item_exists INT DEFAULT 0;

    -- Проверяем, существует ли пользователь с данным user_id
    SELECT COUNT(*) INTO user_exists FROM User WHERE user_id = NEW.user_id;
    -- Проверяем, существует ли пункт дохода с данным in_it_id
    SELECT COUNT(*) INTO item_exists FROM Income_Item WHERE in_it_id = NEW.in_it_id;


    -- Если пользователь или категория не найдены, выдаем ошибку
    IF user_exists = 0 OR item_exists = 0 THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Ошибка целостности ссылок: пользователь или категория не существует.';
    END IF;
END;
//
DELIMITER ;

DROP TRIGGER before_insert_income;

INSERT INTO Income (in_id, in_name, in_date, in_money, in_it_id, user_id)
VALUES (6, 'Доход Один', '2023-04-01', 45000.00, 1, 1);

DELETE FROM Income WHERE in_id = 6;

INSERT INTO Income (in_name, in_date, in_money, in_it_id, user_id)
VALUES ('Неверный доход', '2023-04-01', 50000.00, 999, 999);










DELIMITER //
CREATE TRIGGER after_insert_income
AFTER INSERT ON Income
FOR EACH ROW
BEGIN
    -- Добавляем запись в таблицу логов с полной информацией о вставленной записи
    INSERT INTO Income_Log (in_id, in_name, in_date, in_money, in_it_id, user_id, action, action_time)
    VALUES (NEW.in_id, NEW.in_name, NEW.in_date, NEW.in_money, NEW.in_it_id, NEW.user_id, 'INSERT', NOW());
END;
//
DELIMITER ;
DELIMITER ;

DROP TRIGGER after_insert_income;

INSERT INTO Income (in_name, in_date, in_money, in_it_id, user_id)
VALUES ('Тестовый доход', '2023-04-01', 30000.00, 1, 1);

SELECT * FROM Income_Log;

DELETE FROM Income WHERE in_name = 'Тестовый доход' AND in_date = '2023-04-01';

DELETE FROM Income_Log;












DELIMITER //
CREATE TRIGGER before_delete_income_item
BEFORE DELETE ON Income_Item
FOR EACH ROW
BEGIN
    -- Удаляем все связанные записи из таблицы Income
    DELETE FROM Income WHERE in_it_id = OLD.in_it_id;
END;
//
DELIMITER ;

DROP TRIGGER before_delete_income_item;


INSERT INTO Income_Category (in_cat_id, in_cat_name) VALUES (999, 'Тестовая категория');
INSERT INTO Income_Item (in_it_id, in_it_name, in_cat_id) VALUES (999, 'Тестовый элемент дохода', 999);
INSERT INTO Income (in_name, in_date, in_money, in_it_id, user_id) VALUES ('Тестовый доход', '2023-04-01', 10000.00, 999, 1);

DELETE FROM Income_Item WHERE in_it_id = 999;

DELETE FROM Income_Category WHERE in_cat_id = 999;













DELIMITER //
CREATE TRIGGER after_delete_income
AFTER DELETE ON Income
FOR EACH ROW
BEGIN
    -- Добавляем запись в таблицу логов с информацией об удаленной записи
    INSERT INTO Income_Delete_Log (in_id, in_name, in_date, in_money, in_it_id, user_id, action, action_time)
    VALUES (OLD.in_id, OLD.in_name, OLD.in_date, OLD.in_money, OLD.in_it_id, OLD.user_id, 'DELETE', NOW());
END;
//
DELIMITER ;

INSERT INTO Income (in_name, in_date, in_money, in_it_id, user_id)
VALUES ('Тестовый доход', '2023-04-01', 20000.00, 1, 1);

DELETE FROM Income WHERE in_name = 'Тестовый доход' AND in_date = '2023-04-01';

SELECT * FROM Income_Delete_Log;

DELETE FROM Income_Delete_Log;














DELIMITER //
CREATE TRIGGER before_update_income
BEFORE UPDATE ON Income
FOR EACH ROW
BEGIN
    -- Проверяем, что сумма дохода не отрицательная
    IF NEW.in_money < 0 THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Ошибка: сумма дохода не может быть отрицательной.';
    END IF;
END;
//
DELIMITER ;

SELECT * FROM Income;

INSERT INTO Income (in_name, in_date, in_money, in_it_id, user_id)
VALUES ('Тестовый доход', '2023-04-01', 10000.00, 1, 1);

UPDATE Income SET in_money = 15000.00 WHERE in_name = 'Тестовый доход' AND in_date = '2023-04-01';

UPDATE Income SET in_money = -15000.00 WHERE in_name = 'Тестовый доход' AND in_date = '2023-04-01';

DELETE FROM Income WHERE in_name = 'Тестовый доход' AND in_date = '2023-04-01';















CREATE TABLE Income_Update_Log (
    log_id INT AUTO_INCREMENT PRIMARY KEY,
    in_id INT,
    old_in_money DECIMAL(10, 2),
    new_in_money DECIMAL(10, 2),
    update_time DATETIME
);

DELIMITER //
CREATE TRIGGER after_update_income
AFTER UPDATE ON Income
FOR EACH ROW
BEGIN
    -- Добавляем запись в таблицу логов с информацией об обновлении
    INSERT INTO Income_Update_Log (in_id, old_in_money, new_in_money, update_time)
    VALUES (NEW.in_id, OLD.in_money, NEW.in_money, NOW());
END;
//
DELIMITER ;


INSERT INTO Income (in_name, in_date, in_money, in_it_id, user_id)
VALUES ('Тестовый доход для обновления', '2023-04-01', 10000.00, 1, 1);

UPDATE Income SET in_money = 20000.00 WHERE in_name = 'Тестовый доход для обновления' AND in_date = '2023-04-01';

SELECT * FROM Income_Update_Log;

DELETE FROM Income WHERE in_name = 'Тестовый доход для обновления' AND in_date = '2023-04-01';

DELETE FROM Income_Update_Log;
