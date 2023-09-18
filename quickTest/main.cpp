#include <iostream>
#include "../Math/Random.h"
int main(){
    Lina::Math::Random i(4) ;
    std::cout<<i.int64() % 64<<'\n';
	return 0;
}
