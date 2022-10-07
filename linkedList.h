template <typename T>
class LinkedList{
public:
    LinkedList(){
        Node * nil = new Node();

        m_nil = nil;
        m_head = m_nil;
    }

    void insertFirst(T data);
    void insertLast(T data);
    void insertAfter(T prevData, T data);

    void pop(T data);

    void print();
private:

    struct Node{
        Node(){};
        Node(T d) : data(d){};

        T data;
        Node * next;
        Node * prev;
    };

    Node * m_nil;
    Node * m_head;
    Node * m_tail;

    bool isNil(Node * n){ return n == m_nil; }
    void find(Node **& prevNode, T prevData);
};