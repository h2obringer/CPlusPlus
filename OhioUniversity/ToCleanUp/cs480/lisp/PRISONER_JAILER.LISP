(defun solve-pj (state goal) (path state goal nil))

;;;(defun path (state goal been-list)
;;;  (cond ((null state) nil)
;;;	 ((equal state goal) (reverse (cons state been-list)))
;;;	 ((not (member state been-list :test #'equal))
;;;	      (or (path (farmer-takes-self state) goal (cons state been-list))
;;;	          (path (farmer-takes-wolf state) goal (cons state been-list))
;;;	          (path (farmer-takes-goat state) goal (cons state been-list))
;;;	          (path (farmer-takes-cabbage state) goal (cons state been-list))))))

;;; These functions define legal moves in the state space.  The take
;;; a state as argument, and return the state produced by that operation.

(defun j1-takes-self (state)
   (safe (make-state (opposite (j1-side state))
		(j2-side state)
	 	(j3-side state)
	 	(p1-side state)
		(p2-side state)
		(p3-side state))))

(defun j1-takes-p1 (state)
   (cond ((equal (j1-side state) (p1-side state))
	(safe (make-state (opposite (j1-side state))
		(j2-side state)
		(j3-side state)
		(opposite (p1-side state))
		(p2-side state)
		(p3-side state)))
   (t nil)))

(defun j1-takes-p2 (state)
   (cond ((equal (j1-side state) (p2-side state))
	(safe (make-state (opposite (j1-side state))
		(j2-side state)
		(j3-side state)
		(p1-side state)
		(opposite (p2-side state))
		(p3-side state)))
   (t nil)))

(defun j1-takes-p3 (state)
   (cond ((equal (j1-side state) (p3-side state))
	(safe (make-state (opposite (j1-side state))
		(j2-side state)
		(j3-side state)
		(p1-side state)
		(p2-side state)
		(opposite (p3-side state))))
   (t nil)))

(defun j2-takes-self (state)
   (safe (make-state (j1-side state)
	(opposite (j2-side state))
	(j3-side state)
	(p1-side state)
	(p2-side state)
	(p3-side state))))

(defun j2-takes-p1 (state)
   (cond ((equal (j2-side state) (p1-side state))
	(safe (make-state (j1-side state)
	(opposite (j2-side state))
	(j3-side state)
	(opposite (p1-side state))
	(p2-side state)
	(p3-side state))))
   (t nil)))

(defun j2-takes-p2 (state)
   (cond ((equal (j2-side state) (p2-side state))
	(safe (make-state (j1-side state)
	(opposite (j2-side state))
	(j3-side state)
	(p1-side state)
	(opposite (p2-side state))
	(p3-side state))))
   (t nil)))

(defun j2-takes-p3 (state)
   (cond ((equal (j2-side state) (p3-side state))
	(safe (make-state (j1-side state)
	(opposite (j2-side state))
	(j3-side state)
	(p1-side state)
	(p2-side state)
	(opposite (p3-side state)))))
   (t nil)))

(defun j3-takes-self (state)
   (safe (make-state (j1-side state)
		(j2-side state)
	 	(opposite (j3-side state))
	 	(p1-side state)
		(p2-side state)
		(p3-side state))))

(defun j3-takes-p1 (state)
   (cond ((equal (j3-side state) (p1-side state))
	(safe (make-state (j1-side state)
	(j2-side state)
	(opposite (j3-side state))
	(opposite (p1-side state))
	(p2-side state)
	(p3-side state))))
   (t nil)))

(defun j3-takes-p2 (state)
   (cond ((equal (j3-side state) (p2-side state))
	(safe (make-state (j1-side state)
	(j2-side state)
	(opposite (j3-side state))
	(p1-side state)
	(opposite (p2-side state))
	(p3-side state))))
   (t nil)))

(defun j3-takes-p3 (state)
   (cond ((equal (j3-side state) (p3-side state))
	(safe (make-state (j1-side state)
	(j2-side state)
	(opposite (j3-side state))
	(p1-side state)
	(p2-side state)
	(opposite (p3-side state)))))
   (t nil)))

;;; These functions define states of the world
;;; as an abstract data type.

(defun make-state (j1 j2 j3 p1 p2 p3) (list j1 j2 j3 p1 p2 p3))

(defun j1-side ( state )
   (nth 0 state))

(defun j2-side ( state )
   (nth 1 state))

(defun j3-side ( state )
   (nth 2 state))

(defun p1-side ( state )
   (nth 3 state))

(defun p2-side ( state )
   (nth 4 state))

(defun p3-side ( state )
   (nth 5 state))

;;; The function "opposite" takes a side and returns the opposite
;;; side of the river.

(defun opposite (side)
   (cond ((equal side 'e) 'w)
             ((equal side 'w) 'e)))

;;; Safe returns nil if a state is not safe; it returns the state unchanged
;;; if it is safe.

(defun safe (state)
   (cond ((and (equal (j1-side state) (p1-side state))
		(j1-side state

   (cond ((and (equal (goat-side state) (wolf-side state))
	             (not (equal (farmer-side state) (wolf-side state))))  nil)
            ((and (equal (goat-side state) (cabbage-side state))
	             (not (equal (farmer-side state) (goat-side state)))) nil)
	   (t state)))




