#ifndef BoundedBuffer_h
#define BoundedBuffer_h

#include <stdio.h>
#include <queue>
#include <string>
#include <pthread.h>
#include <thread>
#include <mutex> 
#include <assert.h>

using namespace std;

class BoundedBuffer
{
private:
	int cap; // max number of items in the buffer
	queue<vector<char>> q;	/* the queue of items in the buffer. Note
	that each item a sequence of characters that is best represented by a vector<char> for 2 reasons:
	1. An STL std::string cannot keep binary/non-printables
	2. The other alternative is keeping a char* for the sequence and an integer length (i.e., the items can be of variable length).
	While this would work, it is clearly more tedious */

	// add necessary synchronization variables and data structures 

	//for thread-safety
	mutex m;

public:
	BoundedBuffer(int _cap) {
		cap = _cap;
	}
	~BoundedBuffer(){

	}

	void push(char* data, int len){
		//1. Wait until there is room in the queue (i.e., queue lengh is less than cap)
		//TBD
		//2. Convert the incoming byte sequence given by data and len into a vector<char>
		vector<char> d(data, data + len);

		//3. Then push the vector at the end of the queue, watch out for race condition
		
		//4. Wake up pop() threads
		//TBD
	}

	int pop(char* buf, int bufcap){
		//1. Wait until the queue has at least 1 item
		//TBD
		//2. pop the front item of the queue. The popped item is a vector<char>
		m.lock();
		vector<char> d = q.front();
		q.pop();
		m.unlock();
		//3. Convert the popped vector<char> into a char*, copy that into buf, make sure that vector<char>'s length is <= bufcap
		assert(d.size() <= d.size());
		memcpy(buf, d.data(), d.size());
		//4. Wake up potentially sleeping push() threads
		//5. Return the vector's length to the caller so that he knows many bytes were popped	
		return d.size();
	}
};

#endif /* BoundedBuffer_ */
