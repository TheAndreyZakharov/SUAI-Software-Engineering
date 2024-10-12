(setq lst '(3 2 1 2 3))

(defun Onion (L)
  (cond
    ((null L) nil)
    ((null (cdr L)) L)
    (T
      (cons (car L)
            (cons (Onion (cdr (butlast L)))
                  (last L))))))

(write (Onion lst))
