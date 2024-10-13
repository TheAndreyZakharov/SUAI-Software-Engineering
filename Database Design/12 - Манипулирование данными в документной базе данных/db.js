db.categories.aggregate([
  { $match: { name: /спорт/i } },
  { $lookup: {
      from: "items",
      localField: "_id",
      foreignField: "category_id",
      as: "items"
  }},
  { $unwind: "$items" },
  { $project: { "items.name": 1, _id: 0 } }
])



db.items.aggregate([
  { $match: { type: "доход" } },
  { $unwind: "$transactions" },
  { $group: {
      _id: { month: { $month: "$transactions.date" }, year: { $year: "$transactions.date" } },
      uniqueIncomeItems: { $addToSet: "$name" }
  }},
  { $project: {
      month: "$_id.month",
      year: "$_id.year",
      numberOfUniqueIncomeItems: { $size: "$uniqueIncomeItems" },
      _id: 0
  }},
  { $match: { numberOfUniqueIncomeItems: { $gt: 1 } } }
]);



var currentDate = new Date();
var currentYear = currentDate.getFullYear();

db.items.aggregate([
  { $match: { 
      type: "расход", 
      "transactions.date": { 
          $gte: new Date(currentYear, 0, 1), 
          $lt: currentDate 
      } 
  }},
  { $unwind: "$transactions" },
  { $group: { _id: "$category_id", totalSpent: { $sum: "$transactions.amount" } } },
  { $sort: { totalSpent: -1 } },
  { $group: { _id: null, maxSpent: { $max: "$totalSpent" }, categories: { $push: { category_id: "$_id", totalSpent: "$totalSpent" } } } },
  { $unwind: "$categories" },
  { $match: { $expr: { $eq: ["$categories.totalSpent", "$maxSpent"] } } }, // Исправление здесь
  { $lookup: { 
      from: "categories",
      localField: "categories.category_id",
      foreignField: "_id",
      as: "categoryInfo"
  }},
  { $unwind: "$categoryInfo" },
  { $project: { _id: 0, totalSpent: "$categories.totalSpent", "categoryInfo.name": 1, "categoryInfo.type": 1 } }
]);






db.categories.aggregate([
  {
    $lookup: {
      from: "items",
      localField: "_id",
      foreignField: "category_id",
      as: "items"
    }
  },
  {
    $project: {
      name: 1,
      type: 1,
      hasFebTransactions: {
        $anyElementTrue: {
          $map: {
            input: "$items",
            as: "item",
            in: {
              $and: [
                { $eq: ["$$item.type", "расход"] },
                { $eq: [{ $size: { $filter: { input: "$$item.transactions", as: "transaction", cond: { $eq: [{ $month: "$$transaction.date" }, 2] } } } }, 0] }
              ]
            }
          }
        }
      }
    }
  },
  {
    $project: { name: 1, _id: 0 }
  }
])







db.items.aggregate([
  { $group: { _id: "$added_by", itemCount: { $sum: 1 } } },
  { $group: { _id: "$itemCount", users: { $push: "$_id" } } },
  { $sort: { "_id": 1 } },
  { $limit: 1 },
  { $unwind: "$users" },
  { $lookup: {
      from: "users",
      localField: "users",
      foreignField: "_id",
      as: "user"
  }},
  { $unwind: "$user" },
  { $project: { _id: 0, name: "$user.name", surname: "$user.surname", itemCount: "$_id" } }
])







db.items.updateOne(
  { "transactions.description": "Покупка курицы" },
  { $set: { "transactions.$.description": "Покупка куриного филе" } }
)

db.items.updateOne(
  { "transactions.description": "Покупка куриного филе" },
  { $set: { "transactions.$.description": "Покупка курицы" } }
)






db.users.updateOne(
  { name: "Алексей", surname: "Алексеев" },
  { $set: { name: "Александр" } }
)


db.users.updateOne(
  { name: "Александр", surname: "Алексеев" },
  { $set: { name: "Алексей" } }
)






db.items.updateOne(
  { name: "Напитки" },
  { $push: { transactions: { amount: 100, date: new Date(), description: "Тестовая покупка", user_id: ObjectId() } } }
)

db.items.updateOne(
  { name: "Напитки" },
  { $pull: { transactions: { description: "Тестовая покупка" } } }
)






db.categories.insertOne({ name: "Тестовая категория", type: "расход" })

db.categories.deleteOne({ name: "Тестовая категория" })


