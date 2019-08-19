/*
 * MACROSh.h
 *
 * Created: 5/3/2019 10:39:58 AM
 *  Author: Hamdy
 */ 


#ifndef MACROSH_H_
#define MACROSH_H_

	#define SETBIT(R,B)			(R |= (1<<(B)))
	#define CLEARBIT(R,B)		(R &=~ (1<<(B)))
	#define TOGGLEBIT(R,B)		(R ^= (1<<(B)))
	
	#define ISBITSET(R,B)		( (R & (1<<(B))) >>(B))
	#define ISBETCLEAR(R,B)		(!ISBITSET(R,B))

#endif /* MACROSH_H_ */