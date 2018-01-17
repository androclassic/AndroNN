#include "AndroNN.hpp"
#include <math.h>

namespace andro
{

	 NeuralNetwork::NeuralNetwork(const std::vector<int>& layers)
	 {
		 mLayers.resize(layers.size() - 1);
		 for (int i = 0; i < mLayers.size(); i++)
		 {
			 mLayers[i] = new Layer(*this, layers[i], layers[i + 1], i == (mLayers.size()-1));
		 }

		 Activation = [](float v) -> float { return std::tanh(v); };
		 ActivationDer = [](float v) -> float {return  1.0f - (v * v); };
		 CostDer = [](float y, float o) -> float { return  (o - y); };

		 mLearningRate = 0.0333f;
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

		 mLayers[0]->ForwardProp(input);

		 for (int i = 1; i < mLayers.size(); i++)
		 {
			 mLayers[i]->ForwardProp(mLayers[i - 1]->GetOutputs());
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


	Layer::Layer(const NeuralNetwork& nn,int nbInputs, int nbOutputs, bool isOutputL)
		:mNN(nn)
	{
		mNbInputs = nbInputs;
		mNbOutputs = nbOutputs;
		mIsOutputLayer = isOutputL;

		if (!mIsOutputLayer)
			mNbInputs++; //add bias term

		mOutputs.resize(mNbOutputs);
		mGamma.resize(mNbOutputs);
		mWeights.resize(mNbInputs);
		mWeightsDt.resize(mNbInputs);
		mOffset = 0.0f;

		for (int i = 0; i < mNbInputs; i++)
		{
			mWeights[i].resize(mNbOutputs);
			mWeightsDt[i].resize(mNbOutputs);
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


	void Layer::ForwardProp(const std::vector<float>& input)
	{
		mInputs = &input;
		for (int j = 0; j < mNbOutputs; j++)
		{
			mOutputs[j] = 0.0f;
			for (int i = 0; i < (*mInputs).size(); i++)
			{
				mOutputs[j] += (mWeights[i][j] * (*mInputs)[i]) ;
			}
	
			if (!mIsOutputLayer)
			{
				//bias term
				int biasIdx = mNbInputs - 1;
				mOutputs[j] += mWeights[biasIdx][j];

				//activation
				mOutputs[j] = mNN.Activation(mOutputs[j]);
			}
		}
	}

	void Layer::UpdateWeights()
	{
		for (int i = 0; i < mNbInputs; i++)
		{
			for (int j = 0; j < mNbOutputs; j++)
				mWeights[i][j] -= (mWeightsDt[i][j] * mNN.GetLearingRate());
		}
	}

	void Layer::BackProOutput(const std::vector<float>& expected)
	{
		_ASSERT(mNbOutputs == expected.size());
		_ASSERT(mIsOutputLayer);

		for (int i = 0; i < mNbOutputs; i++)
		{
			//get error
			float error = mNN.CostDer(expected[i], mOutputs[i]);
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
		_ASSERT(mIsOutputLayer == false);

		for (int i = 0; i < mNbOutputs; i++)
		{
			mGamma[i] = 0.0f;
			for (int j = 0; j < gammaForward.size(); j++)
			{
				mGamma[i] +=  (gammaForward[j] * weightsForward[i][j]);
			}
			mGamma[i] *= mNN.ActivationDer(mOutputs[i]);
		}

		//layer weights delta
		for (int i = 0; i < mNbInputs-1; i++)
		{
			for (int j = 0; j < mNbOutputs; j++)
			{
				mWeightsDt[i][j] = mGamma[j] * (*mInputs)[i];
			}
		}

		//bias term
		int biasIdx = mNbInputs - 1;
		for (int j = 0; j < mNbOutputs; j++)
		{
			mWeightsDt[biasIdx][j] = mGamma[j];
		}
	}
}
