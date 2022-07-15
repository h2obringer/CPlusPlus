;;; This file contains the depth first search algorithm from chapter 7.

; This version of depth first search does not use open and closed lists
; to keep track of states.  Instead, it uses recursion to manage the search.

;;; It takes as arguments a start state, a goal state, and a list of
;;; move functions.

;;; For example, to run depth first search with the farmer, wolf, 
;;; goat, etc. problem, evaluate the definitions found in the file 
;;; farmer_wolf_etc_rules_only, and evaluate:
;
;     (run-depth-first '(e e e e) '(w w w w)
;	'(farmer-takes-self farmer-takes-wolf 
;	  farmer-takes-goat farmer-takes-cabbage))
;




(defun depth-first-search (start goal been-list moves)
  (cond ((equal start goal) 
         (reverse been-list))
        (t (try-moves start goal been-list moves moves))))

; Try-moves scans down the list of moves in moves-to-try, 
; attempting to generate a child state.  If it produces 
; this state, it calls depth-first-search to complete the search.

(defun try-moves (start goal been-list moves-to-try moves)
  (cond ((null moves-to-try) nil)
        ((member start been-list :test #'equal) nil)
        (t (let ((child (funcall (car moves-to-try) start)))
             (if child 
               (or (depth-first-search (funcall (car moves-to-try) start)
                                       goal
                                       (cons start been-list)
                                       moves)
                   (try-moves start goal been-list (cdr moves-to-try) moves))
               (try-moves start goal been-list (cdr moves-to-try) moves))))))

; run-depth-first calls depth-first-search, initializing the been-list to ().
(defun run-depth-first (start goal moves)
  (depth-first-search start goal () moves))



