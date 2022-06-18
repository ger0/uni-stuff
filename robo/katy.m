function t = katy(p)
    theta1 	= atan2(p(2), p(1))
    if (theta1 < 0)
	theta1_2 = theta1 + pi();
    else
	theta1_2 = theta1 - pi();
    endif
    endfunction
