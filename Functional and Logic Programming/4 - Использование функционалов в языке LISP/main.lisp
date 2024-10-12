(defparameter *goods* nil)
(defparameter *name* 0)
(defparameter *quantity* 1)
(defparameter *price* 2)
 
(defun add-good (name quantity price)
 (push (list name quantity price) *goods*))
 
(defun edit-good (name quantity price)
 (let ((good (find name *goods* :key #'first)))
   (when good
     (setf (second good) quantity
       (third good) price))))
 
(defun remove-good (name)
 (setf *goods* (remove (find name *goods* :key #'first) *goods*)))
 
(defun out-of-stock ()
 (remove-if-not (lambda (good) (= (second good) 0)) *goods*))
 
(defun most-abundant ()
 (reduce #'(lambda (a b) (if (> (second a) (second b)) a b)) *goods*))
 
(defun most-expensive()
 (reduce #'(lambda (a b) (if (> (third a) (third b)) a b)) *goods*))
 
(defun find-good (name)
 (find name *goods* :key #'first))
 
(add-good 'apple 10 15)
(add-good 'orange 20 20)
(add-good 'banana 15 10)
(add-good 'pear 0 10)
 
(print "Все товары на складе")
(print *goods*)(terpri)
 
(edit-good 'banana 20 12)
 
(print "Замена данных о банане")
(print *goods*)(terpri)
 
(print "Удаление товара")
(print (remove-good 'orange))(terpri)
 
(print "Распродано")
(print (out-of-stock))(terpri)
 
(print "Товар с минимальной ценой")
(print (most-expensive))(terpri)
 
(print "Товар с максимальной ценой")
(print (most-abundant))(terpri)
 
