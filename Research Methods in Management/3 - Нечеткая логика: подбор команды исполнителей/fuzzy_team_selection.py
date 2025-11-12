import os
import csv
import numpy as np

import matplotlib
matplotlib.use("Agg")  # сохраняем в файлы, без окон
import matplotlib.pyplot as plt
plt.rcParams['font.family'] = 'DejaVu Sans'  # кириллица в подписях

import skfuzzy as fuzz
from skfuzzy import control as ctrl

# --- Папка для всех результатов ---
OUT_DIR = "ЛР3_результаты"

# ---------- 1) СБОРКА FIS (Мамдани) ----------

def build_fis():
    # Универсы значений
    age = ctrl.Antecedent(np.linspace(20, 45, 501), 'age')
    edu = ctrl.Antecedent(np.linspace(1, 10, 451), 'edu')
    exp = ctrl.Antecedent(np.linspace(1, 5, 401), 'exp')
    soft = ctrl.Antecedent(np.linspace(1, 10, 451), 'soft')
    quality = ctrl.Consequent(np.linspace(0, 100, 1001), 'quality', defuzzify_method='centroid')

    # Функции принадлежности
    age['молодой']          = fuzz.gaussmf(age.universe, 24.0, 2.5)   # mean, sigma
    age['средний']          = fuzz.gaussmf(age.universe, 32.5, 3.5)
    age['выше_среднего']    = fuzz.gaussmf(age.universe, 40.0, 3.0)

    edu['бакалавр']         = fuzz.trapmf(edu.universe,  [1, 1, 5, 7])
    edu['магистр']          = fuzz.trapmf(edu.universe,  [6, 8, 10, 10])

    exp['малый']            = fuzz.trimf(exp.universe,   [1, 1, 3])
    exp['большой']          = fuzz.trimf(exp.universe,   [3, 5, 5])

    # Полное покрытие шкалы 1..10 без «дыр»
    soft['хорошо']          = fuzz.trapmf(soft.universe, [1, 1, 7.5, 9])
    soft['отлично']         = fuzz.trapmf(soft.universe, [7.5, 9, 10, 10])

    quality['малое']        = fuzz.trimf(quality.universe, [0, 0, 40])
    quality['среднее']      = fuzz.trimf(quality.universe, [30, 50, 70])
    quality['высокое']      = fuzz.trimf(quality.universe, [60, 100, 100])

    # Правила (24) через «подсчёт сильных условий»
    age_terms  = ['молодой', 'средний', 'выше_среднего']
    edu_terms  = ['бакалавр', 'магистр']
    exp_terms  = ['малый', 'большой']
    soft_terms = ['хорошо', 'отлично']

    rules = []
    text_rules = []
    for a in age_terms:
        for e in edu_terms:
            for x in exp_terms:
                for s in soft_terms:
                    strong = 0
                    if a in ('средний', 'выше_среднего'): strong += 1
                    if e == 'магистр': strong += 1
                    if x == 'большой': strong += 1
                    if s == 'отлично': strong += 1

                    if strong >= 3:
                        cons = 'высокое'
                    elif strong == 2:
                        cons = 'среднее'
                    else:
                        cons = 'малое'

                    antecedent = (age[a] & edu[e] & exp[x] & soft[s])
                    rules.append(ctrl.Rule(antecedent, quality[cons]))
                    text_rules.append(f"ЕСЛИ age={a} И edu={e} И exp={x} И soft={s} ТО quality={cons}")

    system = ctrl.ControlSystem(rules)
    return system, (age, edu, exp, soft, quality), rules, text_rules

# ---------- 2) УТИЛИТЫ ----------

def p(fn):  # путь в папку результатов
    return os.path.join(OUT_DIR, fn)

def save_tsv(path, header, rows):
    with open(path, "w", newline="", encoding="utf-8") as f:
        w = csv.writer(f, delimiter="\t")
        if header: w.writerow(header)
        w.writerows(rows)

def eval_candidate(system, a, e, x, s):
    sim = ctrl.ControlSystemSimulation(system, flush_after_run=1)
    sim.input['age']  = float(a)
    sim.input['edu']  = float(e)
    sim.input['exp']  = float(x)
    sim.input['soft'] = float(s)
    sim.compute()
    out = sim.output.get('quality', None)
    if out is None or np.isnan(out):
        return 0.0
    return float(out)

def save_view_marked(var, filepath, crisp=None, sim=None, title=None):
    """
    Рисует график ФП как обычно, + вертикальная пунктирная линия на crisp-значении.
    Для выхода можно передать crisp = sim.output['quality'].
    """
    plt.ioff()
    var.view(sim=sim)           # базовый график из skfuzzy
    ax = plt.gca()
    if crisp is not None:
        ax.axvline(float(crisp), linestyle='--', linewidth=2)
        ax.text(float(crisp), 1.02, f"{float(crisp):.1f}",
                rotation=90, va='bottom', ha='center', fontsize=9)
    if title:
        ax.set_title(title)
    fig = plt.gcf()
    fig.savefig(filepath, dpi=150, bbox_inches='tight')
    plt.close(fig)

def print_table(rows, header, title=None, max_rows=10):
    if title: print(f"\n{title}")
    show = rows[:max_rows]
    widths = [len(h) for h in header]
    for r in show:
        for i, cell in enumerate(r):
            widths[i] = max(widths[i], len(str(cell)))
    def line(L='┌', M='┬', R='┐', fill='─'):
        return L + M.join(fill*(w+2) for w in widths) + R
    print(line())
    print("│ " + " │ ".join(str(h).ljust(widths[i]) for i, h in enumerate(header)) + " │")
    print(line('├','┼','┤'))
    for r in show:
        print("│ " + " │ ".join(str(r[i]).ljust(widths[i]) for i in range(len(header))) + " │")
    if len(rows) > max_rows:
        print("│ " + " │ ".join("…".ljust(widths[i]) for i in range(len(header))) + " │")
    print(line('└','┴','┘'))

# ---------- 3) ОСНОВНОЙ СЦЕНАРИЙ ----------

def main():
    os.makedirs(OUT_DIR, exist_ok=True)

    system, (age, edu, exp, soft, quality), rules, text_rules = build_fis()

    # Инфо + правила
    with open(p("инфо_система_НЛ.txt"), "w", encoding="utf-8") as f:
        f.write("Тип: Мамдани, дефаззификация = центроид (centroid)\n")
        f.write(f"Число правил: {len(rules)}\n")
        f.write("Входы: возраст[20..45], образование[1..10], опыт[1..5], софт[1..10]; Выход: качество[0..100]\n")
    with open(p("правила_НЛ.txt"), "w", encoding="utf-8") as f:
        for i, r in enumerate(text_rules, 1):
            f.write(f"{i:02d}. {r}\n")

    # ФП (как в редакторе FIS)
    save_view_marked(age,     p("фп_возраст.png"))
    save_view_marked(edu,     p("фп_образование.png"))
    save_view_marked(exp,     p("фп_опыт.png"))
    save_view_marked(soft,    p("фп_софт.png"))
    save_view_marked(quality, p("фп_качество.png"))

    # --- Генерация ровно 100 кандидатов (полностью случайно, без фиксированного seed) ---
    rng = np.random.default_rng()  # каждый запуск — новые данные
    N = 100
    ages  = rng.integers(20, 46, size=N)
    edus  = rng.integers(1, 11, size=N)
    exps  = rng.integers(1, 6,  size=N)
    softs = rng.integers(1, 11, size=N)

    batch = []
    for i in range(N):
        q = eval_candidate(system, ages[i], edus[i], exps[i], softs[i])
        batch.append([i+1, int(ages[i]), int(edus[i]), int(exps[i]), int(softs[i]), f"{q:.1f}"])

    # Сортировка по качеству
    batch_sorted = sorted(batch, key=lambda r: float(r[-1]), reverse=True)
    save_tsv(p("результаты_100_кандидатов.tsv"),
             ["ID", "Возраст", "Образование(1-10)", "Опыт(лет)", "Софт(1-10)", "Качество(0-100)"],
             batch_sorted)

    print_table(batch_sorted[:10],
                ["ID", "Возраст", "Образование(1-10)", "Опыт(лет)", "Софт(1-10)", "Качество(0-100)"],
                title="Топ-10 из 100 (по качеству)")

    # Порог для команды
    THRESH = 70.0
    team = [r for r in batch_sorted if float(r[-1]) >= THRESH]
    save_tsv(p("команда_порог_70.tsv"),
             ["ID", "Возраст", "Образование(1-10)", "Опыт(лет)", "Софт(1-10)", "Качество(0-100)"],
             team)
    print(f"\nПорог команды: ≥ {THRESH:.0f} баллов — выбрано {len(team)} из {N} кандидатов.")

    # Просмотр переменных/выхода для Топ-1 кандидата (как Variable Viewer)
    if batch_sorted:
        top = batch_sorted[0]  # [ID, age, edu, exp, soft, quality_str]

        sim = ctrl.ControlSystemSimulation(system, flush_after_run=1)
        sim.input['age']  = float(top[1])
        sim.input['edu']  = float(top[2])
        sim.input['exp']  = float(top[3])
        sim.input['soft'] = float(top[4])
        sim.compute()
        q_crisp = float(sim.output['quality'])

        save_view_marked(age,     p("просмотр_возраст_топ.png"),
                        crisp=top[1], sim=sim, title=f"Возраст (топ): {top[1]}")
        save_view_marked(edu,     p("просмотр_образование_топ.png"),
                        crisp=top[2], sim=sim, title=f"Образование (топ): {top[2]}")
        save_view_marked(exp,     p("просмотр_опыт_топ.png"),
                        crisp=top[3], sim=sim, title=f"Опыт (топ): {top[3]}")
        save_view_marked(soft,    p("просмотр_софт_топ.png"),
                        crisp=top[4], sim=sim, title=f"Софт (топ): {top[4]}")
        save_view_marked(quality, p("просмотр_качество_топ.png"),
                        crisp=q_crisp, sim=sim, title=f"Качество (топ): {q_crisp:.1f}")

    # Просмотр по одному правилу для каждого класса вывода
    idx_low = idx_mid = idx_high = None
    for i, txt in enumerate(text_rules):
        if ("quality=малое" in txt) and (idx_low is None): idx_low = i
        if ("quality=среднее" in txt) and (idx_mid is None): idx_mid = i
        if ("quality=высокое" in txt) and (idx_high is None): idx_high = i
        if idx_low is not None and idx_mid is not None and idx_high is not None:
            break
    if idx_low is not None:
        rules[idx_low].view();  plt.gcf().savefig(p("правило_малое.png"),   dpi=150, bbox_inches='tight'); plt.close()
    if idx_mid is not None:
        rules[idx_mid].view();  plt.gcf().savefig(p("правило_среднее.png"), dpi=150, bbox_inches='tight'); plt.close()
    if idx_high is not None:
        rules[idx_high].view(); plt.gcf().savefig(p("правило_высокое.png"), dpi=150, bbox_inches='tight'); plt.close()

    # Итог: перечислим файлы
    print("\nФайлы сохранены в папку:", os.path.abspath(OUT_DIR))

if __name__ == "__main__":
    main()