//Jonathan St. Aubin
//5-6-13
//HW6

//http://www.math.ucla.edu/~wittman/10a.1.10w/ccc/ch16/ch16.html

#ifndef Smaph_H
#define Smaph_H

#include <cassert>
#include <climits>
#include <utility>
#include <functional>
#include <iostream>

//There is code in here from Jack Applin's slink.h

template <typename T_key, typename T_map, typename T_funk = std::less<std::pair<T_key, T_map> > >
class Smaph {
  private:
    struct node {
		std::pair<T_key, T_map> datum;
		struct node *next;
		struct node *prev;
    };
    node *head, *tail;
  public:
    typedef unsigned int size_type;
    typedef T_key key_type;
	typedef T_map mapped_type;
	T_funk compare;
    typedef std::pair<T_key, T_map> value_type;
    class iterator {
      private:
		node *p;
		// This private ctor is for the container class only:
		friend class Smaph;
		iterator(node *ptr) : p(ptr) { }
      public:
		iterator() : p(0) { }
		~iterator(){ }
		iterator(const iterator &copyi) : p (copyi.p){}
		iterator &operator=(const iterator &assign){
			if(this != &assign){
				p=assign.p;
			}
			return *this;
		}
		iterator &operator++() {	// Preincrement
			assert(p);
			p = p->next;
			return *this;
		}
		iterator operator++(int) {	// Postincrement
			const iterator tmp = *this;
			++*this;
			return tmp;
		}
		iterator &operator--() {	// Predecrement
			assert(p);
			p = p->prev;
			return *this;
		}
		iterator operator--(int) {	// Postdecrement
			const iterator tmp = *this;
			--*this;
			return tmp;
		}
		// *iterator: Return a reference to the datum
		value_type &operator*() const {
			assert(p);
			return p->datum;
		}
		// iterator->: Return the address of the datum
		value_type *operator->() const {
			assert(p);
			return &p->datum;
		}
	bool operator==(const iterator &rhs) const {
	    return p==rhs.p;
	}
	bool operator!=(const iterator &rhs) const {
	    return !(*this == rhs);
	}
    };

    Smaph() : head(0), tail(0) {
    }
    
	Smaph(const Smaph &copys) : head(copys.head), tail(copys.tail){
		
	}
	//same as the copy constructor except that it now returns *this
	Smaph &operator=(const Smaph &copys){
		head = copys.head;
		tail = copys.tail;
		
		return *this;
	}
	
	Smaph(key_type firstnum, mapped_type secondnum){
		node* p = new node;
		value_type vt(firstnum, secondnum);
		p->datum = vt;
		p->next = 0;
		head = p;
		tail = p;
	}
	
	Smaph(value_type datum){
		node* p = new node;
		p->datum = datum;
		p->next = 0;
		head = p;
		tail = p;
	}
	
	Smaph(iterator it1, iterator it2){
		head = 0;
		tail = 0;
		insert(it1, it2);
	}
    ~Smaph() {
		clear();
    }

    void push_back(const value_type &datum) {
		node *p = new node;
		p->datum = datum;
		p->next = 0;
		if (!tail){		// empty list?
			head = p;
		}else{
			tail->next = p;
			p->prev = tail;
		}
		tail = p;
    }

    iterator begin() const {
		return head;
    }

    iterator end() const {
		return 0;
    }
	

    // An O(1) operation:
    bool empty() const {
		return !head;
    }

    // An O(N) operation:
    size_type size() const {
		int count=0;
		for (node *p = head; p; p=p->next)
			count++;
		return count;
    }
	
	size_type max_size() const{										//TO-DO
		return UINT_MAX;
	}
	
	iterator find(const key_type &firstnum, const mapped_type &secondnum) const{		//TO-DO
		value_type vt(firstnum, secondnum);
		return find(vt);
	}
	
	iterator find(const value_type &val) const{	//TO-DO 
		node* newnode = head;
		node* valnode = new node;
		valnode->datum = val;
		while(newnode){
		//if the new node made equals the first and second numbers of the pair,return the newly made node
			if((valnode->datum.first == newnode->datum.first) && (valnode->datum.second == newnode->datum.second)){
				return newnode;
			}
			newnode = newnode -> next;
		}
		//if fail then return end
		return end();
	}
	
	size_type count(const key_type &firstnum, const mapped_type &secondnum) const{
		value_type datum(firstnum, secondnum);
		return count(datum);
	}
	
	size_type count(const value_type &val) const{		
		node* newnode = head;
		node* valnode = newnode->val;
		size_type counter = 0;
		while(newnode){
			//if the value is in the range then increment the counter
			if(!(valnode<val) && !(val<valnode)){
				counter++;
			}
			newnode = newnode -> next;
		}
		//return the counter of the values
		return counter;
	}

	
	std::pair<iterator, bool> insert(const key_type &firstnum, const mapped_type &secondnum){
		value_type vt(firstnum, secondnum);
		return insert(vt);
	}
	
	std::pair<iterator, bool> insert(const value_type &val){
		node* newnode = new node;
		node* headnode = head;
		newnode->datum = val;
		while(headnode){
		//checking to see if the two values are the same
			if(compare(val, headnode->datum)){
				newnode->prev = headnode->prev;
				newnode->next = headnode;
				headnode->prev = newnode;
				//the newly made node's prev is not 0 set it else the set the head and return the pair
				if(!newnode->prev==0){
					newnode->prev->next = newnode;
				}else{
					head = newnode;
				}
					return std::make_pair<iterator, bool> (newnode, true);
			//values are different and making the pair to return
			}else{
				if(val.first==headnode->datum.first && val.second==headnode->datum.second){
					return std::make_pair<iterator, bool>(headnode, true);
				}
			}
			//if the next is 0 then set the newly made node's next to 0, then set the tail of the newnode and return the pair
			if(headnode->next==0){
				newnode->next = 0;
				tail->next = newnode;
				tail = newnode;
				return std::make_pair<iterator, bool>(newnode, true);
			}
			headnode = headnode->next;
		}
		
	}
	template<typename newIterator>
	void insert(newIterator first, newIterator second){
		while(first != second){
			insert(*first);
			++first;
		}
	}
	
	bool erase(const key_type &firstnum, const mapped_type &secondnum){
		value_type vt(firstnum, secondnum);
		return erase(vt);
	}
	
	bool erase(const value_type &val){		
		if(find(val)!=0){
			node* newnode = find(val).p;
			//if the newly made nodes next isnt 0 set the next prev to the current prev
			if(newnode->next != 0){
				newnode->next->prev = newnode->prev;
			}
			//if the newly made nodes prev isnt 0 set the prev next to the current next
			if(newnode->prev != 0){
				newnode->prev->next = newnode->next;
			}
			//if the two values are the same set the head to the head of the next
			if(newnode->datum.first==head->datum.first && newnode->datum.second==head->datum.second){
				head = head->next;
			}
			delete newnode;
			return true;
		}else{
			return false;
		}
	}
	
	bool erase(iterator val){	
		erase(*val);
	}
	
	bool erase(iterator val1, iterator val2){
		while(val1!=val2){
			erase(*val1);
			val1++;
		}
		if(val1==val2){
			erase(*val1);
		}
	}
	
    void clear() {
		while (head) {
			node *p = head->next;
			delete head;
			head = p;
		}	
    }

	Smaph operator|(const Smaph &val) const{
		Smaph s = val;
		for (iterator it=begin(); it!=end(); ++it){
			s.insert(*it);
		}
		return s;
	}
	
	Smaph operator|(const value_type &val) const{
		Smaph s = *this;
		s.insert(val);
		return s;
	}
	
	//value_type | Smaph
	
	
	Smaph operator&(const Smaph &val) const{
		Smaph s;
		for (iterator it=val.begin(); it!=val.end(); ++it){
			iterator findval = find(*it);
			if(findval!=NULL){
				s.insert(*findval);
			}
		}
		return s;
	}
	
	Smaph operator&(const value_type &val) const{
		Smaph s;
		iterator findval = find(val);
		if(findval!=NULL){
			s.insert(*findval);
		}
		return s;
	}
	
	//value_type & Smaph

	/*Smaph &operator|=(const Smaph &val){
		*this = 
	}
	*/
	Smaph &operator|=(const value_type &val){
	
	}
	
	Smaph operator&=(Smaph &val){
	
	}
	
	Smaph operator&=(const value_type &val){
	
	}
	
	
	
};









#endif //Smaph_H
