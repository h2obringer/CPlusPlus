;;; This is one of the example programs from the textbook:
;;;
;;; Artificial Intelligence: 
;;; Structures and strategies for complex problem solving
;;;
;;; by George F. Luger and William A. Stubblefield
;;; 
;;; These programs are copyrighted by Benjamin/Cummings Publishers.
;;;
;;; We offer them for use, free of charge, for educational purposes only.
;;;
;;; Disclaimer: These programs are provided with no warranty whatsoever as to
;;; their correctness, reliability, or any other property.  We have written 
;;; them for specific educational purposes, and have made no effort
;;; to make them commercial quality computer programs.  Please do not expect 
;;; more of them then we have intended.
;;;



;;; simple recursive function to compute square roots 
;;; using newton's method.  Solution to problem 7.1 
;;;
;;; For example, to find the square root of 2, to an accuracy of
;;; 0.000001, evaluate
;;;    
;;;      (newton 2 0.000001)

(defun newton (x tol)
  (repeat-guesses 1.0 x tol))

(defun repeat-guesses (guess x tol)
  (print guess)
  (if (< (abs (- x (* guess guess))) tol)
    guess
    (repeat-guesses (/ (+ guess (/ x guess)) 2) x tol)))


