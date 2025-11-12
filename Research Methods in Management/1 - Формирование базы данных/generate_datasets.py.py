#  1) (п.5.1) Формирует базу из 20 строк и 3 столбцов,
#     каждый столбец ~ N(с заданными СЗ и СКО).
#  2) (Вариант 2) "Компетенции персонала":
#     40 сотрудников, 4 входа (оценки 1..10), 5-й столбец — класс (1/2),
#     по 20 человек на класс, метод Монте-Карло (т.е. случайная генерация).
#  3) Поля/заголовки И ВЫВОД
#  4) Всё сохраняется ТОЛЬКО в TSV (табличный .tsv) в текущую папку.
#  5) (доп. к п.4*) Генерирует 100 значений возраста (25..45) и сохраняет в TSV.

import os
import csv
from typing import Sequence, Tuple
import numpy as np

# --- Настройки воспроизводимости ---
SEED = 2025
rng = np.random.default_rng(SEED)

# ---------- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ----------

def save_tsv(matrix: np.ndarray, header: Sequence[str], filepath: str) -> None:
    """
    Сохраняет numpy-матрицу в табличный TXT (TSV) с заголовком (UTF-8).
    """
    os.makedirs(os.path.dirname(filepath) or ".", exist_ok=True)
    with open(filepath, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f, delimiter="\t")
        writer.writerow(header)
        for row in matrix:
            out_row = []
            for x in row:
                xv = float(x)
                out_row.append(str(int(xv)) if xv.is_integer() else f"{xv:.3f}")
            writer.writerow(out_row)


def print_table(matrix: np.ndarray, header: Sequence[str], max_rows: int = 10, title: str | None = None) -> None:
    """
    Печатает компактную таблицу в консоль с русскими заголовками.
    max_rows — максимум строк для предпросмотра (остальное помечается как ...).
    """
    if title:
        print(f"\n{title}")

    rows = matrix.tolist()
    n = len(rows)
    show_n = min(n, max_rows)

    # Подготовка строк с форматированием
    str_rows = [[str(int(x)) if float(x).is_integer() else f"{float(x):.3f}" for x in row] for row in rows[:show_n]]
    widths = [len(h) for h in header]
    for r in str_rows:
        for j, cell in enumerate(r):
            widths[j] = max(widths[j], len(cell))

    # Линия
    def line(sep_left="┌", sep_mid="┬", sep_right="┐", fill="─"):
        parts = []
        for w in widths:
            parts.append(fill * (w + 2))
        return sep_left + sep_mid.join(parts) + sep_right

    # Печать
    print(line())
    header_row = "│ " + " │ ".join(h.ljust(widths[i]) for i, h in enumerate(header)) + " │"
    print(header_row)
    print(line("├", "┼", "┤"))

    for r in str_rows:
        row_line = "│ " + " │ ".join(r[i].ljust(widths[i]) for i in range(len(widths))) + " │"
        print(row_line)

    if n > show_n:
        dots = ["…"] * len(widths)
        print("│ " + " │ ".join(dots[i].ljust(widths[i]) for i in range(len(widths))) + " │")

    print(line("└", "┴", "┘"))


# ---------- П.5.1: НОРМАЛЬНО РАСПРЕДЕЛЁННЫЕ ПРИЗНАКИ 20x3 ----------

def generate_task_5_1(n_rows: int = 20) -> Tuple[np.ndarray, Sequence[str]]:
    """
    Генерирует таблицу 20x3:
      X1 ~ N(10, 2^2), X2 ~ N(20, 3^2), X3 ~ N(70, 5^2)
    Возвращает (матрица, заголовок).
    """
    means = [10, 20, 70]
    stds = [2, 3, 5]

    X = np.column_stack([
        rng.normal(loc=means[0], scale=stds[0], size=n_rows),
        rng.normal(loc=means[1], scale=stds[1], size=n_rows),
        rng.normal(loc=means[2], scale=stds[2], size=n_rows),
    ])

    X = np.round(X, 3)

    header = [
        "X1 (СЗ=10; СКО=2)",
        "X2 (СЗ=20; СКО=3)",
        "X3 (СЗ=70; СКО=5)",
    ]

    # Краткая проверка эмпирических СЗ и СКО
    print("\n[Проверка п.5.1] Эмпирические оценки по сгенерированным данным:")
    for j, (m, s) in enumerate(zip(means, stds), start=1):
        col = X[:, j - 1]
        print(f"  X{j}: среднее = {col.mean():.3f} (ожидалось {m}), СКО = {col.std(ddof=1):.3f} (ожидалось {s})")

    return X, header


# ---------- ВАРИАНТ 2: КОМПЕТЕНЦИИ ПЕРСОНАЛА (40x5) ----------

def sample_trunc_normal_int(mu: float, sigma: float, low: int, high: int, n: int) -> np.ndarray:
    """
    Выборка размера n из N(mu, sigma^2), обрезанная в [low, high],
    затем округление до целых и клип к [low, high].
    Реализация: rejection sampling (корректнее простого clip()).
    """
    collected = []
    batch = max(64, n * 2)
    while len(collected) < n:
        cand = rng.normal(loc=mu, scale=sigma, size=batch)
        ok = cand[(cand >= low) & (cand <= high)]
        collected.extend(ok.tolist())
    arr = np.array(collected[:n])
    arr = np.rint(arr)             # округление к ближайшему целому
    arr = np.clip(arr, low, high)  # подгонка в границы шкалы
    return arr.astype(int)


def generate_competency_class(n_per_class: int,
                              mus: Tuple[float, float, float, float],
                              sigmas: Tuple[float, float, float, float],
                              cls_label: int) -> np.ndarray:
    """
    Блок из n_per_class сотрудников для одного класса.
    mus/sigmas заданы для каналов:
      (оценка руководителя, подчинённых, коллег, самооценка).
    """
    mgr  = sample_trunc_normal_int(mus[0], sigmas[0], 1, 10, n_per_class)
    sub  = sample_trunc_normal_int(mus[1], sigmas[1], 1, 10, n_per_class)
    peer = sample_trunc_normal_int(mus[2], sigmas[2], 1, 10, n_per_class)
    selfr= sample_trunc_normal_int(mus[3], sigmas[3], 1, 10, n_per_class)
    cls  = np.full(n_per_class, cls_label, dtype=int)
    return np.column_stack([mgr, sub, peer, selfr, cls])


def generate_competencies_dataset() -> Tuple[np.ndarray, Sequence[str]]:
    """
    Итог: 40 строк и 5 столбцов (4 входных признака + «Класс»).
    Класс 1 — высокие оценки, Класс 2 — низкие оценки.
    Диапазон шкалы: 1..10, целые.
    """
    n_per_class = 20

    # Средние и СКО задаём так, чтобы класс 1 был реально "высоким", а класс 2 — "низким".
    # Самооценка — чуть выше (типичное смещение).
    mus_cls1 = (7.8, 7.2, 7.6, 8.2)
    sig_cls1 = (1.2, 1.2, 1.2, 1.1)

    mus_cls2 = (3.2, 3.8, 3.4, 4.4)
    sig_cls2 = (1.2, 1.3, 1.2, 1.1)

    data_c1 = generate_competency_class(n_per_class, mus_cls1, sig_cls1, cls_label=1)
    data_c2 = generate_competency_class(n_per_class, mus_cls2, sig_cls2, cls_label=2)
    data = np.vstack([data_c1, data_c2])

    # Перемешаем строки (но воспроизводимо, т.к. общий rng с SEED)
    rng.shuffle(data)

    header = ["Оценка руководителя", "Оценка подчинённых", "Оценка коллег", "Самооценка", "Класс"]

    # Краткая сводка
    print("\n[Компетенции] Средние оценки по классам:")
    for cls in [1, 2]:
        subset = data[data[:, -1] == cls][:, :-1]
        m = subset.mean(axis=0)
        print(
            f"  Класс {cls}: "
            f"Рук-ль={m[0]:.2f}, Подчин.={m[1]:.2f}, Коллеги={m[2]:.2f}, Самооц.={m[3]:.2f}"
        )

    return data, header


# ---------- (ДОП.) П.4*: 100 ВОЗРАСТОВ 25..45 ----------

def generate_ages_demo(n: int = 100) -> Tuple[np.ndarray, Sequence[str]]:
    """
    Генерирует n целых возрастов в диапазоне [25, 45] (включительно).
    """
    ages = rng.integers(25, 46, size=n)  # верхняя граница 46 не включается
    ages = ages.reshape(-1, 1)
    header = ["Возраст кандидата"]
    return ages, header


# ---------- MAIN ----------

def main() -> None:
    # ---- П.5.1 ----
    data_5_1, header_5_1 = generate_task_5_1(n_rows=20)
    file_5_1_tsv = "п5_1_нормально_распределённые_признаки.tsv"
    save_tsv(data_5_1, header_5_1, file_5_1_tsv)

    print_table(data_5_1, header_5_1, max_rows=10, title="Предпросмотр п.5.1 (первые строки):")
    print("[ФАЙЛ п.5.1]")
    print(f"  TSV: {os.path.abspath(file_5_1_tsv)}")

    # ---- Вариант 2: Компетенции ----
    data_comp, header_comp = generate_competencies_dataset()
    file_comp_tsv = "вариант2_компетенции_персонала.tsv"
    save_tsv(data_comp, header_comp, file_comp_tsv)

    print_table(data_comp, header_comp, max_rows=12, title="Предпросмотр Вариант 2 (первые строки):")
    print("[ФАЙЛ Вариант 2]")
    print(f"  TSV: {os.path.abspath(file_comp_tsv)}")

    # ---- (доп.) п.4*: Возраст 100 значений ----
    ages, header_ages = generate_ages_demo(n=100)
    file_ages_tsv = "п4_возраст_кандидатов_100.tsv"
    save_tsv(ages, header_ages, file_ages_tsv)

    print_table(ages, header_ages, max_rows=15, title="Предпросмотр п.4* (первые строки возрастов):")
    print("[ФАЙЛ п.4*]")
    print(f"  TSV: {os.path.abspath(file_ages_tsv)}")

    print("\nГотово ✅")

if __name__ == "__main__":
    main()