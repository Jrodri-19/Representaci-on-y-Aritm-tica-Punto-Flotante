#include <bits/stdc++.h>
using namespace std;
typedef union {float input; int output;} FloatIntUnion;
bitset<32> floatToBitset(float f) {
	FloatIntUnion fiu;fiu.input = f;
	return bitset<32>(fiu.output);
}
float bitsetToFloat(std::bitset<32> bits) {
	FloatIntUnion fiu;fiu.output =  (int)(bits.to_ulong());
	return fiu.input;
}
void extractComponents(const bitset<32>& bits, bitset<1>& sign, bitset<8>& exponent, bitset<23>& significa) {
	sign = bitset<1>(bits.to_string().substr(0, 1));
	exponent = bitset<8>(bits.to_string().substr(1, 8));
	significa = bitset<23>(bits.to_string().substr(9, 23));
}
bitset<32> emulateFloatingPointMultiplication(const bitset<32>& x_b, const bitset<32>& y_b) {
	bitset<1> x_sign, y_sign;
	bitset<8> x_exponent, y_exponent;
	bitset<23> x_significa, y_significa;
	extractComponents(x_b, x_sign, x_exponent, x_significa);extractComponents(y_b, y_sign, y_exponent, y_significa);
	int exp = x_exponent.to_ulong() + y_exponent.to_ulong()-127;
	float sig = (1.0f + x_significa.to_ulong() / pow(2, 23)) * (1.0f + y_significa.to_ulong() / pow(2, 23));
	if (sig >= 2.0f) {sig /= 2;exp++;}
	bitset<32> result((x_sign.to_ulong() ^ y_sign.to_ulong()) << 31 | exp << 23 | static_cast<int>((sig - 1.0f) * pow(2, 23)));
	return result;
}
void printFloatMultiplication(float x, float y) {
	bitset<32> x_b = floatToBitset(x);bitset<32> y_b = floatToBitset(y);
	bitset<32> mult_result = emulateFloatingPointMultiplication(x_b, y_b);
	float mult = x * y;
	std::bitset<32> mult_bits = floatToBitset(mult);
	cout<<"-----------------------------------------\nResultados\nx: \t" << x_b << "\ny: \t"<<y_b <<"\nx * y: \t"<< mult_result<<"\nRpta:\t"<<mult_bits;	
}
int main() {
	float x, y;
	cout << "Ingrese dos numeros\nx:\t";cin >> x ;cout<<"y:\t";cin>>y;
	printFloatMultiplication(x, y);
	return 0;
}
