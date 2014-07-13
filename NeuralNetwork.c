#include "Neuron.h"
#include "NeuralNetwork.h"

typedef struct {

	Neuron** neurons;
	int networkSize;
	int* layerSize;
	
} NeuralNetwork;

void setInput(NeuralNetwork* neuralNetwork, int pos, double val) {

	neuralNetwork->neurons[0][pos].inputs[0] = val;
}

double getOutput(NeuralNetwork* neuralNetwork, int outPos) {
	
	int i;
	int j;
	int k;

	//printf("Network size %d\n",neuralNetwork->networkSize);
	
	for(i = 0 ; i < neuralNetwork->networkSize ; i++) {
	
		//printf("Layer size %d\n",neuralNetwork->layerSize[i]);
		
		for(j = 0 ; j < neuralNetwork->layerSize[i] ; j++) {

//			calculateOutput(neuralNetwork->neurons[i][j], &neuralNetwork->neurons[i-1]);
			//printf("Doing %d,%d ",i,j);
			calculateOutput(&neuralNetwork->neurons[i][j]);

			//printf("Output after runnning %f\n",neuralNetwork->neurons[i][j].output);
			
			if(i < (neuralNetwork->networkSize-1)) {
				
				for(k = 0 ; k < neuralNetwork->layerSize[i+1] ; k++) {
					neuralNetwork->neurons[i+1][k].inputs[j] = neuralNetwork->neurons[i][j].output;
				}
			}
		}
	}
	
	return neuralNetwork->neurons[neuralNetwork->networkSize-1][outPos].output;
}

void flushErrorSignal(NeuralNetwork* neuralNetwork) {
	
	int i;
	int j;

	for(i = 0 ; i < neuralNetwork->networkSize ; i++) {

		for(j = 0 ; j < neuralNetwork->layerSize[i] ; j++) {
			neuralNetwork->neurons[i][j].errorSignal = 0;
		}
	}
	
}

void trainNetwork(NeuralNetwork* neuralNetwork, int outPos, double outVal) {
	
	flushErrorSignal(neuralNetwork);
	
	double currentOut = getOutput(neuralNetwork, outPos);

	//allNeurons[allNeurons.length-1][index].errorSignal = value
	neuralNetwork->neurons[neuralNetwork->networkSize-1][outPos].errorSignal = outVal - currentOut;
	//printf("%f = %f - %f\n",neuralNetwork->neurons[neuralNetwork->networkSize-1][outPos].errorSignal,outVal,currentOut);
	int i;
	int j;
	int k;

	for(i = neuralNetwork->networkSize-1 ; i >= 0 ; i--) {
		
		for(j = 0 ; j < neuralNetwork->layerSize[i] ; j++) {

			if(i > 0) {
				for(k = 0 ; k < neuralNetwork->layerSize[i-1] ; k++) {
					neuralNetwork->neurons[i-1][k].errorSignal += 
							(neuralNetwork->neurons[i][j].errorSignal * neuralNetwork->neurons[i][j].weights[k]);
//					printf("%d,%d,%d: %f\n",i,j,k,neuralNetwork->neurons[i-1][k].errorSignal);
				}
			}
		}
	}

	for(i = 0 ; i < neuralNetwork->networkSize ; i++) {
		
		for(j = 0 ; j < neuralNetwork->layerSize[i] ; j++) {
			updateWeights(&neuralNetwork->neurons[i][j]);
		}
	}

	
//	printf("Current out: %f\n",currentOut);
	
}

NeuralNetwork generateNetwork(int* neuronStructure, int structureSize) {

	NeuralNetwork generatedNetwork;
	generatedNetwork.networkSize = structureSize;
	generatedNetwork.layerSize = malloc(sizeof(*generatedNetwork.layerSize * structureSize));
	
	int i = 0;
	int j = 0;
	int k = 0;
	//generatedNetwork.neurons = Neuron[structureSize];
	
	// allocating memory for neurons
	Neuron** neurons = (Neuron** ) malloc(structureSize * sizeof(Neuron*));
	
	for(i = 0 ; i < structureSize ; i++) {
		neurons[i] = (Neuron*)malloc(neuronStructure[i] * sizeof(Neuron));
	}

	//printf("Neuron structure size %d\n",structureSize);
	
	for(i = 0 ; i < structureSize ; i++) {
		
		//printf("Neuron structure %d\n",neuronStructure[i]);

		for(j = 0 ; j < neuronStructure[i] ; j++) {
			
			Neuron newNeuron;
//			newNeuron.output = 9001;
			
			generatedNetwork.layerSize[i] = neuronStructure[i];

			if(i == 0) {
				
				newNeuron.inputCount = 1;
				newNeuron.inputs = malloc(sizeof(*newNeuron.inputs * 1));
				newNeuron.weights = malloc(sizeof(*newNeuron.weights * 1));				
			} else {
				int mallocVal = sizeof(*newNeuron.inputs * neuronStructure[i-1]);
				
				//printf("Malloc val: %d\n", mallocVal);
				newNeuron.inputCount = neuronStructure[i-1];
				newNeuron.inputs = malloc(sizeof(*newNeuron.inputs * neuronStructure[i-1]));
				newNeuron.weights = malloc(sizeof(*newNeuron.weights * neuronStructure[i-1]));
				
			}

			for(k = 0 ; k < newNeuron.inputCount ; k++) {

				// randomising the weights
				newNeuron.weights[k] = (double)rand()/RAND_MAX*2;
				//printf("Random value %f\n",newNeuron.weights[k]);
			}

			neurons[i][j] = newNeuron;
		}
	}
	
	generatedNetwork.neurons = neurons;

	return generatedNetwork;
}