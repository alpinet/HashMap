#include <iostream>
#include "HashMap.hpp"


unsigned int default_hash_func(const std::string& key) //default hash function
{
	unsigned int hash = 0;

	for(int i = 0; i < key.length();i++)
	{
		hash = hash + (int)key[i];
	}
	hash = hash * key.length();// multiplies hash with length of the key
	return hash;
}

HashMap::HashMap() //initializes HashMap to use default hash function
{
	sizeOfHash = 0; //hashmaps begins with no items
	numberOfBuckets = initialBucketCount; //initial # of buckets = 10;
	hasher = default_hash_func; //default hash function to use
	hash_table = new Node*[numberOfBuckets]; //creates array of node pointers of size numBuckets
	for (unsigned int i = 0; i<numberOfBuckets;i++)
	{
		hash_table[i] = nullptr; //makes each element in the hash_table point to a nullpetr
	}
}

HashMap::HashMap(HashFunction hasher) //initializes HashMap that uses hasher parameter
{
	sizeOfHash = 0; //hashmap begins with no items
	numberOfBuckets = initialBucketCount; //initial # of buckets = 10;
	this->hasher = hasher; //hash function is whatever is put into parameter
	hash_table = new Node*[numberOfBuckets]; //creates array of node pointers of size NumBuckets
	for (unsigned int i = 0; i<numberOfBuckets;i++)
	{
		hash_table[i] = nullptr; //makes each element in hash table point to nullptr
	}
}

HashMap::HashMap(const HashMap& hm)
{
	sizeOfHash = hm.sizeOfHash; //size of Hash = size of hash of hm
	numberOfBuckets = hm.numberOfBuckets; // num buckets = num buckets of hm
	hasher = hm.hasher; // hasher function = hasher function of hm
	hash_table = new Node*[numberOfBuckets]; // creates array of node pointers
	for (unsigned int i = 0;i<numberOfBuckets;i++)
	{
		hash_table[i] = nullptr; //makes each element in hash table point to nullptr
	}
	// copies the elements of hashmap
	for (unsigned int i = 0; i< numberOfBuckets;i++)
	{
		Node* pointer_1 = hm.hash_table[i]; //points to first node of the inital linked list
		Node* temporary_pointer = hash_table[i]; //points to first node of copy link list
		while (pointer_1 != nullptr) //checks to make sure the first value of initial LL isn't nullptr
		{
			if(pointer_1 == nullptr)
			{
				return;
			}
			temporary_pointer -> key = pointer_1 -> key; //sets key of copy LL to first key in initiial
			temporary_pointer -> value = pointer_1 -> value; //sets value of copy LL to first value in inital
			if (pointer_1->next == nullptr) //if LL only has one element, next one is null
			{
				temporary_pointer-> next = nullptr; //sets copy next element to null
			}
			else
			{
				temporary_pointer->next = new Node; //creates new node in link list
				temporary_pointer = temporary_pointer->next; //sets next element as the next value
			}
			pointer_1 = pointer_1->next;
		}
	}
}

//Destructor
HashMap::~HashMap()
{
	for(int i = 0; i < numberOfBuckets;i++) //creates LL from buckets
	{
		Node* toDelete = hash_table[i];
		while (toDelete != nullptr) //while the element is not a nullptr, run
		{
			if (toDelete == nullptr)
			{
				return;
			}
			Node* temp = toDelete; //creats a temporary node = to toDelete
			toDelete = temp->next; //sets toDelete to the next value
			delete temp; //deallocates tmeporary node which points to actual node 
		}
	}
	delete[] hash_table; //deallocations array
}

HashMap& HashMap::operator=(const HashMap& hm)
{
	//check for self assignment
	if (this == &hm)
	{
		return *this;
	}
	else
	{
		hasher = hm.hasher;
		sizeOfHash = hm.sizeOfHash;
		numberOfBuckets = hm.numberOfBuckets;
		Node** new_hash_table = new Node* [hm.numberOfBuckets]; //keeps old list of arrays
		for (unsigned int i = 0; i< numberOfBuckets;i++) //makes new LL
		{
			Node* pointer_1 = hm.hash_table[i]; //points to first node of the inital linked list
			Node* temporary_pointer = hash_table[i]; //points to first node of copy link list
			while (pointer_1 != nullptr) //checks to make sure the first value of initial LL isn't nullptr
			{
				if(pointer_1 == nullptr)
				{
					continue;
				}
				temporary_pointer -> key = pointer_1 -> key; //sets key of copy LL to first key in initiial
				temporary_pointer -> value = pointer_1 -> value; //sets value of copy LL to first value in inital
				if (pointer_1->next == nullptr) //if LL only has one element, next one is null
				{
					temporary_pointer-> next = nullptr; //sets copy next element to null
				}
				else
				{
					temporary_pointer->next = new Node; //creates new node in link list
					temporary_pointer = temporary_pointer->next; //sets next element as the next value
				}
			pointer_1 = pointer_1->next;
			}
		}
		delete[] hash_table; //deletes all old pointers
		hash_table = new_hash_table; 
	}
	return *this;
}

void HashMap::add(const std::string &key, const std::string &value)
{
	if (HashMap::contains(key) == false)
	{
		int index = getIndexFromHash(key);
		Node* addedNode = new Node; //creates new Node for the new element
		addedNode->key = key; //new Node key is the input key
		addedNode->value = value; //new Node value is the input value
		addedNode->next = hash_table[index]; //moves original element to next element
		hash_table[index] = addedNode; // creates new node
		sizeOfHash+=1; //size of Hash increases by 1*/

		if (HashMap::loadFactor() >= 0.8)
		{
			int oldNumberOfBuckets = numberOfBuckets;
			numberOfBuckets = oldNumberOfBuckets*2 +1; //size of buckets doubles + 1
			Node **new_hash_table = new Node*[numberOfBuckets]; //makes a new node object
			for (int i = 0; i < numberOfBuckets; i++)
			{
				new_hash_table[i] = nullptr;
			}
			for (int i = 0; i < oldNumberOfBuckets;i++)
			{
				Node* newPtr = hash_table[i]; //initializes new pointer in the hash table 
				while (newPtr != nullptr)
				{
					Node* temp = newPtr;
					newPtr = newPtr -> next;

					int newIndex = hasher(temp->key) % numberOfBuckets;
					Node*& newBucket = new_hash_table[newIndex];
					temp->next = newBucket;
					newBucket = temp;
					delete temp;
				}
				delete newPtr;
			}
			delete[] hash_table;
			hash_table = new_hash_table;
		}
	}

}

void HashMap::remove(const std::string& key)
{
	if (HashMap::contains(key) == true)
	{
		int index = getIndexFromHash(key);
		Node* currentNode = nullptr;
		Node* currentNodeBefore = hash_table[index];
		if(hash_table[index]->key == key) //checks if key is first in LL
		{
			currentNode = hash_table[index]->next;
		}
		else
		{
			currentNode = hash_table[index];
		}
		while(currentNode!= nullptr)
		{
			currentNodeBefore = currentNode; //sets node before to the node
			currentNode = currentNode->next;
		}	
		if(hash_table[index]->key == key)
		{
			hash_table[index] = currentNode;
		}
		else
		{
			currentNodeBefore->next = currentNode->next;
		}
		delete currentNodeBefore;
		sizeOfHash--;
	}
}


bool HashMap::contains(const std::string& key) const
{
	Node* containedNode = hash_table[getIndexFromHash(key)];
	while(containedNode!= nullptr)
	{
		if(containedNode->key == key)//if the key is equal to the input key
		{
			return true; 

		}
		else
		{
			containedNode = containedNode->next; //looks at next node
		}
	}
	return false;
}	

double HashMap::loadFactor() const //return load factor (size of hash/num buckets)
{
	return double(sizeOfHash)/double(numberOfBuckets);
}

unsigned int HashMap::size() const //returns size of Hashmap
{
	return sizeOfHash;
}

std::string HashMap::value(const std::string& key) const //returns value with associating string
{
	if (!HashMap::contains(key)) //if key not in hashmap, return ""
	{
		return "";
	}
	else
	{
		int index = getIndexFromHash(key); //bucket in which the key is in
		Node* valued = hash_table[index]; // new node for the bucket
		while (valued->key != key) //while key isn't equal to input key
		{
			valued = valued->next; //go to the next element in LL
		}
		return valued->value;
	}
}

unsigned int HashMap::bucketCount () const //returns number of buckets
{
	return numberOfBuckets;
}

unsigned int HashMap::maxBucketSize() const //gets size of largest bucket
{
	int max_size = 0; //set initial max size as 0
	for (int i = 0; i < numberOfBuckets; i++) 
	{
		int length = 0; //sets initial length as 0
		Node* eachNode = hash_table[i];
		while (eachNode != nullptr) //goes until the last element in the LL bc last element points to null
		{
			length++; //length increases by one
			eachNode = eachNode->next; //looks through next node
		}
		if (length > max_size) //if temp value is greater than max size, replace
		{
			max_size = length;
		}
	}
	return max_size;
}

void HashMap::clear()
{
	for (int i = 0; i < numberOfBuckets; i++)
	{
		Node* eachNode = hash_table[i];
		while(eachNode != nullptr)
		{
			delete eachNode;
			eachNode = hash_table[i]->next;
		}
	}
	sizeOfHash = 0;
	std::cout << "CLEARED" << std::endl;
}
//Helper Functinos
unsigned int HashMap::getIndexFromHash(const std::string& key) const
{
	int index = hasher(key)%numberOfBuckets;
	return index;
}
