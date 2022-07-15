;;; this file contains the best-first search algorithm from chapter 7.

;;; for a simple example of its use with the farmer wolf goat and cabbage rules, 
;;; evaluate the move rule definitions in farmer_wolf_etc_rules_only.lisp,
;;; and bind them to the gloabl variable, *moves*:

; (setq *moves* 
;      '(farmer-takes-self farmer-takes-wolf 
;       farmer-takes-goat farmer-takes-cabbage))

;;; Also, the algorithm requires that a simple heuristic be used to evaluate
;;; states.  For the farmer, wolf, goat and cabbage rules, a simple heuristic 
;;; counts the number of players not in their goal positions:

; (defun heuristic (state)
;  (heuristic-eval state *goal*))

; (defun heuristic-eval (state goal)
;  (cond ((null state) 0)
;        ((equal (car state) (car goal)) 
;        (heuristic-eval (cdr state) (cdr goal)))
;        (t (1+ (heuristic-eval (cdr state) (cdr goal))))))
;
;;; Once these have been defined, evaluate:
;;;
;;;  (run-best '(e e e e) '(w w w w))





;;; insert-by-weight will add new child states to an ordered list of 
;;; states-to-try.  
(defun insert-by-weight (children sorted-list)
  (cond ((null children) sorted-list)
        (t (insert (car children) 
           (insert-by-weight (cdr children) sorted-list)))))

(defun insert (item sorted-list)
  (cond ((null sorted-list) (list item))
        ((< (get-weight item) (get-weight (car sorted-list)))
         (cons item sorted-list))
        (t (cons (car sorted-list) (insert item (cdr sorted-list))))))


;;; run-best is a simple top-level "calling" function to run best-first-search

(defun run-best (start goal)
  (setq *goal* goal)
  (setq *open* (list (build-record start nil 0 (heuristic start))))
  (setq *closed* nil)
  (best-first))

;;; These functions handle the creation and access of (state parent) 
;;; pairs.

(defun build-record (state parent depth weight) 
  (list state parent depth weight))

(defun get-state (state-tuple) (nth 0 state-tuple))

(defun get-parent (state-tuple) (nth 1 state-tuple))

(defun get-depth (state-tuple) (nth 2 state-tuple))

(defun get-weight (state-tuple) (nth 3 state-tuple))

(defun retrieve-by-state (state list)
  (cond ((null list) nil)
        ((equal state (get-state (car list))) (car list))
        (t (retrieve-by-state state (cdr list)))))


;; best-first defines the actual best-first search algorithm
;;; it uses "global" open and closed lists.

(defun best-first ()
  (print "open =") (print *open*)
  (print "closed =") (print *closed*)
  (cond ((null *open*) nil)
        (t (let ((state (car *open*)))
             (setq *closed* (cons state *closed*))
             (cond ((equal (get-state state) *goal*) (build-solution *goal*))
                   (t (setq *open* 
                            (insert-by-weight 
                                    (generate-descendants (get-state state)
                                                          (1+ (get-depth state))
                                                          *moves*)
                                    (cdr *open*)))
                      (best-first)))))))


;;; generate-descendants produces all the descendants of a state

(defun generate-descendants (state depth moves)
  (cond ((null moves) nil)
        (t (let ((child (funcall (car moves) state))
                 (rest (generate-descendants state depth (cdr moves))))
             (cond ((null child) rest)
                   ((retrieve-by-state child rest) rest)
                   ((retrieve-by-state child *open*) rest)
                   ((retrieve-by-state child *closed*) rest)
                   (t (cons (build-record child state depth 
                                          (+ depth (heuristic child))) 
                            rest)))))))


(defun build-solution (state)
  (cond ((null state) nil)
        (t (cons state (build-solution 
                        (get-parent 
                         (retrieve-by-state state *closed*)))))))


