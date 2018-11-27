#include <iostream>
#include <vector>



void breaker()
{
    std::vector<int> vec {1,2,3};
    for (int i=0; i<=vec.size(); i++) {
        std::cout << "never happening.?" << vec[i] << " ";
    }
    
}


int main()
{
    std::cout << "Hello CI" << std::endl;
    
    
    breaker();
    
    return 0;
}
