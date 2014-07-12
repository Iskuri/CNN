/* 
 * File:   main.c
 * Author: christopher
 *
 * Created on 11 July 2014, 22:32
 */

#include <stdio.h>
#include <stdlib.h>
#include "NeuralNetwork.h"
#include "Neuron.h"

/*
 * 
 */
int main(int argc, char** argv) {

	srand(time(NULL));
	
	int i = 0;

	int neuronStructure[] = {3,3,5,3,1};
//	int neuronStructure[] = {2,3,1};

	NeuralNetwork neuralNetwork = generateNetwork(neuronStructure,5);

	//printf("Output before runnning %f\n",neuralNetwork.neurons[0][0].output);
	
	char* format = "%f ";
	
	while(1) {

		//printf("Starting round\n");

		setInput(&neuralNetwork,2,1);
	
		setInput(&neuralNetwork,0,1);
		setInput(&neuralNetwork,1,0);
		trainNetwork(&neuralNetwork,0,1);
//		printf(format,getOutput(&neuralNetwork,0));

		setInput(&neuralNetwork,0,1);
		setInput(&neuralNetwork,1,1);
		trainNetwork(&neuralNetwork,0,0);
//		printf(format,getOutput(&neuralNetwork,0));
//
		setInput(&neuralNetwork,0,0);
		setInput(&neuralNetwork,1,1);
		trainNetwork(&neuralNetwork,0,1);
//		printf(format,getOutput(&neuralNetwork,0));
//
		setInput(&neuralNetwork,0,0);
		setInput(&neuralNetwork,1,0);
		trainNetwork(&neuralNetwork,0,0);
//		printf(format,getOutput(&neuralNetwork,0));
		
		printf("\n");
	}
	

	
	return (EXIT_SUCCESS);
}

