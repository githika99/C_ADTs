/*
Githika Annapureddy
CruzId: gannapur
pa6
*/
//-----------------------------------------------------------------------------
//  BigIntegerTest.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   //MY TESTS
   cout << "New: " << BigInteger(123456789) << endl;

   BigInteger AL = BigInteger(123456789);
   cout << "AL: " << AL << endl << endl << endl << endl;

   BigInteger GL = BigInteger(-123456789);
   cout << "GL: " << GL << endl << endl << endl << endl;
   BigInteger ALL = BigInteger("123456789");
   try{
      BigInteger ALLL = BigInteger("");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   BigInteger BL = BigInteger("123456789");
   BigInteger CL = BigInteger("-123456789");
   BigInteger DL = BigInteger("0000000");
   cout << "(D + A) = " << DL + AL;
   cout << "(C + B) = " << CL + BL;
   
   //compare tests
   cout << "(D < A) = " << ((DL < AL)?"True":"False") << endl;      //True
   cout << "(D > A) = " << ((DL > AL)?"True":"False") << endl;      //False
   cout << "(D == A) = " << ((DL == AL)?"True":"False") << endl;      //False
   cout << "(C < A) = " << ((CL < AL)?"True":"False") << endl;      //True
   cout << "(C > A) = " << ((CL > AL)?"True":"False") << endl;      //False
   cout << "(C == A) = " << ((CL == AL)?"True":"False") << endl;      //False
   cout << "(D < C) = " << ((DL < CL)?"True":"False") << endl;      //False
   cout << "(D > C) = " << ((DL > CL)?"True":"False") << endl;      //True
   cout << "(D == C) = " << ((DL == CL)?"True":"False") << endl;      //False
   cout << "(A < B) = " << ((AL < BL)?"True":"False") << endl;      //False
   cout << "(A > B) = " << ((AL > BL)?"True":"False") << endl;      //False
   cout << "(A == B) = " << ((AL == BL)?"True":"False") << endl;      //True

   cout << "(A <= B) = " << ((AL <= BL)?"True":"False") << endl;      //True
   cout << "(A >= B) = " << ((AL >= BL)?"True":"False") << endl;      //True
   cout << "(D <= A) = " << ((DL <= AL)?"True":"False") << endl;      //True
   cout << "(D >= A) = " << ((DL >= AL)?"True":"False") << endl;      //False
   cout << "(D <= C) = " << ((DL <= CL)?"True":"False") << endl;      //False
   cout << "(D >= C) = " << ((DL >= CL)?"True":"False") << endl;      //True
   cout << "(C <= A) = " << ((CL <= AL)?"True":"False") << endl;      //True
   cout << "(C >= A) = " << ((CL >= AL)?"True":"False") << endl;      //False

   //make zero test
   AL.makeZero();
   DL.makeZero();

   //negate tests
   BL.negate();
   CL.negate();
   AL.negate();
   
   cout << "D: " << DL << endl << endl << endl << endl;

   cout << "(D < A) = " << ((DL < AL)?"True":"False") << endl;
   BigInteger EL = BigInteger("000000");
   BigInteger GLL = AL + DL;
   
   cout << "B: " << BL << endl;
   cout << "G: " << GL << endl;
   cout << "A: " << BigInteger(-123456789) << endl;
   cout << "B: " << BL << endl;
   cout << "G: " << GL << endl;
   cout << "A: " << BigInteger(000) << endl;
   cout << "B: " << BL << endl;
   cout << "G: " << GL << endl;
   cout << "D: " << DL << endl;
   cout << "E: " << CL << endl;

   //BigInteger N;
   BigInteger AA = BigInteger(2147483647);
   cout << "AA = " << AA << endl;
   BigInteger AB = BigInteger(-2147483647);
   cout << "AB = " << AB << endl;
   BigInteger AC = BigInteger(0000000000);
   cout << "AC = " << AC << endl;


   
   //TANTALO TESTS
   //Test input 0000000
   string s1 = "91287346670000043892345634563400005619187236478";
   //string s2 = "-330293847502398475";
   string s3 = "9876545439000000345634560000000002000034565430000000006543654365346534";
   //string s4 = "9876545439000000000000000100000000000006543654365346534";
   string s5 = "98765454390000034563456191872363456345619187236000456456345756780000065436543";
   //string s6 = "9876545439000000000000000000000000000006543";

   BigInteger A = BigInteger(s1);
   BigInteger B = BigInteger(s3);
   BigInteger C = BigInteger(s5);

   cout << endl;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;

   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

   cout << " doing D = A+B" << endl;
   BigInteger D = A+B;
   cout << " doing E = B+A" << endl;
   BigInteger E = B+A;
   cout << " doing F = D-E" << endl;
   BigInteger F = D-E;
   cout << " doing G = 53234*A + 29384747*B + 928374*C" << endl;
   BigInteger G = 53234*A + 29384747*B + 928374*C;
   cout << " doing H = A*B" << endl;
   BigInteger H = A*B;
   cout << " doing I = B*A" << endl;
   BigInteger I = B*A;
   cout << " doing J = G*H*I" << endl;
   BigInteger J = G*H*I;

   cout << "D = " << D << endl;
   cout << "E = " << E << endl;
   cout << "(D==E) = " << ((D==E)?"True":"False") << endl;
   cout << "F = " << F << endl;
   cout << "G = " << G << endl;
   cout << "H = " << H << endl;
   cout << "I = " << I << endl;
   cout << "(H==I) = " << ((H==I)?"True":"False") << endl;
   cout << "J = " << J << endl << endl;

   cout << endl;

   cout << " doing A += B" << endl;
   A += B;
   cout << " doing B -= C" << endl;
   B -= C;
   cout << " doing C *= J" << endl;
   C *= J;

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;

   cout << A*B*C*D*E*G*H*I*J << endl << endl;

   cout << endl;

   // test exceptions
   cout << "first test:" <<endl;
   try{
      BigInteger J = BigInteger("");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   cout << "second test:" <<endl;
   try{
      BigInteger J = BigInteger("+");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   cout << "third test:" <<endl;
   try{
      BigInteger J = BigInteger("12329837492387492837492$4982379487293847");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   cout << "forth test:" <<endl;
   try{
      BigInteger J = BigInteger("5298374902837409+82734098729287349827398");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;
   

   return EXIT_SUCCESS;
}
/*

A = 91287346670000043892345634563400005619187236478
B = 9876545439000000345634560000000002000034565430000000006543654365346534
C = 98765454390000034563456191872363456345619187236000456456345756780000065436543

(A==B) = False
(A<B)  = True
(A<=B) = True
(A>B)  = False
(A>=B) = False

D = 9876545439000000345634651287346672000078457775634563406549273552583012
E = 9876545439000000345634651287346672000078457775634563406549273552583012
(D==E) = True
F = 0
G = 91691570173650851106757235057418467332079268623067668385924075924402893716400757832
H = 901603627392000803186807983911639635120177567956653774933087809594845872987983475989051173678812345278791356275667252
I = 901603627392000803186807983911639635120177567956653774933087809594845872987983475989051173678812345278791356275667252
(H==I) = True
J = 74535078040990221951579707664760083086194636252376057102875923822906784220802539003149718034573047938535029242308756956856746757203239654898553664856328697188650413317308676844093819953117379814120261091686365495161362772820114843698880436049710688561679618896170992168113950326602961426544121458199784856876441139328


A = 9876545439000000345634651287346672000078457775634563406549273552583012
B = -98765444513454595563455846237803456345617187201435026456345750236345700090009
C = 7361490850712512892784627033366712377962608677954778335567887688438699506458048695347135782298367251714193352297106125262185543692679226723456078336212281289033433526300541147317124089743774438392318975745770239822243919695549122883934462327415993720513037054202880924166077086016967703242033543931551392070700003782811005555057350956360991232997642441779203214776248960685958387926300605663104

-3891413836891634252603615944231533100802311932304539756631535191438569425955743011321244420825684271689812326377153614738866866996133078158617889706419411534748335044442873162002796822470923766037137857440201960116618085157210253486884526177262783782705897644014301385303709172070034335275197758118880319539873891549555644440821323572680746022837469210040122292685611210042984137990156691308020660660827025623027412635529232750724357731406619886350388818722292963300705286643677587360400689200812647516590030658135316500722332253136096015760549515670629373898849533715980971404265333328511563689953623157371913284985370410351070670039907772235103563714960286884670192131872212095199385484660165714397741416705658725948232822665490201231815492741199714386588404788071113395521677743541468675362205467436537834687964538697153814823061832987605959031029817973811700657393455352459454041579437657796979071679463259675514987045858535789140795465177402481108254913037785984068710780894830244500184736455799035280681991797475217613525941392380001790763277368917109192906438857375813387875188571829780382730139483569791522204246860441084955415329854895637747893659337084907750866329434344167095647313506330214397554528563267241116166085836715953572260156247546648771307439370015663445306198669514256889534243589702153142272


BigInteger: Constructor: empty string
   continuing without interruption
BigInteger: Constructor: non-numeric string
   continuing without interruption
BigInteger: Constructor: non-numeric string
   continuing without interruption
BigInteger: Constructor: non-numeric string
   continuing without interruption
*/
