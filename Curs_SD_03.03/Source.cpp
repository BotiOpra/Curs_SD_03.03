#include <iostream>
#include <string>

// forward-list

struct List
{
	struct Node
	{
		int key;
		Node* next_node;
		Node* previous_node;

		Node() {}

		Node(int key, Node* next_node = nullptr, Node* previous_node = nullptr)
		{
			this->key = key;
			this->next_node = next_node;
			this->previous_node = previous_node;
		}
	};

private:
	Node* first_node = nullptr, * last_node = nullptr;
	int m_size = 0;

public:
	int size()
	{
		return this->m_size;
	}

	void push_front(int value)
	{
		Node* newNode = new Node(value);
		if (!this->m_size)
		{
			this->first_node = newNode;
			this->last_node = this->first_node;
		}
		else
		{
			newNode->next_node = this->first_node;
			this->first_node->previous_node = newNode;
			this->first_node = newNode;
		}
		m_size++;
	}

	void push_back(int value)
	{
		Node* newNode = new Node(value);
		if (!this->m_size)
		{
			this->last_node = newNode;
			this->first_node = this->last_node;
		}
		else
		{
			this->last_node->next_node = newNode;
			newNode->previous_node = this->last_node;
			this->last_node = newNode;
		}
		m_size++;
	}

	void pop_front()
	{
		if (!this->m_size)
		{
			std::cout << "List already empty!\n";
			exit(-1);
		}
		Node* newFirst = this->first_node->next_node;
		if (newFirst)
			newFirst->previous_node = nullptr;
		delete this->first_node;
		this->first_node = newFirst;

		m_size--;
	}

	void pop_back()
	{

		if (this->m_size == 0)
		{
			std::cout << "List already empty!\n";
			exit(-1);
		}
		Node* newLast = this->last_node->previous_node;
		if (!newLast) {
			first_node = last_node = nullptr;
			delete this->last_node;
		}
		else {
			newLast->next_node = nullptr;
			delete last_node;
			this->last_node = newLast;
		}
		m_size--;
	}

	void erase(Node* nod)
	{
		if (this->first_node == nod)
		{
			this->pop_front();
			return;
		}
		if (this->last_node == nod)
		{
			this->pop_back();
			return;
		}
		nod->previous_node->next_node = nod->next_node;
		nod->next_node->previous_node = nod->previous_node;
		delete nod;
		m_size--;
	}

	void remove(int key)
	{
		Node* nodeCur = first_node;
		while (nodeCur != nullptr)
		{
			Node* tempNode = nodeCur->next_node;
			if (nodeCur->key == key) {
				erase(nodeCur);
			}
			nodeCur = tempNode;
		}
	}

	Node* find(int key)
	{
		Node* iterator;
		for (iterator = this->first_node; iterator != nullptr && iterator->key != key; iterator = iterator->next_node);
		return iterator;
	}

	bool empty()
	{
		return m_size == 0;
	}

	void insert(Node* nod, int val)
	{
		Node* newNode = new Node(val, nod, nod->previous_node);
		nod->previous_node->next_node = newNode;
		nod->previous_node = newNode;
		m_size++;
	}

	void clear()
	{
		Node* nodeCur = first_node;
		while (nodeCur) {
			Node* tempNode = nodeCur->next_node;
			erase(nodeCur);
			nodeCur = tempNode;
		}
	}

	void print()
	{
		for (Node* iterator = this->first_node; iterator != nullptr; iterator = iterator->next_node)
		{
			std::cout << iterator->key << ' ';
		}
		std::cout << std::endl;
	}
	friend bool compare(List L1, List L2);
	friend bool palindrom(List L);
};

bool compare(List L1, List L2)
{
	if (L1.size() != L2.size()) return false;
	List::Node* curNode_first, * curNode_second;
	for (curNode_first = L1.first_node, curNode_second = L2.first_node; curNode_first != nullptr; curNode_first = curNode_first->next_node, curNode_second = curNode_second->next_node) {
		if (curNode_first->key != curNode_second->key)
			return false;
	}
	return true;
}

bool palindrom(List L)
{
	List::Node* forwardIt = L.first_node, * reverseIt = L.last_node;
	for (; forwardIt != nullptr && reverseIt != nullptr; forwardIt = forwardIt->next_node, reverseIt = reverseIt->previous_node) {
		if (forwardIt->key != reverseIt->key)
			return false;
	}
	return true;
}

inline void main_menu(List list)
{
	system("cls");
	list.print();
	std::cout << "--------------------------------------------------------------------------------------------------\n";
	std::cout << "1 - push_front(key) --> Adauga un nod nou la inceputul listei" << std::endl;
	std::cout << "2 - push_back(key) --> Adauga un nod nou la sfarsitul listei" << std::endl;
	std::cout << "3 - pop_front() --> Sterge primul nod al listei" << std::endl;
	std::cout << "4 - pop_back() --> Sterge ultimul nod al listei" << std::endl;
	std::cout << "5 - find(key) --> Cauta adresa unui nod din lista" << std::endl;
	std::cout << "6 - erase(Node* nod) --> Sterge un nod din lista (fara cautare)" << std::endl;
	std::cout << "7 - remove(key) --> Sterge un nod lista (implica cautare)" << std::endl;
	std::cout << "8 - insert(Node* nod, key) --> Inserarea unui nod nou cu campul \"key\" inaintea nodului \"nod\"" << std::endl;
	std::cout << "9 - empty() --> Verifica daca lista e vida" << std::endl;
	std::cout << "10 - clear() --> Goleste lista" << std::endl;
	std::cout << "11 - size() --> Returneaza marimea listei" << std::endl;
	std::cout << "12 - palindrom(List L) --> Verifica daca lista e palindrom" << std::endl;
	std::cout << "13 - compare(List L1, List L2) --> Verifica daca listele L1 si L2 sunt egale" << std::endl;
	std::cout << "-1 - Terminare program" << std::endl;
	std::cout << "--------------------------------------------------------------------------------------------------\n";
}

inline void PressEnter()
{
	std::cout << "Press enter to continue...";
	std::cin.ignore(256, '\n');
	std::cin.get();
}

inline void input_handler(List& list, int input)
{
	int key;
	List newList;
	switch (input) {
	case 1:
		std::cout << "> ";
		std::cin >> key;
		list.push_front(key);
		std::cout << "Node added\n";
		PressEnter();
		break;
	case 2:
		std::cout << "> ";
		std::cin >> key;
		list.push_back(key);
		std::cout << "Node added\n";
		PressEnter();
		break;
	case 3:
		list.pop_front();
		std::cout << "Node removed\n";
		PressEnter();
		break;
	case 4:
		list.pop_back();
		std::cout << "Node removed\n";
		PressEnter();
		break;
	case 5:
		std::cout << "> ";
		std::cin >> key;
		if (!list.find(key))
			std::cout << "Node not found\n";
		else
			std::cout << "Node found at address " << list.find(key) << std::endl;
		PressEnter();
		break;
	case 6:
		void* address;
		std::cout << "> ";
		std::cin >> address;
		list.erase((struct List::Node*)address);
		std::cout << "Node erased\n";
		PressEnter();
		break;
	case 7:
		std::cout << "> ";
		std::cin >> key;
		list.remove(key);
		std::cout << "Node removed\n";
		PressEnter();
		break;
	case 8:
		void* node_address;
		int key;
		std::cout << "> ";
		std::cin >> node_address >> key;
		list.insert((struct List::Node*)node_address, key);
		std::cout << "Node with key " << key << "inserted before Node with address " << node_address << '\n';
		PressEnter();
		break;
	case 9:
		switch (list.empty()) {
		case true:
			std::cout << "List is empty\n";
			break;
		case false:
			std::cout << "List is not empty\n";
			break;
		}
		PressEnter();
		break;
	case 10:
		list.clear();
		std::cout << "List cleared\n";
		PressEnter();
		break;
	case 11:
		std::cout << "Number of elements is " << list.size() << '\n';
		PressEnter();
		break;
	case 12:
		switch (palindrom(list))
		{
		case true:
			std::cout << "Elements of list form a palindrome\n";
			break;
		case false:
			std::cout << "Elements of list do not form a palindrome\n";
			break;
		}
		PressEnter();
		break;
	case 13:
	{
		std::cout << "Enter elements of new list\n";
		int list_input = -1;
		char c;
		std::cout << "> ";
		while (true) {
			std::cin >> list_input;
			newList.push_back(list_input);
			std::cin.get(c);
			if (c == '\n') break;
		}
		switch (compare(list, newList)) {
		case true:
			std::cout << "The two lists are identical\n";
			break;
		case false:
			std::cout << "The two lists are not identical\n";
			break;
		}
		newList.clear();
		std::cout << "Press enter to continue...";
		std::cin.get();
		break;
	}
	case -1:
		std::cout << "Program terminated successfully\n";
		exit(0);
	default:
		if (!isdigit(input)) {
			std::cout << "Fatal error: Input is not of type int\n";
			exit(-1);
		}
		std::cout << "Incorrect input\nPlease re-enter input!\n";
		PressEnter();
	}
}

inline void event_handler(List list)
{
	int input;
	do {
		main_menu(list);
		std::cout << "> ";
		std::cin >> input;
		input_handler(list, input);
	} while (true);
}

int main()
{
	List newList;
	event_handler(newList);



	return 0;
}
