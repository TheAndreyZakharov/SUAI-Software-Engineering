import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from statsmodels.tsa.seasonal import seasonal_decompose

# Создание фиктивных данных
data = pd.DataFrame({
    "Дата": pd.date_range(start="2021-01-01", periods=365, freq='D'),
    "Товар A Продажи": np.random.randint(140, 180, 365) + 20*np.sin(np.linspace(0, 2*np.pi, 365)),
    "Товар A Цена": np.random.uniform(18, 22, 365),
    "Товар B Продажи": np.random.randint(90, 120, 365) + 15*np.sin(np.linspace(0, 2*np.pi, 365)),
    "Товар B Цена": np.random.uniform(28, 32, 365),
    "Товар C Продажи": np.random.randint(190, 230, 365) + 25*np.sin(np.linspace(0, 2*np.pi, 365)),
    "Товар C Цена": np.random.uniform(23, 27, 365)
})

product_columns = ['Товар A Продажи', 'Товар B Продажи', 'Товар C Продажи']



# Функция для расчета EOQ
def calculate_eoq(demand, order_cost, holding_cost):
    return np.sqrt((2 * demand * order_cost) / holding_cost)



# Функция для имитации JIT подхода
def simulate_jit(sales_data, threshold):
    jit_points = sales_data[sales_data <= threshold]
    return jit_points


order_cost = 100
holding_cost = 5
jit_threshold = 150  # Пороговое значение для JIT



# Визуализация прогноза будущего спроса и сезонного эффекта
future_dates = pd.date_range(start=data["Дата"].iloc[-1] + pd.Timedelta(days=1), periods=90, freq='D')




# Функция для анализа ценовой эластичности спроса
def price_elasticity_analysis(sales_data, price_data):
    sales_data = sales_data.to_numpy().reshape(-1, 1)
    price_data = price_data.to_numpy().reshape(-1, 1)
    regression_model = LinearRegression().fit(price_data, sales_data)
    elasticity = regression_model.coef_[0][0]
    return elasticity

# Функция для сезонного анализа продаж
def seasonal_analysis(sales_data):
    result = seasonal_decompose(sales_data, model='additive', period=30)
    return result.seasonal

# Прогноз будущего спроса
def demand_forecast(sales_data):
    model = LinearRegression()
    days = np.array(range(len(sales_data))).reshape(-1, 1)
    model.fit(days, sales_data)
    # Изменение размера future_days на 90 дней
    future_days = np.array(range(len(sales_data), len(sales_data) + 90)).reshape(-1, 1)
    future_forecast = model.predict(future_days)
    return future_forecast





plt.figure(figsize=(20, 25))


# Общий график продаж всех товаров
plt.subplot(5, 2, 1)
total_sales = pd.Series(dtype=float)
for column in product_columns:
    total_sales = total_sales.add(data[column], fill_value=0)
    plt.plot(data['Дата'], data[column], label=column)
plt.title('Общий график продаж всех товаров')
plt.xlabel('Дата')
plt.ylabel('Продажи')
plt.legend()

# Обработка данных для каждого товара
for i, column in enumerate(product_columns, start=2):
    data[f'{column} Moving Average'] = data[column].rolling(window=7).mean().bfill()
    data[f'{column} EOQ'] = calculate_eoq(data[column].sum(), order_cost, holding_cost)
    jit_points = simulate_jit(data[column], jit_threshold)
    plt.subplot(5, 2, i)
    plt.plot(data['Дата'], data[column], label=f'{column} Продажи')
    plt.plot(data['Дата'], data[f'{column} Moving Average'], label=f'{column} Скользящее среднее', linestyle='--')
    plt.scatter(data['Дата'][jit_points.index], data[column][jit_points.index], color='red', label='JIT точки заказа')
    plt.title(f'График продаж для {column}')
    plt.xlabel('Дата')
    plt.ylabel('Продажи')
    plt.legend()

plt.subplot(5, 2, 5)
plt.plot(data['Дата'], total_sales, label='Суммарные продажи')
plt.title('График суммарных продаж')
plt.xlabel('Дата')
plt.ylabel('Продажи')
plt.legend()

# Прогноз для Товара A
sales_data_a = data['Товар A Продажи']
future_forecast_a = demand_forecast(sales_data_a)
plt.subplot(5, 2, 6)
plt.plot(data['Дата'], sales_data_a, label='Фактические продажи')
plt.plot(future_dates, future_forecast_a, label='Прогноз', linestyle='--')
plt.title('Прогноз спроса для Товара A')
plt.xlabel('Дата')
plt.ylabel('Продажи')
plt.legend()

# Прогноз для Товара B
sales_data_b = data['Товар B Продажи']
future_forecast_b = demand_forecast(sales_data_b)
plt.subplot(5, 2, 7)
plt.plot(data['Дата'], sales_data_b, label='Фактические продажи')
plt.plot(future_dates, future_forecast_b, label='Прогноз', linestyle='--')
plt.title('Прогноз спроса для Товара B')
plt.xlabel('Дата')
plt.ylabel('Продажи')
plt.legend()

# Прогноз для Товара C
sales_data_c = data['Товар C Продажи']
future_forecast_c = demand_forecast(sales_data_c)
plt.subplot(5, 2, 8)
plt.plot(data['Дата'], sales_data_c, label='Фактические продажи')
plt.plot(future_dates, future_forecast_c, label='Прогноз', linestyle='--')
plt.title('Прогноз спроса для Товара C')
plt.xlabel('Дата')
plt.ylabel('Продажи')
plt.legend()

plt.tight_layout()
plt.subplots_adjust(hspace=0.5)  # Увеличение вертикального пространства между графиками
plt.show()





# Вывод дополнительной аналитической информации и рекомендаций
print("Дополнительный анализ и рекомендации:")
for column in product_columns:
    total_sales = data[column].sum()
    average_price = data[f'{column[:-8]} Цена'].mean()
    eoq = data[f'{column} EOQ'].iloc[0]
    jit_points_count = len(simulate_jit(data[column], jit_threshold))

    # Рекомендации по закупке
    recommended_order_frequency = round(365 / (eoq / (total_sales / 365)))

    # Дополнительные рекомендации
    std_demand = data[column].std()
    safety_stock = round(std_demand * 1.65)  # Предположим, что уровень сервиса 95%
    lead_time = 10  # Предположим, что среднее время выполнения заказа составляет 10 дней

    # Расчет коэффициента оборачиваемости запасов
    average_inventory = data[column].mean()
    turnover_rate = total_sales / average_inventory

    # Расчет точки безубыточности (примерные значения фиксированных и переменных издержек)
    fixed_costs = 10000  # Примерная сумма фиксированных издержек
    variable_costs = average_price * 0.6  # Примерно 60% от цены товара
    break_even_point = fixed_costs / (average_price - variable_costs)

    sales_data = data[column]
    price_data = data[f"{column[:-8]} Цена"]

    total_sales = sales_data.sum()
    average_price = price_data.mean()
    eoq = calculate_eoq(total_sales, order_cost, holding_cost)
    jit_points = simulate_jit(sales_data, jit_threshold)

    elasticity = price_elasticity_analysis(sales_data, price_data)
    seasonal_effect = seasonal_analysis(sales_data)
    future_sales_forecast = demand_forecast(sales_data)


    print(
        f'{column}: \n'
        f'  - Общие продажи: {total_sales} единиц \n'
        f'  - Средняя цена: {average_price:.2f} \n'
        f'  - EOQ (оптимальный размер заказа): {eoq:.2f} единиц \n'
        f'  - JIT точек заказа: {jit_points_count} \n'
        f'  - Рекомендуемая частота заказов: {recommended_order_frequency} раз(а) в год\n'
        f'  - Запас безопасности: {safety_stock} единиц \n'
        f'  - Рекомендуемый уровень запасов до нового заказа: {eoq + safety_stock} единиц \n'
        f'  - Время выполнения заказа: {lead_time} дней\n'
        f'  - Совет: Пересматривайте уровень запасов каждые {lead_time} дней и дополняйте до уровня {eoq + safety_stock} единиц при необходимости\n'
        f'  - Коэффициент оборачиваемости запасов: {turnover_rate:.2f} \n'
        f'  - Точка безубыточности: {break_even_point:.0f} единиц \n'
        f"  - Сезонный эффект: максимальный влияние {seasonal_effect.max():.2f}, минимальный {seasonal_effect.min():.2f}\n"

    )





