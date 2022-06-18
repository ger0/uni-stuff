(define (domain piwnica)
   (:requirements :adl)
   (:predicates
      (has_ball   ?room ?color)
      (trans      ?room1 ?room2 ?color)
      (location   ?room)
      (holds      ?color)
   )

   (:action wez
      :parameters (?color ?loc)
      :precondition
      (and
         (location ?loc)
         (has_ball ?loc ?color)
      )
      :effect
      (and 
         (not (has_ball ?loc ?color))
         (holds ?color)
      )
   )

   (:action idz
      :parameters (?cel ?loc ?color)
      :precondition
      (and
         (location ?loc)
         (holds ?color)

         (trans ?loc ?cel ?color)
      )
      :effect
      (and
         (location ?cel)
         (not (holds ?color))
      )
   )
)
