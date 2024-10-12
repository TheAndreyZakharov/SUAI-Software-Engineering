% ?- start.
% ?- add_employee("Алексеев Алексей", "аналитик", 60000).
% ?- remove_employee(1).
% ?- replace_employee(2, "Петров Петр", "разработчик", 85000).
% ?- find_by_name("Петров Петр").
% ?- find_by_position("дизайнер").
% ?- find_higher_salary(42000).
 
:- dynamic employee/4.
 
% Примеры сотрудников
employee(1, "Иванов Иван", "менеджер", 50000).
employee(2, "Петров Петр", "разработчик", 80000).
employee(3, "Сидоров Сергей", "дизайнер", 40000).
 
% Получение максимального ID сотрудника
max_employee_id(MaxId) :-
   findall(Id, employee(Id, _, _, _), Ids),
   max_list(Ids, MaxId).
 
% Включение сотрудника с автоматическим расчетом ID
add_employee(Name, Position, Salary) :-
   max_employee_id(MaxId),
   NewId is MaxId + 1,
   assertz(employee(NewId, Name, Position, Salary)),
   display_all.
 
% Исключение сотрудника
remove_employee(Id) :-
   retract(employee(Id, _, _, _)),
   display_all.
 
% Замена данных о сотруднике
replace_employee(Id, Name, Position, Salary) :-
   retract(employee(Id, _, _, _)),
   assertz(employee(Id, Name, Position, Salary)),
   display_all.
 
% Вывод всех сотрудников в порядке возрастания по ID
display_all :-
   writeln("Список сотрудников:"),
   findall(Id, employee(Id, _, _, _), Ids),
   sort(Ids, SortedIds),
   forall(member(SortedId, SortedIds), (
       employee(SortedId, Name, Position, Salary),
       format('~w ~w ~w ~w~n', [SortedId, Name, Position, Salary])
   )).
 
% Поиск сотрудников по имени
find_by_name(Name) :-
   writeln("Сотрудники с заданным именем:"),
   forall(employee(Id, Name, Position, Salary), format('~w ~w ~w ~w~n', [Id, Name, Position, Salary])).
 
% Поиск сотрудников по должности
find_by_position(Position) :-
   writeln("Сотрудники с заданной должностью:"),
   forall(employee(Id, Name, Position, Salary), format('~w ~w ~w ~w~n', [Id, Name, Position, Salary])).
 
% Поиск сотрудников с зарплатой выше указанной
find_higher_salary(SalaryThreshold) :-
   writeln("Сотрудники с зарплатой выше указанной:"),
   forall((employee(Id, Name, Position, Salary), Salary > SalaryThreshold), format('~w ~w ~w ~w~n', [Id, Name, Position, Salary])).
 
% Запуск программы
start :-
   display_all.
 
