#pragma once;

namespace sv
{
	template <class T>
	class list //TODO SECOND POINTER
	{
	private:

		class Node
		{
		public:

			Node* pNext;
			Node* pPrev;
			T data;

			Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr);
		};

		int size;
		Node* head;

	public:

		list();

		list(const list& other);

		list<T>& operator = (const list& other);

		list(list&& other);

		list<T>& operator = (list&& other);

		~list();

		void push_back(T data);

		void push_front(T data);

		void insert(T data, int index);

		void pop_back();

		void pop_front();

		void remove_at(int index);

		void clear();

		T at(int index) const;

		int get_size() const;


	};

	template <class T>
	list<T>::Node::Node(T data, Node* pNext, Node* pPrev) : data{ data }, pNext{ pNext }, pPrev{ pPrev } {}

	template <class T>
	list<T>::list() : size{ 0 }, head{ nullptr } {}

	template <class T>
	list<T>::list(const list& other)
	{
		for (int i = 0; i < other.size; i++)
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
			this->size++;
		}
	}

	template <class T>
	list<T>& list<T>::operator = (const list& other)
	{
		this->clear();

		for (int i = 0; i < other.size; i++)
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
			this->size++;
		}
		return *this;
	}

	template <class T>
	list<T>::list(list&& other)
	{
		this->head = other.head;
		this->size = other.size;
		other.size = 0;
		other.head = nullptr;
	}

	template <class T>
	list<T>& list<T>::operator = (list&& other)
	{
		this->clear();
		this->head = other.head;
		this->size = other.size;
		other.size = 0;
		other.head = nullptr;
		return *this;
	}

	template <class T>
	list<T>::~list()
	{
		clear();
	}

	template <class T>
	void list<T>::push_back(T data)
	{
		if (head == nullptr)
		{
			head = new Node(data);
		}
		else
		{
			Node* curr = head;

			while (curr->pNext != nullptr)
			{
				curr = curr->pNext;
			}
			curr->pNext = new Node(data);
		}
		size++;
	}

	template <class T>
	void list<T>::push_front(T data)
	{
		head = new Node(data, head);
		size++;
	}

	template <class T>
	void list<T>::insert(T data, int index)
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

			size++;
		}
	}

	template <class T>
	void list<T>::pop_back()
	{
		remove_at(size - 1);
	}

	template <class T>
	void list<T>::pop_front()
	{
		Node* temp = head;

		head = head->pNext;
		delete temp;
		size--;
	}

	template <class T>
	void list<T>::remove_at(int index)
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

			size--;
		}
	}

	template <class T>
	void list<T>::clear()
	{
		while (size)
			pop_front();
	}

	template <class T>
	T list<T>::at(const int index) const
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
	int list<T>::get_size() const
	{
		return size;
	}

}
