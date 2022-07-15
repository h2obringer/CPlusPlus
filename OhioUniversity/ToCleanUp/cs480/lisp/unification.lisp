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



;;; This is the unification algorithm from section 7.6 of the text.

;;; recursive unification algorithm, takes two patterns and a list of
;;; substitutions found so far and returns either "failed" or the 
;;; substitution-list augmented with those bindings needed for a match

(defun unify (pattern1 pattern2 substitution-list)
   (cond ((equal substitution-list 'failed) 'failed)
	 ((varp pattern1) 
                     (match-var pattern1 pattern2 substitution-list))
 	 ((varp pattern2) 
                     (match-var pattern2 pattern1 substitution-list))
	 ((is-constant-p pattern1) 
	    (cond ((equal pattern1 pattern2) substitution-list)
		  (t 'failed)))
	 ((is-constant-p pattern2) 'failed)
	 (t (unify (cdr pattern1) (cdr pattern2) 
			     (unify (car pattern1) (car pattern2)
					      substitution-list)))))

;;; will attempt to match a variable to a pattern, first
;;; checking for existing bindings on the variable, then
;;; performing an occurs check.

(defun match-var (var pattern substitution-list)
   (cond ((equal var pattern) substitution-list)
         (t (let ((binding (get-binding var substitution-list)))
		 (cond (binding 
			   (unify (get-binding-value binding) 
					    pattern substitution-list))
		       ((occursp var pattern) 'failed)
		       (t (acons var pattern  substitution-list)))))))


;;; occursp will check if a variable occurs in a pattern.

(defun occursp (var pattern)
   (cond ((equal var pattern) t)
	 ((or (varp pattern) (is-constant-p pattern))
	      nil)
	  (t (or (occursp var (car pattern))
		 (occursp var (cdr pattern))))))

;;; is-constant-p determines if an item is a constant.  In this simple
;;; program, we are assuming that all constants are atoms.

(defun is-constant-p (item)
  (atom item))

(defun varp (item)
  (and (listp item) 
	(equal (length item) 2)
	(equal (car item) 'var)))


;;; get-binding takes a variable and a substitution list, and returns 
;;; a (variable . binding-value) pair 

(defun get-binding (var substitution-list) 
	(assoc var substitution-list :test #'equal))

;;; get-binding-value returns the binding value from 
;;; a (variable . binding-value) pair

(defun get-binding-value (binding) (cdr binding))
  
;;; add-substitution adds a variable and a binding-value to a
;;; substitution-list

(defun add-substitution (var pattern substitution-list)
   (acons var pattern substitution-list))



