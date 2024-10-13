CREATE DATABASE FinancialDB;

USE FinancialDB;


CREATE TABLE User (
  user_id INT NOT NULL PRIMARY KEY,
  name VARCHAR(50) NOT NULL,
  surname VARCHAR(50) NOT NULL
);

CREATE TABLE Income_Category (
  in_cat_id INT NOT NULL PRIMARY KEY,
  in_cat_name VARCHAR(50) NOT NULL
);

CREATE TABLE Income_Item (
  in_it_id INT NOT NULL PRIMARY KEY,
  in_it_name VARCHAR(50) NOT NULL,
  in_cat_id INT NOT NULL,
  FOREIGN KEY (in_cat_id) REFERENCES Income_Category(in_cat_id) ON DELETE RESTRICT ON UPDATE RESTRICT
);

CREATE TABLE Income (
  in_id INT NOT NULL PRIMARY KEY,
  in_name VARCHAR(50) NOT NULL,
  in_date DATE,
  in_money NUMERIC(10,2),
  in_it_id INT NOT NULL,
  user_id INT NOT NULL,
  FOREIGN KEY (in_it_id) REFERENCES Income_Item(in_it_id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (user_id) REFERENCES User(user_id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Expense_Category (
  exp_cat_id INT NOT NULL PRIMARY KEY,
  exp_cat_name VARCHAR(50) NOT NULL
);

CREATE TABLE Expense_Item (
  exp_it_id INT NOT NULL PRIMARY KEY,
  exp_it_name VARCHAR(50) NOT NULL,
  exp_cat_id INT NOT NULL,
  FOREIGN KEY (exp_cat_id) REFERENCES Expense_Category(exp_cat_id) ON DELETE RESTRICT ON UPDATE RESTRICT
);

CREATE TABLE Expense (
  exp_id INT NOT NULL PRIMARY KEY,
  exp_name VARCHAR(50) NOT NULL,
  exp_date DATE,
  exp_money NUMERIC(10,2),
  exp_it_id INT NOT NULL,
  user_id INT NOT NULL,
  FOREIGN KEY (exp_it_id) REFERENCES Expense_Item(exp_it_id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (user_id) REFERENCES User(user_id) ON DELETE CASCADE ON UPDATE CASCADE
);



-- ALTER TABLE User
-- ADD email VARCHAR(255);
-- ---
--ALTER TABLE User
--DROP COLUMN email;
