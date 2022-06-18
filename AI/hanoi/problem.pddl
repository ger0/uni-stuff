(define (problem wieza)
(:domain hanoi)
(:objects x y z k1 k2 k3 k4 k5)
(:init
    (larger k1 k2)
    (larger k1 k3)
    (larger k1 k4)
    (larger k1 k5)
    
    (larger k2 k3)
    (larger k2 k4)
    (larger k2 k5)
    
    (larger k3 k4)
    (larger k3 k5)
    
    (larger k4 k5)
    
    (on x k5)
    (on k5 k4)
    (on k4 k3)
    (on k3 k2)
    (on k2 k1)
    
    (with x k5)
    (with x k4)
    (with x k3)
    (with x k2)
    (with x k1)
    
    (with x x)
    (with y y)
    (with z z)
    
    (clear k1)
    (clear y)
    (clear z)
)
(:goal
    (and
        (on k5 k4)
        (on k4 k3)
        (on k3 k2)
        (on k2 k1)
        (clear k1)
        (on z k5)
    )
)
)
