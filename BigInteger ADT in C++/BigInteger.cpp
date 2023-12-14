/*
Githika Annapureddy
CruzId: gannapur
pa6
*/
#include<string>
#include<sstream>
#include"BigInteger.h"

// BASE = 10^POWER, 0 <= POWER <= 9
const long BASE = 1000000000;
const int POWER = 9;

BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}

// MY LONG CONSTRUCTOR
// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    // std::cout << std::endl<< std::endl;
    // std::cout << "in long constructor" << std::endl;
    // std::cout << "x: " << x << std::endl;
    // create a BigInteger object representing the integer x
    signum = 0;
    if (x < 0){
        signum = -1;
        x *= -1;                //make x positive
    } else if (x == 0) {
        signum = 0;
        // std::cout << "printing digits as a List: " << this -> digits << std::endl;
        // std::cout << "signnum: " << this -> signum << std::endl;
        // std::cout << "Address of the object: " << this << std::endl;
        return;                 //return while List digits is empty
    } else {
        signum = 1;
    }
    //x is in BASE 10
    //parse p elements
    long temp = 0;
    while (x > 0) {
        temp = x % BASE;
        x -= temp;
        x /= BASE;
        //std::cout << "inserted: " << temp << std::endl;
        digits.insertAfter(temp);
        //std::cout << "printing digits as a List: " << this -> digits << std::endl;
    }
    // std::cout << "printing digits as a List: " << this -> digits << std::endl;
    // std::cout << "signnum: " << this -> signum << std::endl;
    // std::cout << "Address of the object: " << this << std::endl;

}

BigInteger::BigInteger(std::string s){
    if(s.length() == 0){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    signum = 1;
    if (int(s[0]) == 45) {                                  //'-'
        signum = -1;
        s = s.substr(1);       // eg: s = "-1234" -> s = "1234"
    }else if (int(s[0]) == 43) {                           //'+'
        s = s.substr(1);       // eg: s = "+1234" -> s = "1234"
    }
    bool zero = true;                      //yes string is only 0s

    if(s.length() == 0){
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }

    int n = -1;
    int length = s.length();
    for(int count = 0; count < length; count++){
        if(int(s[count]) < 48 ||  int(s[count]) > 57){                   //check that the ASCII value is in the number range
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
        if (zero && int(s[count]) != 48 ) {         //if s[count] != '0'
            n = count;
            zero = false;
        }
    }

    if(zero) {
        signum = 0;
        return;
    }
    s.erase(0, n);       //remove leading 0s
    length = s.length();
    
    for(int n = 1;(n * POWER) - length < POWER; n++){
        int p = length - n * POWER;
        std::string curr_num;
        if(p <= 0){
            curr_num = s.substr(0, POWER + p);
        }else{
            curr_num = s.substr(p, POWER);
        }
        ListElement curr_long = std::stol(curr_num);
        digits.insertAfter(curr_long);
    }
}

BigInteger::BigInteger(const BigInteger& N){
    signum = N.signum;
    digits = List(N.digits);
}

int BigInteger::sign() const{
    return(signum);
}

int BigInteger::compare(const BigInteger& N) const{
    BigInteger M = N;
    BigInteger K = *this;

    if (K.signum == 0){
        if (M.signum == -1)
            return 1;               //0 > -1
        else if (M.signum == 0)
            return 0;               //0 = 0
        else
            return -1;              //0 < 1
    }
    else if (K.signum == 1){
        if (M.signum == 1) {       //compare which number is bigger
            if(K.digits.length() > M.digits.length()){                    //this > N
                return 1;
            } else if(K.digits.length() < M.digits.length()){                    //this < N
                return -1;
            }
            while(K.digits.length() > 0) {
                ListElement temp1 = K.digits.front();
                ListElement temp2 = M.digits.front();
                if (temp1 > temp2) {
                    return 1;                                   //this > N
                }
                else if (temp1 < temp2) {
                    return -1;                                   //this < N
                }
                K.digits.eraseAfter();
                M.digits.eraseAfter();
            }
            return 0; 
        }           
        else                        //N.signum = -1 or 0, either way 
            return 1;               //signum > N.signum            
    }
    else { //signum == -1
        if (M.signum == -1) {       //compare which number is bigger/smaller
            if(K.digits.length() > M.digits.length()){                    //this > N
                return 1;
            } else if(K.digits.length() < M.digits.length()){                    //this < N
                return -1;
            }
            while(K.digits.length() > 0) {
                ListElement temp1 = K.digits.front();
                ListElement temp2 = M.digits.front();
                if (temp1 > temp2) {
                    return -1;                                   //magnitude of this > N, meaning this < N
                }
                else if (temp1 < temp2) {
                    return 1;                                   //magnitude of this < N, meaning this > N
                }
                K.digits.eraseAfter();
                M.digits.eraseAfter();
            }
            return 0; 
        }
        else                        //N.signum = 0 or 1, either way 
            return -1;               //signum < N.signum
    }
}

void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
}

void BigInteger::negate(){
    signum *= -1;
}

// Helper Functions------------------------------------------------------------------------------------------------------------------------

void normalize(List& N, int& s){
    N.moveFront();
    //first remove leading 0s
    while(N.length() > 0 && N.front() == 0){
        N.eraseAfter();
    }
    if(N.length() == 0){
        //if List contained only 0s
        s = 0;  //sets signum to 0
        return;
    } else {
        N.moveBack();
    }
    
    while(N.position() > 0){
        ListElement curr = N.movePrev();
        ListElement carry = 0;
        if (curr >= 0 && BASE < curr){      //curr is too large
            carry = 1;
            // while curr num + carry is larger than base, increment carry
            while(BASE < (BASE * -carry) + curr) {        
                    carry++;
                }
            N.setAfter((BASE * -carry) + curr);
        } else if(curr < 0){
            if(N.position() == 0){  
                //the negative gets taken to the signum
                s *= -1;
                N.moveNext();
                N.setBefore(-1 * curr);
                return;
            } else {
                carry = -1;
                //keep decreasing carry while it would not make curr positive
                while((BASE * -carry) + curr < 0) {        
                    carry--;
                }
                //set curr to desired value
                N.setAfter((BASE * -carry) + curr);
            }
        } 
        if(N.position() == 0){ 
            if (carry > 0) {
                N.insertAfter(carry);   
            } else if (carry < 0){
                s = -1;             //since carry is negative at front of list, signum must be made to -1
                ListElement after = N.peekNext();
                N.setAfter(-after);
                if(N.front() < 0){
                    N.setAfter(BASE + -after);
                    N.moveNext();
                    while(N.length() > N.position()){
                        after = N.moveNext();
                        N.setBefore(BASE - after);
                    }
                }
            }
        } else if(N.position() > 0){
            ListElement prev = N.peekPrev();
            N.setBefore(carry + prev);
        }
    }
}

void shiftList(List& L, int shift){
    L.moveBack();
    for (int i = 0; i < shift; i++) {
        L.insertAfter(0);
    }
}

void sumList(List& A, List M1, List N1, int sgn){
    N1.moveBack();
    M1.moveBack();
    while(M1.position() > 0 && N1.position() > 0){
        ListElement m = M1.movePrev();
        ListElement n = N1.movePrev();
        if (sgn == 1) {
            A.insertAfter(m + n);
        } else if (sgn == -1) {
            A.insertAfter(m - n);
        }
    }
    
    while(N1.position() > 0){
        ListElement n = N1.movePrev();
        if (sgn == 1) {
            A.insertAfter(n);
        } else if (sgn == -1) { 
            A.insertAfter(-n);
        }
    }

    while(M1.position() > 0){
        ListElement m = M1.movePrev();
        A.insertAfter(m);
    }
}

List scalarMultList(List A, ListElement scalar) {
    ListElement curr = 0;
    ListElement carry = 0;
    List L; 
    A.moveBack();
    while (A.position() > 0) {
        curr = carry + (scalar * A.peekPrev());
        carry = curr / BASE;
        curr %= BASE;
        L.insertAfter(curr);
        A.movePrev();
    }
    if (carry > 0) {
        L.insertAfter(carry);
    }
    return L;
}

BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger A;
    BigInteger N1(N);
    BigInteger M1(*this);
    if(M1.sign() == 0){
        return N1;
    }
    if(N1.sign() == 0){
        return M1;
    } 
    if(M1.sign() != N1.sign()){
        if(N1.sign() < 0){
            // return M1 - N1
            N1.negate();
            return M1.sub(N1);
        } else if (M1.sign() < 0) {
            // return N1 - M1
            M1.negate();
            return N1.sub(M1);
        }
    }
    A.signum = signum; 
    sumList(A.digits, M1.digits, N1.digits, 1);
    
    normalize(A.digits, A.signum);
    return A;
}

//returns M - N
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger A;
    BigInteger N1(N);
    BigInteger M1(*this);
    if(M1.sign() == 0){
        N1.negate();
        return(N1);
    }
    if(N1.sign() == 0){
        return M1;
    } 

    if(M1.sign() != N1.sign()){
        // if -M - N --> -M + -N
        // if M - (-N) --> M + N
        N1.negate();
        return M1.add(N1);
    }
    //now they're either both negative or both positive

    // -M - (-N) --> N - M
    if(N1.sign() < 0){
        M1.negate();
        N1.negate();
        return N1.sub(M1);
    }

    // 5 - 10 --> -(10 - 5)
    if(N1 > M1){
        //switch them 
        BigInteger temp = N1.sub(M1);
        temp.negate();
        return(temp);
    }
  
    A.signum = M1.signum;
    sumList(A.digits, M1.digits, N1.digits, -1);
    normalize(A.digits, A.signum);
    return A;
}


BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger A;       //change to A
    BigInteger M1 = *this;   //B -> M1
    BigInteger N1 = N;       //A -> N1
    if(M1.sign() == 0 || N1.sign() == 0){
        return A;
    }
    
    //make sure smaller number comes second, saves operation time
    if (N1.digits.length() > M1.digits.length()) {
        N1.mult(M1);
    }
    
    //multiplying M1 with N1
    //so N1 should be shorter
    int shift = 0;
    int l = N1.digits.length();
    N1.digits.moveBack();
    M1.digits.moveBack();
    for (int i = 0; i < l; i++) {      
        BigInteger temp;        
        List curr = scalarMultList(M1.digits, N1.digits.peekPrev()); 
        shiftList(curr, shift);
        temp.signum = 1;
        N1.digits.movePrev();   //move to previous element
        shift++;                //shift increments by 1 each time
        temp.digits = curr;
        A = A.add(temp);   
    }

    A.signum = M1.signum * N1.signum;
    return A; 
}


std::string BigInteger::to_string(){
    std::string s = "";
    if (signum < 0){
        s += "-";
    } else if (signum == 0){                //is this the right way to print 0?
        s += "0";
        return s;
    }
    digits.moveFront();
    while(digits.position() < digits.length()){
        ListElement temp = digits.moveNext();
        std::string temp_str = std::to_string(temp);
        //not sure if this does anything
        while(digits.position() != 1 && temp_str.length() < POWER){
            temp_str = '0' + temp_str;
        }
        s += temp_str;
    }
    return s;
}

std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 0){
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == -1){
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == -1 || A.compare(B) == 0){
        return true;
    }
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 1){
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 1 || A.compare(B) == 0){
        return true;
    }
    return false;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A.mult(B);
}