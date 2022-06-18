(define
	(domain world-of-blocks)
	(:requirements :adl)
	(:predicates
		(on-top ?x ?y)
		(on-floor ?x)
		(clear ?x)
	)
	; przesu? paczk? na pod?og?
	(:action move-to-floor
		:parameters (?x ?z)
		:precondition
		(and
			(clear ?x)
			(on-top ?x ?z)
		)
		:effect
		(and
			(not (on-top ?x ?z))
			(on-floor ?x)
			(clear ?z)
		)
	)
	; przesu? paczk? na inn? paczk?
	(:action move-to-block
		:parameters (?x ?y)
		:precondition
		(and
			(clear ?x)
			(clear ?y)
                        (on-floor ?x)
		)
		:effect
		(and
			(on-top ?x ?y)
			(not (clear ?y))
			(not (on-floor ?x))
		)
	)
)
