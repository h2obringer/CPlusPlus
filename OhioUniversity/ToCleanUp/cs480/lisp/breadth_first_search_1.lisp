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
;;; to produce commercial quality computer programs.  Please do not expect 
;;; more of them then we have intended.
;;;


;;; This file contains a simple general breadth first search algorithm
;;; described in chapter 7 of the text.
;;; although it finds solutions, it does not reproduce the path to them.
;;; A more useful algorithm that does so is described in the 
;;; file breadth_first_search_2.lisp


;;; To run it on the farmer, wolf, goat and cabbage problem,
;;; use the farmer, wolf, goat and cabbage rules defined
;;; in the file farmer_wolf_etc_rules_only.lisp.  Bind the
;;; global variable *moves* to those rules by evaluating:

;;; (setq *moves* 
;;;       '(farmer-takes-self farmer-takes-wolf 
;;;         farmer-takes-goat farmer-takes-cabbage))
;;;
;;; Then evaluate (run-breadth '(e e e e) '(w w w w))
;;; 

(defun run-breadth (start goal)
  (declare (special *open*)
           (special *closed*)
           (special *goal*))
  (setq *open* (list start))
  (setq *closed* nil)
  (setq *goal* goal)
  (breadth-first))


(defun breadth-first ()
  (declare (special *open*)
           (special *closed*)
           (special *goal*)
           (special *moves*))
  (cond ((null *open*) nil)
        (t (let ((state (car *open*)))
             (cond ((equal state *goal*) 'success)
                   (t (setq *closed* (cons state *closed*))
                      (setq *open* 
                            (append (cdr *open*)
                                    (generate-descendants state *moves*)))
                      (breadth-first)))))))

;;; Generates all the descendants of a given state.

(defun generate-descendants (state moves)
  (declare (special *open*)
           (special *closed*))
  (cond ((null moves) nil)
        (t (let ((child (funcall (car moves) state))
                 (rest (generate-descendants state (cdr moves))))
             (cond ((null child) rest)
                   ((member child rest :test #'equal) rest)
                   ((member child *open* :test #'equal) rest)
                   ((member child *closed* :test #'equal) rest)
                   (t (cons child rest)))))))



