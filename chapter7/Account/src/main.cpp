

#include <iostream>

class Account{
public:
	int balance(Money price, size_t num) 
        {
		bal = price * num;
		return 1;
	};
private:
	typedef double Money;
	Money bal;
};

int main(int argc, char *argv[])
{
    Account acc;
    return 0;
}
