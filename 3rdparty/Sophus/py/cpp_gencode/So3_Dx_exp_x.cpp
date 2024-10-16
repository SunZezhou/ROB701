Scalar const c0 = pow(omega[0], 2);
Scalar const c1 = pow(omega[1], 2);
Scalar const c2 = pow(omega[2], 2);
Scalar const c3 = c0 + c1 + c2;
Scalar const c4 = sqrt(c3);
Scalar const c5 = 1.0/c4;
Scalar const c6 = 0.5*c4;
Scalar const c7 = sin(c6);
Scalar const c8 = c5*c7;
Scalar const c9 = pow(c3, -3.0L/2.0L);
Scalar const c10 = c7*c9;
Scalar const c11 = 1.0/c3;
Scalar const c12 = cos(c6);
Scalar const c13 = 0.5*c11*c12;
Scalar const c14 = c7*c9*omega[0];
Scalar const c15 = 0.5*c11*c12*omega[0];
Scalar const c16 = -c14*omega[1] + c15*omega[1];
Scalar const c17 = -c14*omega[2] + c15*omega[2];
Scalar const c18 = omega[1]*omega[2];
Scalar const c19 = -c10*c18 + c13*c18;
Scalar const c20 = 0.5*c5*c7;
result[0] = -c0*c10 + c0*c13 + c8;
result[1] = c16;
result[2] = c17;
result[3] = c16;
result[4] = -c1*c10 + c1*c13 + c8;
result[5] = c19;
result[6] = c17;
result[7] = c19;
result[8] = -c10*c2 + c13*c2 + c8;
result[9] = -c20*omega[0];
result[10] = -c20*omega[1];
result[11] = -c20*omega[2];
