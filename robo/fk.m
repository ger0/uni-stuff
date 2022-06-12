function E = fk(theta1,theta2,d3,theta4,theta5,theta6)
    d1 = 400;
    d6 = 100;

    d2 = 0;
    d3 = 0;
    d4 = 1000;
    d5 = 1000;

    T00 = [1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1];
    T01 = DH(theta1,d1,0,-90);
    T12 = DH(theta2,d2,0,90);
    T23 = DH(0,d3,0,-90);
    T34 = DH(theta4,d4,0,-90);
    T45 = DH(theta5,0,0,90);
    T56 = DH(theta6,d6,0,0);
    E = T00 * T01 * T12 * T23 * T34 * T45 * T56
endfunction 

