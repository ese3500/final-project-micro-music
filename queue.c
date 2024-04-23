/*
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

int qSize = 25;
int arr[qSize];
int qStart = 0;
int numElements = 0; 
int qPointer = 0;

int enqueue(int element) {
	
	if (numElements < qSize) {
		if (qPointer >= qSize - 1) {
			qPointer = 0; 
			
		} else {
			qPointer++;
		}
		arr[qPointer] = element;
		numElements++;
	}
	
}

int dequeue() {
	if (numElements > 0) {
		numElements--; 
		if (qPointer == 0) {
			qPointer = qSize - 1; 
		} else {
			qPointer - 1; 
		}
		int posPrev = qStart; 
		if( qStart == qSize - 1) {
			qStart = 0;
		} else {
			qStart++;
		}
		
		return arr[posPrev];
	}
}
*/