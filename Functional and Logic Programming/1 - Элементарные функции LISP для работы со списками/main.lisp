(setq lst1 '(A X C))
(setq lst2 '(F Y))
(setq lst3 '(Z))

(write (cons (cadr lst1)
             (cons (cadr lst2)
                   (cons (car lst3) nil))))

(setq lst1 '((A) (BX) (C D)))
(setq lst2 '((Y (Z))))

(write (cons (cadadr lst1)
             (cons (caar lst2)
                   (cons (caadar lst2) nil))))

(setq lst1 '(A X BY))
(setq lst2 '(Y Z))

(write (cons (cadr lst1)
             (cons (cadddr lst1)
                   (cons (cadr lst2) nil))))
