#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

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

	 std::function<float(float)> Activation;
	 std::function<float(float)> ActivationDer;
	 std::function<float(float expected, float output)> Cost;
	 std::function<float(float expected, float output)> CostDer;

	 float GetLearingRate() const { return mLearningRate; }
	 void SetLearingRate(float lr)  { mLearningRate = lr; }

private:
	float mLearningRate;

	std::vector<Layer*> mLayers;

};


class Layer
{
	typedef std::vector<std::vector<float>> DynMatf;


public:
	Layer(const NeuralNetwork& nn, int nbInputs, int nbOutputs, bool isOutputLayer);
	
	void ForwardProp(const std::vector<float>& input);
	void BackProOutput(const std::vector<float>& input);
	void BackPropHidden(const std::vector<float>& gammaForward, const DynMatf& weightsForward);


	const std::vector<float>& GetOutputs() const { return mOutputs; }
	const std::vector<float>& GetGamma() const { return mGamma; }
	const DynMatf& GetWeights() const { return mWeights; }
	bool isOutputLayer() const { return mIsOutputLayer; }

	void UpdateWeights();
private:
	void InitializeWeights();

	int mNbInputs;
	int mNbOutputs;
	bool mIsOutputLayer;

	const NeuralNetwork& mNN;
	const std::vector<float>* mInputs;
	std::vector<float> mOutputs;
	std::vector<float> mGamma;
	float mOffset;
	DynMatf  mWeights;
	DynMatf  mWeightsDt;

};

}
