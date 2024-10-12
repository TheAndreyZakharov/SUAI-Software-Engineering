(SETQ GRAPH '((A B C) (B A) (C D) (D A)))
;; (SETQ GRAPH '((A B C) (B D) (D A)))
 
; вход: граф
; выход: список точек
(DEFUN POINTS (orgr)
 (COND
  ((NULL orgr) ())
  (T (CONS (CAAR orgr) (POINTS (CDR orgr))))
 )
)
 
; вход: список
;           символ
; выход: обрезанный список с конца по символ
(DEFUN CUT_LAST_ON_SYMBOL (lst symbol)
 (COND
   ((NULL lst) NIL)
   ((EQ (CAR (LAST lst)) symbol) lst)
   (T (CUT_LAST_ON_SYMBOL (BUTLAST lst) symbol))
 )
)
 
; вход: список
; выход: обрезанный список, у которого
;             первый и последний элементы одинаковые
(DEFUN CUT_ON_CYCLE (lst)
 (COND
   ((NULL lst) NIL)
   ((FIND_IN_LIST (CDR lst) (CAR lst))
   (CUT_LAST_ON_SYMBOL lst (CAR lst)))
   (T (CUT_ON_CYCLE (CDR lst)))
 )
)
 
; вход: список
;           значение
; выход: Найден или не найден символ (T или NIL)
(DEFUN FIND_IN_LIST (lst value)  
 (COND
   ((NULL lst) NIL)
   ((eq (CAR lst) value) T)
   (T (FIND_IN_LIST (cdr lst) value))
 )
)
 
; вход: список
;           значение
; выход: список без найденного значения
(DEFUN REMOVE_ELEMENT(lst elem)
 (COND
  ((NULL lst) NIL)
  ((EQUAL (CAR lst) elem) (REMOVE_ELEMENT (CDR lst) elem))
  (T (CONS (CAR lst) (REMOVE_ELEMENT (CDR lst) elem)))
 )
)
 
; вход: список
;           символ
;           счетчик переборов
; выход: список, в котором выведены все возможные
;            варианты повторения цикла
(DEFUN VARIANTS(lst elem len)
 (COND
   ((<= len 2) lst)
   (T (VARIANTS (REMOVE_ELEMENT lst elem) (APPEND (CDR elem) (LIST (CADR elem))) (- len 1)))
)  
)
 
; вход: список
; выход: список, в котором удалены все повторяющиеся циклы
(DEFUN DEL_DUBLICATE(lst)
 (COND
  ((NULL lst) NIL)
  (T (CONS (CAR lst) (DEL_DUBLICATE
    (CDR (VARIANTS lst (CAR lst) (LENGTH (CAR lst))))))
  )
 )
)
 
; вход: граф
; выход: список циклов
(DEFUN SEARCH_CYCLES_GRAPH(GRAPH)
     (COND
       ((NULL GRAPH) NIL)
       (T (DEL_DUBLICATE (DEFI NIL GRAPH NIL (LIST (CAR (POINTS graph))) (POINTS graph))))
     )
)
 
; вход: уже найденные циклы
;           граф
;           список посещённых вершин
;           путь по которому мы прошли
;           список начальных посещенных вершин
; выход: список всех найденных циклов
(DEFUN DEFI  (RES GRAPH VISITED PATH VISITED_ROOT)
 (COND
   ((OR (NULL PATH) (NULL (CAR PATH))) RES)
   (T
     (COND
       (
         (FIND_IN_LIST (BUTLAST PATH) (CAR (LAST PATH)))
         (DEFI
             (APPEND RES (LIST (CUT_ON_CYCLE (REVERSE PATH))))
             GRAPH VISITED (CDR PATH) VISITED_ROOT)
         )
         (
           (EQ (LENGTH VISITED) (LENGTH GRAPH))
           (DEFI RES GRAPH NIL (LIST(CADR VISITED_ROOT)) (CDR VISITED_ROOT))
         )
         (
           (NULL (EXPND GRAPH VISITED (CAR PATH)))
          (DEFI RES GRAPH VISITED (CDR PATH) VISITED_ROOT)
         )
         (T (DEFI RES GRAPH  
           (CONS (EXPND GRAPH VISITED (CAR PATH)) VISITED)
           (CONS (EXPND GRAPH VISITED (CAR PATH)) PATH)
           VISITED_ROOT
           )
         )
        )
       )
     )
)
 
; вход: граф
;           список посещенных вершин
;           вершина из которой будет переход
; выход: вершина в которую будет переход
(DEFUN EXPND (GRAPH VISITED VERTEX)
 (COND
  ((NULL (NEIGHBOUR3 VERTEX GRAPH)) NIL)
  (T (FIRSTNOTVISITED VISITED (NEIGHBOUR3 VERTEX GRAPH)))
 )
)
 
; вход: список посещенных вершин
;           список возможных для перехода вершин
; выход: первая из не посещённых вершин
(DEFUN FIRSTNOTVISITED  (VISITED VLIST)
 (COND
  ((NULL VLIST) NIL)
  (T  
   (COND
     ((NULL (MEMBER (CAR VLIST) VISITED)) (CAR VLIST))
     (T (FIRSTNOTVISITED VISITED (CDR VLIST)))
   )
  )
 )
)
 
; вход: вершина
;           граф
; выход: список вершин в которые можно перейти
(DEFUN NEIGHBOUR3 (X GRAPH)
 (COND
  ((NULL (ASSOC X GRAPH)) NIL)
  (T (CDR (ASSOC X GRAPH)))
 )
)
 
; вход: граф
; выход: список всех найденных циклов
(DEFUN SEARCH_CYCLES_GRAPH(GRAPH)
 (COND
   ((NULL GRAPH) NIL)
   (T (DEL_DUBLICATE (DEFI NIL GRAPH NIL (LIST (CAR (POINTS GRAPH))) (POINTS GRAPH))))
 )
)
 
(write graph)(terpri)
(write (SEARCH_CYCLES_GRAPH graph))
 
