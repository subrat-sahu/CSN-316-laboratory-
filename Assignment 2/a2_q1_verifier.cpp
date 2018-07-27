#include <iostream>
#include <cstdlib>
#include <string>         // std::string
#include <bitset>
#include <stdexcept>
using namespace std;

template<size_t N> int top_bit_set(const bitset<N> &a) {
    int i;
    for (i = N-1; i >= 0; i--)
        if (a.test(i)) break;
    return i;
}

template<size_t N>
bitset<N> gf2_div(bitset<N> dividend, bitset<N> divisor, bitset<N> &remainder) {
    bitset<N> quotient(0);
    int divisor_size = top_bit_set(divisor);
    //if (divisor_size < 0) throw divide_by_zero();
    int bit;
    while ((bit = top_bit_set(dividend)) >= divisor_size) {
        quotient.set(bit - divisor_size);
        dividend ^= divisor << (bit - divisor_size); }
    remainder = dividend;
    return quotient;
}

string trimLeadingZeroes(string str_bits) {
	    // http://en.cppreference.com/w/cpp/string/basic_string/find
    const auto first_digit = str_bits.find('1') ; // locate the first '1'

    if( first_digit != std::string::npos ) // found it; print the substring starting at the first '1'
        return str_bits.substr(first_digit);
        
        return str_bits;
}

int main(int argc, char *argv[]) {
        string message = argv[1];
	string polynomial = argv[2];
	string newMessage = message;
        //cout << polynomial.length() << endl;
        // cout << message << "," << polynomial << endl;
        int s = polynomial.length();
	while(s > 1){
		message.append("0");
		s--;
	}
        char * p, * d;
        //long long parsed = strtoll(message, p, 2);
        //long long parsedP = strtoll(polynomial, d, 2);
        const int k = message.length();
	bitset<32> b3(message);  
	bitset<32> b4(polynomial);  // [0,0,1,1,0,0,1,0]
	bitset<32> rem;
	gf2_div(b3, b4, rem);
	if(trimLeadingZeroes(rem.to_string()) == rem.to_string()) cout << "YES" << endl;
	else cout << "NO" << endl;

        return 0;
}


