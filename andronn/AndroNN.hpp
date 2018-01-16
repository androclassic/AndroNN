#include<iostream>
#include<vector>
#include<algorithm>

namespace andro
{
	class Layer;

class NeuralNetwork
{
public:
	NeuralNetwork(const std::vector<int>& layers);
	~NeuralNetwork();

	const std::vector<float>&  FeedForward(const std::vector<float>& input);
	void BackProp(std::vector<float>& expected);

	static float Activation(float);
	static float ActivationDer(float);
	static float LearningRate;

private:
	std::vector<Layer*> mLayers;
};


class Layer
{
	typedef std::vector<std::vector<float>> DynMatf;


public:
	Layer(int nbInputs, int nbOutputs);
	
	void ForwardProp(const std::vector<float>& input, bool isLast);
	void BackProOutput(const std::vector<float>& input);
	void BackPropHidden(const std::vector<float>& gammaForward, const DynMatf& weightsForward);


	const std::vector<float>& GetOutputs() const { return mOutputs; }
	const std::vector<float>& GetGamma() const { return mGamma; }
	const DynMatf& GetWeights() const { return mWeights; }

	void UpdateWeights();
private:
	void InitializeWeights();

	int mNbInputs;
	int mNbOutputs;

	const std::vector<float>* mInputs;
	std::vector<float> mOutputs;
	std::vector<float> mGamma;
	DynMatf  mWeights;
	DynMatf  mWeightsDt;

};

}
