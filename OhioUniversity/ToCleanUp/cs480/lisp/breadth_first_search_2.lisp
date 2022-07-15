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


;;; This program defines a more sophisticated version of breadth first search.
;;; on finding a solution, it uses a record of each state's parents to print 
;;; the path to the goal.  It is discussed in chapter 7 of the text.
;;;
;;; For example, to run it on the farmer, wolf, goat, etc. problem,
;;; evaluate the definitions of move rules found in the file:
;;;      farmer_wolf-etc-rules-only.lisp
;;;
;;; and then evaluate
;;;
;;; (run-breadth '(e e e e) '(w w w w)
;;;             '(farmer-takes-self farmer-takes-wolf
;;;              farmer-takes-goat farmer-takes-cabbage))


(defun run-breadth (start goal moves)
  (declare (special *open*))
  (declare (special *closed*))
  (declare (special *goal*))
  (setq *open* (list (build-record start nil)))
  (setq *closed* nil)
  (setq *goal* goal)
  (breadth-first moves))

;;; These functions handle the creation and access of (state parent) 
;;; pairs.

(defun build-record (state parent) (list state parent))

(defun get-state (state-tuple) (nth 0 state-tuple))

(defun get-parent (state-tuple) (nth 1 state-tuple))

(defun retrieve-by-state (state list)
  (cond ((null list) nil)
        ((equal state (get-state (car list))) (car list))
        (t (retrieve-by-state state (cdr list)))))



(defun breadth-first (moves)
  (declare (special *open*))
  (declare (special *closed*))
  (declare (special *goal*))
  (cond ((null *open*) nil)
        (t (let ((state (car *open*)))
             (setq *closed* (cons state *closed*))

             (cond 
	;;; found solution: print path to it
	    ((equal (get-state state) *goal*) (reverse (build-solution *goal*)))
             
            ;;; try next child state
                (t (setq *open* 
                            (append (cdr *open*)
                                    (generate-descendants (get-state state)
                                                          moves)))
                      (breadth-first moves)))))))

(defun generate-descendants (state moves)
  (declare (special *open*))
  (declare (special *closed*))
  (cond ((null moves) nil)
        (t (let ((child (funcall (car moves) state))
                 (rest (generate-descendants state (cdr moves))))
             (cond ((null child) rest)
                   ((retrieve-by-state child rest) rest)
                   ((retrieve-by-state child *open*) rest)
                   ((retrieve-by-state child *closed*) rest)
                   (t (cons (build-record child state) rest)))))))


(defun build-solution (state)
  (declare (special *closed*))
  (cond ((null state) nil)
        (t (cons state (build-solution 
                        (get-parent 
                         (retrieve-by-state state *closed*)))))))


