#pragma once;

#include <initializer_list>

#ifdef _DEBUG

#include <iostream>

#endif

namespace sv
{
	template <class T>
	class forward_list
	{
		struct Node
		{
			Node* pNext;
			T data;

			Node(T data = T(), Node* pNext = nullptr);
		};

		size_t _size;
		Node* head;

	public:

		class iterator // : public const_iterator TODO
		{
			Node* pNode;

		public:

			iterator(Node *pNode = nullptr);
			
			iterator& operator ++();
			
			bool operator !=(const iterator& other) const;

			T& operator *() const;

			~iterator() = default;
		};

		forward_list();

		forward_list(std::initializer_list<T>&& lst);

		forward_list(const forward_list& other);

		forward_list(forward_list&& other);

		forward_list<T>& operator = (const forward_list& other);

		forward_list<T>& operator = (forward_list&& other);

		~forward_list();

		void push_front(T data); //TODO perfect reference with const& and &&

		void insert(T data, int index);

		void pop_front();

		void remove_at(int index);

		void clear();

		void reverse();

		bool empty() const;

		T at(int index) const;

		int size() const;

		iterator begin() const;

		iterator end() const;
	};

	template <class T>
	forward_list<T>::Node::Node(T data, Node* pNext) : data{ data }, pNext{ pNext } {}

	template <class T>
	forward_list<T>::forward_list() : _size{ 0 }, head{ nullptr } 
	{
#ifdef _DEBUG
		std::cout << "forward_list<T>::forward_list()" << std::endl;
#endif
	}

	template<class T>
	forward_list<T>::forward_list(std::initializer_list<T>&& init_lst)
	{
#ifdef _DEBUG
		std::cout << "forward_list<T>::forward_list(std::initializer_list<T>&& init_lst)" << std::endl;
#endif

		for (auto&& el : init_lst)
		{
			this->push_front(el); // TODO std forward and perfect forwarding
		}
		this->reverse();
	}

	template <class T>
	forward_list<T>::forward_list(const forward_list& other)
	{
#ifdef _DEBUG
		std::cout << "forward_list<T>::forward_list(const forward_list& other)" << std::endl;
#endif
		for (int i = 0; i < other._size; i++)
		{
			if (this->head == nullptr)
			{
				this->head = new Node(other.get_data(i));
			}
			else
			{
				Node* curr = this->head;
				while (curr->pNext != nullptr)
				{
					curr = curr->pNext;
				}
				curr->pNext = new Node(other.get_data(i));
			}
			this->_size++;
		}
	}

	template <class T>
	forward_list<T>& forward_list<T>::operator = (const forward_list& other)
	{
#ifdef _DEBUG
		std::cout << "forward_list<T>& forward_list<T>::operator = (const forward_list& other)" << std::endl;
#endif
		this->clear();

		for (int i = 0; i < other._size; i++)
		{
			if (this->head == nullptr)
			{
				this->head = new Node(other.get_data(i));
			}
			else
			{
				Node* curr = this->head;
				while (curr->pNext != nullptr)
				{
					curr = curr->pNext;
				}
				curr->pNext = new Node(other.get_data(i));
			}
			this->_size++;
		}
		return *this;
	}

	template <class T>
	forward_list<T>::forward_list(forward_list&& other)
	{
#ifdef _DEBUG
		std::cout << "forward_list<T>::forward_list(forward_list&& other)" << std::endl;
#endif
		this->head = other.head;
		this->_size = other._size;
		other._size = 0;
		other.head = nullptr;
	}

	template <class T>
	forward_list<T>& forward_list<T>::operator = (forward_list&& other)
	{
#ifdef _DEBUG
		std::cout << "forward_list<T>& forward_list<T>::operator = (forward_list&& other)" << std::endl;
#endif
		this->clear();
		this->head = other.head;
		this->_size = other._size;
		other._size = 0;
		other.head = nullptr;
		return *this;
	}

	template <class T>
	forward_list<T>::~forward_list()
	{
#ifdef _DEBUG
		std::cout << "forward_list<T>::~forward_list()" << std::endl;
#endif
		clear();
	}

	template <class T>
	void forward_list<T>::push_front(T data)
	{
		head = new Node(data, head);
		_size++;
	}

	template <class T>
	void forward_list<T>::insert(T data, int index)
	{
		if (index == 0)
		{
			push_front(data);
		}
		else
		{
			Node* prev = head;

			for (int i = 0; i < index - 1; i++)
			{
				prev = prev->pNext;
			}
			prev->pNext = new Node(data, prev->pNext);

			_size++;
		}
	}

	template <class T>
	void forward_list<T>::pop_front()
	{
		if (empty())
			return;

		Node* temp = head;

		head = head->pNext;
		delete temp;
		_size--;
	}

	template <class T>
	void forward_list<T>::remove_at(int index)
	{
		if (index == 0)
		{
			pop_front();
		}
		else
		{
			Node* prev = this->head;
			for (int i = 0; i < index - 1; i++)
			{
				prev = prev->pNext;
			}
			Node* toDelete = prev->pNext;
			prev->pNext = toDelete->pNext;
			delete toDelete;

			_size--;
		}
	}

	template <class T>
	void forward_list<T>::reverse()
	{
		if (empty())
			return;
		Node* curr = head;
		Node* next = nullptr;
		head = nullptr;

		while (curr != nullptr)
		{
			next = curr->pNext;
			curr->pNext = head;
			head = curr;
			curr = next;
		}
	}

	template<class T>
	bool forward_list<T>::empty() const
	{
		return _size == 0 ? true : false;
	}

	template <class T>
	void forward_list<T>::clear()
	{
		while (_size)
			pop_front();
	}

	template <class T>
	T forward_list<T>::at(const int index) const
	{
		int	c = 0;
		Node* curr = this->head;

		while (curr != nullptr)
		{
			if (c == index)
				return curr->data;

			curr = curr->pNext;
			c++;
		}
		return T();
	}

	template <class T>
	int forward_list<T>::size() const
	{
		return _size;
	}

	template<class T>
	forward_list<T>::iterator::iterator(Node* pNode) : pNode(pNode) {}

	template<class T>
	forward_list<T>::iterator& forward_list<T>::iterator::operator++()
	{
		pNode = pNode->pNext;
		return *this;
	}

	template<class T>
	bool forward_list<T>::iterator::operator!=(const iterator& other) const
	{
		return this->pNode != other.pNode;
	}

	template<class T>
	T& forward_list<T>::iterator::operator*() const
	{
		return pNode->data;
	}

	template<class T>
	forward_list<T>::iterator forward_list<T>::begin() const
	{
		return iterator(head);
	}

	template<class T>
	forward_list<T>::iterator forward_list<T>::end() const
	{
		return iterator();
	}
}
