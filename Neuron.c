#include <math.h>

typedef double LEARNING_COEFFICIENT;
#define LEARNING_COEFFICIENT 0.1;


typedef struct {

	double output;
	double* inputs;
	double* weights;
	double errorSignal;
	int inputCount;
	
} Neuron;

double activationFunction(double input) {
	return 1/(1+exp(-input));
}

double derivativeFunction(double input) {
	return activationFunction(input)*(1-activationFunction(input));
}

double calculateDerivative(Neuron* neuron) {
	
	double increment = 0;
	int i;
	
	for(i = 0 ; i < neuron->inputCount ; i++) {
		increment += neuron->inputs[i]*neuron->weights[i];
	}

	return derivativeFunction(increment);
}

void updateWeights(Neuron* neuron) {
	
	double derivative = calculateDerivative(neuron);
	int i;
	
	for(i = 0 ; i < neuron->inputCount ; i++) {
		
		//printf("Updating weights with input val %f\n",neuron->inputs[i]);
		//printf("Updating weights with errorSignal val %f\n",neuron->errorSignal);
		neuron->weights[i] = neuron->weights[i] + (0.25 * neuron->errorSignal * derivative * neuron->inputs[i]);
		//printf("New weight value for %d: %f\n",i,neuron->weights[i]);
	}
}

//void calculateOutput(Neuron* neuron, Neuron inputNeurons) {
double calculateOutput(Neuron* neuron) {

	int i;
	neuron->output = 0;
	
	for(i = 0 ; i < neuron->inputCount ; i++) {
		
		//printf("Using input val: %f\n",neuron->inputs[i]);
		//printf("Using weight val: %f\n",neuron->weights[i]);
		neuron->output += neuron->inputs[i] * neuron->weights[i];
	}
	
	neuron->output = activationFunction(neuron->output);
	return neuron->output;
}


