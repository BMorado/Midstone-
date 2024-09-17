#pragma once
#include <shared_mutex>

	template <typename Type>
	class DLinkedList {

	public:
		//constructor
		DLinkedList();

		//destructor
		~DLinkedList();

		/// <summary>
		/// will iterate through the Vector and return data at location [i]
		/// </summary>
		/// <param name="location_">the index location of the data in the vector</param>
		/// <returns>data at location if data is out of scope return a blank Type [i]</returns>
		Type& operator [](int location_);

		/// <summary>
		/// returns the size of the array
		/// </summary>
		/// <returns>the size of the array</returns>
		int size();

		/// <summary>
		/// adds a new node to the end of the vector
		/// </summary>
		/// <param name="data_">data to be inserted into the new node</param>
		void pushBack(Type data_);

		/// <summary>
		/// returns the data from the last node and removes it from the vector
		/// </summary>
		/// <returns>the data from last node</returns>
		Type popBack();

		/// <summary>
		/// adds a new node to the front of the vector
		/// </summary>
		/// <param name="data_">data to be inserted into the new node</param>
		void pushFront(Type data_);

		/// <summary>
		/// returns the data from the first node and removes it from the vector
		/// </summary>
		/// <returns>the data from first node</returns>
		Type popFront();

		/// <summary>
		/// removes the node at desierd location from the vectoe
		/// </summary>
		/// <param name="location_">location of node to be removed</param>
		void killNode(int location_);

		/// <summary>
		/// adds a new node at the desierd location in the vector
		/// </summary>
		/// <param name="location_">the location that the node will be inserted</param>
		/// <param name="data_">the data to be inserted into new node</param>
		void insert(int location_, Type data_);

		//int countData(Type dataValue_);

	private:

		//used to dynamicly expand or contract the vector
		struct Node
		{
			// The next and last node;
			std::shared_ptr<Node> Back;
			std::shared_ptr<Node> Next;

			//the stored data
			Type Data;
		};

		//first node in the vector
		std::shared_ptr<Node> First;
		//last node in the vector
		std::shared_ptr<Node> Last;
		//size of the vector
		int Vsize = 0;

		Type def = Type();

		//int countFront(Type data_);
		//int countBack(Type data_);

		//mutex for multithreading
		std::shared_mutex mutex;

	};





template<typename Type>
inline DLinkedList<Type>::DLinkedList()
{
}

template<typename Type>
inline DLinkedList<Type>::~DLinkedList()
{
	for (int i = 0; i < Vsize; i++) {
		popBack();
	}
}



template<typename Type>
inline Type& DLinkedList<Type>::operator[](int location_)
{
	//locks thread during editing to stop breaking
	std::shared_lock<std::shared_mutex> sLock(mutex);

	//checks to see if location is out of scope if so return null
	if (location_ <= Vsize && location_ >= 0) {
		//create iterator
		std::shared_ptr<Node> iter = nullptr;
		Node* n;

		//if the location is in the first half if so move from first node
		if (location_ <= Vsize / 2) {

			//iterate to correct node
			iter = First;
			for (int i = 0; i < location_; i++) {
				n = iter.get();
				iter = n->Next;
			}

			//returns data;
			n = iter.get();
			return(n->Data);
		}
		else
		{
			//iterate to correct node from the last node
			iter = Last;
			for (int i = Vsize - 1; i > location_; i--) {
				n = iter.get();
				iter = n->Back;
			}

			//returns data;
			n = iter.get();
			return(n->Data);
		}

	}

	return def;
}

template<typename Type>
inline int DLinkedList<Type>::size()
{
	return Vsize;
}

template<typename Type>
inline void DLinkedList<Type>::pushBack(Type data_)
{
	//shared locking it to not breack due to other lockes
	std::shared_lock<std::shared_mutex> sLock(mutex);

	//create new node and insert data
	std::shared_ptr<Node> temp = std::shared_ptr<Node>(new Node());
	Node* n = temp.get();
	n->Data = data_;

	//locks the array during the writing process 
	sLock.unlock();
	std::unique_lock<std::shared_mutex> uLock(mutex);

	//if the vector is not empty set node back pointer to Last node, the old last node next to the node and set last node to new node
	if (Vsize > 0) {
		n->Back = Last;

		n = Last.get();
		n->Next = temp;

		Last = temp;
		Vsize++;
	}
	else
	{//if the vector is empty set the first and last to new node
		First = temp;
		Last = temp;
		Vsize++;
	}


}

template<typename Type>
inline Type DLinkedList<Type>::popBack()
{

	//shared locking it to not breack due to other lockes
	std::shared_lock<std::shared_mutex> sLock(mutex);

	//check if empty
	if (Vsize > 0) {
		//get the data and save in a varible
		Type ans;
		Node* n = Last.get();
		ans = n->Data;

		//locks thread during the deleting process
		sLock.unlock();
		std::unique_lock<std::shared_mutex> uLock(mutex);

		if (Vsize > 1) {
			//setting last node to new last and removing the new last pointer to old last
			Last = n->Back;
			n = Last.get();
			n->Next = nullptr;
		}
		else
		{//if there is only one node left set first and last to null
			Last = nullptr;
			First = nullptr;
		}
		Vsize--;

		return ans;
	}

}

template<typename Type>
inline void DLinkedList<Type>::pushFront(Type data_)
{
	//shared locking it to not breack due to other lockes
	std::shared_lock<std::shared_mutex> sLock(mutex);

	//create new node and insert data
	std::shared_ptr<Node> temp = std::shared_ptr<Node>(new Node());
	Node* n = temp.get();
	n->Data = data_;


	//locks thread during the deleting process
	sLock.unlock();
	std::unique_lock<std::shared_mutex> uLock(mutex);

	//if the vector is not empty set node back pointer to Last node, the old last node next to the node and set last node to new node
	if (Vsize > 0) {
		n->Next = First;

		n = First.get();
		n->Back = temp;

		First = temp;
		Vsize++;
	}
	else
	{//if the vector is empty set the first and last to new node
		First = temp;
		Last = temp;
		Vsize++;
	}


}

template<typename Type>
inline Type DLinkedList<Type>::popFront()
{

	//shared locking it to not breack due to other lockes
	std::shared_lock<std::shared_mutex> sLock(mutex);

	//check if empty
	if (Vsize > 0) {
		//get the data and save in a varible
		Type ans;
		Node* n = First.get();
		ans = n->Data;

		//locks thread during writing process
		sLock.unlock();
		std::unique_lock<std::shared_mutex> uLock(mutex);

		if (Vsize > 1) {
			//setting last node to new last and removing the new last pointer to old last
			First = n->Next;
			n = First.get();
			n->Back = nullptr;

		}
		else
		{//if there is only one node left set first and last to null
			Last = nullptr;
			First = nullptr;
		}
		Vsize--;

		return ans;
	}
}

template<typename Type>
inline void DLinkedList<Type>::killNode(int location_)
{

	//shared locking it to not breack due to other lockes
	std::shared_lock<std::shared_mutex> sLock(mutex);

	//checks to see if location is out of scope if so return null
	if (location_ <= Vsize-1 && location_ >= 0 && Vsize > 2) {
		//create iterator
		std::shared_ptr<Node> iter = nullptr;
		std::shared_ptr<Node> left = nullptr;
		std::shared_ptr<Node> right = nullptr;
		Node* n;

		//if the location is in the first half if so move from first node
		if (location_ <= Vsize / 2) {

			//iterate to correct node
			iter = First;
			for (int i = 0; i < location_; i++) {
				n = iter.get();
				iter = n->Next;
			}

			n = iter.get();

			//locks the array during the writing process 
			sLock.unlock();
			std::unique_lock<std::shared_mutex> uLock(mutex);

			if(location_ != 0){
				//fint left and right nodes
				left = n->Back;
				right = n->Next;

				//set left next node to right node
				n = left.get();
				n->Next = right;

				//set right back node to left node
				n = right.get();
				n->Back = left;

				Vsize--;
			}
			else{
				right = n->Next;
				n = right.get();
				n->Back = nullptr;
				First = right;
				Vsize--;
			}
			

		}
		else
		{
			//iterate to correct node from the last node
			iter = Last;
			for (int i = Vsize - 1; i > location_; i--) {
				n = iter.get();
				iter = n->Back;
			}

			//locks the array during the writing process 
			sLock.unlock();
			std::unique_lock<std::shared_mutex> uLock(mutex);

			//returns data;
			n = iter.get();

			if(location_ != Vsize - 1){
				

				//fint left and right nodes
				left = n->Back;
				right = n->Next;

				//set left next node to right node
				n = left.get();
				n->Next = right;

				//set right back node to left node
				n = right.get();
				n->Back = left;

				Vsize--;
			}
			else
			{
				left = n->Back;
				n = left.get();
				n->Next = nullptr;
				Last = left;
				Vsize--;
			}


		}

	}
	else if (Vsize == 1) {
		//locks the array during the writing process 
		sLock.unlock();
		std::unique_lock<std::shared_mutex> uLock(mutex);
		First = nullptr;
		Last = nullptr;
		Vsize--;
	}
	else if (Vsize == 2) {
		sLock.unlock();
		std::unique_lock<std::shared_mutex> uLock(mutex);
		if (location_ == 0) {
			First = Last;
			Node* n = Last.get();
			n->Back = nullptr;
		}
		else
		{
			Last = First;
			Node* n = First.get();
			n->Next = nullptr;
		}
		Vsize--;
	}



}

template<typename Type>
inline void DLinkedList<Type>::insert(int location_, Type data_)
{

	//shared locking it to not breack due to other lockes
	std::shared_lock<std::shared_mutex> sLock(mutex);

	std::shared_ptr<Node> temp = std::shared_ptr<Node>(new Node());
	Node* n = temp.get();
	n->Data = data_;

	//checks to see if location is out of scope if so return null
	if (location_ <= Vsize && location_ >= 0 && Vsize > 1) {
		//create iterator
		std::shared_ptr<Node> left = nullptr;
		std::shared_ptr<Node> right = nullptr;


		//if the location is in the first half if so move from first node
		if (location_ <= Vsize / 2) {

			//iterate to correct node
			right = First;
			for (int i = 0; i < location_; i++) {
				n = right.get();
				right = n->Next;
			}

			//locks the array during the writing process 
			sLock.unlock();
			std::unique_lock<std::shared_mutex> uLock(mutex);

			n = right.get();

			//fint left 
			left = n->Back;

			//set temp back and next
			n = temp.get();
			n->Next = right;
			n->Back = left;

			//set left next node to right node
			n = left.get();
			n->Next = temp;

			//set right back node to left node
			n = right.get();
			n->Back = temp;

			Vsize++;

		}
		else
		{
			//iterate to correct node from the last node
			right = Last;
			for (int i = Vsize - 1; i > location_; i--) {
				n = right.get();
				right = n->Back;
			}

			//locks the array during the writing process 
			sLock.unlock();
			std::unique_lock<std::shared_mutex> uLock(mutex);

			n = right.get();

			//fint left 
			left = n->Back;

			//set temp back and next
			n = temp.get();
			n->Next = right;
			n->Back = left;

			//set left next node to right node
			n = left.get();
			n->Next = temp;

			//set right back node to left node
			n = right.get();
			n->Back = temp;

			Vsize++;
		}

	}
	else if (Vsize == 0) {
		//locks the array during the writing process 
		sLock.unlock();
		std::unique_lock<std::shared_mutex> uLock(mutex);

		First = temp;
		Last = temp;
		Vsize++;
	}
	else if (Vsize == 1) {

		//locks the array during the writing process 
		sLock.unlock();
		std::unique_lock<std::shared_mutex> uLock(mutex);
		
		if (location_ == 0) {
			std::shared_ptr<Node> right = First;
			n = temp.get();
			n->Next = right;
			First = temp;

			n = right.get();
			n->Back = temp;

		}
		else
		{
			std::shared_ptr<Node> left = Last;
			n = temp.get();
			n->Back = left;
			Last = temp;

			n = left.get();
			n->Next = temp;
		}
	}

}