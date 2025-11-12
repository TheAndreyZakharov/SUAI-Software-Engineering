# generate_startup_nn_data_txt.py
# ------------------------------------------------------------
# ЛР2: НС (оценка успеха стартапа) — данные ТОЛЬКО в .txt
#
# Что генерим:
#   - X1 (компетентность команды)     : 1..10
#   - X2 (рыночные возможности), %     : 0..100
#   - X3 (ликвидность продукта)        : 1..10
#   - X4 (конкурентное окружение), %   : 0..100 (больше = сильнее конкуренты)
#   - X5 (необходимость доп. вложений) : 1..10 (больше = нужно больше денег)
#   - Y (класс успеха): 1=исключительный, 2=высокий, 3=низкий
#
# Файлы на выходе (ВСЕ .txt и БЕЗ заголовков — удобно импортировать в nnstart/nprtool):
#   startup_raw_numeric.txt            (N x 6)  X1..X5 Y
#   startup_inputs_5xN.txt             (5 x N)  входы (наблюдения по столбцам)
#   startup_targets_1xN.txt            (1 x N)  классы 1..3
#   startup_targets_onehot_3xN.txt     (3 x N)  one-hot цели (для nprtool идеал)
#   startup_inputs_brackets.txt        MATLAB-матрица для Inputs (копи/паст)
#   startup_targets_brackets.txt       MATLAB-строка  для Targets (классы)
#   startup_targets_onehot_brackets.txt MATLAB-матрица one-hot (копи/паст)
#
# Зависимости: numpy
# Запуск: python generate_startup_nn_data_txt.py
# ------------------------------------------------------------

import os
import numpy as np

# ------------ ПАРАМЕТРЫ ------------
SEED = 2025         # фиксируем для воспроизводимости (можно менять)
N_PER_CLASS = 30    # по 30 на класс => 90 наблюдений
OUT_DIR = "."

rng = np.random.default_rng(SEED)

# ------------ УТИЛИТЫ ------------

def trunc_normal(mu: float, sigma: float, low: float, high: float, n: int) -> np.ndarray:
    """Усечённое N(mu, sigma^2) методом отбраковки (rejection sampling)."""
    res = []
    batch = max(64, n*2)
    while len(res) < n:
        cand = rng.normal(mu, sigma, size=batch)
        ok = cand[(cand >= low) & (cand <= high)]
        res.extend(ok.tolist())
    return np.array(res[:n])

def save_txt_numeric(matrix: np.ndarray, path: str, float_decimals: int = 1) -> None:
    """
    Сохраняет массив в .txt без заголовка.
    Разделитель — пробел, десятичная точка — ".", локаль не влияет.
    """
    os.makedirs(os.path.dirname(path) or ".", exist_ok=True)
    # Формат: целые как %d, иначе с 1 знаком после запятой
    def fmt(x):
        return f"{int(x)}" if float(x).is_integer() else f"{x:.{float_decimals}f}"
    with open(path, "w", encoding="utf-8") as f:
        for row in matrix:
            f.write(" ".join(fmt(v) for v in row) + "\n")

def to_matlab_brackets(rows_as_lists) -> str:
    """
    Преобразует список строк (каждая — список чисел) в MATLAB-матрицу:
    [ r1 ... ; r2 ... ; ... ]
    """
    def fmt(x): return f"{int(x)}" if float(x).is_integer() else f"{x:.1f}"
    row_strs = [" ".join(fmt(v) for v in row) for row in rows_as_lists]
    return "[ " + " ;\n  ".join(row_strs) + " ]"

# ------------ ГЕНЕРАЦИЯ ДАННЫХ ------------

def gen_class(n: int, label: int) -> np.ndarray:
    """
    Блок из n наблюдений данного класса (X1..X5, Y).
    1 — исключительный; 2 — высокий; 3 — низкий.
    """
    if label == 1:
        x1 = trunc_normal(8.0, 1.0, 1, 10, n)
        x2 = trunc_normal(75, 10, 0, 100, n)
        x3 = trunc_normal(8.5, 1.0, 1, 10, n)
        x4 = trunc_normal(15, 8, 0, 100, n)   # меньше — лучше
        x5 = trunc_normal(2.0, 0.8, 1, 10, n) # меньше — лучше
    elif label == 2:
        x1 = trunc_normal(6.0, 1.0, 1, 10, n)
        x2 = trunc_normal(55, 12, 0, 100, n)
        x3 = trunc_normal(6.5, 1.0, 1, 10, n)
        x4 = trunc_normal(50, 12, 0, 100, n)
        x5 = trunc_normal(6.0, 1.0, 1, 10, n)
    else:  # 3
        x1 = trunc_normal(3.0, 1.0, 1, 10, n)
        x2 = trunc_normal(25, 15, 0, 100, n)
        x3 = trunc_normal(2.5, 1.0, 1, 10, n)
        x4 = trunc_normal(85, 8, 0, 100, n)   # больше — сильная конкуренция
        x5 = trunc_normal(9.0, 0.8, 1, 10, n) # больше — много денег нужно
    y = np.full(n, label, dtype=float)
    return np.column_stack([x1, x2, x3, x4, x5, y])

def main() -> None:
    # 1) Полный датасет
    data = np.vstack([gen_class(N_PER_CLASS, 1),
                      gen_class(N_PER_CLASS, 2),
                      gen_class(N_PER_CLASS, 3)])
    rng.shuffle(data)

    # 2) Сохраняем RAW (N x 6) — числа, без заголовка
    raw_path = os.path.join(OUT_DIR, "startup_raw_numeric.txt")
    save_txt_numeric(data, raw_path)

    # 3) Разворачиваем для nprtool: Inputs 5xN, Targets (1xN и 3xN)
    inputs = data[:, :5].T                            # 5 x N (наблюдения по столбцам)
    targets = data[:, 5].astype(int).reshape(1, -1)   # 1 x N (классы 1..3)
    # one-hot 3xN
    targets_onehot = np.zeros((3, targets.shape[1]), dtype=int)
    targets_onehot[targets[0]-1, np.arange(targets.shape[1])] = 1

    save_txt_numeric(inputs, os.path.join(OUT_DIR, "startup_inputs_5xN.txt"))
    save_txt_numeric(targets, os.path.join(OUT_DIR, "startup_targets_1xN.txt"))
    save_txt_numeric(targets_onehot, os.path.join(OUT_DIR, "startup_targets_onehot_3xN.txt"))

    # 4) MATLAB-формы для копипаста (на всякий случай)
    with open(os.path.join(OUT_DIR, "startup_inputs_brackets.txt"), "w", encoding="utf-8") as f:
        f.write(to_matlab_brackets(inputs.tolist()) + "\n")
    with open(os.path.join(OUT_DIR, "startup_targets_brackets.txt"), "w", encoding="utf-8") as f:
        f.write(to_matlab_brackets(targets.tolist()) + "\n")
    with open(os.path.join(OUT_DIR, "startup_targets_onehot_brackets.txt"), "w", encoding="utf-8") as f:
        f.write(to_matlab_brackets(targets_onehot.tolist()) + "\n")

    # 5) Короткий анонс
    print("\n[Готово] Основные файлы (.txt, без заголовков):")
    for name in [
        "startup_raw_numeric.txt",
        "startup_inputs_5xN.txt",
        "startup_targets_1xN.txt",
        "startup_targets_onehot_3xN.txt",
        "startup_inputs_brackets.txt",
        "startup_targets_brackets.txt",
        "startup_targets_onehot_brackets.txt",
    ]:
        print("  ", os.path.abspath(os.path.join(OUT_DIR, name)))
    print("\nИмпорт в MATLAB (nnstart → Pattern Recognition → Import → From File):")
    print("  Predictors: startup_inputs_5xN.txt  (Observations in: Columns)")
    print("  Responses : startup_targets_onehot_3xN.txt  (Observations in: Columns)")

if __name__ == "__main__":
    main()