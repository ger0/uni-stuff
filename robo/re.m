function t = re(T)
    d6 = 100;

    pwx = T(1, 4) - T(1, 3) * d6;
    pwy = T(2, 4) - T(2, 3) * d6;
    pwz = T(3, 4) - T(3, 3) * d6;
    t = [pwx; pwy; pwz];
    endfunction
