#include "main.h"
#include "vector.h"
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

/*
  void make8bit(){

  FILE * pFile;
  pFile = fopen("lookup8bit.def","w");

  fprintf(pFile,"%s","const unsigned char lookup8bit[]={");

  Vector<bool> c;
  for(unsigned int i=0;i<(1<<8);++i){
  c = i;
  if(i!= (1<<8)-1 ){
  fprintf(pFile,"0x0%X,",static_cast<char>(c.weight_math()));
  }else{
  fprintf(pFile,"0x0%X",static_cast<char>(c.weight_math()));
  }
  }

  fprintf(pFile,"%s","};");

  fclose(pFile);

  };

  void make16bit(){

  FILE * pFile;
  pFile = fopen("lookup16bit.def","w");

  fprintf(pFile,"%s","const unsigned char lookup16bit[]={");

  Vector<bool> c;
  for(unsigned int i=0;i< (1<<16);++i){
  c = i;
  if(i!= (1<<16)-1){
  fprintf(pFile,"0x0%X,",static_cast<char>(c.weight_math()));
  }else{
  //only the last one is 0x10 and it shouldnt have a ','
  fprintf(pFile,"0x%X",static_cast<char>(c.weight_math()));
  }

  }

  fprintf(pFile,"%s","};");
  fclose(pFile);
  };
*/

__inline__ unsigned long long int rdtsc(){
//assembler inline, volatile, means that the compiler cant optimize this part of code by moving it. RDTSC is a assembler instruction to pop the CPU_instruction_counter to eax:edx
    unsigned long long int x;
    __asm__ volatile ("rdtsc" : "=A" (x));
    return x;
}

int main(int argc,char * argv[]){

//make8bit();
//make16bit();

//test vectorer
    unsigned int NUMBER_OF_VECTORS = 65536/16;
    unsigned int NUM_CLASSES = 32;

    Vector<bool> vtest[NUMBER_OF_VECTORS][NUM_CLASSES];

//unsigned int counter[] ={NUMBER_OF_VECTORS,NUMBER_OF_VECTORS,NUMBER_OF_VECTORS,NUMBER_OF_VECTORS,NUMBER_OF_VECTORS,NUMBER_OF_VECTORS,NUMBER_OF_VECTORS,NUMBER_OF_VECTORS};

    unsigned int tmp;
    unsigned int popcount;

    unsigned int pos;
    unsigned int testvalue;

    for(unsigned int c =0; c<32;c++){
        for(unsigned int n=0;n<NUMBER_OF_VECTORS;n++){
            if(c<32/2){
                testvalue=0;//all bits unset
                for(unsigned int b=0;b<c;b++){
                    //randomly set one bit
                    do{
                        pos = rand()%32;
                    }while(((1<<pos)&testvalue)!=0);//while bit is already set, try another
                    testvalue|=(1<<pos); //set the choosen bit
                }
                //              std::cerr << "small:" << std::flush;
            }else{//when more bits are set, go from the other direction
                testvalue=-1;//all bitset and then unset
                for(unsigned int b=0;b<(32-c);b++){
                    //randomly unset one bit
                    do{
                        pos = rand()%32;
                    }while( ((1<<pos)&testvalue)==0 );//while bit is already unset, try another
                    testvalue&=(~(1<<pos)); //set the choosen bit
                }
                //              std::cerr << "big:" << std::flush;
            }
            vtest[n][c] = testvalue;
            //  std::cerr << vtest[n][c].weight_lookup16() << std::endl;
        }
    }
    Vector<bool>& v1 = vtest[4][10];
    v1.print();
    v1.push_back(true);
    v1.push_back(false);
    v1.push_back(true);
    v1.push_back(true);
    v1.print();
    Vector<bool>::iterator it = v1.begin();
    for(; it != v1.end(); ++it){
	(*it) = true;
        std::cout << (*it);
    }
    std::cout << std::endl;
    for(int i=1; i<=35; i++){
	it = v1.begin();
	std::cout << *(it+i) << std::endl;
    }

//    std::cout << *(it) << *(it+1) << *(it+2) << *(it+3) << *(it+4) << *(it+5) << *(it+6) << std::endl;
//    std::cout << *(it+31) << *(it+32) << *(it+33) << *(it+34) << std::endl; //SIMON weird output when ostreamed like this and not using endl

    for(it = vtest[4][10].end(); it != vtest[4][10].begin(); --it){
	std::cout << (*it);
    }
    std::cout << std::endl;

    Vector<bool> v(31);
    v[3] = true;
    Vector<bool> w;
//    std::copy(v.begin(), v.end(), std::back_inserter(w));



/*while(counter[0]||counter[1]||counter[2]||counter[3]||counter[4]||counter[5]||counter[6]||counter[7]){ //while there is some class to still calculate values for

  tmp = rand(); //test this value
  popcount = __builtin_popcount(tmp); //weight
  if(popcount<4){//[0,3]
  if(counter[0]){ //while class not full
  vtest[--counter[0]][0] = tmp;
  }
  }else if(popcount<8){//[4,7]
  if(counter[1]){
  vtest[--counter[1]][1] = tmp;
  }
  }else if(popcount<12){//[8,11]
  if(counter[2]){
  vtest[--counter[2]][2] = tmp;
  }
  }else if(popcount<16){//[12,15]
  if(counter[3]){
  vtest[--counter[3]][3] = tmp;
  }
  }else if(popcount<20){//[16,19]
  if(counter[4]){
  vtest[--counter[4]][4] = tmp;
  }
  }else if(popcount<24){//[20,23]
  if(counter[5]){
  vtest[--counter[5]][5] = tmp;
  }
  }else if(popcount<28){//[24,27]
  if(counter[6]){
  vtest[--counter[6]][6] = tmp;
  }
  }else{//[28,31]
  if(counter[7]){
  vtest[--counter[7]][7] = tmp;
  }
  }
//std::cerr << "[" << counter[0] << ":" << counter[1] << ":" << counter[2] << ":" << counter[3] << ":" << counter[4] << ":" << counter[5] << ":" << counter[6] << ":" << counter[7] << std::endl;
}*/


//functionspekare
// std::size_t (Vector<bool>::*)(void)


/*
  typedef std::size_t (Vector<bool>::*VectorWeight)(void) const;

//WRITE THE RESULT TO FILE, USE builtin as reference

VectorWeight weight[] = {
&Vector<bool>::weight_builtin,  //0
&Vector<bool>::weight_math,     //1
&Vector<bool>::weight_lookup8,  //2
&Vector<bool>::weight_lookup16, //3
&Vector<bool>::weight_sparse,   //4
&Vector<bool>::weight_dense     //5
};

FILE * pFile[6] = {
fopen("val_builtin.dat","w"),
fopen("val_math.dat","w"),
fopen("val_lookup8.dat","w"),
fopen("val_lookup16.dat","w"),
fopen("val_sparse.dat","w"),
fopen("val_dense.dat","w"),
};

for(std::size_t f=0;f<6;++f){
unsigned long long int start_time,final_time;
for(std::size_t c=0;c<32;c++){//test the 32 classes of density
start_time = rdtsc();
std::size_t val;

fprintf(pFile[f],"---[class%u]---",static_cast<unsigned int>(c));
for(std::size_t t=0;t<NUMBER_OF_VECTORS;t++){
val = CALL_MEMBER_FN(vtest[t][c],weight[f])(); //wo macro: (vtest[t].*weight[f])();

fprintf(pFile[f],"%u:%u\n",static_cast<unsigned int>(vtest[t][c]),static_cast<unsigned int>(val));
}
final_time = rdtsc();
std::cout<<(final_time-start_time)<<'\t'<<std::flush;
}
std::cout << std::endl;
};

for(unsigned int i=0;i<6;++i){ //close all files
fclose(pFile[i]);
}
*/



//Testing the result
    //diff val_builtin.dat val_math.dat
    //diff val_builtin.dat val_lookup8.dat
    //diff val_builtin.dat val_lookup16.dat
    //diff val_builtin.dat val_sparse.dat
    //diff val_builtin.dat val_dense.dat

    return 0;
}
