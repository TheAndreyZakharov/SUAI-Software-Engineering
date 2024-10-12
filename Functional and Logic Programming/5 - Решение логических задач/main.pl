%запуск решения:
%? wins (Wins)
карточки
cards ([1,2,3, 4, 5, 6, 7, 8, 9, 101) .
:записанные выигрыши
records ([[erdei, 11], [feldi, 4], [hedi, 7], [mezei, 161, [vizi, 1711).
вреальные выигрыши
wins (Wins):-
records (Records) ,
cards (Cards) ,
wins (Records, Cards, Wins),
! .

wins([l,[1,l]).
wins([[Name, Sum] |Teil], Cards, [[Name, [Numl, Num2]] |Rest]) :-
remove (Num], Cards, Cards1),
remove (Num2, Cards1, Cards2),
Sum is Num1 + Num2,
wins(Teil, Cards2, Rest)•
remove (Elem, [Elem (Tail], Tail) •
remove(Elem, [Head | Taill, [Head | Rest]):-
remove (Elem, Tail, Rest).
