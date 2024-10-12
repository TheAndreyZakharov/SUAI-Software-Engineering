% process_list([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 111, 200], Result).
 
% Предикат, изменяющий значения элементов списка в соответствии с условиями задачи
modify_element(X, Y) :-
   (X mod 2 =:= 0 -> Y is X - 2; Y is X + 1).
 
% Предикат, проверяющий, является ли значение числом
is_number(X) :-
   number(X).
 
% Основной предикат, рекурсивно применяющий modify_element к каждому элементу списка
process_list([], []).
process_list([H1|T1], [H2|T2]) :-
   is_number(H1),
   modify_element(H1, H2),
   process_list(T1, T2).
process_list([H1|T1], T2) :-
   \+ is_number(H1),
   process_list(T1, T2).
 
