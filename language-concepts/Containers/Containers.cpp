//============================================================================
// Name        : Containers.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Knowledge of Containers:
//					DEQUE (double ended queue)
//					FORWARD_LIST (singly-linked list)
//					LIST (double-linked list)
//					SET, MAP, MULTISET, MULTIMAP (trees)
//					UNORDERED_SET/MAP/MULTISET/MULTIMAP (hash maps)
//					Custom types using associative containers (examples)
//					Nested maps (map of maps)
//					QUEUE, PRIORITY_QUEUE (fifo)
//					STACK (lifo)
//============================================================================
//Compile with -std=c++17
//============================================================================

#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <iomanip>

#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

int main() {

	//cout << __cplusplus; //201402 = C++14

	//--------------------------------------------------------------------------------------------------
	// COMMON THEORY
	/*--------------------------------------------------------------------------------------------------
	SEQUENTIAL CONTAINERS:
	- Data does not depend of particular order;
	- Data remains in a given position unless program changes it
	- Data is accessed by position (index, iterator)
	Examples: vector, string, array, deque, list

	ASSOCIATIVE CONTAINER:
	- Data is stored in order depending of values (automatic)
	- Elements have a key associated
	- Data is accessed by key, being more searchable than sequential containers
	- Do not support push_back / push_front
	Sets:
	- Unstructured collection of elements
	- An element is a data considered as key
	- More used to check whether a key is present or not
	Maps:
	- Unstructured collection of elements
	- An element is a pair of data, one key plus an associated value
	- More used to search for a key and collects an associated value
	Examples: set, map, multiset, multimap, unordered set/map/multiset/multimap

	CONTAINER ADAPTORS:
	- Data structures implemented using sequential containers
	- Data depend of particular order
	Examples: stack, queue, priority_queue
	//------------------------------------------------------------------------------------------------*/



	//--------------------------------------------------------------------------------------------------
	cout << "DEQUE ................................................................................\n\n";
	/*--------------------------------------------------------------------------------------------------
	Very similar to vector. Main differences:
	- Deque has push_front while vector does not
	- Vector stores elements in a single block of memory; deque overall several blocks
	
	Vector in memo: | size | ptr |
							  |------> | E1 | E2 | E3 | EX | EX | where Ex are some extra space it allocates
	When inserting a new element, if no space is left on the allocated block, a bigger block
	is allocated and all elements are copied into, releasing the current block
	
	Deque in memo: | size | ptr | ptr | ptr |
								   |	   |	 |------> | E6 | E7 | E8 | EX | EX |
								   |	   |-------> | E3 | E4 | E5 |
								   |------->| Ex | E1 | E2 |
	When inserting in front/back of a deque, if no space is left in first/last block allocated, it allocates
	another block, not copying/moving any data
	*/

		deque<int> D1{4,2,3,5,1};
		cout << "Deque D1 = "; for (auto iter : D1) {cout << iter << " ";} cout << endl;
		cout << "Deque D1[0] = " << D1[0] << endl;
		D1.push_back(4);
		D1.push_back(2);
		D1.push_front(1);
		D1.push_front(5);
		cout << "Deque D1 = "; for (auto iter : D1) {cout << iter << " ";} cout << endl;

	cout << endl;
	//--------------------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------------------------
	cout << "FORWARD_LIST .........................................................................\n\n";
	/*--------------------------------------------------------------------------------------------------
	- Do not use blocks of memory; each element has its own memo allocation (node)
	- Each node has its value and a pointer to the next node in the list
	- Add/remove nodes in any position is equal to allocate/free memo and re-point pointers of previous
	  and next nodes
	- Does not support generic sort once it does not provide random access to nodes
	- Provides its own (more efficient) implementation of some generic algorithms (sort, unique...)
	- Allow only forward iterations (iterators cannot be decremented)
	
	Forward list in memo: | V1 | ptr | ---> | V2 | ptr | ---> | VN | null |
	*/

		forward_list<int> FL1 {7, 9, 11};
		cout << "Fwd_list FL1 = "; for (auto iter : FL1) {cout << iter << " ";} cout << endl;
		cout << "Fwd_list FL1[0] = index notation not supported" << endl;
		FL1.push_front(1);
		FL1.insert_after(FL1.begin(), {3,6});
		FL1.remove(1);
		FL1.splice_after(FL1.begin(), {4,5});
		FL1.merge({8,15});
		//No push_back implemented (neither minus operation for iterators)!
		//No ways of insert items in the end, unless the list is iterated
		cout << "Fwd_list FL1 = "; for (auto iter : FL1) {cout << iter << " ";} cout << endl;

	cout << endl;
	//--------------------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------------------------
	cout << "LIST .................................................................................\n\n";
	/*--------------------------------------------------------------------------------------------------
	- Do not use blocks of memory; each element has its own memo allocation (node)
	- Each node has its value and two pointers, to the previous and next nodes in the list
	- Add/remove nodes in any position is equal to allocate/free memo and re-point pointers of previous
	  and next nodes
	- Add/remove nodes in the middle of a <list> is faster than in <vector> or <deque>
	- Access nodes in the middle of a <list> is slower than in <vector> or <deque> (it has to iterate
	  until the desired node)
	- Does not support generic sort once it does not provide random access to nodes
	- Provides its own (more efficient) implementation of some generic algorithms (sort, unique...)
	- Uses more memo than <vector> or <deque>
	
	List in memo: | null | V1 | ptr | <---> | ptr | V2 | ptr | <---> | ptr | VN | null |
	*/

		list<int> L1 {5, 7, 9};
		cout << "List L1 = "; for (auto iter : L1) {cout << iter << " ";} cout << endl;
		cout << "List L1[0] = index notation not supported" << endl;
		L1.push_back(11);
		L1.push_front(3);
		L1.insert(++L1.begin(), 4);
		L1.insert(--L1.end(), 10);
		L1.sort(); //provides its own implementation of sort()...
		L1.remove(7); //It does not support generic remove() for the same reason as sort...
		L1.splice(L1.end(), {21, 23, 25});
		L1.merge({15, 16, 17});
		cout << "List L1 = "; for (auto iter : L1) {cout << iter << " ";} cout << endl;

	cout << endl;
	//--------------------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------------------------
	cout << "SET ..................................................................................\n\n";
	/*--------------------------------------------------------------------------------------------------
	- Unstructured collection of elements
	- Each element is unique and stored in order
	- Implemented as tree
	- Elements are const, so they cannot be changed (only add/rmv allowed)
	- Very fast accessing arbitrary elements
	- Add/rmv are usually very fast (when the tree is not unbalanced; otherwise, it will take time
	  balancing itself)
	
	Set in memo: | ptr | 6 | ptr |
					|		  |---> | null | 7 | null |
					|---> | null | 4 | ptr |
										|---> | null | 5 | null |
	*/

		set<int> S1 {2, 5, 3, 4};
		cout << "Set S1 = "; for (auto iter : S1) {cout << iter << " ";} cout << endl;
		cout << "Set S1[0] = index notation not supported" << endl;
		S1.insert(7);
		auto pairInsS1 = S1.insert(3); //.second = bool OK/NOK; .first = iter inserted/existing elem
			if (pairInsS1.second) { /*cout << *pairInsS1.first << "inserted!";*/ }
			else { /*cout << "Oh, no! Not inserted due to existent " << *pairInsS1.first; */}
		S1.erase(5);
		S1.insert(10);
		S1.count(5); //returns 1 (exists) or 0 (does not exist)
		cout << "Set S1 = "; for (auto iter : S1) {cout << iter << " ";} cout << endl;

	cout << endl;
	//--------------------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------------------------
	cout << "MAP ..................................................................................\n\n";
	/*--------------------------------------------------------------------------------------------------
	- Each element is stored as PAIR (one key and respective value)
	- Each key is unique and stored in order
	- Implemented as tree
	- Keys const, so they cannot be changed (only add/rmv allowed)
	- Values associated to keys can be changed (map[key] = value)
	- Very fast accessing arbitrary elements
	- Add/rmv are usually very fast (when the tree is not unbalanced; otherwise, it will take time
	  balancing itself)
	
	Map in memo: | 672 | "analista" |        // onde cada par = (chave, valor)
					|		  |---> | 731 | gerente |
					|---> | 426 | "motorista"
										|---> | 567 | secretario |
	*/

		map<int,string> M1 {{1,"Mari"}, {3,"Marina"}};
		cout << "Map M1 = "; for (auto iter : M1) {cout << iter.first << ":" << iter.second << " ";} cout << endl;
		cout << "Map M1[0] = index notation not supported; but subscripting M1[key] is, so M1[3] = " << M1[3] << endl;
		M1.insert({4,"Amanda"});
		M1.erase(1);
		M1.insert({2,"Tetéco"});
		auto pairInsM1 = M1.insert({4,"Amanda"}); //.second = bool OK/NOK; .first = iter inserted/existing elem
			if (pairInsM1.second) { /*cout << *pairInsM1.first << "inserted!";*/ }
			else { /*cout << "Oh, no! Not inserted due to existent " << *pairInsM1.first; */}
		cout << "Map M1 = "; for (auto [key,value] : M1) {cout << key << ":" << value << " ";} cout << endl; //C++17

	cout << endl;
	//--------------------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------------------------
	cout << "MULTISET .............................................................................\n\n";
	/*--------------------------------------------------------------------------------------------------
	- Same as SET, but accepting repeated values
	- Erase removes all elements with value; to erase one instance of the repetitions, is necessary to
	  erase using iterator instead
	*/

		multiset<int> MS1 {2, 5, 3, 4};
		cout << "Multiset MS1 = "; for (auto iter : MS1) {cout << iter << " ";} cout << endl;
		cout << "Multiset MS1[0] = index notation not supported" << endl;
		MS1.insert(7);
		//auto pairInsMS1 = S2.insert(3); //nothing ever returned! return for insert N/A
		MS1.insert(3);
		MS1.erase(5);
		MS1.insert(10);
		MS1.insert(10);
		MS1.count(3);  //returns 2
		MS1.erase(10); //erase all values 10
		cout << "Multiset MS1 = "; for (auto iter : MS1) {cout << iter << " ";} cout << endl;
		MS1.insert(20);
		MS1.insert(20);
		//Erase single instance of repetitions:
		{	int value2erase = 20;
			auto countMS1 = MS1.count(value2erase);
			if (countMS1 > 1) {
				auto findMS1 = MS1.find(value2erase);
				MS1.erase(findMS1);
			} //else: all this trouble worths it only if we have multiple keys! use erase(key) here!
		}
		cout << "Multiset MS1 = "; for (auto iter : MS1) {cout << iter << " ";} cout << endl;

	cout << endl;
	//--------------------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------------------------
	cout << "MULTIMAP .............................................................................\n\n";
	/*--------------------------------------------------------------------------------------------------
	- Same as MAP, but accepting pair with repeated keys (subscripting notation not accepted then)
	- Erase(key) removes all elements with key; to erase one instance of the repetitions, is necessary to
	  erase using iterator instead
	*/

		multimap<int,string> MM1 {{1,"Mari"}, {3,"Marina"}};
		cout << "Multimap MM1 = "; for (auto iter : MM1) {cout << iter.first << ":" << iter.second << " ";} cout << endl;
		cout << "Multimap MM1[0] = index notation not supported; neither subscripting M1[key]" << endl;
		MM1.insert({4,"Amanda"});
		MM1.erase(1); //1, Mari
		MM1.insert({2,"Tetéco"});
		MM1.insert({2,"Tetecos"});
		//auto pairInsMM1 = MM1.insert({4,"Amanda"}); //nothing ever returned! return for insert N/A
		MM1.insert({4,"AmandaAgain"});
		MM1.insert({4,"Aminda"});
		cout << "Multimap MM1 = "; for (auto iter : MM1) {cout << iter.first << ":" << iter.second << " ";} cout << endl;
		MM1.erase(2); //erased all keys = 2 (Tetéco e Tetecos)

		//METHOD1: Search (and erase) single instance of repetitions:
		{	int key2erase = 4;
			string value2erase = "Again";
			auto countMM1 = MM1.count(key2erase);
			if (countMM1 > 1) {
				auto findMM1 = MM1.find(key2erase);
				size_t counter = 1;
				do {
					if ((findMM1->second).find(value2erase) != string::npos){
						MM1.erase(findMM1);
						break;
					}
				} while (findMM1++, counter++ < countMM1);
			} //else: all this trouble worths it only if we have multiple keys! use erase(key) here!
		}
		cout << "Multimap MM1 = "; for (auto iter : MM1) {cout << iter.first << ":" << iter.second << " ";} cout << endl;

		MM1.insert({2,"Tetéco"});
		MM1.insert({2,"Tetecos"});
		MM1.insert({2,"TetecoAgain"});
		cout << "Multimap MM1 = "; for (auto iter : MM1) {cout << iter.first << ":" << iter.second << " ";} cout << endl;
		
		//METHOD2: Search (and erase) single instance of repetitions:
		{	int key2erase = 2;
			string value2erase = "Again";
			auto iterStart = MM1.lower_bound(key2erase); //first key 2 found
			auto iterEnd = MM1.upper_bound(key2erase); //first key after all occurrences of key 2
			for (auto iter=iterStart; iter!=iterEnd; iter++)
				if ((iter->second).find(value2erase) != string::npos){
					MM1.erase(iter);
					break;
				}
		}

		MM1.insert({3,"Mairina"});
		MM1.insert({3,"MarinaAgain"});
		cout << "Multimap MM1 = "; for (auto iter : MM1) {cout << iter.first << ":" << iter.second << " ";} cout << endl;
		
		//METHOD3: Search (and erase) single instance of repetitions:
		{	int key2erase = 3;
			string value2erase = "Again";
			auto iterEquals = MM1.equal_range(key2erase);
			for (auto iter=iterEquals.first; iter!=iterEquals.second; iter++)
				if ((iter->second).find(value2erase) != string::npos){
					MM1.erase(iter);
					break;
				}
		}

		//METHOD4: Search (and erase) single instance of repetitions:
		{	int key2erase = 3;
			string value2erase = "Mairina";
			auto iterEquals = MM1.equal_range(key2erase);
			auto find_lambda = [value2erase](pair<int,string> p){ return p.second.find(value2erase) != string::npos; };
			auto iterFind = find_if(iterEquals.first, iterEquals.second, find_lambda);
			if (iterFind != iterEquals.second)
				MM1.erase(iterFind);
		}
		cout << "Multimap MM1 = "; for (auto [key,value] : MM1) {cout << key << ":" << value << " ";} cout << endl; //C++17

	cout << endl;
	//--------------------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------------------------
	//UNORDERED_: SET/MAP/MULTISET/MULTIMAP (hash maps)
	/*--------------------------------------------------------------------------------------------------
	- Behavior similar to respective containers, but unordered
	- Implemented as hash table (has calculated over the keys, in case of maps)
	- Each hash code (index) is stored into an array of buckets (or slots); each bucket points to a
	  linked-list of corresponding values
	- Ideally each bucket points to a single value; but once that hash functions can generate same hash
	  for different values (collisions), the linked-list may have more than one value and shall be iterated
	- Allow only forward iterations (iterators cannot be decremented)
	- Order of data is determined by hash codes generated
	- Do not support begin/end/lower_bound/upper_bound
	- It does not have the overhead of sorting as standard set/map, but it gets slower as the collision
	  grow (bad hash functions = bad unordered structures)
	- The hash function brings cost to operations in the structure
	- Resize of structure can be slow
	- Given all drawbacks mentioned, if well defined, it can be faster than other structures
	*/

		unordered_set<int> US1 {2, 5, 3, 4};
		unordered_map<int,string> UM1 {{2,"Mari"},{3,"Mendes"},{5,"Medeiros"}};
		unordered_multiset<int> UMS1 {2, 5, 3, 3, 4};
		unordered_multimap<int,string> UMM1 {{2,"Mari"},{2,"Mari"},{3,"Mendes"},{5,"Medeiros"}};
	
	cout << endl;
	//--------------------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------------------------
	cout << "Associative containers with custom types ...............................................\n\n";
	/*--------------------------------------------------------------------------------------------------
	//- Creating a Library:
	//-- Store books and respective author (key-value);
	//-- An author can have more than one book (duplicate keys);
	*/

	//EXAMPLE 1 - structure sorted by key (author) only
		cout << "Associative containers for custom types (example 1)...\n";
		class book {
			private:
				string title, publisher;
			public:
				book(string t, string p) : title(t), publisher(p) {}
				string getTitle() {return title;}
				string getPubl() {return publisher;}
		};
		auto printBook = [](string a, book b){cout << "V1 BOOK: " << b.getTitle() << "; AUTHOR: " << a << "; PUBLISHER: " << b.getPubl() << endl;};
		multimap<string, book> Library;
		book b1("The C++ Programming Language","Addison-Wesley");
			Library.insert({"Stroustrup, Bjame", b1});
		book b2("C++ Primer","Addison-Wesley");
			Library.insert({"Lippman, Stanley", b2});
		book b3("Programming Principles and Practice","Addison-Wesley");
			Library.insert({"Stroustrup, Bjame", b3});
		for (auto iter : Library) printBook(iter.first, iter.second);
		cout << endl;

	//EXAMPLE 2 - structure sorted by key (author, title)
		cout << "Associative containers for custom types (example 2)...\n";
		class book_idx {
			private:
				string author, title;
			public:
				book_idx(string a, string t) : author(a), title(t) {}
				string getTitle() {return title;}
				string getAuthor() {return author;}
				bool operator < (const book_idx & SecondBook) const {
					return (author!=SecondBook.author) ? author<SecondBook.author : title<SecondBook.title;
				}
		};
		auto printBookV2 = [](book_idx bx, book b){cout << "V2 BOOK: " << b.getTitle() << "; AUTHOR: " << bx.getAuthor() << "; PUBLISHER: " << b.getPubl() << endl;};
		multimap<book_idx, book> LibraryV2;
		//class book could be modified to not store book; but for now, only for testing, let's keep it
		book b4("The C++ Programming Language","Addison-Wesley");
		book_idx b4x("Stroustrup, Bjame","The C++ Programming Language");
			LibraryV2.insert({b4x, b4});
		book b5("C++ Primer","Addison-Wesley");
		book_idx b5x("Lippman, Stanley","C++ Primer");
			LibraryV2.insert({b5x, b5});
		book b6("Programming Principles and Practice","Addison-Wesley");
		book_idx b6x("Stroustrup, Bjame","Programming Principles and Practice");
			LibraryV2.insert({b6x, b6});
		for (auto iter : LibraryV2) printBookV2(iter.first, iter.second);

	cout << endl;
	//--------------------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------------------------
	cout << "NESTED MAPS ..........................................................................\n\n";
	//--------------------------------------------------------------------------------------------------
	//Declaration 1
		map<int, map<int,string>> NM1{
			{1, { {1,"Bike1"},{3,"Bike3"} }},
			{2, { {1,"Car1"} }}
		};
	//Declaration 2
		typedef map<int,string> submap;
		map<int,submap> NM2;
	//Declaration 3
		using submap1 = map<int,string>;
		map<int,submap1> NM3;

	//Iterating
		for (auto iterMap : NM1) {
			cout << "Nested map NM1 key = " << iterMap.first << "; value = submap:" << endl;
			for (auto iterSubmap : iterMap.second)
				cout << "... submap key = " << iterSubmap.first << "; submap value = " << iterSubmap.second << endl;
		} cout << endl;
		
	//Inserting item on map
		NM1.insert({3, { {1,"Train1"} }});
		NM1.insert({4, { {3,"Plane3"} }});
	//Inserting item on submap (when you KNOW that map key exists)
		NM1.at(1).insert({2,"Bike2"});
	//Inserting item on submap (when you are not sure that map key exists)
		auto iterMap1 = NM1.find(1);
		if (iterMap1 != NM1.end())
			iterMap1->second.insert({5,"Bike5"});

	//Iterating
		for (auto iterMap : NM1) {
			cout << "Nested map NM1 key = " << iterMap.first << "; value = submap:" << endl;
			for (auto iterSubmap : iterMap.second)
				cout << "... submap key = " << iterSubmap.first << "; submap value = " << iterSubmap.second << endl;
		} cout << endl;

	//Removing item from map
		NM1.erase(3);
	//Removing item from submap (when you KNOW that map and submap keys exist)
		NM1.at(1).erase(3);
	//Removing item from submap (when you are not sure that map or submap keys exist)
		auto iterMap2 = NM1.find(1);
		if (iterMap2 != NM1.end()) {
			auto iterSubmap2 = iterMap2->second.find(2);
			if (iterSubmap2 != iterMap2->second.end())
				iterMap2->second.erase(iterSubmap2);
		}
	//Iterating
		for (auto iterMap : NM1) {
			cout << "Nested map NM1 key = " << iterMap.first << "; value = submap:" << endl;
			for (auto iterSubmap : iterMap.second)
				cout << "... submap key = " << iterSubmap.first << "; submap value = " << iterSubmap.second << endl;
		}

	cout << endl;
	//--------------------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------------------------
	cout << "QUEUE (FIFO) .........................................................................\n\n";
	/*--------------------------------------------------------------------------------------------------
	- Insert always in the back, remove always from the front
	- Stored always in the order of insertion
	- Limited operations (front/back return first/last elements; push to insert in the back); pop to
	  remove in the front; empty and size for verifications)
	- No iterator operations!
	*/

		queue<int> Q1;
		Q1.push(10);
		Q1.push(4);
		Q1.push(13);
		Q1.push(2);
		cout << "Queue Q1 size = " << Q1.size() << ", so, it is empty? " << Q1.empty() << endl;
		cout << "Queue Q1 first element = " << Q1.front() << endl;
		cout << "Queue Q1 last element = " << Q1.back() << endl << endl;
		Q1.pop();
		Q1.push(1);
		cout << "Queue Q1 size = " << Q1.size() << endl;
		cout << "Queue Q1 first element = " << Q1.front() << endl;
		cout << "Queue Q1 last element = " << Q1.back() << endl << endl;

		size_t sizeQ1 = Q1.size(); //Popping elements inside loop changes .size()!
		cout << "Queue Q1 (size" << sizeQ1 << ") = ";
		for (size_t i=0; i<sizeQ1;i++) {
			cout << Q1.front() << " ";
			Q1.pop();
		} cout << endl;

	cout << endl;
	//--------------------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------------------------
	cout << "PRIORITY_QUEUE .......................................................................\n\n";
	/*--------------------------------------------------------------------------------------------------
	- Also a FIFO, add elements in order of insertion, in front of all elements of lower priorities
	- Limited operations (top returns first element; push to insert in front of all elements of lower
	  priority; pop to remove first element; empty and size for verifications)
	- No iterator operations!
	*/

		class restaurant_queue {
			private:
				string client_name;
				string client_type; //vip, reservation, normal (it would be easier use numbers; strs just for fun!)
				time_t client_arrival;
			public:
				restaurant_queue(string cn, string ct, time_t ca) : client_name(cn), client_type(ct), client_arrival(ca) {}
				bool operator < (const restaurant_queue &client2) const {
					//element already in queue has lower priority then "client2" being added?
					if (client_type == client2.client_type)
						return client_arrival > client2.client_arrival; //yes, if it has greater time (arrived later)
					return client_type < client2.client_type; //normal < reserva < vip
				}
				void printRQ() const {
					cout << left << "  Name = " << setw(18) << client_name << " | Type = " << setw(10) << client_type << " | Arrival = " << ctime(&client_arrival);
				}
		};

		priority_queue<restaurant_queue> PQ1;
		restaurant_queue client1{"Pessoa 1 vip", "vip", time(0)};			PQ1.push(client1);
		this_thread::sleep_for(std::chrono::milliseconds(1000)); //1s of difference to the next (avoiding math with ms)
		restaurant_queue client2{"Pessoa 2 normal", "normal", time(0)}; 	PQ1.push(client2);
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		restaurant_queue client3{"Pessoa 3 normal", "normal", time(0)};		PQ1.push(client3);
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		restaurant_queue client4{"Pessoa 4 reserva", "reserva", time(0)};	PQ1.push(client4);
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		restaurant_queue client5{"Pessoa 5 reserva", "reserva", time(0)};	PQ1.push(client5);
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		restaurant_queue client6{"Pessoa 6 vip", "vip", time(0)};			PQ1.push(client6);
		this_thread::sleep_for(std::chrono::milliseconds(1000));
		restaurant_queue client7{"Pessoa 7 normal", "normal", time(0)};		PQ1.push(client7);

		size_t sizePQ1 = PQ1.size(); //Popping elements inside loop changes .size()!
		cout << "Priority Queue PQ1 (size" << sizePQ1 << "):" << endl;
		for (size_t i=0; i<sizePQ1;i++) {
			PQ1.top().printRQ();
			PQ1.pop();
		}

	cout << endl;
	//--------------------------------------------------------------------------------------------------



	//--------------------------------------------------------------------------------------------------
	cout << "STACK (LIFO) .........................................................................\n\n";
	/*--------------------------------------------------------------------------------------------------
	- Insert always in the top, remove always from the top
	- Stored in the order of insertion
	- Limited operations (top returns 1st element; push to insert in the top; pop removes top element;
	  empty and size for verifications)
	- No iterator operations!
	*/
	
		stack<int> St1;
		St1.push(10);
		St1.push(4);
		St1.push(13);
		St1.push(2);
		cout << "Stack St1 size = " << St1.size() << ", so, it is empty? " << St1.empty() << endl;
		cout << "Stack St1 first element = " << St1.top() << endl << endl;
		St1.pop();
		St1.push(1);
		cout << "Stack St1 size = " << St1.size() << endl;
		cout << "Stack St1 first element = " << St1.top() << endl << endl;

		size_t sizeSt1 = St1.size(); //Popping elements inside loop changes .size()!
		cout << "Stack St1 (size" << sizeSt1 << ") = ";
		for (size_t i=0; i<sizeSt1;i++) {
			cout << St1.top() << " ";
			St1.pop();
		}  cout << endl;

	cout << endl;
	//--------------------------------------------------------------------------------------------------



	cout << "END OF PROGRAM" << endl;
	return 0;
}
