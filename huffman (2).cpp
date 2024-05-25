// haffman.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
using namespace std;
struct Node {
	char data;
	int freq;
	Node* left;
	Node* right;
	Node(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}   
};

// создаем компаратор, чтобы поменять порядок в очереди с убывания на возрастание
struct Compare {
	bool operator()(const Node* a, const Node* b) {
		return a->freq > b->freq;
	}
};


// функция для создания родительских узлов

Node* createParentNode(Node* left, Node* right) {
	int sumFreq = left->freq + right->freq;
	Node* parent = new Node('\0', sumFreq);
	parent->left = left;
	parent->right = right;
	return parent;
} 

Node* buildHuffmanTree(unordered_map<char, int> freq) {     // строим дерево
	priority_queue<Node*, vector<Node*>, Compare> pq;

	// Создание листьев для каждого символа с указанием частоты
	for (auto pair : freq) {
		Node* leaf = new Node(pair.first, pair.second);
		pq.push(leaf);
	}

	// Построение дерева Хаффмана путем объединения узлов с наименьшей частотой
	while (pq.size() > 1) {
		Node* left = pq.top();
		pq.pop();
		Node* right = pq.top();
		pq.pop();

		Node* parent = createParentNode(left, right);
		pq.push(parent);
	}
	if (!pq.empty()) {
		return pq.top();
	}
	else {
		return nullptr;
	}
	
}

void encode(Node* root, string str, unordered_map<char, string>& huffmanCode) {         
	if (root == nullptr) {
		return;
	}

	if (!root->left && !root->right) {
		huffmanCode[root->data] = str;
		return;
	}
	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}


int main()
{
	ifstream file("TextFile1.txt");
	unordered_map<char, int> freq;
	Node* root;
	if (!file.is_open()) {
		cout << "!" << endl;
		return 0;
	}

	char c;
	while (file.get(c)) {
		if (freq.find(c) == freq.end()) {
			freq[c] = 1;
		}
		else {
			freq[c]++;
		}
		cout << freq[c] << ' ' << c << endl;
	}

	file.close();
    root = buildHuffmanTree(freq);
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "shifr:"<<endl;
	for (auto pair : huffmanCode) {
		cout << pair.first << " : " << pair.second << endl;
	}

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
