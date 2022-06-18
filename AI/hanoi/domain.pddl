(define (domain hanoi)
(:requirements :adl)
(:predicates
    (clear ?x)
    (with ?src ?x)
    (larger ?x ?y)
    (on ?x ?y)
)
    ; przesun x na y / src na dst
(:action przesun
    :parameters (?src ?dst ?x ?y ?xb)
    :precondition
    (and
        (clear ?x)
        (clear ?y)
        (with ?src ?x)
        (with ?src ?xb)
        (with ?dst ?y)
        (on ?xb ?x)
        (or 
            (larger ?x ?y)
            (clear ?dst)
        )
        (and
            (not (on ?dst ?x))
            (not (on ?y ?x))
            (not (on ?xb ?y))
            (not (on ?x ?y))
            (not (on ?y ?xb))
            (not (with ?dst ?x))
        )
    )
    :effect
    (and
        (not (clear ?y))
        (not (on ?src ?x))
        (not (on ?xb ?x))
        (on ?y ?x)
        (clear ?xb)
        (not (clear ?dst))
        (not (with ?src ?x))
        (with ?dst ?x)
    )
)
)
