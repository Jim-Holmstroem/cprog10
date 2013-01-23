void testWhat(void){

    TS_ASSERT(test==2);

}



void mathOperators(void){

    //0
    Matrix a0(0);
    Matrix b0(0);

    Matrix big(5);

    TS_ASSERT(a0.cols()==0 && a0.rows()==0);
    TS_ASSERT(b0.cols()==0 && b0.rows()==0);
    TS_ASSERT(big.cols()==5 && big.rows()==5);

    Matrix c0;

    c0 = a0 + b0;
    TS_ASSERT(c0.cols()==0 && c0.rows()==0);
    TS_ASSERT_THROWS_ANYTHING(big + a0);

    c0 = a0 - b0;
    TS_ASSERT(c0.cols()==0 && c0.rows()==0);
    TS_ASSERT_THROWS_ANYTHING(big - a0);

    c0 = a0 * b0;
    TS_ASSERT(c0.cols()==0 && c0.rows()==0);
    TS_ASSERT_THROWS_ANYTHING(big * b0);
    TS_ASSERT_THROWS_ANYTHING(a0 * big);

    c0 = 3*b0;
    TS_ASSERT(c0.cols()==0 && c0.rows()==0);
    c0 = b0*3;
    TS_ASSERT(c0.cols()==0 && c0.rows()==0);
    c0 = -b0;
    TS_ASSERT(c0.cols()==0 && c0.rows()==0);

    //1

    Matrix a1(1);
    Matrix b1(1);

    a1 = 7 * a1;
    b1 = b1 * 3;

    TS_ASSERT(a1[0][0]==7); //tests int*matrix
    TS_ASSERT(b1[0][0]==3); //tests matrix*int

    Matrix c1;

    c1 = a1 + b1;
    TS_ASSERT(c1[0][0]==10);
    c1 = a1 - b1;
    TS_ASSERT(c1[0][0]==4);
    c1 = a1 * b1;
    TS_ASSERT(c1[0][0]==21);
    c1 = 3*b1;
    TS_ASSERT(c1[0][0]==9);
    c1 = a1*3;
    TS_ASSERT(c1[0][0]==21);
    c1 = -b1;
    TS_ASSERT(c1[0][0]==-3);

    //Test to check chaining-operations
    Matrix ac(2);
    Matrix bc(2);
    Matrix cc(2);

    Matric dc(2);

    TS_ASSERT_THROWS_NOTHING(ac+ac+cc);
    dc = ac+bc+cc;
    TS_ASSERT(dc[0][0]==3);
    TS_ASSERT(dc[0][1]==0);
    TS_ASSERT(dc[1][0]==0);
    TS_ASSERT(dc[1][1]==3);

    dc = ac-bc-cc;
    TS_ASSERT(dc[0][0]==-1);
    TS_ASSERT(dc[0][1]==0);
    TS_ASSERT(dc[1][0]==0);
    TS_ASSERT(dc[1][1]==-1);

    dc = ac*bc*cc;

    TS_ASSERT(dc[0][0]==1);
    TS_ASSERT(dc[0][1]==0);
    TS_ASSERT(dc[1][0]==0);
    TS_ASSERT(dc[1][1]==1);


    //dimsions when matrix*matrix

    Matrix a13(1,3);
    Matrix b32(3,2);

    TS_ASSERT_THROWS_ANYTHING(b32*a13);
    TS_ASSERT_THROWS_NOTHING(a13*b32);

    //have already tested with empty matrices

}
void testTranspose(void){
    Matrix a0(0);
    a0.transpose();
    TS_ASSERT(a0.rows()==0 && a0.cols()==0);

    Matrix a1(1);
    a1.transpose();
    TS_ASSERT(a1.rows()==1 && a1.cols()==1);

    Matrix mt(3,2);
    mt[0][1] = 1337;
    mt.transpose();
    TS_ASSERT(mt.rows()==2 && mt.cols()==3);
    TS_ASSERT_EQUALS(mt[1][0], 1337);
}

void testOutput(void){
    Matrix mout(2,1);
    //ins >> mout;
    mout[0][1] = 42;
    cout << mout;
}
