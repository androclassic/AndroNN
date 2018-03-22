#include <time.h>
#include <AndroNN.hpp>

using namespace andro;
int main()
{


	// 0 0 0     => 0
	// 0 0 1     => 1
	// 0 1 0     => 2
	// 0 1 1     => 3
	// 1 0 0     => 4
	// 1 0 1     => 5
	// 1 1 0     => 6
	// 1 1 1     => 7

	srand(time(NULL));
	NeuralNetwork net({ 3, 15, 15, 1 });

	std::vector<float> t0 = { 0, 0, 0 }; std::vector<float> e0 = { 0 };
	std::vector<float> t1 = { 0, 0, 1 }; std::vector<float> e1 = { 1 };
	std::vector<float> t2 = { 0, 1, 0 }; std::vector<float> e2 = { 2 };
	std::vector<float> t3 = { 0, 1, 1 }; std::vector<float> e3 = { 3 };
	std::vector<float> t4 = { 1, 0, 0 }; std::vector<float> e4 = { 4 };
	std::vector<float> t5 = { 1, 0, 1 }; std::vector<float> e5 = { 5 };
	std::vector<float> t6 = { 1, 1, 0 }; std::vector<float> e6 = { 6 };
	std::vector<float> t7 = { 1, 1, 1 }; std::vector<float> e7 = { 7 };

	for (int i = 0; i < 5000; i++)
	{
		net.FeedForward(t0); net.BackProp(e0);
		net.FeedForward(t1); net.BackProp(e1);
		net.FeedForward(t2); net.BackProp(e2);
		net.FeedForward(t3); net.BackProp(e3);
		net.FeedForward(t4); net.BackProp(e4);
		net.FeedForward(t5); net.BackProp(e5);
		net.FeedForward(t6); net.BackProp(e6);
		net.FeedForward(t7); net.BackProp(e7);

	}


	std::cout << "LOG: " << (net.FeedForward(t0)[0]) << std::endl;
	std::cout << "LOG: " << (net.FeedForward(t1)[0]) << std::endl;
	std::cout << "LOG: " << (net.FeedForward(t2)[0]) << std::endl;
	std::cout << "LOG: " << (net.FeedForward(t3)[0]) << std::endl;
	std::cout << "LOG: " << (net.FeedForward(t4)[0]) << std::endl;
	std::cout << "LOG: " << (net.FeedForward(t5)[0]) << std::endl;
	std::cout << "LOG: " << (net.FeedForward(t6)[0]) << std::endl;
	std::cout << "LOG: " << (net.FeedForward(t7)[0]) << std::endl;

	getchar();
	return 1;
}
