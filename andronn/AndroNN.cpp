#include "AndroNN.hpp"
#include <math.h>

namespace andro
{
	 float NeuralNetwork::LearningRate = 0.0333f;

	 float NeuralNetwork::Activation(float value)
	 {
		 return  std::tanh(value);
	 }

	 float  NeuralNetwork::ActivationDer(float value)
	 {
		 return  1.0f - (value * value);
	 }


	 NeuralNetwork::NeuralNetwork(const std::vector<int>& layers)
	 {
		 mLayers.resize(layers.size() - 1);
		 for (int i = 0; i < mLayers.size(); i++)
		 {
			 mLayers[i] = new Layer(layers[i], layers[i + 1]);
		 }

	 }

	 NeuralNetwork::~NeuralNetwork()
	 {
		 for (int i = 0; i < mLayers.size(); i++)
		 {
			 if (mLayers[i])
				 delete mLayers[i];
		 }

		 mLayers.clear();
	 }

	 const std::vector<float>&  NeuralNetwork::FeedForward(const std::vector<float>& input)
	 {
		 _ASSERT(mLayers.size());

		 mLayers[0]->ForwardProp(input, false);

		 for (int i = 1; i < mLayers.size(); i++)
		 {
			 mLayers[i]->ForwardProp(mLayers[i - 1]->GetOutputs(), i == (mLayers.size()-1));
		 }

		 return  mLayers[mLayers.size() - 1]->GetOutputs();
	 }


	 void NeuralNetwork::BackProp(std::vector<float>& expected)
	 {
		 _ASSERT(mLayers.size());
		 mLayers[mLayers.size() - 1]->BackProOutput(expected);
		 for (int i = mLayers.size() - 2; i >= 0; i--)
			 mLayers[i]->BackPropHidden(mLayers[i + 1]->GetGamma(), mLayers[i + 1]->GetWeights());

		 for (int i = 0; i < mLayers.size(); i++)
			 mLayers[i]->UpdateWeights();
	 }


	Layer::Layer(int nbInputs, int nbOutputs)
	{
		mNbInputs = nbInputs;
		mNbOutputs = nbOutputs;
		mOutputs.resize(nbOutputs);
		mGamma.resize(nbOutputs);
		mWeights.resize(nbInputs);
		mWeightsDt.resize(nbInputs);
		for (int i = 0; i < nbInputs; i++)
		{
			mWeights[i].resize(nbOutputs);
			mWeightsDt[i].resize(nbOutputs);
		}
		InitializeWeights();
	}

	void Layer::InitializeWeights()
	{
		for (int i = 0; i < mNbInputs; i++)
		{
			for (int j = 0; j < mNbOutputs; j++)
			{
				float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				mWeights[i][j] = r - 0.5f;
				mWeightsDt[i][j] = 0.0f;
			}
		}
	}


	void Layer::ForwardProp(const std::vector<float>& input, bool isLast)
	{
		mInputs = &input;
		for (int j = 0; j < mNbOutputs; j++)
		{
			mOutputs[j] = 0.0f;
			for (int i = 0; i < mNbInputs; i++)
			{
				mOutputs[j] += (mWeights[i][j] * (*mInputs)[i]) ;
			}
	
			//activation
			if (!isLast)
				mOutputs[j] = NeuralNetwork::Activation(mOutputs[j]);
		}
	}

	void Layer::UpdateWeights()
	{
		for (int i = 0; i < mNbInputs; i++)
		{
			for (int j = 0; j < mNbOutputs; j++)
				mWeights[i][j] -= (mWeightsDt[i][j] * NeuralNetwork::LearningRate);
		}
	}

	void Layer::BackProOutput(const std::vector<float>& expected)
	{
		_ASSERT(mNbOutputs == expected.size());

		for (int i = 0; i < mNbOutputs; i++)
		{
			//get error
			float error = mOutputs[i] - expected[i];
			//gamma
			mGamma[i] = error;
		}
		//layer weights delta
		for (int i = 0; i < mNbInputs; i++)
		{
			for (int j = 0; j < mNbOutputs; j++)
			{
				mWeightsDt[i][j] = mGamma[j] * (*mInputs)[i];
			}
		}
	}

	void Layer::BackPropHidden(const std::vector<float>& gammaForward, const DynMatf& weightsForward)
	{

		for (int i = 0; i < mNbOutputs; i++)
		{
			mGamma[i] = 0.0f;
			for (int j = 0; j < gammaForward.size(); j++)
			{
				mGamma[i] +=  (gammaForward[j] * weightsForward[i][j]);
			}
			mGamma[i] *= NeuralNetwork::ActivationDer(mOutputs[i]);
		}

		//layer weights delta
		for (int i = 0; i < mNbInputs; i++)
		{
			for (int j = 0; j < mNbOutputs; j++)
			{
				mWeightsDt[i][j] = mGamma[j] * (*mInputs)[i];
			}
		}
	}
}
