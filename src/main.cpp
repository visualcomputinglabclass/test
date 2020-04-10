#include<iostream>
#include<memory>

int main( int argc, char** argv )
{
    std::cout << "Hello World\n";
    std::unique_ptr< int > x = std::make_unique< int >( 3 );
    std::cout << *x << "\n";
    return 0;
}
