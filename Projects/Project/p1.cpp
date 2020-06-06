#include <iostream>
#include <cmath>
using namespace std;
bool if_triangle_helper(int test_integer) {
    //EFFECTS: Determine whether test_integer is a triangle number

    int max_n = sqrt(2 * test_integer); //the maximum of n
    // We use sqrt(2 * test_integer) to reduce loop

    bool if_triangle = 0;
    for(int i = 0;i < max_n;++i) {
        if(test_integer == max_n * (max_n + 1) / 2) {
            if_triangle = 1;
        }
    }
    return if_triangle;
}
bool if_palindrome_helper(int test_integer){
    //REQUIRES: Test_integer should be positive
    //EFFECTS: Determine whether test_integer is palindrome number

    // Reversely construct int: reverse_num
    // If reverse_num==test_integer, then it's palindrome

    int digit,ten_exp = 0,reverse_num = 0,ordered_num = test_integer;
    // Ten_exp used to multiple 10
    // Ordered_num is a copy of test_integer, reduced by digit

    bool if_palindrome = 0;
    while(ordered_num) {
        digit=ordered_num % 10; // Last digit
        if(ordered_num != test_integer) {
            ten_exp = 10;
        }// When the last digit is removed, multiple by 10
        // Before last digit is removed, multiple by 0 (reverse_num=last digit)

        reverse_num = reverse_num * ten_exp+digit;
        ordered_num /= 10;
    }
    if(reverse_num == test_integer) {
        if_palindrome = 1;
    }
    return if_palindrome;
}
bool if_power_givenbase(int test_integer, int base) {
    // REQUIRES: Base>=2(given), abs(test_integer)>=2, and index>=2
    int power = 1;// We use power to "reproduce" the input test_integer, to see if they are the same

    power *= base * base;// Because in tutorial, index>=2
    while(power < test_integer) {
        power *= base;
    }
    return (power == test_integer);
}
bool if_power_helper(int test_integer) {
    // REQUIRES: Index>=2
    // EFFECTS: Determine whether test_integer is a power number or not
    int base = 2;
    bool if_power = 0;
    // Special case: 1 base=1
    if(test_integer == 1) {
        if_power = 1;
        return if_power;
    }
    while(base <= sqrt(test_integer) && if_power == 0) {
        //If base hasn't reached its maximum try, or not a power number
        //Maximum try=sqrt(abs(test_integer)), to reduce while loop
        if_power=if_power_givenbase(test_integer,base);
        // Try if the given base is the right base
        base ++;
        // Try another base
    }
    return if_power;
}
bool if_abundant_helper(int test_integer) {
    //REQUIRES: Test_integer should be positive
    //EFFECTS: Determine whether test_integer is abundant
    int num = test_integer;
    //cout<<"num "<<num<<endl;
    int sum = 0;
    bool if_abundant = 0;
    // Use this loop to find out all divisors, store them in divisor_array
    for(int i = 2;i < sqrt(num);++ i) {
        if(num % i == 0) {
            sum += num / i + i;
            //cout << "i is: " << i <<endl;
        }
    }
    sum++;
    if(sum>test_integer){
        if_abundant = 1;
    }
    return if_abundant;
}

int main() {
    int test_integer = 0,case_num = 0;
    while(test_integer <= 0 || test_integer > 10000000|| case_num > 4 || case_num < 1){
        cout << "Please enter the integer and the test number: " << endl;
        cin >> test_integer >> case_num;
    }
    switch(case_num) {
        case(1):cout << if_triangle_helper(test_integer) << endl;
            break;
        case(2):cout << if_palindrome_helper(test_integer) << endl;
            break;
        case(3):cout << if_power_helper(test_integer) << endl;
            break;
        case(4):cout << if_abundant_helper(test_integer) << endl;
            break;
        default:
            break;
    }
    return 0;
}
