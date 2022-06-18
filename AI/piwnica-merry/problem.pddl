(define (problem ucieczka)
   (:domain piwnica)
   (:objects 
      A B C D E F G H I 
      z c p r n
   )
   (:init 
      trans A B p      

      trans A C c
      trans C A c

      trans B D p

      trans D F n
      trans F D n

      trans F I n
      trans I F n

      trans E F n
      trans F E n

      trans H I n
      trans I H n

      trans H E c
      trans E H c

      trans E C z
      trans C E z

      trans F G r

      has_ball F n
      has_ball F n

      has_ball I p
      has_ball I n

      has_ball H z
      has_ball H c

      has_ball E n
      has_ball E z
      
      has_ball C p
      has_ball C n

      has_ball A z
      
      has_ball B r

      has_ball D z
      
      has_ball D c

      location F
   )
   (:goal
      (and
         
      )
   )
)
