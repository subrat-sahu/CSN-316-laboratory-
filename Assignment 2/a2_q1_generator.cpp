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

string addBitStrings( string first, string second )
{
    string result;  // To store the sum bits
 
    // make the lengths same before adding
    int length = first.length();
 
    int carry = 0;  // Initialize carry
 
    // Add all bits one by one
    for (int i = length-1 ; i >= 0 ; i--)
    {
        int firstBit = first.at(i) - '0';
        int secondBit = second.at(i) - '0';
 
        // boolean expression for sum of 3 bits
        int sum = (firstBit ^ secondBit ^ carry)+'0';
 
        result = (char)sum + result;
 
        // boolean expression for 3-bit addition
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
    }
 
    // if overflow, then add a leading 1
    if (carry)
        result = '1' + result;
 
    return result;
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

int main() {
        string message, polynomial;
        getline(cin, message);
        getline(cin, polynomial);
	string newMessage = message;
        //cout << polynomial.length() << endl;
        //cout << message << "," << polynomial << endl;
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
	// cout << b3.to_string() << std::endl ;
	// cout << b3.to_string()  << " " << b4.to_string() << " " << rem << " "  << endl;
	string sum = newMessage.append(trimLeadingZeroes(rem.to_string()));
	cout << trimLeadingZeroes(sum) << endl; // 110010100 1100100101
	cout << trimLeadingZeroes(b4.to_string()) << endl;
	

        return 0;
}


