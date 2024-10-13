-- Вставка данных в таблицу users
-- Пользователи калькулятора бюджета
INSERT INTO users (name) VALUES
    (('Алексей', 'Иванов', 'Петрович')),  -- user_id = 1
    (('Мария', 'Смирнова', 'Игоревна')),  -- user_id = 2
    (('Ян', 'Кузнецов', 'Сергеевич')); -- user_id = 3

-- Вставка данных в таблицу admin (администраторы)
-- Администраторы калькулятора бюджета
INSERT INTO admin (name, description) VALUES
    (('Иван', 'Сидоров', 'Алексеевич'), 'Главный администратор'), -- user_id = 4
    (('Елена', 'Козлова', 'Викторовна'), 'Администратор категории доходов'); -- user_id = 5

-- Вставка данных в таблицу category (категории доходов и расходов)
-- Категории доходов и расходов, добавленные администраторами
INSERT INTO category (name, cat_type, created_by) VALUES
    ('Продажа', 'Доходы', 4),      -- Иван Сидоров добавил категорию Продажа
    ('Зарплата', 'Доходы', 5),     -- Елена Козлова добавила категорию Зарплата
    ('Еда', 'Расходы', 4),         -- Иван Сидоров добавил категорию Еда
    ('Счета за КУ', 'Расходы', 5), -- Елена Козлова добавила категорию Счета за КУ
    ('Здоровье', 'Расходы', 4),    -- Иван Сидоров добавил категорию Здоровье
    ('Спорт и фитнес', 'Расходы', 4); -- Иван Сидоров добавил категорию Спорт и фитнес



-- Вставка данных в таблицу item (статьи доходов и расходов)
-- Статьи доходов и расходов, добавленные пользователями
INSERT INTO item (title, item_type, value, date, category_id, added_by) VALUES
    ('Продажа автомобиля', 'Доходы', 500000, '2024-01-15', 1, 1), 
    ('Зарплата за январь', 'Доходы', 60000, '2024-01-31', 2, 2),  
    ('Покупка продуктов', 'Расходы', 5000, '2024-02-10', 3, 3), 
    ('Оплата коммунальных услуг', 'Расходы', 8000, '2024-02-20', 4, 1), 
    ('Медицинская страховка', 'Расходы', 12000, '2024-03-01', 5, 2),
    ('Абонемент в спортзал', 'Расходы', 3000, '2024-04-05', 6, 3), 
    ('Спортивная одежда', 'Расходы', 7000, '2024-04-15', 6, 1), 
    ('Зарплата за февраль', 'Доходы', 60000, '2024-02-28', 2, 2), 
    ('Покупка велосипеда', 'Расходы', 15000, '2024-05-20', 6, 1); 









WITH user_article_counts AS (
    SELECT u.user_id, (u.name).first_name, (u.name).last_name, COUNT(i.item_id) AS item_count
    FROM users u
    LEFT JOIN item i ON u.user_id = i.added_by
    GROUP BY u.user_id
)
SELECT user_id, first_name, last_name, item_count
FROM user_article_counts
WHERE item_count = (SELECT MIN(item_count) FROM user_article_counts);











SELECT user_id, (name).first_name, (name).last_name
FROM ONLY users
WHERE (name).last_name LIKE 'И%';








SELECT a.user_id, (u.name).first_name, (u.name).last_name, a.description
FROM admin a
JOIN users u ON a.user_id = u.user_id
JOIN category c ON a.user_id = c.created_by
WHERE c.cat_type = 'Доходы';









CREATE OR REPLACE FUNCTION is_divisible_by(value FLOAT, multiple FLOAT)
RETURNS BOOLEAN AS $$
BEGIN
    RETURN MOD(value::NUMERIC, multiple::NUMERIC) = 0;
END;
$$ LANGUAGE plpgsql;

CREATE OPERATOR %% (
    LEFTARG = FLOAT,
    RIGHTARG = FLOAT,
    PROCEDURE = is_divisible_by
);

-- Пример использования
SELECT title, value
FROM item
WHERE value %% 7;









SELECT title, value, value %% 7
FROM item






CREATE OR REPLACE FUNCTION find_shortest_full_name(a full_name, b full_name)
RETURNS full_name AS
$$
DECLARE
    a_length INT;
    b_length INT;
BEGIN
    --  проверки на полное NULL значение
    IF a IS NULL THEN
        RETURN b;
    END IF;
    IF b IS NULL THEN
        RETURN a;
    END IF;

    -- Вычисление длины полного имени для каждого аргумента с учётом NULL значений
    a_length := LENGTH(COALESCE(a.first_name, '')) + LENGTH(COALESCE(a.last_name, '')) + LENGTH(COALESCE(a.patronymic, ''));
    b_length := LENGTH(COALESCE(b.first_name, '')) + LENGTH(COALESCE(b.last_name, '')) + LENGTH(COALESCE(b.patronymic, ''));

    -- Сравнение длин полных имен
    IF a_length < b_length THEN
        RETURN a;
    ELSE
        RETURN b;
    END IF;
END;
$$ LANGUAGE plpgsql;

-- Пересоздаем агрегатную функцию
DROP AGGREGATE IF EXISTS shortest_full_name(full_name);

CREATE AGGREGATE shortest_full_name(full_name) (
    SFUNC = find_shortest_full_name,
    STYPE = full_name
);

-- Тестовый запрос для проверки функции:
SELECT shortest_full_name(name) FROM users;












