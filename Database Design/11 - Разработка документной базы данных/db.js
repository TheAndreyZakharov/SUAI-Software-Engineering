// Подключение к базе данных и создание коллекций
use bc;

db.createCollection("users");
db.createCollection("items");
db.createCollection("categories");

// Добавление администраторов
db.users.insertMany([
  { "role": "admin", "name": "Иван", "surname": "Иванов" },
  { "role": "admin", "name": "Петр", "surname": "Петров" }
]);

// Добавление пользователей
db.users.insertMany([
  { "role": "user", "name": "Алексей", "surname": "Алексеев" },
  { "role": "user", "name": "Мария", "surname": "Мариева" },
  { "role": "user", "name": "Ольга", "surname": "Ольгина" }
]);

// Добавление категорий
db.categories.insertMany([
  { _id: ObjectId(), name: "Спорт", type: "расход" },
  { _id: ObjectId(), name: "Продукты", type: "расход" },
  { _id: ObjectId(), name: "Зарплата", type: "доход" },
  { _id: ObjectId(), name: "Подарки", type: "доход" }
]);

// Добавление статей расходов (категория "Спорт")
db.items.insertMany([
  {
    _id: ObjectId(),
    category_id: ObjectId('65dd1be8325f1b9354de3d1c'),
    name: "Спортзал",
    type: "расход",
    transactions: [
      { amount: 3000, date: new Date("2024-03-01"), description: "Оплата спортзала за март", user_id: ObjectId("65dd0e91325f1b9354de3d18") }
    ],
    added_by: ObjectId('65dd0e6a325f1b9354de3d16')
  },
  {
    _id: ObjectId(),
    category_id: ObjectId('65dd1be8325f1b9354de3d1c'),
    name: "Спортинвентарь",
    type: "расход",
    transactions: [
      { amount: 15000, date: new Date("2024-03-15"), description: "Покупка гантелей", user_id: ObjectId("65dd0e91325f1b9354de3d19") }
    ],
    added_by: ObjectId('65dd0e6a325f1b9354de3d16')
  }
]);

// Добавление статей расходов (категория "Продукты")
db.items.insertMany([
  {
    _id: ObjectId(),
    category_id: ObjectId('65dd1be8325f1b9354de3d1d'),
    name: "Мясо",
    type: "расход",
    transactions: [
      { amount: 700, date: new Date("2024-02-01"), description: "Покупка курицы", user_id: ObjectId("65dd0e91325f1b9354de3d1a") }
    ],
    added_by: ObjectId('65dd0e6a325f1b9354de3d17')
  },
  {
    _id: ObjectId(),
    category_id: ObjectId('65dd1be8325f1b9354de3d1d'),
    name: "Напитки",
    type: "расход",
    transactions: [
      { amount: 300, date: new Date("2024-03-01"), description: "Покупка сока", user_id: ObjectId("65dd0e91325f1b9354de3d1a") }
    ],
    added_by: ObjectId('65dd0e6a325f1b9354de3d17')
  }
]);

// Добавление статей доходов (категория "Зарплата")
db.items.insertMany([
  {
    _id: ObjectId(),
    category_id: ObjectId('65dd1be8325f1b9354de3d1e'),
    name: "Зарплата за январь",
    type: "доход",
    transactions: [
      { amount: 50000, date: new Date("2024-01-31"), description: "Зарплата за январь", user_id: ObjectId("65dd0e91325f1b9354de3d18") }
    ],
    added_by: ObjectId('65dd0e6a325f1b9354de3d17')
  },
  {
    _id: ObjectId(),
    category_id: ObjectId('65dd1be8325f1b9354de3d1e'),
    name: "Премия за январь",
    type: "доход",
    transactions: [
      { amount: 10000, date: new Date("2024-01-31"), description: "Премия за январь", user_id: ObjectId("65dd0e91325f1b9354de3d18") }
    ],
    added_by: ObjectId('65dd0e6a325f1b9354de3d17')
  }
]);

// Добавление статей доходов (категория "Подарки")
db.items.insertMany([
  {
    _id: ObjectId(),
    category_id: ObjectId('65dd1be8325f1b9354de3d1f'),
    name: "Подарок за январь",
    type: "доход",
    transactions: [
      { amount: 10000, date: new Date("2024-01-15"), description: "Подарок Алексею", user_id: ObjectId("65dd0e91325f1b9354de3d18") },
      { amount: 15000, date: new Date("2024-01-20"), description: "Подарок Марии", user_id: ObjectId("65dd0e91325f1b9354de3d19") },
      { amount: 5000, date: new Date("2024-01-10"), description: "Подарок Ольге", user_id: ObjectId("65dd0e91325f1b9354de3d1a") }
    ],
    added_by: ObjectId('65dd0e6a325f1b9354de3d17')
  },
  {
    _id: ObjectId(),
    category_id: ObjectId('65dd1be8325f1b9354de3d1f'),
    name: "Подарок за февраль",
    type: "доход",
    transactions: [
      { amount: 3000, date: new Date("2024-02-14"), description: "Открытка Ольге", user_id: ObjectId("65dd0e91325f1b9354de3d1a") }
    ],
    added_by: ObjectId('65dd0e6a325f1b9354de3d17')
  }
]);
