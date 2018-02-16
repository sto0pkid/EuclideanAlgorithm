#include <iostream>
#include <stdlib.h>

/*
Euclid's algorithm to compute the greatest common divisor of
two natural numbers.
*/


struct string{
private:
 char * s;
 unsigned int l;
public:
 unsigned int length(){
  return l;
 }
 string(){
  l = 0;
 }
 string(char * in){
  s = in;
  unsigned int i = i;
  while(s[i-1] != '\0') i++;
  l = i;
 }
 char operator[](unsigned int i){
  if(i >= l){
   std::cout << "string[] access out of bounds error\n";
  }
  return s[i];
 }
 void update(char * in){
  s = in;
  unsigned int i = 1;
  while(s[i-1] != '\0') i++;
  l = i;
 }
};

struct const_string{
private:
 const char * s;
 unsigned int l;
public:
 unsigned int length(){
  return l;
 }
 const_string(){
  l = 0;
 }
 const_string(const char * in){
  s = in;
  unsigned int i = i;
  while(s[i-1] != '\0') i++;
  l = i;
 }
 char operator[](unsigned int i){
  if(i >= l){
   std::cout << "string[] access out of bounds error\n";
  }
  return s[i];
 }
 void update(const char * in){
  s = in;
  unsigned int i = 1;
  while(s[i-1] != '\0') i++;
  l = i;
 }

};

bool str_eq_unguarded(char * s1, char * s2){
 while((*s1 == *s2) && (*s1 != '\0') && (*s2 != '\0')){
  s1++;
  s2++;
 }
 return *s1 == '\0' && *s2 == '\0';
}

bool const_str_eq_unguarded(const char *s1, const char *s2){
 while((*s1 == *s2) && (*s1 != '\0') && (*s2 != '\0')){
  s1++;
  s2++;
 }
 return *s1 == '\0' && *s2 == '\0'; 
}

unsigned int pow_simple(unsigned int x, unsigned int y){
 int r = 1;
 for(int i=0;i<y;i++){
  r = r * x;
 }
 return r;
}


void print(char * s){
 std::cout << s << std::endl;
}

bool check_nat(char * s){
 int i = 0;
 while(s[i] != '\0'){
  if(!(('0' <= s[i]) && (s[i] <= '9'))) return false;
  i++;
 }
 return true;
}

bool checknat2str(char * in, string * out) {
 int i = 0;
 while(in[i] != '\0'){
  if(!(('0' <= in[i]) && (in[i] <= '9'))) return false;
  i++;
 }
 out->update(in);
 return true;
}

bool const_checknat2str(const char * in, const_string * out){
 int i = 0;
 while(in[i] != '\0'){
  if(!(('0' <= in[1]) && (in[1] <= '9'))) return false;
  i++;
 }
 out->update(in);
 return true;
}

/*
s must be null-terminated.
*/
unsigned int get_length(char * s){
 unsigned int i = 0;
 while(s[i] != '\0') i++;
 return i;
}

unsigned int char2digit_unguarded(char c){
 return c - 48;
}

unsigned int char2digit_guarded(char c){
 //section: tag01
 //Bad: doesn't have anything to do with the function, only with
 // how it's used by other things, so it should be the concern
 // of the other things.
 if(!(('0' <= c) && (c <= '9'))){
  std::cout << "char2digit_guarded: only 0-9 please.\n" << std::endl;
  exit(1);
 }
 //endsection: tag01

 return c - 48;
}

unsigned int str2uint_unguarded(string * s){
 unsigned int r = 0;
 unsigned int l = s->length() - 2;
 for(int i = 0; i <= l; i++){
   r += pow_simple(10,l - i) * ((*s)[i] - '0');
 }
 return r;
}

unsigned int const_str2uint_unguarded(const_string * s){
 unsigned int r = 0;
 unsigned int l = s->length() - 2;
 for(int i = 0; i <= l; i++){
   r += pow_simple(10,l - i) * ((*s)[i] - '0');
 }
 return r;
}


unsigned int bitlength(unsigned int n){
 if(n == 0) return 0;
 if(n == 1) return 1;
 unsigned int r = 1;
 while((~0 & (n >>= 1)) != 0) r++;
 return r;
}


//simple, but extremely slow. avoid.
void divide_with_remainder(unsigned int x, unsigned int y, unsigned int * q, unsigned int * r){
 if (y == 0){
  std::cout << "division by 0 error! you fail\n" << std::endl;
  exit(1);
 }
 if (y > x){
  *q = 0;
  *r = x;
  return;
 }
 unsigned int q_tmp = 1;
 while(x - (q_tmp*y) >= y){
  q_tmp++;
 }
 *q = q_tmp;
 *r = x - (q_tmp*y);
}

void divide_with_remainder_faster(unsigned int x, unsigned int y, unsigned int * q, unsigned int * r){
 if (y == 0){
  std::cout << "division by 0 error! you fail\n" << std::endl;
 }
 if (y == 1){
  *q = x;
  *r = 0;
  return;
 }
 if (y > x){
  *q = 0;
  *r = x;
  return;
 }

 if (x == y){
  *q = 1;
  *r = 0;
 }

 unsigned int xl = bitlength(x);
 unsigned int yl = bitlength(y);

 unsigned int q_tmp_y = y;
 unsigned int exp = 0;
 bool pow2 = false;
 
 while((int)(x - (q_tmp_y << 1)) >= 0){
  q_tmp_y <<= 1;
  exp++;
 }
 unsigned int q_tmp = 1 << exp;
 for(int i=exp-1;i>=0;i--){
  if((q_tmp_y + (y << i)) < x){
   q_tmp_y += (y << i);
   q_tmp += (1 << i);
  }
  if((q_tmp_y + (y << i)) == x){
   q_tmp_y += (y << i);
   q_tmp += (1 << i);
   break;
  }
 }
 *q = q_tmp;
 *r = x - q_tmp_y;
}



unsigned int gcd_unguarded_verbose(unsigned int x, unsigned int y){
 if(x == y || y == 0) return x;
 if(x == 1 || y == 1) return 1;
 if(x == 0) return y;
 unsigned int a = x >= y ? x : y;
 unsigned int b = x >= y ? y : x;
 unsigned int q;
 unsigned int r;
 divide_with_remainder_faster(a,b,&q,&r);
 std::cout << a << " = " << b << "*" << q << " + " << r << std::endl;
 if(r == 0) return b;
 unsigned int gcd = r;
 while(r != 0){
  gcd = r;
  a = b;
  b = r;
  divide_with_remainder_faster(a,b,&q,&r);
  std::cout << a << " = " << b << "*" << q << " + " << r << std::endl;
 }
 return gcd;
}

unsigned int gcd_unguarded_silent(unsigned int x, unsigned int y){
 if(x == y || y == 0) return x;
 if(x == 1 || y == 1) return 1;
 if(x == 0) return y;
 unsigned int a = x >= y ? x : y;
 unsigned int b = x >= y ? y : x;
 unsigned int q;
 unsigned int r;
 divide_with_remainder_faster(a,b,&q,&r);
 if(r == 0) return b;
 unsigned int gcd = r;
 while(r != 0){
  gcd = r;
  a = b;
  b = r;
  divide_with_remainder_faster(a,b,&q,&r); 
 }
 return gcd;
}



int main(int argc, char** argv){
 if((argc != 3) && (argc != 4)){
  std::cout << "I'm only implementing this for two inputs right now!" << std::endl;
  return false;
 }

 bool verbose = false;
 const char * arg1;
 const char * arg2;
 if(argc == 4){
  if(const_str_eq_unguarded(argv[1],"-v") || const_str_eq_unguarded(argv[1],"--verbose")){
   verbose = true;
   arg1 = argv[2];
   arg2 = argv[3];
  }
  else{
   std::cout << "Unrecognized option `" << argv[1] << "`." << std::endl;
   exit(1);
  }
 }else{
  arg1 = argv[1];
  arg2 = argv[2];
 }

 const_string * in1 = new const_string();
 const_string * in2 = new const_string();

 if(!const_checknat2str(arg1, in1) || !const_checknat2str(arg2, in2)){
  std::cout << "Only natural number arguments please." << std::endl;
 }
 
 unsigned int int1 = const_str2uint_unguarded(in1);
 delete in1;
 unsigned int int2 = const_str2uint_unguarded(in2);
 delete in2;

 
 unsigned int gcd = verbose ? gcd_unguarded_verbose(int1,int2) : gcd_unguarded_silent(int1,int2);
 
 unsigned int q1,r1,q2,r2;
 
 if(verbose){
  std::cout << "\ngcd(" << int1 << ", " << int2 << "): " << gcd << std::endl;

  /*
  //Uncomment this section to see just how much slower this version is on large inputs.
  std::cout << "\nTesting slower: ..." << std::endl;
  divide_with_remainder(int1,gcd,&q1,&r1);
  divide_with_remainder(int2,gcd,&q2,&r2);
 
  std::cout << int1 << "/" << gcd << " = (" << q1 << ", " << r1 << ")" << std::endl;
  std::cout << int2 << "/" << gcd << " = (" << q2 << ", " << r2 << ")" << std::endl;
  */ 

  std::cout << "\nTesting...\n" << std::endl;
  divide_with_remainder_faster(int1,gcd,&q1,&r1);
  divide_with_remainder_faster(int2,gcd,&q2,&r2);
 
  if(r1 != 0 || r2 != 0){
   std::cout << "Test failed: " << std::endl;
   std::cout << int1 << "/" << gcd << " = (" << q1 << ", " << r1 << ")" << std::endl;
   std::cout << int2 << "/" << gcd << " = (" << q2 << ", " << r2 << ")" << std::endl;
  }else{
   std::cout << int1 << "/" << gcd << " = " << q1 << std::endl;
   std::cout << int2 << "/" << gcd << " = " << q2 << std::endl;
  }
  std::cout << "\nIn loving memory of Euclid." << std::endl;
 }else{
  std::cout << gcd << std::endl;
 }
}
